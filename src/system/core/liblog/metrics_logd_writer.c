/*
 * metrics_logd_writer.c
 *
 * Copyright (c) 2016 Amazon.com, Inc. or its affiliates.  All rights reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * Use is subject to license terms.
 */
// fosmod_fireos_logd newfile
#include <stdarg.h>
#include <string.h>
#include <log/log.h>

#define LOG_BUF_SIZE 1024
#define AMAZON_TAG_METRICS "metrics."

static const char *METRICS_PRIO_NAMES[METRICS_PRIORITY_MAX] = {
    [METRICS_PRIORITY_HIGH] = "HI",
    [METRICS_PRIORITY_NORMAL] = "NR",
    [METRICS_PRIORITY_COUNTER] = "CT",
    [METRICS_PRIORITY_TIMER] = "TI",
    [METRICS_PRIORITY_DISCRETE] = "DV",
};

__attribute__((visibility("default"))) const char *metrics_log_prio_to_name(metrics_prio_t mprio) {
    if (mprio >= METRICS_PRIORITY_MAX) {
        mprio = METRICS_PRIORITY_NORMAL;
    }
    return METRICS_PRIO_NAMES[mprio];
}

__attribute__((visibility("default"))) metrics_prio_t metrics_prio_name_to_metrics_prio(const char *mprioName) {
    const char *b;
    int ret;

    if (!mprioName) {
        return -1;
    }
    b = strrchr(mprioName, '/');
    if (!b) {
        b = mprioName;
    } else {
        ++b;
    }

    for (ret = METRICS_PRIORITY_MIN; ret < METRICS_PRIORITY_MAX; ret++) {
        const char *l = METRICS_PRIO_NAMES[ret];
        if (l && !strcmp(b, l)) {
            return ret;
        }
    }
    return -1;
}

__attribute__((visibility("default"))) int __metrics_log_print(int prio, const char *tag, int mpriority, const char *domain, const char *source, const char *fmt, ...)
{
    va_list ap;
    char datapoints[LOG_BUF_SIZE];
    const char *mprio = metrics_log_prio_to_name(mpriority);

    va_start(ap, fmt);
    vsnprintf(datapoints, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);

    char mtag[LOG_BUF_SIZE];
    snprintf(mtag, LOG_BUF_SIZE, "%s%s", AMAZON_TAG_METRICS, tag);

    char msg[LOG_BUF_SIZE];
    snprintf(msg, LOG_BUF_SIZE, "%s:%s:%s:%s", domain, source, datapoints, mprio);

    return __android_log_buf_write(LOG_ID_METRICS, prio, mtag, msg);
}

__attribute__((visibility("default"))) int __vitals_log_print(const char *tag, const char *program, const char *source, const char *key,
    double cv, const char *unit, const char *metadata, vitals_type type, int is_counter)
{
    char msg[LOG_BUF_SIZE];
    char metadata_msg[LOG_BUF_SIZE];

    if (metadata != NULL && strlen(metadata)) {
        snprintf(metadata_msg, LOG_BUF_SIZE, ",metadata=%s;DV;1", metadata);
    } else {
        metadata_msg[0] = '\0';
    }

    if (key != NULL) {
        snprintf(msg, LOG_BUF_SIZE, "%s:%s:type=%d;DV;1,key=%s;DV;1,%s=%f;%s;1,unit=%s;DV;1%s:HI",
            program, source, type, key,
            is_counter ? "Counter" : "Timer", cv, is_counter ? "CT" : "TI", unit, metadata_msg);
    } else {
        snprintf(msg, LOG_BUF_SIZE, "%s:%s:type=%d;DV;1,%s=%f;%s;1,unit=%s;DV;1%s:HI",
            program, source, type,
            is_counter ? "Counter" : "Timer", cv, is_counter ? "CT" : "TI", unit, metadata_msg);
    }
    return __android_log_buf_write(LOG_ID_VITALS, ANDROID_LOG_INFO, tag, msg);
}

