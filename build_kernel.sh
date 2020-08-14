#!/bin/bash
################################################################################
#
#  build_kernel.sh
#
#  Copyright (c) 2016-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
################################################################################

################################################################################
#
#  I N P U T
#
################################################################################
# Folder for platform tarball.
PLATFORM_TARBALL="${1}"

# Target directory for output artifacts.
TARGET_DIR="${2}"

################################################################################
#
#  V A R I A B L E S
#
################################################################################

# Retrieve the directory where the script is currently held
SCRIPT_BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Configuration file for the build.
CONFIG_FILE="${SCRIPT_BASE_DIR}/build_kernel_config.sh"

# Workspace directory & relevant temp folders.
WORKSPACE_DIR="$(mktemp -d)"

PLATFORM_EXTRACT_DIR="${WORKSPACE_DIR}/src"
WORKSPACE_OUT_DIR="${WORKSPACE_DIR}/out"

for d in "${PLATFORM_EXTRACT_DIR}" "$WORKSPACE_OUT_DIR"
do
    mkdir -p "${d}"
done

# Remove workspace directory upon completion.
trap "rm -rf $WORKSPACE_DIR" EXIT

PARALLEL_EXECUTION="-j8"

function usage {
    echo "Usage: ${BASH_SOURCE[0]} path_to_platform_tar output_folder" 1>&2
    exit 1
}

function validate_input_params {
    if [[ ! -f "${PLATFORM_TARBALL}" ]]
    then
        echo "ERROR: Platform tarball not found."
        usage
    fi

    if [[ ! -f "${CONFIG_FILE}" ]]
    then
        echo "ERROR: Could not find config file ${CONFIG_FILE}. Please check" \
             "that you have extracted the build script properly and try again."
        usage
    fi
}

function validate_cross_compiler {
    if [[ -z "${CROSS_COMPILER_PATH}" ]]
    then
        echo "ERROR: CROSS_COMPILER_PATH not set correctly"
        usage
    fi
}

function display_config {
    echo "-------------------------------------------------------------------------"
    echo "SOURCE TARBALL: ${PLATFORM_TARBALL}"
    echo "TARGET DIRECTORY: ${TARGET_DIR}"
    echo "KERNEL SUBPATH: ${KERNEL_SUBPATH}"
    echo "DEFINITION CONFIG: ${DEFCONFIG_NAME}"
    echo "TARGET ARCHITECTURE: ${TARGET_ARCH}"
    echo "TOOLCHAIN PREFIX: ${TOOLCHAIN_PREFIX}"
    echo "-------------------------------------------------------------------------"
    echo "Sleeping 3 seconds before continuing."
    sleep 3
}

function setup_output_dir {
    if [[ -d "${TARGET_DIR}" ]]
    then
        FILECOUNT=$(find "${TARGET_DIR}" -type f | wc -l)
        if [[ ${FILECOUNT} -gt 0 ]]
        then
            echo "ERROR: Destination folder is not empty. Refusing to build" \
                 "to a non-clean target"
            exit 3
        fi
    else
        echo "Making target directory ${TARGET_DIR}"
        mkdir -p "${TARGET_DIR}"

        if [[ $? -ne 0 ]]
        then
            echo "ERROR: Could not make target directory ${TARGET_DIR}"
            exit 1
        fi
    fi
}

function extract_tarball {
    echo "Extracting tarball to ${PLATFORM_EXTRACT_DIR}"
    tar xf "${PLATFORM_TARBALL}" -C ${PLATFORM_EXTRACT_DIR}
}

function exec_build_kernel {
    CCOMPILE="${CROSS_COMPILER_PATH}/bin/${TOOLCHAIN_PREFIX}"

    if [[ -n "${KERNEL_SUBPATH}" ]]
    then
        MAKE_ARGS="-C ${KERNEL_SUBPATH}"
    fi

    MAKE_ARGS="${MAKE_ARGS} O=${WORKSPACE_OUT_DIR} ARCH=${TARGET_ARCH} CROSS_COMPILE=${CCOMPILE}"
    echo "Base make args: ${MAKE_ARGS}"
    
    # Move into the build base folder.
    pushd "${PLATFORM_EXTRACT_DIR}"

    echo "Make defconfig: make ${MAKE_ARGS} ${DEFCONFIG_NAME}"
    make ${MAKE_ARGS} ${DEFCONFIG_NAME}

    echo "Running full make"
    make ${MAKE_ARGS} ${PARALLEL_EXECUTION}

    if [[ $? -ne 0 ]]
    then
        echo "Build failed"
        exit 10
    fi

    popd
}

function copy_to_output {
    echo "Copying files to output"

    pushd "${WORKSPACE_OUT_DIR}"
    find "./arch/"${TARGET_ARCH}"/boot" -type f | sed 's/^\.\///' | while read CPFILE
    do
        local BASEDIR="$(dirname "${CPFILE}")"
        if [[ ! -d "${TARGET_DIR}/${BASEDIR}" ]]
        then
            mkdir -p "${TARGET_DIR}/${BASEDIR}"
        fi
        cp -v "${CPFILE}" "${TARGET_DIR}/${CPFILE}"
    done
    popd
}

################################################################################
#
#  M A I N
#
################################################################################

# Phase 1: Set up execution
validate_input_params

source "${CONFIG_FILE}"

validate_cross_compiler

setup_output_dir
TARGET_DIR="$(cd "${TARGET_DIR}" && pwd)"
display_config

# Phase 2: Set up environment
extract_tarball

# Phase 3: build
exec_build_kernel

# Phase 4: move to output
copy_to_output