__attribute__((visibility("default"))) int __vitals_log_ext_print(const char *tag, const char *program, const char *source, const char *key,
        double cv, const char *unit, const char *metadata, const vitals_extended_data *ext_data, vitals_type type, int is_counter)
{
    char metadata_msg[LOG_BUF_SIZE];
    char ext_msg[LOG_BUF_SIZE];
    size_t ext_count = 0;
    size_t count_keys = 0;

    if (ext_data == NULL
            || ((ext_data->ext_size[VITALS_EXT_DIMENSION] == 0) && (ext_data->ext_size[VITALS_EXT_META] == 0))) {
        // vital log print
        return __vitals_log_print(tag, program, source, key, cv, unit, metadata, type, is_counter);
    }

    if (ext_data->ext_size[VITALS_EXT_DIMENSION] != 0) {
       ext_count += snprintf(ext_msg, LOG_BUF_SIZE, "\"d\"#{");
       for(count_keys = 0; count_keys < ext_data->ext_size[VITALS_EXT_DIMENSION]; count_keys++) {
           ext_count += snprintf(&ext_msg[ext_count], (LOG_BUF_SIZE - ext_count), "\"%s\"#\"%s\"$", ext_data->ext_type[VITALS_EXT_DIMENSION].keypair[count_keys].key,
                   ext_data->ext_type[VITALS_EXT_DIMENSION].keypair[count_keys].val);
       }
       // delete count-1 to remove extra "$" in the end to replace with a '}'
       ext_msg[ext_count-1] = '}';
    }

    if (ext_data->ext_size[VITALS_EXT_META] != 0) {
        ext_count += snprintf(&ext_msg[ext_count], (LOG_BUF_SIZE - ext_count), "%s\"m\"#{", ext_data->ext_size[VITALS_EXT_DIMENSION]?"$":"");
        for(count_keys = 0; count_keys < ext_data->ext_size[VITALS_EXT_META]; count_keys++) {
            ext_count += snprintf(&ext_msg[ext_count], (LOG_BUF_SIZE - ext_count), "\"%s\"#\"%s\"$", ext_data->ext_type[VITALS_EXT_META].keypair[count_keys].key,
                    ext_data->ext_type[VITALS_EXT_META].keypair[count_keys].val);
        }
        // delete count-1 to remove extra "$" in the end
        ext_msg[ext_count-1] = '}';
    }

    if (metadata != NULL && strlen(metadata)) {
        snprintf(metadata_msg, LOG_BUF_SIZE, "%s!{%s}", metadata, ext_msg);
    } else {
        snprintf(metadata_msg, LOG_BUF_SIZE, "!{%s}", ext_msg);
    }

    return __vitals_log_print(tag, program, source, key, cv, unit, metadata_msg, type, is_counter);
}

__attribute__((visibility("default"))) void __vitals_log_ext_set_data(vitals_extended_data *ext_data, const char *key, const char *val, vitals_ext_data_type type)
{
    size_t size;
    size_t size_per_metric_field[VITALS_EXT_MAX]={MAX_VITALS_DIMENSION_KEY_VALUE_PAIRS, MAX_VITALS_METADATA_KEY_VALUE_PAIRS};
    if (ext_data && (ext_data->ext_size[type] < size_per_metric_field[type])) {
        size = ext_data->ext_size[type];
        if (key && val) {
            strncpy(ext_data->ext_type[type].keypair[size].key, key, MAX_VITALS_DATA_SIZE);
            ext_data->ext_type[type].keypair[size].key[MAX_VITALS_DATA_SIZE] = '\0';
            strncpy(ext_data->ext_type[type].keypair[size].val, val, MAX_VITALS_DATA_SIZE);
            ext_data->ext_type[type].keypair[size].val[MAX_VITALS_DATA_SIZE] = '\0';
            ext_data->ext_size[type]++;
        }
    }
}
