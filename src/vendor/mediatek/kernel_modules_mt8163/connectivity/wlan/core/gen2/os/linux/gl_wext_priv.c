// SPDX-License-Identifier: GPL-2.0

/*

 * Copyright (c) 2019 MediaTek Inc.

 */

/*
** Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V2_3/os/linux/gl_wext_priv.c#4
*/

/*! \file gl_wext_priv.c
    \brief This file includes private ioctl support.
*/

/*
** Log: gl_wext_priv.c
 *
 * 07 17 2012 yuche.tsai
 * NULL
 * Let netdev bring up.
 *
 * 06 13 2012 yuche.tsai
 * NULL
 * Update maintrunk driver.
 * Add support for driver compose assoc request frame.
 *
 * 03 20 2012 wh.su
 * [WCXRP00001153] [MT6620 Wi-Fi][Driver] Adding the get_ch_list and set_tx_power proto type function
 * [WCXRP00001202] [MT6628 Wi-Fi][FW] Adding the New PN init code
 * use return to avoid the ioctl return not supported
 *
 * 03 02 2012 terry.wu
 * NULL
 * Snc CFG80211 modification for ICS migration from branch 2.2.
 *
 * 01 16 2012 wh.su
 * [WCXRP00001170] [MT6620 Wi-Fi][Driver] Adding the related code for set/get band ioctl
 * Adding the template code for set / get band IOCTL (with ICS supplicant_6)..
 *
 * 01 05 2012 wh.su
 * [WCXRP00001153] [MT6620 Wi-Fi][Driver] Adding the get_ch_list and set_tx_power proto type function
 * Adding the related ioctl / wlan oid function to set the Tx power cfg.
 *
 * 01 02 2012 wh.su
 * [WCXRP00001153] [MT6620 Wi-Fi][Driver] Adding the get_ch_list and set_tx_power proto type function
 * Adding the proto type function for set_int set_tx_power and get int get_ch_list.
 *
 * 11 02 2011 chinghwa.yu
 * [WCXRP00000063] Update BCM CoEx design and settings
 * Fixed typo.
 *
 * 09 20 2011 chinglan.wang
 * [WCXRP00000989] [WiFi Direct] [Driver] Add a new io control API to start the formation for the sigma test.
 * .
 *
 * 07 28 2011 chinghwa.yu
 * [WCXRP00000063] Update BCM CoEx design and settings
 * Add BWCS cmd and event.
 *
 * 07 18 2011 chinghwa.yu
 * [WCXRP00000063] Update BCM CoEx design and settings[WCXRP00000612] [MT6620 Wi-Fi] [FW] CSD update SWRDD algorithm
 * Add CMD/Event for RDD and BWCS.
 *
 * 03 17 2011 chinglan.wang
 * [WCXRP00000570] [MT6620 Wi-Fi][Driver] Add Wi-Fi Protected Setup v2.0 feature
 * .
 *
 * 03 07 2011 terry.wu
 * [WCXRP00000521] [MT6620 Wi-Fi][Driver] Remove non-standard debug message
 * Toggle non-standard debug messages to comments.
 *
 * 01 27 2011 cm.chang
 * [WCXRP00000402] [MT6620 Wi-Fi][Driver] Enable MCR read/write by iwpriv by default
 * .
 *
 * 01 26 2011 wh.su
 * [WCXRP00000396] [MT6620 Wi-Fi][Driver] Support Sw Ctrl ioctl at linux
 * adding the SW cmd ioctl support, use set/get structure ioctl.
 *
 * 01 20 2011 eddie.chen
 * [WCXRP00000374] [MT6620 Wi-Fi][DRV] SW debug control
 * Adjust OID order.
 *
 * 01 20 2011 eddie.chen
 * [WCXRP00000374] [MT6620 Wi-Fi][DRV] SW debug control
 * Add Oid for sw control debug command
 *
 * 01 07 2011 cm.chang
 * [WCXRP00000336] [MT6620 Wi-Fi][Driver] Add test mode commands in normal phone operation
 * Add a new compiling option to control if MCR read/write is permitted
 *
 * 12 31 2010 cm.chang
 * [WCXRP00000336] [MT6620 Wi-Fi][Driver] Add test mode commands in normal phone operation
 * Add some iwpriv commands to support test mode operation
 *
 * 12 15 2010 george.huang
 * [WCXRP00000152] [MT6620 Wi-Fi] AP mode power saving function
 * Support set PS profile and set WMM-PS related iwpriv.
 *
 * 11 08 2010 wh.su
 * [WCXRP00000171] [MT6620 Wi-Fi][Driver] Add message check code same behavior as mt5921
 * add the message check code from mt5921.
 *
 * 10 18 2010 cp.wu
 * [WCXRP00000056] [MT6620 Wi-Fi][Driver] NVRAM implementation with Version Check
 * [WCXRP00000086] [MT6620 Wi-Fi][Driver] The mac address is all zero at android
 * complete implementation of Android NVRAM access
 *
 * 09 24 2010 cp.wu
 * [WCXRP00000056] [MT6620 Wi-Fi][Driver] NVRAM implementation with Version Check
 * correct typo for NVRAM access.
 *
 * 09 23 2010 cp.wu
 * [WCXRP00000056] [MT6620 Wi-Fi][Driver] NVRAM implementation with Version Check
 * add skeleton for NVRAM integration
 *
 * 08 04 2010 cp.wu
 * NULL
 * revert changelist #15371, efuse read/write access will be done by RF test approach
 *
 * 08 04 2010 cp.wu
 * NULL
 * add OID definitions for EFUSE read/write access.
 *
 * 07 08 2010 cp.wu
 *
 * [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
 *
 * 06 06 2010 kevin.huang
 * [WPD00003832][MT6620 5931] Create driver base
 * [MT6620 5931] Create driver base
 *
 * 06 01 2010 cp.wu
 * [WPD00001943]Create WiFi test driver framework on WinXP
 * enable OID_CUSTOM_MTK_WIFI_TEST for RFTest & META tool
 *
 * 05 29 2010 jeffrey.chang
 * [WPD00003826]Initial import for Linux port
 * fix private ioctl for rftest
 *
 * 04 21 2010 jeffrey.chang
 * [WPD00003826]Initial import for Linux port
 * add for private ioctl support
**  \main\maintrunk.MT5921\32 2009-10-08 10:33:25 GMT mtk01090
**  Avoid accessing private data of net_device directly. Replace with netdev_priv(). Add more checking for input
**  parameters and pointers.
**  \main\maintrunk.MT5921\31 2009-09-29 16:46:21 GMT mtk01090
**  Remove unused functions
**  \main\maintrunk.MT5921\30 2009-09-29 14:46:47 GMT mtk01090
**  Fix compile warning
**  \main\maintrunk.MT5921\29 2009-09-29 14:28:48 GMT mtk01090
**  Fix compile warning
**  \main\maintrunk.MT5921\28 2009-09-28 22:21:38 GMT mtk01090
**  Refine lines to suppress compile warning
**  \main\maintrunk.MT5921\27 2009-09-28 20:19:14 GMT mtk01090
**  Add private ioctl to carry OID structures. Restructure public/private ioctl interfaces to Linux kernel.
**  \main\maintrunk.MT5921\26 2009-08-18 22:56:53 GMT mtk01090
**  Add Linux SDIO (with mmc core) support.
**  Add Linux 2.6.21, 2.6.25, 2.6.26.
**  Fix compile warning in Linux.
**  \main\maintrunk.MT5921\25 2009-05-07 22:26:15 GMT mtk01089
**  Add mandatory and private IO control for Linux BWCS
**  \main\maintrunk.MT5921\24 2009-04-29 10:07:05 GMT mtk01088
**  fixed the compiling error at linux
**  \main\maintrunk.MT5921\23 2009-04-24 09:09:45 GMT mtk01088
**  mark the code not used at linux supplicant v0.6.7
**  \main\maintrunk.MT5921\22 2008-11-24 21:03:51 GMT mtk01425
**  1. Add PTA_ENABLED flag
**  \main\maintrunk.MT5921\21 2008-08-29 14:55:59 GMT mtk01088
**  adjust the code for meet the coding style, and add assert check
**  \main\maintrunk.MT5921\20 2008-07-16 15:23:20 GMT mtk01104
**  Support GPIO2 mode
**  \main\maintrunk.MT5921\19 2008-07-15 17:43:11 GMT mtk01084
**  modify variable name
**  \main\maintrunk.MT5921\18 2008-07-14 14:37:58 GMT mtk01104
**  Add exception handle about length in function priv_set_struct()
**  \main\maintrunk.MT5921\17 2008-07-14 13:55:32 GMT mtk01104
**  Support PRIV_CMD_BT_COEXIST
**  \main\maintrunk.MT5921\16 2008-07-09 00:20:15 GMT mtk01461
**  Add priv oid to support WMM_PS_TEST
**  \main\maintrunk.MT5921\15 2008-06-02 11:15:22 GMT mtk01461
**  Update after wlanoidSetPowerMode changed
**  \main\maintrunk.MT5921\14 2008-05-30 19:31:07 GMT mtk01461
**  Add IOCTL for Power Mode
**  \main\maintrunk.MT5921\13 2008-05-30 18:57:15 GMT mtk01461
**  Not use wlanoidSetCSUMOffloadForLinux()
**  \main\maintrunk.MT5921\12 2008-05-30 15:13:18 GMT mtk01084
**  rename wlanoid
**  \main\maintrunk.MT5921\11 2008-05-29 14:16:31 GMT mtk01084
**  rename for wlanoidSetBeaconIntervalForLinux
**  \main\maintrunk.MT5921\10 2008-04-17 23:06:37 GMT mtk01461
**  Add iwpriv support for AdHocMode setting
**  \main\maintrunk.MT5921\9 2008-03-31 21:00:55 GMT mtk01461
**  Add priv IOCTL for VOIP setting
**  \main\maintrunk.MT5921\8 2008-03-31 13:49:43 GMT mtk01461
**  Add priv ioctl to turn on / off roaming
**  \main\maintrunk.MT5921\7 2008-03-26 15:35:14 GMT mtk01461
**  Add CSUM offload priv ioctl for Linux
**  \main\maintrunk.MT5921\6 2008-03-11 14:50:59 GMT mtk01461
**  Unify priv ioctl
**  \main\maintrunk.MT5921\5 2007-11-06 19:32:30 GMT mtk01088
**  add WPS code
**  \main\maintrunk.MT5921\4 2007-10-30 12:01:39 GMT MTK01425
**  1. Update wlanQueryInformation and wlanSetInformation
*/

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"

#include "gl_os.h"
#include "gl_wext_priv.h"
#if CFG_SUPPORT_WAPI
#include "gl_sec.h"
#endif
#if CFG_ENABLE_WIFI_DIRECT
#include "gl_p2p_os.h"
#endif

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define NUM_SUPPORTED_OIDS      (sizeof(arWlanOidReqTable) / sizeof(WLAN_REQ_ENTRY))
#define CMD_START			"START"
#define CMD_STOP			"STOP"
#define CMD_SCAN_ACTIVE			"SCAN-ACTIVE"
#define CMD_SCAN_PASSIVE		"SCAN-PASSIVE"
#define CMD_RSSI			"RSSI"
#define CMD_LINKSPEED			"LINKSPEED"
#define CMD_RXFILTER_START		"RXFILTER-START"
#define CMD_RXFILTER_STOP		"RXFILTER-STOP"
#define CMD_RXFILTER_ADD		"RXFILTER-ADD"
#define CMD_RXFILTER_REMOVE		"RXFILTER-REMOVE"
#define CMD_BTCOEXSCAN_START		"BTCOEXSCAN-START"
#define CMD_BTCOEXSCAN_STOP		"BTCOEXSCAN-STOP"
#define CMD_BTCOEXMODE			"BTCOEXMODE"
#define CMD_SETSUSPENDOPT		"SETSUSPENDOPT"
#define CMD_SETSUSPENDMODE		"SETSUSPENDMODE"
#define CMD_P2P_DEV_ADDR		"P2P_DEV_ADDR"
#define CMD_SETFWPATH			"SETFWPATH"
#define CMD_SETBAND			"SETBAND"
#define CMD_GETBAND			"GETBAND"
#define CMD_COUNTRY			"COUNTRY"
#define CMD_P2P_SET_NOA			"P2P_SET_NOA"
#define CMD_P2P_GET_NOA			"P2P_GET_NOA"
#define CMD_P2P_SET_PS			"P2P_SET_PS"
#define CMD_SET_AP_WPS_P2P_IE		"SET_AP_WPS_P2P_IE"
#define CMD_SETROAMMODE			"SETROAMMODE"
#define CMD_MIRACAST			"MIRACAST"

#define CMD_PNOSSIDCLR_SET	"PNOSSIDCLR"
#define CMD_PNOSETUP_SET	"PNOSETUP "
#define CMD_PNOENABLE_SET	"PNOFORCE"
#define CMD_PNODEBUG_SET	"PNODEBUG"
#define CMD_WLS_BATCHING	"WLS_BATCHING"

#define CMD_OKC_SET_PMK		"SET_PMK"
#define CMD_OKC_ENABLE		"OKC_ENABLE"

/* miracast related definition */
#define MIRACAST_MODE_OFF	0
#define MIRACAST_MODE_SOURCE	1
#define MIRACAST_MODE_SINK	2

#ifndef MIRACAST_AMPDU_SIZE
#define MIRACAST_AMPDU_SIZE	8
#endif

#ifndef MIRACAST_MCHAN_ALGO
#define MIRACAST_MCHAN_ALGO     1
#endif

#ifndef MIRACAST_MCHAN_BW
#define MIRACAST_MCHAN_BW       25
#endif

#define	CMD_BAND_AUTO	0
#define	CMD_BAND_5G		1
#define	CMD_BAND_2G		2
#define	CMD_BAND_ALL	3

/* Mediatek private command */

#define CMD_SET_SW_CTRL	        "SET_SW_CTRL"
#define CMD_GET_SW_CTRL         "GET_SW_CTRL"
#define CMD_SET_CFG             "SET_CFG"
#define CMD_GET_CFG             "GET_CFG"
#define CMD_SET_CHIP            "SET_CHIP"
#define CMD_GET_CHIP            "GET_CHIP"
#define CMD_SET_DBG_LEVEL       "SET_DBG_LEVEL"
#define CMD_GET_DBG_LEVEL       "GET_DBG_LEVEL"

#define CMD_GET_1XTX_STATUS     "GET_1XTX_STATUS"
#define CMD_TEST_1XTX_STATUS    "TEST_1XTX_STATUS"


static UINT_32 g_ucMiracastMode = MIRACAST_MODE_OFF;

#define PRIV_CMD_SIZE 512

typedef struct cmd_tlv {
	char prefix;
	char version;
	char subver;
	char reserved;
} cmd_tlv_t;

typedef struct priv_driver_cmd_s {
	char buf[PRIV_CMD_SIZE];
	int used_len;
	int total_len;
} priv_driver_cmd_t;

#if CFG_SUPPORT_BATCH_SCAN
#define CMD_BATCH_SET           "WLS_BATCHING SET"
#define CMD_BATCH_GET           "WLS_BATCHING GET"
#define CMD_BATCH_STOP          "WLS_BATCHING STOP"
#endif

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

static int
priv_get_ndis(IN struct net_device *prNetDev, IN NDIS_TRANSPORT_STRUCT * prNdisReq, OUT PUINT_32 pu4OutputLen);

static int
priv_set_ndis(IN struct net_device *prNetDev, IN NDIS_TRANSPORT_STRUCT * prNdisReq, OUT PUINT_32 pu4OutputLen);

#if 0				/* CFG_SUPPORT_WPS */
static int
priv_set_appie(IN struct net_device *prNetDev,
	       IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, OUT char *pcExtra);

static int
priv_set_filter(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, OUT char *pcExtra);
#endif /* CFG_SUPPORT_WPS */

static BOOLEAN reqSearchSupportedOidEntry(IN UINT_32 rOid, OUT P_WLAN_REQ_ENTRY * ppWlanReqEntry);

#if 0
static WLAN_STATUS
reqExtQueryConfiguration(IN P_GLUE_INFO_T prGlueInfo,
			 OUT PVOID pvQueryBuffer, IN UINT_32 u4QueryBufferLen, OUT PUINT_32 pu4QueryInfoLen);

static WLAN_STATUS
reqExtSetConfiguration(IN P_GLUE_INFO_T prGlueInfo,
		       IN PVOID pvSetBuffer, IN UINT_32 u4SetBufferLen, OUT PUINT_32 pu4SetInfoLen);
#endif

static WLAN_STATUS
reqExtSetAcpiDevicePowerState(IN P_GLUE_INFO_T prGlueInfo,
			      IN PVOID pvSetBuffer, IN UINT_32 u4SetBufferLen, OUT PUINT_32 pu4SetInfoLen);

/*******************************************************************************
*                       P R I V A T E   D A T A
********************************************************************************
*/
static UINT_8 aucOidBuf[OID_BUF_SIZE] = { 0 };

/* OID processing table */
/* Order is important here because the OIDs should be in order of
   increasing value for binary searching. */
static WLAN_REQ_ENTRY arWlanOidReqTable[] = {
	/*
	   {(NDIS_OID)rOid,
	   (PUINT_8)pucOidName,
	   fgQryBufLenChecking, fgSetBufLenChecking, fgIsHandleInGlueLayerOnly, u4InfoBufLen,
	   pfOidQueryHandler,
	   pfOidSetHandler}
	 */
	/* General Operational Characteristics */

	/* Ethernet Operational Characteristics */
	{OID_802_3_CURRENT_ADDRESS,
	 DISP_STRING("OID_802_3_CURRENT_ADDRESS"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, 6,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryCurrentAddr,
	 NULL},

	/* OID_802_3_MULTICAST_LIST */
	/* OID_802_3_MAXIMUM_LIST_SIZE */
	/* Ethernet Statistics */

	{OID_802_11_RSSI,
	 DISP_STRING("OID_802_11_RSSI"),
	 TRUE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(int),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryRssi,
	 NULL}
	,

	/* NDIS 802.11 Wireless LAN OIDs */
	{OID_802_11_SUPPORTED_RATES,
	 DISP_STRING("OID_802_11_SUPPORTED_RATES"),
	 TRUE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_RATES_EX),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQuerySupportedRates,
	 NULL}
	,
	/*
	   {OID_802_11_CONFIGURATION,
	   DISP_STRING("OID_802_11_CONFIGURATION"),
	   TRUE, TRUE, ENUM_OID_GLUE_EXTENSION, sizeof(PARAM_802_11_CONFIG_T),
	   (PFN_OID_HANDLER_FUNC_REQ)reqExtQueryConfiguration,
	   (PFN_OID_HANDLER_FUNC_REQ)reqExtSetConfiguration},
	 */
	{OID_PNP_SET_POWER,
	 DISP_STRING("OID_PNP_SET_POWER"),
	 TRUE, FALSE, ENUM_OID_GLUE_EXTENSION, sizeof(PARAM_DEVICE_POWER_STATE),
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) reqExtSetAcpiDevicePowerState}
	,

	/* Custom OIDs */
	{OID_CUSTOM_OID_INTERFACE_VERSION,
	 DISP_STRING("OID_CUSTOM_OID_INTERFACE_VERSION"),
	 TRUE, FALSE, ENUM_OID_DRIVER_CORE, 4,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryOidInterfaceVersion,
	 NULL}
	,

	/*
	   #if PTA_ENABLED
	   {OID_CUSTOM_BT_COEXIST_CTRL,
	   DISP_STRING("OID_CUSTOM_BT_COEXIST_CTRL"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_BT_COEXIST_T),
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetBtCoexistCtrl},
	   #endif
	 */

	/*
	   {OID_CUSTOM_POWER_MANAGEMENT_PROFILE,
	   DISP_STRING("OID_CUSTOM_POWER_MANAGEMENT_PROFILE"),
	   FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryPwrMgmtProfParam,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetPwrMgmtProfParam},
	   {OID_CUSTOM_PATTERN_CONFIG,
	   DISP_STRING("OID_CUSTOM_PATTERN_CONFIG"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_PATTERN_SEARCH_CONFIG_STRUCT_T),
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetPatternConfig},
	   {OID_CUSTOM_BG_SSID_SEARCH_CONFIG,
	   DISP_STRING("OID_CUSTOM_BG_SSID_SEARCH_CONFIG"),
	   FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetBgSsidParam},
	   {OID_CUSTOM_VOIP_SETUP,
	   DISP_STRING("OID_CUSTOM_VOIP_SETUP"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryVoipConnectionStatus,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetVoipConnectionStatus},
	   {OID_CUSTOM_ADD_TS,
	   DISP_STRING("OID_CUSTOM_ADD_TS"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidAddTS},
	   {OID_CUSTOM_DEL_TS,
	   DISP_STRING("OID_CUSTOM_DEL_TS"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidDelTS},
	 */

	/*
	   #if CFG_LP_PATTERN_SEARCH_SLT
	   {OID_CUSTOM_SLT,
	   DISP_STRING("OID_CUSTOM_SLT"),
	   FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQuerySltResult,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetSltMode},
	   #endif

	   {OID_CUSTOM_ROAMING_EN,
	   DISP_STRING("OID_CUSTOM_ROAMING_EN"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryRoamingFunction,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetRoamingFunction},
	   {OID_CUSTOM_WMM_PS_TEST,
	   DISP_STRING("OID_CUSTOM_WMM_PS_TEST"),
	   TRUE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetWiFiWmmPsTest},
	   {OID_CUSTOM_COUNTRY_STRING,
	   DISP_STRING("OID_CUSTOM_COUNTRY_STRING"),
	   FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryCurrentCountry,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetCurrentCountry},

	   #if CFG_SUPPORT_802_11D
	   {OID_CUSTOM_MULTI_DOMAIN_CAPABILITY,
	   DISP_STRING("OID_CUSTOM_MULTI_DOMAIN_CAPABILITY"),
	   FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryMultiDomainCap,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetMultiDomainCap},
	   #endif

	   {OID_CUSTOM_GPIO2_MODE,
	   DISP_STRING("OID_CUSTOM_GPIO2_MODE"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(ENUM_PARAM_GPIO2_MODE_T),
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetGPIO2Mode},
	   {OID_CUSTOM_CONTINUOUS_POLL,
	   DISP_STRING("OID_CUSTOM_CONTINUOUS_POLL"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CONTINUOUS_POLL_T),
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryContinuousPollInterval,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetContinuousPollProfile},
	   {OID_CUSTOM_DISABLE_BEACON_DETECTION,
	   DISP_STRING("OID_CUSTOM_DISABLE_BEACON_DETECTION"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryDisableBeaconDetectionFunc,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetDisableBeaconDetectionFunc},
	 */

	/* WPS */
	/*
	   {OID_CUSTOM_DISABLE_PRIVACY_CHECK,
	   DISP_STRING("OID_CUSTOM_DISABLE_PRIVACY_CHECK"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	   NULL,
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidSetDisablePriavcyCheck},
	 */

	{OID_CUSTOM_MCR_RW,
	 DISP_STRING("OID_CUSTOM_MCR_RW"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_MCR_RW_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryMcrRead,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetMcrWrite}
	,

	{OID_CUSTOM_EEPROM_RW,
	 DISP_STRING("OID_CUSTOM_EEPROM_RW"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_EEPROM_RW_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryEepromRead,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetEepromWrite}
	,

	{OID_CUSTOM_SW_CTRL,
	 DISP_STRING("OID_CUSTOM_SW_CTRL"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_SW_CTRL_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQuerySwCtrlRead,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetSwCtrlWrite}
	,

	{OID_CUSTOM_MEM_DUMP,
	 DISP_STRING("OID_CUSTOM_MEM_DUMP"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_MEM_DUMP_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryMemDump,
	 NULL}
	,

#ifdef CONFIG_MTK_WIFI_ANTENNA_SELECT
	{OID_CUSTOM_ANT_SELECT,
	 DISP_STRING("OID_CUSTOM_ANT_SELECT"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE,
	 sizeof(struct antenna_select_param),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_get_antenna_rssi,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_set_antenna_rssi}
	,

	{OID_CUSTOM_ANT_SELECT_SWITCH,
	 DISP_STRING("OID_CUSTOM_ANT_SELECT_SWITCH"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE,
	 sizeof(struct antenna_select_param),
	 (PFN_OID_HANDLER_FUNC_REQ) NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_set_antenna_switch}
	,

	{OID_CUSTOM_ANT_SELECT_CONN_CONFIG,
	 DISP_STRING("OID_CUSTOM_ANT_SELECT_CONN_CONFIG"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE,
	 sizeof(struct antenna_select_config),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_get_antenna_config,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_update_antenna_config}
	,

	{OID_CUSTOM_ANT_SELECT_MOVING_AVG,
	 DISP_STRING("OID_CUSTOM_ANT_SELECT_MOVING_AVG"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE,
	 sizeof(unsigned char),
	 (PFN_OID_HANDLER_FUNC_REQ) NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoid_set_antenna_moving_avg_mode}
	,
#endif
	{OID_CUSTOM_TEST_MODE,
	 DISP_STRING("OID_CUSTOM_TEST_MODE"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidRftestSetTestMode}
	,

	/*
	   {OID_CUSTOM_TEST_RX_STATUS,
	   DISP_STRING("OID_CUSTOM_TEST_RX_STATUS"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_RFTEST_RX_STATUS_STRUCT_T),
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryRfTestRxStatus,
	   NULL},
	   {OID_CUSTOM_TEST_TX_STATUS,
	   DISP_STRING("OID_CUSTOM_TEST_TX_STATUS"),
	   FALSE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_RFTEST_TX_STATUS_STRUCT_T),
	   (PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryRfTestTxStatus,
	   NULL},
	 */
	{OID_CUSTOM_ABORT_TEST_MODE,
	 DISP_STRING("OID_CUSTOM_ABORT_TEST_MODE"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidRftestSetAbortTestMode}
	,
	{OID_CUSTOM_MTK_WIFI_TEST,
	 DISP_STRING("OID_CUSTOM_MTK_WIFI_TEST"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_MTK_WIFI_TEST_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidRftestQueryAutoTest,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidRftestSetAutoTest}
	,

	/* OID_CUSTOM_EMULATION_VERSION_CONTROL */

	/* BWCS */
#if CFG_SUPPORT_BCM && CFG_SUPPORT_BCM_BWCS
	{OID_CUSTOM_BWCS_CMD,
	 DISP_STRING("OID_CUSTOM_BWCS_CMD"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(PTA_IPC_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryBT,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetBT}
	,
#endif

/*    {OID_CUSTOM_SINGLE_ANTENNA,
	DISP_STRING("OID_CUSTOM_SINGLE_ANTENNA"),
	FALSE, FALSE, ENUM_OID_DRIVER_CORE, 4,
	(PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryBtSingleAntenna,
	(PFN_OID_HANDLER_FUNC_REQ)wlanoidSetBtSingleAntenna},
    {OID_CUSTOM_SET_PTA,
	DISP_STRING("OID_CUSTOM_SET_PTA"),
	FALSE, FALSE, ENUM_OID_DRIVER_CORE, 4,
	(PFN_OID_HANDLER_FUNC_REQ)wlanoidQueryPta,
	(PFN_OID_HANDLER_FUNC_REQ)wlanoidSetPta},
    */

	{OID_CUSTOM_MTK_NVRAM_RW,
	 DISP_STRING("OID_CUSTOM_MTK_NVRAM_RW"),
	 TRUE, TRUE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_CUSTOM_NVRAM_RW_STRUCT_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryNvramRead,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetNvramWrite}
	,

	{OID_CUSTOM_CFG_SRC_TYPE,
	 DISP_STRING("OID_CUSTOM_CFG_SRC_TYPE"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(ENUM_CFG_SRC_TYPE_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryCfgSrcType,
	 NULL}
	,

	{OID_CUSTOM_EEPROM_TYPE,
	 DISP_STRING("OID_CUSTOM_EEPROM_TYPE"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(ENUM_EEPROM_TYPE_T),
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidQueryEepromType,
	 NULL}
	,

	{OID_CUSTOM_SET_RESETCOUNTER,
	 DISP_STRING("OID_CUSTOM_SET_RESETCOUNTER"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetResetCounter}
	,

#if CFG_SUPPORT_WAPI
	{OID_802_11_WAPI_MODE,
	 DISP_STRING("OID_802_11_WAPI_MODE"),
	 FALSE, TRUE, ENUM_OID_DRIVER_CORE, 4,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetWapiMode}
	,
	{OID_802_11_WAPI_ASSOC_INFO,
	 DISP_STRING("OID_802_11_WAPI_ASSOC_INFO"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetWapiAssocInfo}
	,
	{OID_802_11_SET_WAPI_KEY,
	 DISP_STRING("OID_802_11_SET_WAPI_KEY"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, sizeof(PARAM_WPI_KEY_T),
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetWapiKey}
	,
#endif

#if CFG_SUPPORT_WPS2
	{OID_802_11_WSC_ASSOC_INFO,
	 DISP_STRING("OID_802_11_WSC_ASSOC_INFO"),
	 FALSE, FALSE, ENUM_OID_DRIVER_CORE, 0,
	 NULL,
	 (PFN_OID_HANDLER_FUNC_REQ) wlanoidSetWSCAssocInfo}
	,
#endif
};

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/*----------------------------------------------------------------------------*/
/*!
* \brief Dispatching function for private ioctl region (SIOCIWFIRSTPRIV ~
*   SIOCIWLASTPRIV).
*
* \param[in] prNetDev Net device requested.
* \param[in] prIfReq Pointer to ifreq structure.
* \param[in] i4Cmd Command ID between SIOCIWFIRSTPRIV and SIOCIWLASTPRIV.
*
* \retval 0 for success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EFAULT For fail.
*
*/
/*----------------------------------------------------------------------------*/
int priv_support_ioctl(IN struct net_device *prNetDev, IN OUT struct ifreq *prIfReq, IN int i4Cmd)
{
	/* prIfReq is verified in the caller function wlanDoIOCTL() */
	struct iwreq *prIwReq = (struct iwreq *)prIfReq;
	struct iw_request_info rIwReqInfo;

	/* prDev is verified in the caller function wlanDoIOCTL() */

	/* Prepare the call */
	rIwReqInfo.cmd = (__u16) i4Cmd;
	rIwReqInfo.flags = 0;

	switch (i4Cmd) {
	case IOCTL_SET_INT:
		/* NOTE(Kevin): 1/3 INT Type <= IFNAMSIZ, so we don't need copy_from/to_user() */
		return priv_set_int(prNetDev, &rIwReqInfo, &(prIwReq->u), (char *)&(prIwReq->u));

	case IOCTL_GET_INT:
		/* NOTE(Kevin): 1/3 INT Type <= IFNAMSIZ, so we don't need copy_from/to_user() */
		return priv_get_int(prNetDev, &rIwReqInfo, &(prIwReq->u), (char *)&(prIwReq->u));

	case IOCTL_SET_STRUCT:
	case IOCTL_SET_STRUCT_FOR_EM:
		return priv_set_struct(prNetDev, &rIwReqInfo, &prIwReq->u, (char *)&(prIwReq->u));

	case IOCTL_GET_STRUCT:
		return priv_get_struct(prNetDev, &rIwReqInfo, &prIwReq->u, (char *)&(prIwReq->u));

	default:
		return -EOPNOTSUPP;

	}			/* end of switch */

}				/* priv_support_ioctl */

#if CFG_SUPPORT_BATCH_SCAN

EVENT_BATCH_RESULT_T g_rEventBatchResult[CFG_BATCH_MAX_MSCAN];

UINT_32 batchChannelNum2Freq(UINT_32 u4ChannelNum)
{
	UINT_32 u4ChannelInMHz;

	if (u4ChannelNum >= 1 && u4ChannelNum <= 13)
		u4ChannelInMHz = 2412 + (u4ChannelNum - 1) * 5;
	else if (u4ChannelNum == 14)
		u4ChannelInMHz = 2484;
	else if (u4ChannelNum == 133)
		u4ChannelInMHz = 3665;	/* 802.11y */
	else if (u4ChannelNum == 137)
		u4ChannelInMHz = 3685;	/* 802.11y */
	else if (u4ChannelNum >= 34 && u4ChannelNum <= 165)
		u4ChannelInMHz = 5000 + u4ChannelNum * 5;
	else if (u4ChannelNum >= 183 && u4ChannelNum <= 196)
		u4ChannelInMHz = 4000 + u4ChannelNum * 5;
	else
		u4ChannelInMHz = 0;

	return u4ChannelInMHz;
}

#define TMP_TEXT_LEN_S 40
#define TMP_TEXT_LEN_L 60
static UCHAR text1[TMP_TEXT_LEN_S], text2[TMP_TEXT_LEN_L], text3[TMP_TEXT_LEN_L];	/* A safe len */

WLAN_STATUS
batchConvertResult(IN P_EVENT_BATCH_RESULT_T prEventBatchResult,
		   OUT PVOID pvBuffer, IN UINT_32 u4MaxBufferLen, OUT PUINT_32 pu4RetLen)
{
	CHAR *p = pvBuffer;
	CHAR ssid[ELEM_MAX_LEN_SSID + 1];
	INT_32 nsize = 0, nsize1, nsize2, nsize3, scancount;
	INT_32 i, j, nleft;
	UINT_32 freq;

	P_EVENT_BATCH_RESULT_ENTRY_T prEntry;
	P_EVENT_BATCH_RESULT_T pBr;

	nleft = u4MaxBufferLen - 5;	/* -5 for "----\n" */

	pBr = prEventBatchResult;
	scancount = 0;
	for (j = 0; j < CFG_BATCH_MAX_MSCAN; j++) {
		scancount += pBr->ucScanCount;
		pBr++;
	}

	nsize1 = kalSnprintf(text1, TMP_TEXT_LEN_S, "scancount=%x\nnextcount=%x\n", scancount, scancount);
	if (nsize1 < nleft) {
		p += nsize1 = kalSprintf(p, "%s", text1);
		nleft -= nsize1;
	} else
		goto short_buf;

	pBr = prEventBatchResult;
	for (j = 0; j < CFG_BATCH_MAX_MSCAN; j++) {
		DBGLOG(SCN, TRACE, "convert mscan = %d, apcount=%d, nleft=%d\n", j, pBr->ucScanCount, nleft);

		if (pBr->ucScanCount == 0) {
			pBr++;
			continue;
		}

		nleft -= 5;	/* -5 for "####\n" */

		/* We only support one round scan result now. */
		nsize1 = kalSnprintf(text1, TMP_TEXT_LEN_S, "apcount=%d\n", pBr->ucScanCount);
		if (nsize1 < nleft) {
			p += nsize1 = kalSprintf(p, "%s", text1);
			nleft -= nsize1;
		} else
			goto short_buf;

		for (i = 0; i < pBr->ucScanCount; i++) {
			prEntry = &pBr->arBatchResult[i];

			nsize1 = kalSnprintf(text1, TMP_TEXT_LEN_S, "bssid=" MACSTR "\n",
					     prEntry->aucBssid[0],
					     prEntry->aucBssid[1],
					     prEntry->aucBssid[2],
					     prEntry->aucBssid[3],
					     prEntry->aucBssid[4], prEntry->aucBssid[5]);

			kalMemCopy(ssid,
				   prEntry->aucSSID,
				   (prEntry->ucSSIDLen < ELEM_MAX_LEN_SSID ? prEntry->ucSSIDLen : ELEM_MAX_LEN_SSID));
			ssid[(prEntry->ucSSIDLen <
			      (ELEM_MAX_LEN_SSID - 1) ? prEntry->ucSSIDLen : (ELEM_MAX_LEN_SSID - 1))] = '\0';
			nsize2 = kalSnprintf(text2, TMP_TEXT_LEN_L, "ssid=%s\n", ssid);

			freq = batchChannelNum2Freq(prEntry->ucFreq);
			nsize3 =
			    kalSnprintf(text3, TMP_TEXT_LEN_L,
					"freq=%u\nlevel=%d\ndist=%u\ndistSd=%u\n====\n", freq,
					prEntry->cRssi, prEntry->u4Dist, prEntry->u4Distsd);

			nsize = nsize1 + nsize2 + nsize3;
			if (nsize < nleft) {

				kalStrnCpy(p, text1, TMP_TEXT_LEN_S);
				p += nsize1;

				kalStrnCpy(p, text2, TMP_TEXT_LEN_L);
				p += nsize2;

				kalStrnCpy(p, text3, TMP_TEXT_LEN_L);
				p += nsize3;

				nleft -= nsize;
			} else {
				DBGLOG(SCN, TRACE, "Warning: Early break! (%d)\n", i);
				break;	/* discard following entries, TODO: apcount? */
			}
		}

		nsize1 = kalSnprintf(text1, TMP_TEXT_LEN_S, "%s", "####\n");
		p += kalSprintf(p, "%s", text1);

		pBr++;
	}

	nsize1 = kalSnprintf(text1, TMP_TEXT_LEN_S, "%s", "----\n");
	kalSprintf(p, "%s", text1);

	*pu4RetLen = u4MaxBufferLen - nleft;
	DBGLOG(SCN, TRACE, "total len = %d (max len = %d)\n", *pu4RetLen, u4MaxBufferLen);

	return WLAN_STATUS_SUCCESS;

short_buf:
	DBGLOG(SCN, TRACE,
	       "Short buffer issue! %d > %d, %s\n", u4MaxBufferLen + (nsize - nleft),
		u4MaxBufferLen, (char *)pvBuffer);
	return WLAN_STATUS_INVALID_LENGTH;
}
#endif

#if CFG_SUPPORT_GET_CH_ENV
WLAN_STATUS
scanEnvResult(P_GLUE_INFO_T prGlueInfo, OUT PVOID pvBuffer, IN UINT_32 u4MaxBufferLen, OUT PUINT_32 pu4RetLen)
{
	P_ADAPTER_T prAdapter = NULL;
	CHAR *p = pvBuffer;
	INT_32 nsize;
	INT_32 i, nleft;
	P_SCAN_INFO_T prScanInfo;
	P_LINK_T prBSSDescList;
	P_BSS_DESC_T prBssDesc;
	CH_ENV_T chEnvInfo[54];	/* 54: from FW define; TODO: sync MAXIMUM_OPERATION_CHANNEL_LIST */
	UINT_32 i4GetCh = 0;
	INT_32 i4Argc = 0;
	PCHAR apcArgv[WLAN_CFG_ARGV_MAX] = { 0 };
	UINT_8 ucTextLen = 40;
	UCHAR text[ucTextLen];
	INT_32 u4Ret;

	prAdapter = prGlueInfo->prAdapter;
	prScanInfo = &(prAdapter->rWifiVar.rScanInfo);
	prBSSDescList = &prScanInfo->rBSSDescList;

	kalMemZero(chEnvInfo, sizeof(chEnvInfo));

	DBGLOG(SCN, TRACE, "pvBuffer:%s, pu4RetLen:%d\n", (char *)pvBuffer, *pu4RetLen);

	wlanCfgParseArgument(pvBuffer, &i4Argc, apcArgv);
	DBGLOG(REQ, LOUD, "argc is %i\n", i4Argc);

	if (i4Argc >= 2) {
		u4Ret = kalkStrtou32(apcArgv[1], 0, &i4GetCh);
		if (u4Ret)
			DBGLOG(SCN, TRACE, "parse pvBuffer error u4Ret=%d\n", u4Ret);
		/* i4GetCh = kalStrtoul(apcArgv[1], NULL, 0); */
	}

	nleft = u4MaxBufferLen - 5;	/* -5 for "----\n" */

	nsize = kalSnprintf(text, ucTextLen, "%s", "scanEnvResult\nResult:1\n");/* Always return 1 for alpha version. */

	if (nsize < nleft) {
		p += nsize = kalSnprintf(p, ucTextLen, "%s", text);
		nleft -= nsize;
	} else
		goto short_buf;

	/* Search BSS Desc from current SCAN result list. */
	LINK_FOR_EACH_ENTRY(prBssDesc, prBSSDescList, rLinkEntry, BSS_DESC_T) {
		if (prBssDesc->ucChannelNum > 0) {
			if (prBssDesc->ucChannelNum <= 14) {	/* 1~14 */
				chEnvInfo[prBssDesc->ucChannelNum - 1].ucChNum = prBssDesc->ucChannelNum;
				chEnvInfo[prBssDesc->ucChannelNum - 1].ucApNum++;
			} else if (prBssDesc->ucChannelNum <= 64) {	/* 15~22 */
				chEnvInfo[prBssDesc->ucChannelNum / 4 + 5].ucChNum = prBssDesc->ucChannelNum;
				chEnvInfo[prBssDesc->ucChannelNum / 4 + 5].ucApNum++;
			} else if (prBssDesc->ucChannelNum <= 116) {	/* 23~27 */
				chEnvInfo[prBssDesc->ucChannelNum / 4 - 3].ucChNum = prBssDesc->ucChannelNum;
				chEnvInfo[prBssDesc->ucChannelNum / 4 - 3].ucApNum++;
			} else if (prBssDesc->ucChannelNum <= 140) {	/* 28~30 */
				chEnvInfo[prBssDesc->ucChannelNum / 4 - 6].ucChNum = prBssDesc->ucChannelNum;
				chEnvInfo[prBssDesc->ucChannelNum / 4 - 6].ucApNum++;
			} else if (prBssDesc->ucChannelNum <= 165) {	/* 31~35 */
				chEnvInfo[(prBssDesc->ucChannelNum - 1) / 4 - 7].ucChNum = prBssDesc->ucChannelNum;
				chEnvInfo[(prBssDesc->ucChannelNum - 1) / 4 - 7].ucApNum++;
			}
		}
	}

	for (i = 0; i < 54; i++) {
		if (chEnvInfo[i].ucChNum != 0) {
			if (i4GetCh == 0 || (chEnvInfo[i].ucChNum == (UINT_8)i4GetCh)) {
				DBGLOG(SCN, TRACE, "chNum=%d,apNum=%d\n", chEnvInfo[i].ucChNum, chEnvInfo[i].ucApNum);
				p += nsize =
				    kalSnprintf(p, ucTextLen, "chNum=%d,apNum=%d\n", chEnvInfo[i].ucChNum,
						chEnvInfo[i].ucApNum);
				nleft -= nsize;
			}
		}
	}

	p += nsize = kalSnprintf(p, ucTextLen, "%s", "----\n");
	nleft -= nsize;

	*pu4RetLen = u4MaxBufferLen - nleft;
	DBGLOG(SCN, TRACE, "total len = %d (max len = %d)\n", *pu4RetLen, u4MaxBufferLen);

	return WLAN_STATUS_SUCCESS;

short_buf:
	DBGLOG(SCN, TRACE, "Short buffer issue! %d > %d, %s\n", u4MaxBufferLen + (nsize - nleft), u4MaxBufferLen, p);
	return WLAN_STATUS_INVALID_LENGTH;
}
#endif


static int
getLastRxRate(IN struct net_device *prNetDev,
	     OUT UINT_32 *pLastRxRate)
{
	PUINT_32 pu4IntBuf;
	UINT_32 u4BufLen = 0;
	int status = 0;
	P_NDIS_TRANSPORT_STRUCT prNdisReq;

	ASSERT(prNetDev);

	prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

	pu4IntBuf = (PUINT_32) &prNdisReq->ndisOidContent[0];
	pu4IntBuf[0] = 0xa0220000;
	pu4IntBuf[1] = 0;

	prNdisReq->ndisOidCmd = OID_CUSTOM_SW_CTRL;
	prNdisReq->inNdisOidlength = 8;
	prNdisReq->outNdisOidLength = 8;

	status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
	if (status == 0) {
		*pLastRxRate = *(PUINT_32) &prNdisReq->ndisOidContent[4];
	}
	return status;
}
/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl set int handler.
*
* \param[in] prNetDev Net device requested.
* \param[in] prIwReqInfo Pointer to iwreq structure.
* \param[in] prIwReqData The ioctl data structure, use the field of sub-command.
* \param[in] pcExtra The buffer with input value
*
* \retval 0 For success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EINVAL If a value is out of range.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_set_int(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	UINT_32 u4SubCmd;
	PUINT_32 pu4IntBuf;
	P_NDIS_TRANSPORT_STRUCT prNdisReq;
	P_GLUE_INFO_T prGlueInfo;
	UINT_32 u4BufLen = 0;
	int status = 0;
	P_PTA_IPC_T prPtaIpc;
	unsigned char dtim_skip_count = 0;

	ASSERT(prNetDev);
	ASSERT(prIwReqInfo);
	ASSERT(prIwReqData);
	ASSERT(pcExtra);

	if (FALSE == GLUE_CHK_PR3(prNetDev, prIwReqData, pcExtra))
		return -EINVAL;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	u4SubCmd = (UINT_32) prIwReqData->mode;
	pu4IntBuf = (PUINT_32) pcExtra;

	switch (u4SubCmd) {
	case PRIV_CMD_TEST_MODE:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		if (pu4IntBuf[1] == PRIV_CMD_TEST_MAGIC_KEY) {
			prNdisReq->ndisOidCmd = OID_CUSTOM_TEST_MODE;
		} else if (pu4IntBuf[1] == 0) {
			prNdisReq->ndisOidCmd = OID_CUSTOM_ABORT_TEST_MODE;
		} else {
			status = 0;
			break;
		}
		prNdisReq->inNdisOidlength = 0;
		prNdisReq->outNdisOidLength = 0;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;

	case PRIV_CMD_TEST_CMD:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_MTK_WIFI_TEST;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;

#if CFG_SUPPORT_PRIV_MCR_RW
	case PRIV_CMD_ACCESS_MCR:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		if (!prGlueInfo->fgMcrAccessAllowed) {
			if (pu4IntBuf[1] == PRIV_CMD_TEST_MAGIC_KEY && pu4IntBuf[2] == PRIV_CMD_TEST_MAGIC_KEY)
				prGlueInfo->fgMcrAccessAllowed = TRUE;
			status = 0;
			break;
		}

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_MCR_RW;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;
#endif

	case PRIV_CMD_SW_CTRL:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_SW_CTRL;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;

#if 0
	case PRIV_CMD_BEACON_PERIOD:
		rStatus = wlanSetInformation(prGlueInfo->prAdapter, wlanoidSetBeaconInterval,
					    (PVOID)&pu4IntBuf[1],/* pu4IntBuf[0] is used as input SubCmd */
					     sizeof(UINT_32), &u4BufLen);
		break;
#endif

#if CFG_TCP_IP_CHKSUM_OFFLOAD
	case PRIV_CMD_CSUM_OFFLOAD:
		{
			UINT_32 u4CSUMFlags;

			if (pu4IntBuf[1] == 1)
				u4CSUMFlags = CSUM_OFFLOAD_EN_ALL;
			else if (pu4IntBuf[1] == 0)
				u4CSUMFlags = 0;
			else
				return -EINVAL;

			if (kalIoctl(prGlueInfo,
				     wlanoidSetCSUMOffload,
				     (PVOID)&u4CSUMFlags,
				     sizeof(UINT_32), FALSE, FALSE, TRUE, FALSE, &u4BufLen) == WLAN_STATUS_SUCCESS) {
				if (pu4IntBuf[1] == 1)
					prNetDev->features |= NETIF_F_HW_CSUM;
				else if (pu4IntBuf[1] == 0)
					prNetDev->features &= ~NETIF_F_HW_CSUM;
			}
		}
		break;
#endif /* CFG_TCP_IP_CHKSUM_OFFLOAD */

	case PRIV_CMD_POWER_MODE:
		kalIoctl(prGlueInfo, wlanoidSet802dot11PowerSaveProfile,
			(PVOID)&pu4IntBuf[1],	/* pu4IntBuf[0] is used as input SubCmd */
			 sizeof(UINT_32), FALSE, FALSE, TRUE, FALSE, &u4BufLen);
		break;

	case PRIV_CMD_WMM_PS:
		{
			PARAM_CUSTOM_WMM_PS_TEST_STRUCT_T rWmmPsTest;

			rWmmPsTest.bmfgApsdEnAc = (UINT_8) pu4IntBuf[1];
			rWmmPsTest.ucIsEnterPsAtOnce = (UINT_8) pu4IntBuf[2];
			rWmmPsTest.ucIsDisableUcTrigger = (UINT_8) pu4IntBuf[3];
			rWmmPsTest.reserved = 0;

			kalIoctl(prGlueInfo,
				 wlanoidSetWiFiWmmPsTest,
				 (PVOID)&rWmmPsTest,
				 sizeof(PARAM_CUSTOM_WMM_PS_TEST_STRUCT_T), FALSE, FALSE, TRUE, FALSE, &u4BufLen);
		}
		break;

#if 0
	case PRIV_CMD_ADHOC_MODE:
		rStatus = wlanSetInformation(prGlueInfo->prAdapter, wlanoidSetAdHocMode,
					    (PVOID)&pu4IntBuf[1],	/* pu4IntBuf[0] is used as input SubCmd */
					     sizeof(UINT_32), &u4BufLen);
		break;
#endif

	case PRIV_CUSTOM_BWCS_CMD:

		DBGLOG(REQ, INFO, "pu4IntBuf[1] = %x, size of PTA_IPC_T = %zu.\n",
				   pu4IntBuf[1], sizeof(PARAM_PTA_IPC_T));

		prPtaIpc = (P_PTA_IPC_T) aucOidBuf;
		prPtaIpc->u.aucBTPParams[0] = (UINT_8) (pu4IntBuf[1] >> 24);
		prPtaIpc->u.aucBTPParams[1] = (UINT_8) (pu4IntBuf[1] >> 16);
		prPtaIpc->u.aucBTPParams[2] = (UINT_8) (pu4IntBuf[1] >> 8);
		prPtaIpc->u.aucBTPParams[3] = (UINT_8) (pu4IntBuf[1]);

		DBGLOG(REQ, INFO,
		       "BCM BWCS CMD : BTPParams[0]=%02x, BTPParams[1]=%02x, BTPParams[2]=%02x, BTPParams[3]=%02x.\n",
			prPtaIpc->u.aucBTPParams[0], prPtaIpc->u.aucBTPParams[1], prPtaIpc->u.aucBTPParams[2],
			prPtaIpc->u.aucBTPParams[3]);

#if 0
		status = wlanSetInformation(prGlueInfo->prAdapter,
					    wlanoidSetBT, (PVOID)&aucOidBuf[0], u4CmdLen, &u4BufLen);
#endif

		status = wlanoidSetBT(prGlueInfo->prAdapter,
				      (PVOID)&aucOidBuf[0], sizeof(PARAM_PTA_IPC_T), &u4BufLen);

		if (WLAN_STATUS_SUCCESS != status)
			status = -EFAULT;

		break;

	case PRIV_CMD_BAND_CONFIG:
		{
			DBGLOG(REQ, INFO, "CMD set_band=%u\n", (UINT_32) pu4IntBuf[1]);
		}
		break;

#if CFG_ENABLE_WIFI_DIRECT
	case PRIV_CMD_P2P_MODE:
		{
			/* no use, move to set_p2p_mode_handler() */
			PARAM_CUSTOM_P2P_SET_STRUCT_T p2pmode;

			p2pmode.u4Enable = pu4IntBuf[1];
			p2pmode.u4Mode = pu4IntBuf[2];
			set_p2p_mode_handler(prNetDev, p2pmode);
#if 0
			PARAM_CUSTOM_P2P_SET_STRUCT_T rSetP2P;
			WLAN_STATUS rWlanStatus = WLAN_STATUS_SUCCESS;
			BOOLEAN fgIsP2PEnding;

			GLUE_SPIN_LOCK_DECLARATION();

			/* avoid remove & p2p off command simultaneously */
			GLUE_ACQUIRE_THE_SPIN_LOCK(&g_p2p_lock);
			fgIsP2PEnding = g_u4P2PEnding;
			g_u4P2POnOffing = 1;
			GLUE_RELEASE_THE_SPIN_LOCK(&g_p2p_lock);

			if (fgIsP2PEnding == 1) {
				/* skip the command if we are removing */
				GLUE_ACQUIRE_THE_SPIN_LOCK(&g_p2p_lock);
				g_u4P2POnOffing = 0;
				GLUE_RELEASE_THE_SPIN_LOCK(&g_p2p_lock);
				break;
			}
			rSetP2P.u4Enable = pu4IntBuf[1];
			rSetP2P.u4Mode = pu4IntBuf[2];

			if (!rSetP2P.u4Enable)
				p2pNetUnregister(prGlueInfo, TRUE);

			/* move out to caller to avoid kalIoctrl & suspend/resume deadlock problem ALPS00844864 */
			/*
			   Scenario:
			   1. System enters suspend/resume but not yet enter wlanearlysuspend()
			   or wlanlateresume();

			   2. System switches to do PRIV_CMD_P2P_MODE and execute kalIoctl()
			   and get g_halt_sem then do glRegisterEarlySuspend() or
			   glUnregisterEarlySuspend();

			   But system suspend/resume procedure is not yet finished so we
			   suspend;

			   3. System switches back to do suspend/resume procedure and execute
			   kalIoctl(). But driver does not yet release g_halt_sem so system
			   suspend in wlanearlysuspend() or wlanlateresume();

			   ==> deadlock occurs.
			 */
			if ((!rSetP2P.u4Enable) && (g_u4HaltFlag == 0) && (fgIsResetting == FALSE)) {
				/* fgIsP2PRegistered == TRUE means P2P is enabled */
				DBGLOG(P2P, INFO, "p2pEalySuspendReg\n");
				p2pEalySuspendReg(prGlueInfo, rSetP2P.u4Enable);	/* p2p remove */
			}

			DBGLOG(P2P, INFO,
			       "wlanoidSetP2pMode 0x%p %d %d\n", &rSetP2P, rSetP2P.u4Enable, rSetP2P.u4Mode);
			rWlanStatus = kalIoctl(prGlueInfo, wlanoidSetP2pMode,
					      (PVOID)&rSetP2P,	/* pu4IntBuf[0] is used as input SubCmd */
					       sizeof(PARAM_CUSTOM_P2P_SET_STRUCT_T),
					       FALSE, FALSE, TRUE, FALSE, &u4BufLen);
			DBGLOG(P2P, INFO, "wlanoidSetP2pMode ok\n");

			/* move out to caller to avoid kalIoctrl & suspend/resume deadlock problem ALPS00844864 */
			if ((rSetP2P.u4Enable) && (g_u4HaltFlag == 0) && (fgIsResetting == FALSE)) {
				/* fgIsP2PRegistered == TRUE means P2P on successfully */
				p2pEalySuspendReg(prGlueInfo, rSetP2P.u4Enable);	/* p2p on */
			}

			if (rSetP2P.u4Enable)
				p2pNetRegister(prGlueInfo, TRUE);

			GLUE_ACQUIRE_THE_SPIN_LOCK(&g_p2p_lock);
			g_u4P2POnOffing = 0;
			GLUE_RELEASE_THE_SPIN_LOCK(&g_p2p_lock);
#endif
		}
		break;
#endif

#if (CFG_SUPPORT_MET_PROFILING == 1)
	case PRIV_CMD_MET_PROFILING:
		{
			/* PARAM_CUSTOM_WFD_DEBUG_STRUCT_T rWfdDebugModeInfo; */
			/* rWfdDebugModeInfo.ucWFDDebugMode=(UINT_8)pu4IntBuf[1]; */
			/* rWfdDebugModeInfo.u2SNPeriod=(UINT_16)pu4IntBuf[2]; */
			/* DBGLOG(REQ, INFO,("WFD Debug Mode:%d Period:%d\n",
			rWfdDebugModeInfo.ucWFDDebugMode,rWfdDebugModeInfo.u2SNPeriod)); */
			prGlueInfo->u8MetProfEnable = (UINT_8) pu4IntBuf[1];
			prGlueInfo->u16MetUdpPort = (UINT_16) pu4IntBuf[2];
			DBGLOG(REQ, INFO, "MET_PROF: Enable=%d UDP_PORT=%d\n", prGlueInfo->u8MetProfEnable,
			       prGlueInfo->u16MetUdpPort);

		}
		break;

#endif
	case PRIV_CMD_WFD_DEBUG_CODE:
		{
			PARAM_CUSTOM_WFD_DEBUG_STRUCT_T rWfdDebugModeInfo;

			rWfdDebugModeInfo.ucWFDDebugMode = (UINT_8) pu4IntBuf[1];
			rWfdDebugModeInfo.u2SNPeriod = (UINT_16) pu4IntBuf[2];
			DBGLOG(REQ, INFO, "WFD Debug Mode:%d Period:%d\n", rWfdDebugModeInfo.ucWFDDebugMode,
			       rWfdDebugModeInfo.u2SNPeriod);
			kalIoctl(prGlueInfo, wlanoidSetWfdDebugMode, (PVOID)&rWfdDebugModeInfo,
				 sizeof(PARAM_CUSTOM_WFD_DEBUG_STRUCT_T), FALSE, FALSE, TRUE, FALSE, &u4BufLen);

		}
		break;
#ifdef CONFIG_MTK_WIFI_ANTENNA_SELECT
	case PRIV_CMD_ANT_SELECT:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT)&aucOidBuf[0];

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_ANT_SELECT;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;
#endif

	case PRIV_CMD_SET_RESETCOUNTER:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT)&aucOidBuf[0];

		prNdisReq->ndisOidCmd = OID_CUSTOM_SET_RESETCOUNTER;

		prNdisReq->inNdisOidlength = 0;
		prNdisReq->outNdisOidLength = 0;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;
	case PRIV_CMD_DTIM_SKIP_COUNT:
		dtim_skip_count = (unsigned char)pu4IntBuf[1];
		if (prGlueInfo->prAdapter &&
		    dtim_skip_count >= 0 &&
		    dtim_skip_count <= 6) {
			prGlueInfo->prAdapter->dtim_skip_count =
				dtim_skip_count;
		} else {
			status = -EINVAL;
		}
		break;
	default:
		return -EOPNOTSUPP;
	}

	return status;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl get int handler.
*
* \param[in] pDev Net device requested.
* \param[out] pIwReq Pointer to iwreq structure.
* \param[in] prIwReqData The ioctl req structure, use the field of sub-command.
* \param[out] pcExtra The buffer with put the return value
*
* \retval 0 For success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EFAULT For fail.
*
*/
/*----------------------------------------------------------------------------*/
UINT_8 gucBufDbgCode[1000];

static int
_priv_get_int(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	UINT_32 u4SubCmd;
	PUINT_32 pu4IntBuf;
	P_GLUE_INFO_T prGlueInfo;
	UINT_32 u4BufLen = 0;
	int status = 0;
	P_NDIS_TRANSPORT_STRUCT prNdisReq;
	INT_32 ch[50];

	ASSERT(prNetDev);
	ASSERT(prIwReqInfo);
	ASSERT(prIwReqData);
	ASSERT(pcExtra);
	if (FALSE == GLUE_CHK_PR3(prNetDev, prIwReqData, pcExtra))
		return -EINVAL;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	u4SubCmd = (UINT_32) prIwReqData->mode;
	pu4IntBuf = (PUINT_32) pcExtra;

	switch (u4SubCmd) {
	case PRIV_CMD_TEST_CMD:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_MTK_WIFI_TEST;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0) {
			prIwReqData->mode = *(PUINT_32) &prNdisReq->ndisOidContent[4];
		}
		return status;

#if CFG_SUPPORT_PRIV_MCR_RW
	case PRIV_CMD_ACCESS_MCR:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		if (!prGlueInfo->fgMcrAccessAllowed) {
			status = 0;
			return status;
		}

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_MCR_RW;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0) {
			prIwReqData->mode = *(PUINT_32) &prNdisReq->ndisOidContent[4];
		}
		return status;
#endif

	case PRIV_CMD_DUMP_MEM:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

#if 1
		if (!prGlueInfo->fgMcrAccessAllowed) {
			status = 0;
			return status;
		}
#endif
		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_MEM_DUMP;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0)
			prIwReqData->mode = *(PUINT_32) &prNdisReq->ndisOidContent[0];
		return status;

	case PRIV_CMD_SW_CTRL:

		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		kalMemCopy(&prNdisReq->ndisOidContent[0], &pu4IntBuf[1], 8);

		prNdisReq->ndisOidCmd = OID_CUSTOM_SW_CTRL;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0) {
			prIwReqData->mode = *(PUINT_32) &prNdisReq->ndisOidContent[4];
		}
		return status;

#if 0
	case PRIV_CMD_BEACON_PERIOD:
		status = wlanQueryInformation(prGlueInfo->prAdapter,
					      wlanoidQueryBeaconInterval,
					      (PVOID) pu4IntBuf, sizeof(UINT_32), &u4BufLen);
		return status;

	case PRIV_CMD_POWER_MODE:
		status = wlanQueryInformation(prGlueInfo->prAdapter,
					      wlanoidQuery802dot11PowerSaveProfile,
					      (PVOID) pu4IntBuf, sizeof(UINT_32), &u4BufLen);
		return status;

	case PRIV_CMD_ADHOC_MODE:
		status = wlanQueryInformation(prGlueInfo->prAdapter,
					      wlanoidQueryAdHocMode, (PVOID) pu4IntBuf, sizeof(UINT_32), &u4BufLen);
		return status;
#endif

	case PRIV_CMD_BAND_CONFIG:
		DBGLOG(REQ, INFO, "CMD get_band=\n");
		prIwReqData->mode = 0;
		return status;

#ifdef CONFIG_MTK_WIFI_ANTENNA_SELECT
	case PRIV_CMD_ANT_SELECT:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT)&aucOidBuf[0];

		prNdisReq->ndisOidCmd = OID_CUSTOM_ANT_SELECT;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0) {
			prIwReqData->mode =
				*(int *)&prNdisReq->ndisOidContent[0];
		}
		return status;
#endif

	case PRIV_CMD_SHOW_CHANNEL:
	{
		UINT_32 freq;

		status = wlanQueryInformation(prGlueInfo->prAdapter, wlanoidQueryFrequency,
			&freq, sizeof(UINT_32), &u4BufLen);
		if (status == 0)
			prIwReqData->mode = freq/1000; /* Hz->MHz */

		return status;
	}
	case PRIV_CMD_DTIM_SKIP_COUNT:
		if (prGlueInfo->prAdapter)
			prIwReqData->mode =
				prGlueInfo->prAdapter->dtim_skip_count;
		return status;

	default:
		break;
	}

	u4SubCmd = (UINT_32) prIwReqData->data.flags;

	switch (u4SubCmd) {
	case PRIV_CMD_GET_CH_LIST:
		{
			UINT_16 i, j = 0;
			UINT_8 NumOfChannel = 50;
			UINT_8 ucMaxChannelNum = 50;
			RF_CHANNEL_INFO_T aucChannelList[50];

			kalGetChannelList(prGlueInfo, BAND_NULL, ucMaxChannelNum, &NumOfChannel, aucChannelList);
			if (NumOfChannel > 50)
				NumOfChannel = 50;

			if (kalIsAPmode(prGlueInfo)) {
				for (i = 0; i < NumOfChannel; i++) {
					if ((aucChannelList[i].ucChannelNum <= 13)
						|| (aucChannelList[i].ucChannelNum == 36
						|| aucChannelList[i].ucChannelNum == 40
						|| aucChannelList[i].ucChannelNum == 44
						|| aucChannelList[i].ucChannelNum == 48)) {
							ch[j] = (INT_32) aucChannelList[i].ucChannelNum;
							j++;
					}
				}
			} else {
				for (j = 0; j < NumOfChannel; j++)
					ch[j] = (INT_32) aucChannelList[j].ucChannelNum;
			}

			prIwReqData->data.length = j;
			if (copy_to_user(prIwReqData->data.pointer, ch, NumOfChannel * sizeof(INT_32)))
				return -EFAULT;
			else
				return status;
		}

	case PRIV_CMD_GET_BUILD_DATE_CODE:
		{
			UINT_8 aucBuffer[16];

			if (kalIoctl(prGlueInfo,
				     wlanoidQueryBuildDateCode,
				     (PVOID) aucBuffer,
				     sizeof(UINT_8) * 16, TRUE, TRUE, TRUE, FALSE, &u4BufLen) == WLAN_STATUS_SUCCESS) {
				prIwReqData->data.length = sizeof(UINT_8) * 16;

				if (copy_to_user(prIwReqData->data.pointer, aucBuffer, prIwReqData->data.length))
					return -EFAULT;
				else
					return status;
			} else {
				return -EFAULT;
			}
		}

	case PRIV_CMD_GET_DEBUG_CODE:
		{
			wlanQueryDebugCode(prGlueInfo->prAdapter);

			kalMemSet(gucBufDbgCode, '.', sizeof(gucBufDbgCode));
			if (copy_to_user(prIwReqData->data.pointer,
				gucBufDbgCode, (prIwReqData->data.length
				< sizeof(gucBufDbgCode)
			 ? prIwReqData->data.length:sizeof(gucBufDbgCode))))
				return -EFAULT;
			else
				return status;
		}

	default:
		return -EOPNOTSUPP;
	}

	return status;
}				/* priv_get_int */

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl set int array handler.
*
* \param[in] prNetDev Net device requested.
* \param[in] prIwReqInfo Pointer to iwreq structure.
* \param[in] prIwReqData The ioctl data structure, use the field of sub-command.
* \param[in] pcExtra The buffer with input value
*
* \retval 0 For success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EINVAL If a value is out of range.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_set_ints(IN struct net_device *prNetDev,
	      IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	UINT_32 u4SubCmd, u4BufLen, u4CmdLen;
	P_GLUE_INFO_T prGlueInfo;
	int status = 0;
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	PUINT_32 pu4IntBuf = NULL;
	P_SET_TXPWR_CTRL_T prTxpwr;
#ifdef CONFIG_MTK_WIFI_ANTENNA_SELECT
	P_NDIS_TRANSPORT_STRUCT prNdisReq;
	struct antenna_select_param params;
#endif
	UINT_16 i;
	INT_32 setting[4] = {0};

	ASSERT(prNetDev);
	ASSERT(prIwReqInfo);
	ASSERT(prIwReqData);
	ASSERT(pcExtra);

	if (FALSE == GLUE_CHK_PR3(prNetDev, prIwReqData, pcExtra))
		return -EINVAL;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	u4SubCmd = (UINT_32) prIwReqData->data.flags;
	pu4IntBuf = (PUINT_32) pcExtra;
	u4CmdLen = prIwReqData->data.length;

	switch (u4SubCmd) {
	case PRIV_CMD_SET_TX_POWER:
		{
			if (u4CmdLen > 4)
				return -EINVAL;
			if (copy_from_user(setting, prIwReqData->data.pointer, u4CmdLen))
				return -EFAULT;

			prTxpwr = &prGlueInfo->rTxPwr;
			if (setting[0] == 0 && prIwReqData->data.length == 4 /* argc num */) {
				/* 0 (All networks), 1 (legacy STA), 2 (Hotspot AP), 3 (P2P), 4 (BT over Wi-Fi) */
				if (setting[1] == 1 || setting[1] == 0) {
					if (setting[2] == 0 || setting[2] == 1)
						prTxpwr->c2GLegacyStaPwrOffset = setting[3];
					if (setting[2] == 0 || setting[2] == 2)
						prTxpwr->c5GLegacyStaPwrOffset = setting[3];
				}
				if (setting[1] == 2 || setting[1] == 0) {
					if (setting[2] == 0 || setting[2] == 1)
						prTxpwr->c2GHotspotPwrOffset = setting[3];
					if (setting[2] == 0 || setting[2] == 2)
						prTxpwr->c5GHotspotPwrOffset = setting[3];
				}
				if (setting[1] == 3 || setting[1] == 0) {
					if (setting[2] == 0 || setting[2] == 1)
						prTxpwr->c2GP2pPwrOffset = setting[3];
					if (setting[2] == 0 || setting[2] == 2)
						prTxpwr->c5GP2pPwrOffset = setting[3];
				}
				if (setting[1] == 4 || setting[1] == 0) {
					if (setting[2] == 0 || setting[2] == 1)
						prTxpwr->c2GBowPwrOffset = setting[3];
					if (setting[2] == 0 || setting[2] == 2)
						prTxpwr->c5GBowPwrOffset = setting[3];
				}
			} else if (setting[0] == 1 && prIwReqData->data.length == 2) {
				prTxpwr->ucConcurrencePolicy = setting[1];
			} else if (setting[0] == 2 && prIwReqData->data.length == 3) {
				if (setting[1] == 0) {
					for (i = 0; i < 14; i++)
						prTxpwr->acTxPwrLimit2G[i] = setting[2];
				} else if (setting[1] <= 14)
					prTxpwr->acTxPwrLimit2G[setting[1] - 1] = setting[2];
			} else if (setting[0] == 3 && prIwReqData->data.length == 3) {
				if (setting[1] == 0) {
					for (i = 0; i < 4; i++)
						prTxpwr->acTxPwrLimit5G[i] = setting[2];
				} else if (setting[1] <= 4)
					prTxpwr->acTxPwrLimit5G[setting[1] - 1] = setting[2];
			} else if (setting[0] == 4 && prIwReqData->data.length == 2) {
				if (setting[1] == 0)
					wlanDefTxPowerCfg(prGlueInfo->prAdapter);
				rStatus = kalIoctl(prGlueInfo,
						   wlanoidSetTxPower,
						   prTxpwr,
						   sizeof(SET_TXPWR_CTRL_T), TRUE, FALSE, FALSE, FALSE, &u4BufLen);
			} else
				return -EFAULT;
		}
		return status;
#ifdef CONFIG_MTK_WIFI_ANTENNA_SELECT
	case PRIV_CMD_ANT_SELECT:
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		params.ant_num = (unsigned int)pu4IntBuf[0];
		params.query_time = (unsigned int)pu4IntBuf[1];

		kalMemCopy(&prNdisReq->ndisOidContent[0],
			   &params, sizeof(params));

		prNdisReq->ndisOidCmd = OID_CUSTOM_ANT_SELECT;
		prNdisReq->inNdisOidlength = sizeof(params);
		prNdisReq->outNdisOidLength = sizeof(params);

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;
#endif
	default:
		break;
	}

	return status;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl get int array handler.
*
* \param[in] pDev Net device requested.
* \param[out] pIwReq Pointer to iwreq structure.
* \param[in] prIwReqData The ioctl req structure, use the field of sub-command.
* \param[out] pcExtra The buffer with put the return value
*
* \retval 0 For success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EFAULT For fail.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_get_ints(IN struct net_device *prNetDev,
	      IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	UINT_32 u4SubCmd;
	P_GLUE_INFO_T prGlueInfo;
	int status = 0;
	INT_32 ch[50];

	ASSERT(prNetDev);
	ASSERT(prIwReqInfo);
	ASSERT(prIwReqData);
	ASSERT(pcExtra);
	if (FALSE == GLUE_CHK_PR3(prNetDev, prIwReqData, pcExtra))
		return -EINVAL;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	u4SubCmd = (UINT_32) prIwReqData->data.flags;

	switch (u4SubCmd) {
	case PRIV_CMD_GET_CH_LIST:
		{
			UINT_16 i;
			UINT_8 NumOfChannel = 50;
			UINT_8 ucMaxChannelNum = 50;
			RF_CHANNEL_INFO_T aucChannelList[50];

			kalGetChannelList(prGlueInfo, BAND_NULL, ucMaxChannelNum, &NumOfChannel, aucChannelList);
			if (NumOfChannel > 50)
				NumOfChannel = 50;

			for (i = 0; i < NumOfChannel; i++)
				ch[i] = (INT_32) aucChannelList[i].ucChannelNum;

			prIwReqData->data.length = NumOfChannel;
			if (copy_to_user(prIwReqData->data.pointer, ch, NumOfChannel * sizeof(INT_32)))
				return -EFAULT;
			else
				return status;
		}
	default:
		break;
	}

	return status;
}				/* priv_get_int */

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl set structure handler.
*
* \param[in] pDev Net device requested.
* \param[in] prIwReqData Pointer to iwreq_data structure.
*
* \retval 0 For success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EINVAL If a value is out of range.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_set_struct(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	UINT_32 u4SubCmd = 0;
	int status = 0;
	/* WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS; */
	UINT_32 u4CmdLen = 0;
	P_NDIS_TRANSPORT_STRUCT prNdisReq;
	PUINT_32 pu4IntBuf = NULL;

	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_32 u4BufLen = 0;

	ASSERT(prNetDev);
	/* ASSERT(prIwReqInfo); */
	ASSERT(prIwReqData);
	/* ASSERT(pcExtra); */

	kalMemZero(&aucOidBuf[0], sizeof(aucOidBuf));

	if (FALSE == GLUE_CHK_PR2(prNetDev, prIwReqData))
		return -EINVAL;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	u4SubCmd = (UINT_32) prIwReqData->data.flags;

#if 0
	DBGLOG(REQ, INFO, "priv_set_struct(): prIwReqInfo->cmd(0x%X), u4SubCmd(%ld)\n",
	       prIwReqInfo->cmd, u4SubCmd);
#endif
	switch (u4SubCmd) {
#if 0				/* PTA_ENABLED */
	case PRIV_CMD_BT_COEXIST:
		u4CmdLen = prIwReqData->data.length * sizeof(UINT_32);
		ASSERT(sizeof(PARAM_CUSTOM_BT_COEXIST_T) >= u4CmdLen);
		if (sizeof(PARAM_CUSTOM_BT_COEXIST_T) < u4CmdLen)
			return -EFAULT;

		if (copy_from_user(&aucOidBuf[0], prIwReqData->data.pointer, u4CmdLen)) {
			status = -EFAULT;	/* return -EFAULT; */
			break;
		}

		rStatus = wlanSetInformation(prGlueInfo->prAdapter,
					     wlanoidSetBtCoexistCtrl, (PVOID)&aucOidBuf[0], u4CmdLen, &u4BufLen);
		if (WLAN_STATUS_SUCCESS != rStatus)
			status = -EFAULT;
		break;
#endif

	case PRIV_CUSTOM_BWCS_CMD:
		u4CmdLen = prIwReqData->data.length * sizeof(UINT_32);
		ASSERT(sizeof(PARAM_PTA_IPC_T) >= u4CmdLen);
		if (sizeof(PARAM_PTA_IPC_T) < u4CmdLen)
			return -EFAULT;
#if CFG_SUPPORT_BCM && CFG_SUPPORT_BCM_BWCS && CFG_SUPPORT_BCM_BWCS_DEBUG
		DBGLOG(REQ, INFO,
		       "ucCmdLen = %d, size of PTA_IPC_T = %d, prIwReqData->data = 0x%x.\n", u4CmdLen,
			sizeof(PARAM_PTA_IPC_T), prIwReqData->data);

		DBGLOG(REQ, INFO, "priv_set_struct(): prIwReqInfo->cmd(0x%X), u4SubCmd(%u)\n",
				   prIwReqInfo->cmd, u4SubCmd);

		DBGLOG(REQ, INFO, "*pcExtra = 0x%x\n", *pcExtra);
#endif

		if (copy_from_user(&aucOidBuf[0], prIwReqData->data.pointer, u4CmdLen)) {
			status = -EFAULT;	/* return -EFAULT; */
			break;
		}
#if CFG_SUPPORT_BCM && CFG_SUPPORT_BCM_BWCS && CFG_SUPPORT_BCM_BWCS_DEBUG
		DBGLOG(REQ, INFO, "priv_set_struct(): BWCS CMD = %02x%02x%02x%02x\n",
				   aucOidBuf[2], aucOidBuf[3], aucOidBuf[4], aucOidBuf[5]);
#endif

#if 0
		status = wlanSetInformation(prGlueInfo->prAdapter,
					    wlanoidSetBT, (PVOID)&aucOidBuf[0], u4CmdLen, &u4BufLen);
#endif

#if 1
		status = wlanoidSetBT(prGlueInfo->prAdapter, (PVOID)&aucOidBuf[0], u4CmdLen, &u4BufLen);
#endif

		if (WLAN_STATUS_SUCCESS != status)
			status = -EFAULT;

		break;

#if CFG_SUPPORT_WPS2
	case PRIV_CMD_WSC_PROBE_REQ:
		{
			/* retrieve IE for Probe Request */
			if (prIwReqData->data.length > 0) {
				if (prIwReqData->data.length > sizeof(prGlueInfo->aucWSCIE)) {
					DBGLOG(OID, INFO, "write data overflow\n");
					return -EINVAL;
				}
				if (copy_from_user(prGlueInfo->aucWSCIE, prIwReqData->data.pointer,
						   prIwReqData->data.length)) {
					status = -EFAULT;
					break;
				}
				prGlueInfo->u2WSCIELen = prIwReqData->data.length;
			} else {
				prGlueInfo->u2WSCIELen = 0;
			}
		}
		break;
#endif
	case PRIV_CMD_OID:
		if (prIwReqData->data.length > sizeof(aucOidBuf)) {
			DBGLOG(OID, INFO, "write data overflow\n");
			return -EINVAL;
		}
		if (copy_from_user(&aucOidBuf[0], prIwReqData->data.pointer, prIwReqData->data.length)) {
			status = -EFAULT;
			break;
		}
		if (!kalMemCmp(&aucOidBuf[0], pcExtra, prIwReqData->data.length))
			DBGLOG(REQ, INFO, "pcExtra buffer is valid\n");
		else
			DBGLOG(REQ, INFO, "pcExtra 0x%p\n", pcExtra);

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0], &u4BufLen);
#ifdef CONFIG_MTK_WIFI_ANTENNA_SWITCH
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];
		/* set default antenna when enter test mode */
		if (prNdisReq->ndisOidCmd == OID_CUSTOM_TEST_MODE)
			antennaSwitch(prGlueInfo->prAdapter, ANT1, FALSE);
#endif
		/* Copy result to user space */
		((P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0])->outNdisOidLength = u4BufLen;

		if (copy_to_user(prIwReqData->data.pointer,
				 &aucOidBuf[0], OFFSET_OF(NDIS_TRANSPORT_STRUCT, ndisOidContent))) {
			DBGLOG(REQ, INFO, "copy_to_user oidBuf fail\n");
			status = -EFAULT;
		}

		break;

	case PRIV_CMD_SW_CTRL:
		pu4IntBuf = (PUINT_32) prIwReqData->data.pointer;
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		if (prIwReqData->data.length > sizeof(prNdisReq->ndisOidContent)) {
			DBGLOG(REQ, INFO, "priv_get_struct() length Err!\n");
			return -EFAULT;
		}
		/* kalMemCopy(&prNdisReq->ndisOidContent[0], prIwReqData->data.pointer, 8); */
		if (copy_from_user(&prNdisReq->ndisOidContent[0], prIwReqData->data.pointer,
			prIwReqData->data.length)) {
			status = -EFAULT;
			break;
		}
		prNdisReq->ndisOidCmd = OID_CUSTOM_SW_CTRL;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		/* Execute this OID */
		status = priv_set_ndis(prNetDev, prNdisReq, &u4BufLen);
		break;

	default:
		return -EOPNOTSUPP;
	}

	return status;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl get struct handler.
*
* \param[in] pDev Net device requested.
* \param[out] pIwReq Pointer to iwreq structure.
* \param[in] cmd Private sub-command.
*
* \retval 0 For success.
* \retval -EFAULT If copy from user space buffer fail.
* \retval -EOPNOTSUPP Parameter "cmd" not recognized.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_get_struct(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	UINT_32 u4SubCmd = 0;
	P_NDIS_TRANSPORT_STRUCT prNdisReq = NULL;

	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_32 u4BufLen = 0;
	PUINT_32 pu4IntBuf = NULL;
	int status = 0;

	kalMemZero(&aucOidBuf[0], sizeof(aucOidBuf));

	ASSERT(prNetDev);
	ASSERT(prIwReqData);
	if (!prNetDev || !prIwReqData) {
		DBGLOG(REQ, INFO, "priv_get_struct(): invalid param(0x%p, 0x%p)\n", prNetDev, prIwReqData);
		return -EINVAL;
	}

	u4SubCmd = (UINT_32) prIwReqData->data.flags;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	ASSERT(prGlueInfo);
	if (!prGlueInfo) {
		DBGLOG(REQ, INFO, "priv_get_struct(): invalid prGlueInfo(0x%p, 0x%p)\n",
				   prNetDev, *((P_GLUE_INFO_T *) netdev_priv(prNetDev)));
		return -EINVAL;
	}
#if 0
	DBGLOG(REQ, INFO, "priv_get_struct(): prIwReqInfo->cmd(0x%X), u4SubCmd(%ld)\n",
	       prIwReqInfo->cmd, u4SubCmd);
#endif
	memset(aucOidBuf, 0, sizeof(aucOidBuf));

	switch (u4SubCmd) {
	case PRIV_CMD_OID:
		if (copy_from_user(&aucOidBuf[0], prIwReqData->data.pointer,
							sizeof(NDIS_TRANSPORT_STRUCT) + sizeof(UINT_8)*16)) {
			DBGLOG(REQ, INFO, "priv_get_struct() copy_from_user oidBuf fail\n");
			return -EFAULT;
		}

		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];
#if 0
		DBGLOG(REQ, INFO, "\n priv_get_struct cmd 0x%02x len:%d OID:0x%08x OID Len:%d\n",
		       cmd, pIwReq->u.data.length, ndisReq->ndisOidCmd, ndisReq->inNdisOidlength);
#endif
		if (priv_get_ndis(prNetDev, prNdisReq, &u4BufLen) == 0) {
			prNdisReq->outNdisOidLength = u4BufLen;
			if (copy_to_user(prIwReqData->data.pointer,
					 &aucOidBuf[0],
					 u4BufLen + sizeof(NDIS_TRANSPORT_STRUCT) + sizeof(UINT_8)*16 -
					 sizeof(prNdisReq->ndisOidContent))) {
				DBGLOG(REQ, INFO, "priv_get_struct() copy_to_user oidBuf fail(1)\n");
				return -EFAULT;
			}
			return 0;
		}
		prNdisReq->outNdisOidLength = u4BufLen;
		if (copy_to_user(prIwReqData->data.pointer,
				 &aucOidBuf[0], OFFSET_OF(NDIS_TRANSPORT_STRUCT, ndisOidContent))) {
			DBGLOG(REQ, INFO, "priv_get_struct() copy_to_user oidBuf fail(2)\n");
		}
		return -EFAULT;

	case PRIV_CMD_SW_CTRL:
		pu4IntBuf = (PUINT_32) prIwReqData->data.pointer;
		prNdisReq = (P_NDIS_TRANSPORT_STRUCT) &aucOidBuf[0];

		if (prIwReqData->data.length > (sizeof(NDIS_TRANSPORT_STRUCT) -
			OFFSET_OF(NDIS_TRANSPORT_STRUCT, ndisOidContent))) {
			DBGLOG(REQ, INFO, "priv_get_struct() length Err!\n");
			return -EFAULT;
		}
		if (copy_from_user(&prNdisReq->ndisOidContent[0], prIwReqData->data.pointer,
			prIwReqData->data.length)) {
			DBGLOG(REQ, INFO, "priv_get_struct() copy_from_user oidBuf fail\n");
			return -EFAULT;
		}

		prNdisReq->ndisOidCmd = OID_CUSTOM_SW_CTRL;
		prNdisReq->inNdisOidlength = 8;
		prNdisReq->outNdisOidLength = 8;

		status = priv_get_ndis(prNetDev, prNdisReq, &u4BufLen);
		if (status == 0) {
			prNdisReq->outNdisOidLength = u4BufLen;

			if (copy_to_user(prIwReqData->data.pointer,
					 &prNdisReq->ndisOidContent[4],
					 4 /* OFFSET_OF(NDIS_TRANSPORT_STRUCT, ndisOidContent) */)) {
				DBGLOG(REQ, INFO, "priv_get_struct() copy_to_user oidBuf fail(2)\n");
			}
		}
		return 0;
	default:
		DBGLOG(REQ, WARN, "get struct cmd:0x%x\n", u4SubCmd);
		return -EOPNOTSUPP;
	}
}				/* priv_get_struct */

/*----------------------------------------------------------------------------*/
/*!
* \brief The routine handles a set operation for a single OID.
*
* \param[in] pDev Net device requested.
* \param[in] ndisReq Ndis request OID information copy from user.
* \param[out] outputLen_p If the call is successful, returns the number of
*                         bytes written into the query buffer. If the
*                         call failed due to invalid length of the query
*                         buffer, returns the amount of storage needed..
*
* \retval 0 On success.
* \retval -EOPNOTSUPP If cmd is not supported.
*
*/
/*----------------------------------------------------------------------------*/
static int
priv_set_ndis(IN struct net_device *prNetDev, IN NDIS_TRANSPORT_STRUCT * prNdisReq, OUT PUINT_32 pu4OutputLen)
{
	P_WLAN_REQ_ENTRY prWlanReqEntry = NULL;
	WLAN_STATUS status = WLAN_STATUS_SUCCESS;
	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_32 u4SetInfoLen = 0;

	ASSERT(prNetDev);
	ASSERT(prNdisReq);
	ASSERT(pu4OutputLen);

	if (!prNetDev || !prNdisReq || !pu4OutputLen) {
		DBGLOG(REQ, INFO, "priv_set_ndis(): invalid param(0x%p, 0x%p, 0x%p)\n",
				   prNetDev, prNdisReq, pu4OutputLen);
		return -EINVAL;
	}

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	ASSERT(prGlueInfo);
	if (!prGlueInfo) {
		DBGLOG(REQ, INFO, "priv_set_ndis(): invalid prGlueInfo(0x%p, 0x%p)\n",
				   prNetDev, *((P_GLUE_INFO_T *) netdev_priv(prNetDev)));
		return -EINVAL;
	}
#if 0
	DBGLOG(REQ, INFO, "priv_set_ndis(): prNdisReq->ndisOidCmd(0x%lX)\n", prNdisReq->ndisOidCmd);
#endif

	if (FALSE == reqSearchSupportedOidEntry(prNdisReq->ndisOidCmd, &prWlanReqEntry)) {
		/* WARNLOG(("Set OID: 0x%08lx (unknown)\n", prNdisReq->ndisOidCmd)); */
		return -EOPNOTSUPP;
	}

	if (NULL == prWlanReqEntry->pfOidSetHandler) {
		/* WARNLOG(("Set %s: Null set handler\n", prWlanReqEntry->pucOidName)); */
		return -EOPNOTSUPP;
	}
#if 0
	DBGLOG(REQ, INFO, "priv_set_ndis(): %s\n", prWlanReqEntry->pucOidName);
#endif

	if (prWlanReqEntry->fgSetBufLenChecking) {
		if (prNdisReq->inNdisOidlength != prWlanReqEntry->u4InfoBufLen) {
			DBGLOG(REQ, WARN, "Set %s: Invalid length (current=%u, needed=%u)\n",
					   prWlanReqEntry->pucOidName,
					   prNdisReq->inNdisOidlength, prWlanReqEntry->u4InfoBufLen);

			*pu4OutputLen = prWlanReqEntry->u4InfoBufLen;
			return -EINVAL;
		}
	}

	if (prWlanReqEntry->eOidMethod == ENUM_OID_GLUE_ONLY) {
		/* GLUE sw info only */
		status = prWlanReqEntry->pfOidSetHandler(prGlueInfo,
							 prNdisReq->ndisOidContent,
							 prNdisReq->inNdisOidlength, &u4SetInfoLen);
	} else if (prWlanReqEntry->eOidMethod == ENUM_OID_GLUE_EXTENSION) {
		/* multiple sw operations */
		status = prWlanReqEntry->pfOidSetHandler(prGlueInfo,
							 prNdisReq->ndisOidContent,
							 prNdisReq->inNdisOidlength, &u4SetInfoLen);
	} else if (prWlanReqEntry->eOidMethod == ENUM_OID_DRIVER_CORE) {
		/* driver core */

		status = kalIoctl(prGlueInfo,
				  (PFN_OID_HANDLER_FUNC) prWlanReqEntry->pfOidSetHandler,
				  prNdisReq->ndisOidContent,
				  prNdisReq->inNdisOidlength, FALSE, FALSE, TRUE, FALSE, &u4SetInfoLen);
	} else {
		DBGLOG(REQ, INFO, "priv_set_ndis(): unsupported OID method:0x%x\n", prWlanReqEntry->eOidMethod);
		return -EOPNOTSUPP;
	}

	*pu4OutputLen = u4SetInfoLen;

	switch (status) {
	case WLAN_STATUS_SUCCESS:
		break;

	case WLAN_STATUS_INVALID_LENGTH:
		/* WARNLOG(("Set %s: Invalid length (current=%ld, needed=%ld)\n", */
		/* prWlanReqEntry->pucOidName, */
		/* prNdisReq->inNdisOidlength, */
		/* u4SetInfoLen)); */
		break;
	}

	if (WLAN_STATUS_SUCCESS != status)
		return -EFAULT;

	return 0;
}				/* priv_set_ndis */

/*----------------------------------------------------------------------------*/
/*!
* \brief The routine handles a query operation for a single OID. Basically we
*   return information about the current state of the OID in question.
*
* \param[in] pDev Net device requested.
* \param[in] ndisReq Ndis request OID information copy from user.
* \param[out] outputLen_p If the call is successful, returns the number of
*                        bytes written into the query buffer. If the
*                        call failed due to invalid length of the query
*                        buffer, returns the amount of storage needed..
*
* \retval 0 On success.
* \retval -EOPNOTSUPP If cmd is not supported.
* \retval -EINVAL invalid input parameters
*
*/
/*----------------------------------------------------------------------------*/
static int
priv_get_ndis(IN struct net_device *prNetDev, IN NDIS_TRANSPORT_STRUCT * prNdisReq, OUT PUINT_32 pu4OutputLen)
{
	P_WLAN_REQ_ENTRY prWlanReqEntry = NULL;
	UINT_32 u4BufLen = 0;
	WLAN_STATUS status = WLAN_STATUS_SUCCESS;
	P_GLUE_INFO_T prGlueInfo = NULL;

	ASSERT(prNetDev);
	ASSERT(prNdisReq);
	ASSERT(pu4OutputLen);

	if (!prNetDev || !prNdisReq || !pu4OutputLen) {
		DBGLOG(REQ, INFO, "priv_get_ndis(): invalid param(0x%p, 0x%p, 0x%p)\n",
				   prNetDev, prNdisReq, pu4OutputLen);
		return -EINVAL;
	}

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	ASSERT(prGlueInfo);
	if (!prGlueInfo) {
		DBGLOG(REQ, INFO, "priv_get_ndis(): invalid prGlueInfo(0x%p, 0x%p)\n",
				   prNetDev, *((P_GLUE_INFO_T *) netdev_priv(prNetDev)));
		return -EINVAL;
	}
#if 0
	DBGLOG(REQ, INFO, "priv_get_ndis(): prNdisReq->ndisOidCmd(0x%lX)\n", prNdisReq->ndisOidCmd);
#endif

	if (FALSE == reqSearchSupportedOidEntry(prNdisReq->ndisOidCmd, &prWlanReqEntry)) {
		/* WARNLOG(("Query OID: 0x%08lx (unknown)\n", prNdisReq->ndisOidCmd)); */
		return -EOPNOTSUPP;
	}

	if (NULL == prWlanReqEntry->pfOidQueryHandler) {
		/* WARNLOG(("Query %s: Null query handler\n", prWlanReqEntry->pucOidName)); */
		return -EOPNOTSUPP;
	}
#if 0
	DBGLOG(REQ, INFO, "priv_get_ndis(): %s\n", prWlanReqEntry->pucOidName);
#endif

	if (prWlanReqEntry->fgQryBufLenChecking) {
		if (prNdisReq->inNdisOidlength < prWlanReqEntry->u4InfoBufLen) {
			/* Not enough room in InformationBuffer. Punt */
			/* WARNLOG(("Query %s: Buffer too short (current=%ld, needed=%ld)\n", */
			/* prWlanReqEntry->pucOidName, */
			/* prNdisReq->inNdisOidlength, */
			/* prWlanReqEntry->u4InfoBufLen)); */

			*pu4OutputLen = prWlanReqEntry->u4InfoBufLen;

			status = WLAN_STATUS_INVALID_LENGTH;
			return -EINVAL;
		}
	}

	if (prWlanReqEntry->eOidMethod == ENUM_OID_GLUE_ONLY) {
		/* GLUE sw info only */
		status = prWlanReqEntry->pfOidQueryHandler(prGlueInfo,
							   prNdisReq->ndisOidContent,
							   prNdisReq->inNdisOidlength, &u4BufLen);
	} else if (prWlanReqEntry->eOidMethod == ENUM_OID_GLUE_EXTENSION) {
		/* multiple sw operations */
		status = prWlanReqEntry->pfOidQueryHandler(prGlueInfo,
							   prNdisReq->ndisOidContent,
							   prNdisReq->inNdisOidlength, &u4BufLen);
	} else if (prWlanReqEntry->eOidMethod == ENUM_OID_DRIVER_CORE) {
		/* driver core */

		status = kalIoctl(prGlueInfo,
				  (PFN_OID_HANDLER_FUNC) prWlanReqEntry->pfOidQueryHandler,
				  prNdisReq->ndisOidContent,
				  prNdisReq->inNdisOidlength, TRUE, TRUE, TRUE, FALSE, &u4BufLen);
	} else {
		DBGLOG(REQ, INFO, "priv_set_ndis(): unsupported OID method:0x%x\n", prWlanReqEntry->eOidMethod);
		return -EOPNOTSUPP;
	}

	*pu4OutputLen = u4BufLen;

	switch (status) {
	case WLAN_STATUS_SUCCESS:
		break;

	case WLAN_STATUS_INVALID_LENGTH:
		/* WARNLOG(("Set %s: Invalid length (current=%ld, needed=%ld)\n", */
		/* prWlanReqEntry->pucOidName, */
		/* prNdisReq->inNdisOidlength, */
		/* u4BufLen)); */
		break;
	}

	if (WLAN_STATUS_SUCCESS != status)
		return -EOPNOTSUPP;

	return 0;
}				/* priv_get_ndis */

/*----------------------------------------------------------------------------*/
/*!
* @brief Parse command value in a string.
*
* @param InStr  Pointer to the string buffer.
* @param OutStr  Pointer to the next command value.
* @param OutLen  Record the resident buffer length.
*
* @retval Command value.
*/
/*----------------------------------------------------------------------------*/
UINT_32 CmdStringDecParse(IN UINT_8 *InStr, OUT UINT_8 **OutStr, OUT UINT_32 *OutLen)
{
	unsigned char Charc, *Buf;
	unsigned int Num;
	int Maxloop;
	int ReadId;
	int TotalLen;

	/* init */
	Num = 0;
	Maxloop = 0;
	ReadId = 0;
	Buf = (unsigned char *)InStr;
	TotalLen = *OutLen;
	*OutStr = Buf;

	/* sanity check */
	if (Buf[0] == 0x00)
		return 0;

	/* check the value is decimal or hex */
	if ((Buf[ReadId] == 'x') || ((Buf[ReadId] == '0') && (Buf[ReadId + 1] == 'x'))) {
		/* skip x or 0x */
		if (Buf[ReadId] == 'x')
			ReadId++;
		else
			ReadId += 2;

		/* translate the hex number */
		while (Maxloop++ < 10) {
			Charc = Buf[ReadId];
			if ((Charc >= 0x30) && (Charc <= 0x39))
				Charc -= 0x30;
			else if ((Charc >= 'a') && (Charc <= 'f'))
				Charc -= 'a';
			else if ((Charc >= 'A') && (Charc <= 'F'))
				Charc -= 'A';
			else
				break;	/* exit the parsing */
			Num = Num * 16 + Charc + 10;
			ReadId++;
			TotalLen--;
		}
	} else {
		/* translate the decimal number */
		while (Maxloop++ < 10) {
			Charc = Buf[ReadId];
			if ((Charc < 0x30) || (Charc > 0x39))
				break;	/* exit the parsing */
			Charc -= 0x30;
			Num = Num * 10 + Charc;
			ReadId++;
			TotalLen--;
		}
	}

	if (Buf[ReadId] == 0x00)
		*OutStr = &Buf[ReadId];
	else
		*OutStr = &Buf[ReadId + 1];	/* skip the character: _ */

	*OutLen = TotalLen - 1;	/* skip the character: _ */
	return Num;
}

/*----------------------------------------------------------------------------*/
/*!
* @brief Parse command MAC address in a string.
*
* @param InStr  Pointer to the string buffer.
* @param OutStr  Pointer to the next command value.
* @param OutLen  Record the resident buffer length.
*
* @retval Command value.
*/
/*----------------------------------------------------------------------------*/
UINT_32 CmdStringMacParse(IN UINT_8 *InStr, OUT UINT_8 **OutStr, OUT UINT_32 *OutLen, OUT UINT_8 *OutMac)
{
	unsigned char Charc, *Buf;
	unsigned int Num;
	int Maxloop;
	int ReadId;
	int TotalLen;

	/* init */
	Num = 0;
	Maxloop = 0;
	ReadId = 0;
	Buf = (unsigned char *)InStr;
	TotalLen = *OutLen;
	*OutStr = Buf;

	/* sanity check */
	if (Buf[0] == 0x00)
		return 0;

	/* parse MAC */
	while (Maxloop < 6) {
		Charc = Buf[ReadId];
		if ((Charc >= 0x30) && (Charc <= 0x39))
			Charc -= 0x30;
		else if ((Charc >= 'a') && (Charc <= 'f'))
			Charc = Charc - 'a' + 10;
		else if ((Charc >= 'A') && (Charc <= 'F'))
			Charc = Charc - 'A' + 10;
		else
			return -1;	/* error, exit the parsing */

		Num = Charc;
		ReadId++;
		TotalLen--;

		Charc = Buf[ReadId];
		if ((Charc >= 0x30) && (Charc <= 0x39))
			Charc -= 0x30;
		else if ((Charc >= 'a') && (Charc <= 'f'))
			Charc = Charc - 'a' + 10;
		else if ((Charc >= 'A') && (Charc <= 'F'))
			Charc = Charc - 'A' + 10;
		else
			return -1;	/* error, exit the parsing */

		Num = Num * 16 + Charc;
		ReadId += 2;	/* skip the character and ':' */
		TotalLen -= 2;

		OutMac[Maxloop] = Num;
		Maxloop++;
	}

	*OutStr = &Buf[ReadId];	/* skip the character: _ */
	*OutLen = TotalLen;	/* skip the character: _ */
	return Num;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief The routine handles a set operation for a single OID.
*
* \param[in] pDev Net device requested.
* \param[in] ndisReq Ndis request OID information copy from user.
* \param[out] outputLen_p If the call is successful, returns the number of
*                         bytes written into the query buffer. If the
*                         call failed due to invalid length of the query
*                         buffer, returns the amount of storage needed..
*
* \retval 0 On success.
* \retval -EOPNOTSUPP If cmd is not supported.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_set_string(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	P_GLUE_INFO_T GlueInfo;
	INT_32 Status = 0;
	UINT_32 Subcmd;
	UINT_8 *pucInBuf = aucOidBuf;
	UINT_32 u4BufLen;

	/* sanity check */
	ASSERT(prNetDev);
	ASSERT(prIwReqInfo);
	ASSERT(prIwReqData);
	ASSERT(pcExtra);

	/* init */
	DBGLOG(REQ, INFO, "priv_set_string (%s)(%d)\n",
			   (UINT8 *) prIwReqData->data.pointer, (INT32) prIwReqData->data.length);

	if (FALSE == GLUE_CHK_PR3(prNetDev, prIwReqData, pcExtra))
		return -EINVAL;

	GlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	u4BufLen = prIwReqData->data.length;

	if (u4BufLen >= OID_BUF_SIZE) {
		DBGLOG(OID, INFO, "write data overflow\n");
		return -EINVAL;
	}
	if (copy_from_user(pucInBuf, prIwReqData->data.pointer, u4BufLen))
		return -EFAULT;

	Subcmd = CmdStringDecParse(pucInBuf, &pucInBuf, &u4BufLen);
	DBGLOG(REQ, INFO, "priv_set_string> command = %u\n", (UINT32) Subcmd);

	/* handle the command */
	switch (Subcmd) {
#if (CFG_SUPPORT_TDLS == 1)
	case PRIV_CMD_OTHER_TDLS:
		TdlsexCmd(GlueInfo, pucInBuf, u4BufLen);
		break;
#endif /* CFG_SUPPORT_TDLS */

#if (CFG_SUPPORT_TXR_ENC == 1)
	case PRIV_CMD_OTHER_TAR:
	{
		rlmCmd(GlueInfo, pucInBuf, u4BufLen);
		break;
	}
#endif /* CFG_SUPPORT_TXR_ENC */
	default:
		break;
	}

	return Status;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief The routine handles a get operation for a single OID.
*
* \param[in] pDev Net device requested.
* \param[in] ndisReq Ndis request OID information copy from user.
* \param[out] outputLen_p If the call is successful, returns the number of
*                         bytes written into the query buffer. If the
*                         call failed due to invalid length of the query
*                         buffer, returns the amount of storage needed..
*
* \retval 0 On success.
* \retval -EOPNOTSUPP If cmd is not supported.
*
*/
/*----------------------------------------------------------------------------*/
static int
_priv_get_string(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_32 u4SubCmd = 0;
	UINT_32 u4TotalLen = 2000;
	UINT_32 u4BufLen = 0;
	int status, pos, i = 0;
	char *buf = pcExtra;
	PARAM_MAC_ADDRESS arBssid;
	PARAM_SSID_T ssid;

	if (!prNetDev || !prIwReqData || !pcExtra) {
		DBGLOG(REQ, WARN, "_priv_get_string(): invalid param(0x%p, 0x%p)\n", prNetDev, prIwReqData);
		return -EINVAL;
	}

	u4SubCmd = (UINT_32) prIwReqData->data.flags;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	if (!prGlueInfo) {
		DBGLOG(REQ, INFO, "priv_get_string(): invalid prGlueInfo(0x%p, 0x%p)\n",
				   prNetDev, *((P_GLUE_INFO_T *) netdev_priv(prNetDev)));
		return -EINVAL;
	}
	if (pcExtra) {
		pcExtra[u4TotalLen] = '\0';
	}
	pos += scnprintf(buf + pos, u4TotalLen - pos, "\n");

	switch (u4SubCmd) {
	case PRIV_CMD_CONNSTATUS:
	{
		kalMemZero(arBssid, MAC_ADDR_LEN);
		rStatus = wlanQueryInformation(prGlueInfo->prAdapter,
					wlanoidQueryBssid, &arBssid[0], sizeof(arBssid), &u4BufLen);

		if (rStatus == WLAN_STATUS_SUCCESS) {
			wlanQueryInformation(prGlueInfo->prAdapter,
				wlanoidQuerySsid, &ssid, sizeof(ssid), &u4BufLen);

			pos += scnprintf(buf + pos, u4TotalLen - pos,
								"connStatus: Connected (AP: %s (", ssid.aucSsid);

			for (i = 0; i < PARAM_MAC_ADDR_LEN; i++) {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "%02x", arBssid[i]);
				if (i != PARAM_MAC_ADDR_LEN - 1) {
					pos += scnprintf(buf + pos, u4TotalLen - pos, ":");
				}
			}
			pos += scnprintf(buf + pos, u4TotalLen - pos, "))");
		} else
			pos += scnprintf(buf + pos, u4TotalLen - pos, "connStatus: Not connected");

		break;
	}
	case PRIV_CMD_STAT:
	{
		static UINT_8 aucBuffer[512];
		P_CMD_SW_DBG_CTRL_T pSwDbgCtrl;
		INT_32 i4Rssi;
		UINT_32 u4Rate = 0;
		P_BSS_INFO_T prBssInfo;
		struct iw_statistics *pStats = (struct iw_statistics *)NULL;

		kalMemZero(aucBuffer, 512);
		pSwDbgCtrl = (P_CMD_SW_DBG_CTRL_T)aucBuffer;

		if (kalIoctl(prGlueInfo,
			wlanoidQueryDbgCntr,
			(PVOID)aucBuffer,
			sizeof(UINT_8) * 512, TRUE, TRUE, TRUE, FALSE, &u4BufLen)
			== WLAN_STATUS_SUCCESS) {
			if (pSwDbgCtrl) {
				if (pSwDbgCtrl->u4Data == SWCR_DBG_TYPE_ALL) {
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "Tx success = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_TX_CNT] -
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_TX_FAILED_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "Tx retry count = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_TX_RETRY_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos,
										"Tx fail to Rcv ACK after retry = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_TX_ERROR_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "Rx success = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_RX_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "Rx with CRC = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_RX_FCSERR_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos,
										"Rx drop due to out of resource = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_RX_FIFOFULL_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "Rx duplicate frame = %d\n",
										pSwDbgCtrl->u4DebugCnt[SWCR_DBG_ALL_RX_DUP_DROP_CNT]);
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "False CCA(total) = \n");
					pos +=	scnprintf(buf + pos, u4TotalLen - pos, "False CCA(one-second) = \n");
				}
			}
		}

		if (kalIoctl(prGlueInfo, wlanoidQueryRssi, &i4Rssi, sizeof(i4Rssi),
				TRUE, TRUE, TRUE, FALSE, &u4BufLen) == WLAN_STATUS_SUCCESS) {

			pStats = (struct iw_statistics *)(&(prGlueInfo->rIwStats));

			pos += scnprintf(buf + pos, u4TotalLen - pos, "RSSI = %d\n", i4Rssi);
			pos += scnprintf(buf + pos, u4TotalLen - pos, "P2P GO RSSI =\n");
			pos += scnprintf(buf + pos, u4TotalLen - pos, "SNR-A = \n");
			pos += scnprintf(buf + pos, u4TotalLen - pos, "SNR-B (if available) =\n");
			pos += scnprintf(buf + pos, u4TotalLen - pos, "NoiseLevel-A = %d\n",-(pStats->qual.noise));
			pos += scnprintf(buf + pos, u4TotalLen - pos, "NoiseLevel-B =\n");
		}

		status = kalIoctl(prGlueInfo, wlanoidQueryLinkSpeed, &u4Rate,
						sizeof(u4Rate), TRUE, TRUE, TRUE, FALSE, &u4BufLen);

		/* STA stats */
		kalMemZero(arBssid, MAC_ADDR_LEN);
		if (wlanQueryInformation(prGlueInfo->prAdapter, wlanoidQueryBssid,
			&arBssid[0], sizeof(arBssid), &u4BufLen) == WLAN_STATUS_SUCCESS) {
			prBssInfo =
				&(prGlueInfo->prAdapter->rWifiVar.arBssInfo[NETWORK_TYPE_AIS_INDEX]);

			wlanQueryInformation(prGlueInfo->prAdapter, wlanoidQuerySsid,
				&ssid, sizeof(ssid), &u4BufLen);

			pos += scnprintf(buf + pos, u4TotalLen - pos, "\n(STA) connected AP MAC Address = ");

			for (i = 0; i < PARAM_MAC_ADDR_LEN; i++) {

				pos += scnprintf(buf + pos, u4TotalLen - pos, "%02x", arBssid[i]);
				if (i != PARAM_MAC_ADDR_LEN - 1) {

					pos += scnprintf(buf + pos, u4TotalLen - pos, ":");
				}
			}
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\n");
			pos += scnprintf(buf + pos, u4TotalLen - pos, "PhyMode:");
			switch (prBssInfo->ucPhyTypeSet) {
			case PHY_TYPE_SET_802_11B:
				pos += scnprintf(buf + pos, u4TotalLen - pos, "802.11b\n");
				break;
			case PHY_TYPE_SET_802_11ABG:
			case PHY_TYPE_SET_802_11BG:
				pos += scnprintf(buf + pos, u4TotalLen - pos, "802.11g\n");
				break;
			case PHY_TYPE_SET_802_11A:
				pos += scnprintf(buf + pos, u4TotalLen - pos, "802.11a\n");
				break;
			case PHY_TYPE_SET_802_11ABGN:
			case PHY_TYPE_SET_802_11BGN:
			case PHY_TYPE_SET_802_11AN:
			case PHY_TYPE_SET_802_11GN:
				pos += scnprintf(buf + pos, u4TotalLen - pos, "802.11n\n");
				break;
			default:
				break;
			}

			pos += scnprintf(buf + pos, u4TotalLen - pos, "Last TX Rate = %d \n", u4Rate*100);

			if (getLastRxRate(prNetDev, &u4Rate) == 0) {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "Last RX Rate = %d\n",
					((u4Rate>>24)&0xff)*1000000);
			} else {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "Last RX Rate = \n");
			}
		} else {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\n(STA) Not connected\n");
		}

		break;
	}
#if CFG_SUPPORT_WAKEUP_STATISTICS
	case PRIV_CMD_INT_STAT:
	{
		P_WAKEUP_STATISTIC *prWakeupSta = NULL;

		prWakeupSta = prGlueInfo->prAdapter->arWakeupStatistic;
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"Abnormal Interrupt:%d\n"
				"Software Interrupt:%d\n"
				"TX Interrupt:%d\n"
				"RX data:%d\n"
				"RX Event:%d\n"
				"RX mgmt:%d\n"
				"RX others:%d\n",
				prWakeupSta[0].u2Count,
				prWakeupSta[1].u2Count,
				prWakeupSta[2].u2Count,
				prWakeupSta[3].u2Count,
				prWakeupSta[4].u2Count,
				prWakeupSta[5].u2Count,
				prWakeupSta[6].u2Count);
		for (i = 0; i < EVENT_ID_END; i++) {
			if (prGlueInfo->prAdapter->wake_event_count[i] > 0)
				pos += scnprintf(buf + pos, u4TotalLen - pos,
						"RX EVENT(0x%0x):%d\n", i,
						prGlueInfo->prAdapter->wake_event_count[i]);
		}

		break;
	}
#endif
#if CFG_SUPPORT_EXCEPTION_STATISTICS
	case PRIV_CMD_EXCEPTION_STAT:
	{
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalBeaconTimeout:%d\n",
				prGlueInfo->prAdapter->total_beacon_timeout_count);
		for (i = 0; i < BEACON_TIMEOUT_TYPE_NUM; i++) {
			if (prGlueInfo->prAdapter->beacon_timeout_count[i] > 0)
				pos += scnprintf(buf + pos, u4TotalLen - pos,
						"BeaconTimeout Reason(0x%0x):%d\n", i,
						prGlueInfo->prAdapter->beacon_timeout_count[i]);
		}
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalTxDoneFail:%d\n",
				prGlueInfo->prAdapter->total_tx_done_fail_count);
		for (i = 0; i < TX_RESULT_NUM; i++) {
			if (prGlueInfo->prAdapter->tx_done_fail_count[i] > 0)
				pos += scnprintf(buf + pos, u4TotalLen - pos,
						"TxDoneFail Reason(0x%0x):%d\n", i,
						prGlueInfo->prAdapter->tx_done_fail_count[i]);
		}
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalRxDeauth:%d\n",
				prGlueInfo->prAdapter->total_deauth_rx_count);
		for (i = 0; i < (REASON_CODE_BSS_SECURITY_CHANGE + 1); i++) {
			if (prGlueInfo->prAdapter->deauth_rx_count[i] > 0)
				pos += scnprintf(buf + pos, u4TotalLen - pos,
						"RxDeauth Reason(0x%0x):%d\n", i,
						prGlueInfo->prAdapter->deauth_rx_count[i]);
		}
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalScanDoneTimeout:%d\n",
				prGlueInfo->prAdapter->total_scandone_timeout_count);
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalTxMgmtTimeout:%d\n",
				prGlueInfo->prAdapter->total_mgmtTX_timeout_count);
		pos += scnprintf(buf + pos, u4TotalLen - pos,
				"TotalRxMgmtTimeout:%d\n",
				prGlueInfo->prAdapter->total_mgmtRX_timeout_count);

		break;
	}
#endif
#if CFG_SHOW_NVRAM
	case PRIV_CMD_SHOW_NVRAM:
	{
		P_ADAPTER_T prAdapter = prGlueInfo->prAdapter;
		P_REG_INFO_T prRegInfo = &prGlueInfo->rRegInfo;
		TX_PWR_PARAM_T rTxPwr = prRegInfo->rTxPwr;

		if (!prAdapter || !prRegInfo)
			return -EFAULT;

		if (prRegInfo->au2CountryCode[0] == 0)
			pos += scnprintf(buf + pos, u4TotalLen - pos, "[Country] %x%x\n", prRegInfo->au2CountryCode[0], prRegInfo->au2CountryCode[1]);
		else
			pos += scnprintf(buf + pos, u4TotalLen - pos, "[Country] %c%c\n", prRegInfo->au2CountryCode[0], prRegInfo->au2CountryCode[1]);

		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Support 5GHz]\n");
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tSupport 5G Band:%d\n", prRegInfo->ucSupport5GBand);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tEnable 5G Band:%d\n", prRegInfo->ucEnable5GBand);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Band Edge Power Used]\n");

		if (prRegInfo->fg2G4BandEdgePwrUsed == 1) {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tBand edge power in 2G4:%x \n", prRegInfo->fg2G4BandEdgePwrUsed);
			if (!prAdapter->fgTestMode) {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "\tMaxPwrCCK/OFDM20/OFDM40 in 2G4:(%x,%x,%x)\n",
					prRegInfo->cBandEdgeMaxPwrCCK, prRegInfo->cBandEdgeMaxPwrOFDM20,
					prRegInfo->cBandEdgeMaxPwrOFDM40);
			} else {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "\tMaxPwrCCK/OFDM20/OFDM40 in 2G4:(%x,%x,%x)\n",
					MAX_TX_POWER, MAX_TX_POWER, MAX_TX_POWER);
			}
		} else {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tBand edge power in 2G4:%x \n", prRegInfo->fg2G4BandEdgePwrUsed);
		}
		if (prRegInfo->aucEFUSE && prRegInfo->aucEFUSE[OFFSET_fg5GBandEdgePwrUsed] == 0x1) {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tBand edge power in 5G:%x \n", prRegInfo->aucEFUSE[OFFSET_fg5GBandEdgePwrUsed]);
			if (!prAdapter->fgTestMode) {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "\tMaxPwrOFDM20/OFDM40 in 5G:(%x,%x)\n",
					prRegInfo->aucEFUSE[OFFSET_c5GBandEdgeMaxPwrOFDM20],
					prRegInfo->aucEFUSE[OFFSET_c5GBandEdgeMaxPwrOFDM40]);
			} else {
				pos += scnprintf(buf + pos, u4TotalLen - pos, "\tMaxPwrOFDM20/OFDM40 in 5G:(%x,%x)\n", MAX_TX_POWER, MAX_TX_POWER);
			}
		} else {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tBand edge power in 5G:%x \n", prRegInfo->aucEFUSE[OFFSET_fg5GBandEdgePwrUsed]);
		}

		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Channel Offset]\n");
		if (prRegInfo->aucEFUSE && prRegInfo->aucEFUSE[OFFSET_ucChannelOffsetValid] == 0x1) {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tEnable in 2G4:%x \n", prRegInfo->aucEFUSE[OFFSET_ucChannelOffsetValid]);
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\taucChOffset:(%x,%x,%x) \n", prRegInfo->aucEFUSE[OFFSET_aucChOffset],
				prRegInfo->aucEFUSE[OFFSET_aucChOffset+1], prRegInfo->aucEFUSE[OFFSET_aucChOffset+2]);
		} else {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tEnable in 2G4:%x \n", prRegInfo->aucEFUSE[OFFSET_ucChannelOffsetValid]);
		}

		if (prRegInfo->aucEFUSE && prRegInfo->aucEFUSE[OFFSET_uc5GChannelOffsetValid] == 0x1) {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tEnable in 5G:%x \n", prRegInfo->aucEFUSE[OFFSET_uc5GChannelOffsetValid]);
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tauc5GChOffset:(%x,%x,%x,%x,%x,%x,%x,%x) \n", prRegInfo->aucEFUSE[OFFSET_auc5GChOffset],
				prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+1], prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+2],
				prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+3], prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+4],
				prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+5], prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+6],
				prRegInfo->aucEFUSE[OFFSET_auc5GChOffset+7]);
		} else {
			pos += scnprintf(buf + pos, u4TotalLen - pos, "\tEnable in 5G:%x \n", prRegInfo->aucEFUSE[OFFSET_uc5GChannelOffsetValid]);
		}
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tacAllChannelOffset:(%x) \n", prRegInfo->aucEFUSE[OFFSET_acAllChannelOffset]);

		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Power Table In Use]\n");
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tucTxPwrValid:%d\n", prRegInfo->ucTxPwrValid);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t2G4Cck:(%x)\n", rTxPwr.cTxPwr2G4Cck);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t2G4OFDM_BPSK/QPSK/16QAM/48M/54M:(%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr2G4OFDM_BPSK, rTxPwr.cTxPwr2G4OFDM_QPSK, rTxPwr.cTxPwr2G4OFDM_16QAM,
			rTxPwr.cTxPwr2G4OFDM_48Mbps, rTxPwr.cTxPwr2G4OFDM_54Mbps);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t2G4HT20_BPSK/QPSK/16QAM/MCS5/MCS6/MCS7:(%x,%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr2G4HT20_BPSK, rTxPwr.cTxPwr2G4HT20_QPSK, rTxPwr.cTxPwr2G4HT20_16QAM,
			rTxPwr.cTxPwr2G4HT20_MCS5, rTxPwr.cTxPwr2G4HT20_MCS6, rTxPwr.cTxPwr2G4HT20_MCS7);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t2G4HT40_BPSK/QPSK/16QAM/MCS5/MCS6/MCS7:(%x,%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr2G4HT40_BPSK, rTxPwr.cTxPwr2G4HT40_QPSK, rTxPwr.cTxPwr2G4HT40_16QAM,
			rTxPwr.cTxPwr2G4HT40_MCS5, rTxPwr.cTxPwr2G4HT40_MCS6, rTxPwr.cTxPwr2G4HT40_MCS7);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t5GOFDM_BPSK/QPSK/16QAM/48M/54M:(%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr5GOFDM_BPSK, rTxPwr.cTxPwr5GOFDM_QPSK, rTxPwr.cTxPwr5GOFDM_16QAM,
			rTxPwr.cTxPwr5GOFDM_48Mbps, rTxPwr.cTxPwr5GOFDM_54Mbps);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t5GHT20_BPSK/QPSK/16QAM/MCS5/MCS6/MCS7:(%x,%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr5GHT20_BPSK, rTxPwr.cTxPwr5GHT20_QPSK, rTxPwr.cTxPwr5GHT20_16QAM,
			rTxPwr.cTxPwr5GHT20_MCS5, rTxPwr.cTxPwr5GHT20_MCS6, rTxPwr.cTxPwr5GHT20_MCS7);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\t5GHT40_BPSK/QPSK/16QAM/MCS5/MCS6/MCS7:(%x,%x,%x,%x,%x,%x)\n",
			rTxPwr.cTxPwr5GHT40_BPSK, rTxPwr.cTxPwr5GHT40_QPSK, rTxPwr.cTxPwr5GHT40_16QAM,
			rTxPwr.cTxPwr5GHT40_MCS5, rTxPwr.cTxPwr5GHT40_MCS6, rTxPwr.cTxPwr5GHT40_MCS7);

		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Fixed 20M]\n");
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tin 2G4 BW:%d\n", prRegInfo->uc2G4BwFixed20M);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tin 5G BW:%d\n", prRegInfo->uc5GBwFixed20M);

		pos += scnprintf(buf + pos, u4TotalLen - pos, "[Rssi Compensation]\n");
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tValid bit:%d\n", prRegInfo->fgRssiCompensationValidbit);
		pos += scnprintf(buf + pos, u4TotalLen - pos, "\tRssi Compensation(2G4,5G):(%d,%d)\n",
			prRegInfo->uc2GRssiCompensation, prRegInfo->uc5GRssiCompensation);

		break;
	}
#endif
	case PRIV_CMD_GET_BAND_WIDTH:
	{
		UINT_8 rQueryBandWith;

		rStatus = kalIoctl(prGlueInfo, wlanoidQueryBandWidth,
				   &rQueryBandWith, sizeof(rQueryBandWith),
				   TRUE, FALSE, TRUE, FALSE,
				   &u4BufLen);

		if (rStatus == WLAN_STATUS_SUCCESS) {
			pos += scnprintf(buf + pos, u4TotalLen - pos,
						    "bandwidth = %d\n",rQueryBandWith);
		}
		else
			pos += scnprintf(buf + pos, u4TotalLen - pos,
						    "get bandwidth fail\n");
		break;
	}
	default:
		DBGLOG(REQ, WARN, "get string cmd:0x%x\n", u4SubCmd);
		return -EOPNOTSUPP;
	}

	DBGLOG(REQ, WARN, "%s i4BytesWritten = %d\n", __func__, pos);
	if (pos > 0) {

		if (pos > u4TotalLen)
			pos = u4TotalLen;
		prIwReqData->data.length = pos;	/* the iwpriv will use the length */

	} else if (pos == 0) {
		prIwReqData->data.length = pos;
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to search desired OID.
*
* \param rOid[in]               Desired NDIS_OID
* \param ppWlanReqEntry[out]    Found registered OID entry
*
* \retval TRUE: Matched OID is found
* \retval FALSE: No matched OID is found
*/
/*----------------------------------------------------------------------------*/
static BOOLEAN reqSearchSupportedOidEntry(IN UINT_32 rOid, OUT P_WLAN_REQ_ENTRY *ppWlanReqEntry)
{
	INT_32 i, j, k;

	i = 0;
	j = NUM_SUPPORTED_OIDS - 1;

	while (i <= j) {
		k = (i + j) / 2;

		if (rOid == arWlanOidReqTable[k].rOid) {
			*ppWlanReqEntry = &arWlanOidReqTable[k];
			return TRUE;
		} else if (rOid < arWlanOidReqTable[k].rOid) {
			j = k - 1;
		} else {
			i = k + 1;
		}
	}

	return FALSE;
}				/* reqSearchSupportedOidEntry */

#if 0
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to query the radio configuration used in IBSS
*        mode and RF test mode.
*
* \param[in] prGlueInfo         Pointer to the GLUE_INFO_T structure.
* \param[out] pvQueryBuffer     Pointer to the buffer that holds the result of the query.
* \param[in] u4QueryBufferLen   The length of the query buffer.
* \param[out] pu4QueryInfoLen   If the call is successful, returns the number of
*                               bytes written into the query buffer. If the call
*                               failed due to invalid length of the query buffer,
*                               returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
*/
/*----------------------------------------------------------------------------*/
static WLAN_STATUS
reqExtQueryConfiguration(IN P_GLUE_INFO_T prGlueInfo,
			 OUT PVOID pvQueryBuffer, IN UINT_32 u4QueryBufferLen, OUT PUINT_32 pu4QueryInfoLen)
{
	P_PARAM_802_11_CONFIG_T prQueryConfig = (P_PARAM_802_11_CONFIG_T) pvQueryBuffer;
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	UINT_32 u4QueryInfoLen = 0;

	DEBUGFUNC("wlanoidQueryConfiguration");

	ASSERT(prGlueInfo);
	ASSERT(pu4QueryInfoLen);

	*pu4QueryInfoLen = sizeof(PARAM_802_11_CONFIG_T);
	if (u4QueryBufferLen < sizeof(PARAM_802_11_CONFIG_T))
		return WLAN_STATUS_INVALID_LENGTH;

	ASSERT(pvQueryBuffer);

	kalMemZero(prQueryConfig, sizeof(PARAM_802_11_CONFIG_T));

	/* Update the current radio configuration. */
	prQueryConfig->u4Length = sizeof(PARAM_802_11_CONFIG_T);

#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidSetBeaconInterval,
			       &prQueryConfig->u4BeaconPeriod, sizeof(UINT_32), TRUE, TRUE, &u4QueryInfoLen);
#else
	rStatus = wlanQueryInformation(prGlueInfo->prAdapter,
				       wlanoidQueryBeaconInterval,
				       &prQueryConfig->u4BeaconPeriod, sizeof(UINT_32), &u4QueryInfoLen);
#endif
	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;
#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidQueryAtimWindow,
			       &prQueryConfig->u4ATIMWindow, sizeof(UINT_32), TRUE, TRUE, &u4QueryInfoLen);
#else
	rStatus = wlanQueryInformation(prGlueInfo->prAdapter,
				       wlanoidQueryAtimWindow,
				       &prQueryConfig->u4ATIMWindow, sizeof(UINT_32), &u4QueryInfoLen);
#endif
	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;
#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidQueryFrequency,
			       &prQueryConfig->u4DSConfig, sizeof(UINT_32), TRUE, TRUE, &u4QueryInfoLen);
#else
	rStatus = wlanQueryInformation(prGlueInfo->prAdapter,
				       wlanoidQueryFrequency,
				       &prQueryConfig->u4DSConfig, sizeof(UINT_32), &u4QueryInfoLen);
#endif
	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;

	prQueryConfig->rFHConfig.u4Length = sizeof(PARAM_802_11_CONFIG_FH_T);

	return rStatus;

}				/* end of reqExtQueryConfiguration() */

/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set the radio configuration used in IBSS
*        mode.
*
* \param[in] prGlueInfo     Pointer to the GLUE_INFO_T structure.
* \param[in] pvSetBuffer    A pointer to the buffer that holds the data to be set.
* \param[in] u4SetBufferLen The length of the set buffer.
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*                           bytes read from the set buffer. If the call failed
*                           due to invalid length of the set buffer, returns
*                           the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_LENGTH
* \retval WLAN_STATUS_NOT_ACCEPTED
*/
/*----------------------------------------------------------------------------*/
static WLAN_STATUS
reqExtSetConfiguration(IN P_GLUE_INFO_T prGlueInfo,
		       IN PVOID pvSetBuffer, IN UINT_32 u4SetBufferLen, OUT PUINT_32 pu4SetInfoLen)
{
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	P_PARAM_802_11_CONFIG_T prNewConfig = (P_PARAM_802_11_CONFIG_T) pvSetBuffer;
	UINT_32 u4SetInfoLen = 0;

	DEBUGFUNC("wlanoidSetConfiguration");

	ASSERT(prGlueInfo);
	ASSERT(pu4SetInfoLen);

	*pu4SetInfoLen = sizeof(PARAM_802_11_CONFIG_T);

	if (u4SetBufferLen < *pu4SetInfoLen)
		return WLAN_STATUS_INVALID_LENGTH;

	/* OID_802_11_CONFIGURATION. If associated, NOT_ACCEPTED shall be returned. */
	if (prGlueInfo->eParamMediaStateIndicated == PARAM_MEDIA_STATE_CONNECTED)
		return WLAN_STATUS_NOT_ACCEPTED;

	ASSERT(pvSetBuffer);

#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidSetBeaconInterval,
			       &prNewConfig->u4BeaconPeriod, sizeof(UINT_32), FALSE, TRUE, &u4SetInfoLen);
#else
	rStatus = wlanSetInformation(prGlueInfo->prAdapter,
				     wlanoidSetBeaconInterval,
				     &prNewConfig->u4BeaconPeriod, sizeof(UINT_32), &u4SetInfoLen);
#endif
	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;
#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidSetAtimWindow,
			       &prNewConfig->u4ATIMWindow, sizeof(UINT_32), FALSE, TRUE, &u4SetInfoLen);
#else
	rStatus = wlanSetInformation(prGlueInfo->prAdapter,
				     wlanoidSetAtimWindow, &prNewConfig->u4ATIMWindow, sizeof(UINT_32), &u4SetInfoLen);
#endif
	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;
#if defined(_HIF_SDIO)
	rStatus = sdio_io_ctrl(prGlueInfo,
			       wlanoidSetFrequency,
			       &prNewConfig->u4DSConfig, sizeof(UINT_32), FALSE, TRUE, &u4SetInfoLen);
#else
	rStatus = wlanSetInformation(prGlueInfo->prAdapter,
				     wlanoidSetFrequency, &prNewConfig->u4DSConfig, sizeof(UINT_32), &u4SetInfoLen);
#endif

	if (rStatus != WLAN_STATUS_SUCCESS)
		return rStatus;

	return rStatus;

}				/* end of reqExtSetConfiguration() */

#endif
/*----------------------------------------------------------------------------*/
/*!
* \brief This routine is called to set beacon detection function enable/disable state
*        This is mainly designed for usage under BT inquiry state (disable function).
*
* \param[in] pvAdapter Pointer to the Adapter structure
* \param[in] pvSetBuffer A pointer to the buffer that holds the data to be set
* \param[in] u4SetBufferLen The length of the set buffer
* \param[out] pu4SetInfoLen If the call is successful, returns the number of
*   bytes read from the set buffer. If the call failed due to invalid length of
*   the set buffer, returns the amount of storage needed.
*
* \retval WLAN_STATUS_SUCCESS
* \retval WLAN_STATUS_INVALID_DATA If new setting value is wrong.
* \retval WLAN_STATUS_INVALID_LENGTH
*
*/
/*----------------------------------------------------------------------------*/
static WLAN_STATUS
reqExtSetAcpiDevicePowerState(IN P_GLUE_INFO_T prGlueInfo,
			      IN PVOID pvSetBuffer, IN UINT_32 u4SetBufferLen, OUT PUINT_32 pu4SetInfoLen)
{
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;

	ASSERT(prGlueInfo);
	ASSERT(pvSetBuffer);
	ASSERT(pu4SetInfoLen);

	/* WIFI is enabled, when ACPI is D0 (ParamDeviceStateD0 = 1). And vice versa */

	/* rStatus = wlanSetInformation(prGlueInfo->prAdapter, */
	/* wlanoidSetAcpiDevicePowerState, */
	/* pvSetBuffer, */
	/* u4SetBufferLen, */
	/* pu4SetInfoLen); */
	return rStatus;
}

int priv_driver_set_chip_config(IN struct net_device *prNetDev, IN char *pcCommand, IN int i4TotalLen)
{
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	P_GLUE_INFO_T prGlueInfo = NULL;
	P_ADAPTER_T prAdapter = NULL;
	UINT_32 u4BufLen = 0;
	INT_32 i4BytesWritten = 0;
	UINT_32 u4CmdLen = 0;
	UINT_32 u4PrefixLen = 0;
	/* INT_32 i4Argc = 0; */
	/* PCHAR  apcArgv[WLAN_CFG_ARGV_MAX] = {0}; */

	PARAM_CUSTOM_CHIP_CONFIG_STRUCT_T rChipConfigInfo;

	ASSERT(prNetDev);
	if (FALSE == GLUE_CHK_PR2(prNetDev, pcCommand))
		return -1;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	prAdapter = prGlueInfo->prAdapter;
	DBGLOG(REQ, INFO, "priv_driver_set_chip_config command is %s\n", pcCommand);
	/* wlanCfgParseArgument(pcCommand, &i4Argc, apcArgv); */
	/* DBGLOG(REQ, LOUD,("argc is %i\n",i4Argc)); */
	/*  */
	u4CmdLen = kalStrnLen(pcCommand, i4TotalLen);
	u4PrefixLen = kalStrLen(CMD_SET_CHIP) + 1 /*space */;

	kalMemZero(&rChipConfigInfo, sizeof(rChipConfigInfo));

	/* if(i4Argc >= 2) { */
	if (u4CmdLen > u4PrefixLen) {

		rChipConfigInfo.ucType = CHIP_CONFIG_TYPE_WO_RESPONSE;
		/* rChipConfigInfo.u2MsgSize = kalStrnLen(apcArgv[1],CHIP_CONFIG_RESP_SIZE); */
		rChipConfigInfo.u2MsgSize = u4CmdLen - u4PrefixLen;
		/* kalStrnCpy(rChipConfigInfo.aucCmd,apcArgv[1],CHIP_CONFIG_RESP_SIZE); */
		if (u4PrefixLen <= CHIP_CONFIG_RESP_SIZE) {
			kalStrnCpy(rChipConfigInfo.aucCmd, pcCommand + u4PrefixLen,
				   CHIP_CONFIG_RESP_SIZE - u4PrefixLen);

			rStatus = kalIoctl(prGlueInfo,
					   wlanoidSetChipConfig,
					   &rChipConfigInfo,
					   sizeof(rChipConfigInfo), FALSE, FALSE, TRUE, TRUE, &u4BufLen);
		} else {

			DBGLOG(REQ, INFO, "%s: kalIoctl Command Len > %d\n", __func__, CHIP_CONFIG_RESP_SIZE);
			rStatus = WLAN_STATUS_FAILURE;
		}

		if (rStatus != WLAN_STATUS_SUCCESS) {
			DBGLOG(REQ, INFO, "%s: kalIoctl ret=%d\n", __func__, rStatus);
			i4BytesWritten = -1;
		}
	}

	return i4BytesWritten;

}

int priv_driver_set_miracast(IN struct net_device *prNetDev, IN char *pcCommand, IN int i4TotalLen)
{
	P_ADAPTER_T prAdapter = NULL;
	P_GLUE_INFO_T prGlueInfo = NULL;
	UINT_32 i4BytesWritten = 0;
	/* WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS; */
	/* UINT_32 u4BufLen = 0; */
	INT_32 i4Argc = 0;
	UINT_32 ucMode = 0;
	P_WFD_CFG_SETTINGS_T prWfdCfgSettings = (P_WFD_CFG_SETTINGS_T) NULL;
	P_MSG_WFD_CONFIG_SETTINGS_CHANGED_T prMsgWfdCfgUpdate = (P_MSG_WFD_CONFIG_SETTINGS_CHANGED_T) NULL;
	PCHAR apcArgv[WLAN_CFG_ARGV_MAX];
	INT_32 u4Ret;

	ASSERT(prNetDev);
	if (FALSE == GLUE_CHK_PR2(prNetDev, pcCommand))
		return -1;

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	DBGLOG(REQ, LOUD, "command is %s\n", pcCommand);
	wlanCfgParseArgument(pcCommand, &i4Argc, apcArgv);
	DBGLOG(REQ, LOUD, "argc is %i\n", i4Argc);

	prAdapter = prGlueInfo->prAdapter;
	if (i4Argc >= 2) {
		u4Ret = kalkStrtou32(apcArgv[1], 0, &ucMode); /* ucMode = kalStrtoul(apcArgv[1], NULL, 0); */
		if (u4Ret)
			DBGLOG(REQ, LOUD, "parse pcCommand error u4Ret=%d\n", u4Ret);

		if (g_ucMiracastMode == ucMode)
			;
			/* XXX: continue or skip */

		g_ucMiracastMode = ucMode;
		prMsgWfdCfgUpdate = cnmMemAlloc(prAdapter, RAM_TYPE_MSG, sizeof(MSG_WFD_CONFIG_SETTINGS_CHANGED_T));

		if (prMsgWfdCfgUpdate != NULL) {

			prWfdCfgSettings = &(prGlueInfo->prAdapter->rWifiVar.prP2pFsmInfo->rWfdConfigureSettings);
			prMsgWfdCfgUpdate->rMsgHdr.eMsgId = MID_MNY_P2P_WFD_CFG_UPDATE;
			prMsgWfdCfgUpdate->prWfdCfgSettings = prWfdCfgSettings;

			if (ucMode == MIRACAST_MODE_OFF) {
				prWfdCfgSettings->ucWfdEnable = 0;
				snprintf(pcCommand, i4TotalLen, CMD_SET_CHIP " mira 0");
			} else if (ucMode == MIRACAST_MODE_SOURCE) {
				prWfdCfgSettings->ucWfdEnable = 1;
				snprintf(pcCommand, i4TotalLen, CMD_SET_CHIP " mira 1");
			} else if (ucMode == MIRACAST_MODE_SINK) {
				prWfdCfgSettings->ucWfdEnable = 2;
				snprintf(pcCommand, i4TotalLen, CMD_SET_CHIP " mira 2");
			} else {
				prWfdCfgSettings->ucWfdEnable = 0;
				snprintf(pcCommand, i4TotalLen, CMD_SET_CHIP " mira 0");
			}
			mboxSendMsg(prAdapter, MBOX_ID_0, (P_MSG_HDR_T) prMsgWfdCfgUpdate, MSG_SEND_METHOD_BUF);

			priv_driver_set_chip_config(prNetDev, pcCommand, i4TotalLen);

		} /* prMsgWfdCfgUpdate */
		else {
			ASSERT(FALSE);
			i4BytesWritten = -1;
		}
	}

	/* i4Argc */
	return i4BytesWritten;
}
static int priv_driver_get_1xtx_status(IN struct net_device *prNetDev,
	IN char *pcCommand, IN int i4TotalLen)
{
	P_GLUE_INFO_T prGlueInfo = NULL;
	INT_32	i4BytesWritten = 0;
	UINT_32 u4BufLen = 0;
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	ENUM_TX_RESULT_CODE_T rM2TxDoneStatus;

	if (!pcCommand)
		return -EFAULT;
	DBGLOG(REQ, TRACE, "command is %s\n", pcCommand);

	prGlueInfo = *((struct _GLUE_INFO_T **) netdev_priv(prNetDev));
	if (!prGlueInfo)
		return -EFAULT;

	rStatus = kalIoctl(prGlueInfo, wlanoidQueryR1xTxDoneStatus,
			   &rM2TxDoneStatus, sizeof(rM2TxDoneStatus),
			   FALSE, FALSE, TRUE, FALSE,
			   &u4BufLen);
	if (rStatus != WLAN_STATUS_SUCCESS) {
		DBGLOG(REQ, WARN, "fail to get rM2TxDoneStatus = %d\n", rM2TxDoneStatus);
		return -1;
	}
	DBGLOG(REQ, TRACE, "set r1xtxDoneStatus %d\n", rM2TxDoneStatus);
	i4BytesWritten = kalSnprintf(pcCommand, i4TotalLen, "r1xTxDoneStatus is %d\n", rM2TxDoneStatus);

	return i4BytesWritten;
}

static int priv_driver_test_1xtx_status(IN struct net_device *prNetDev,
	IN char *pcCommand, IN int i4TotalLen)

{
	P_GLUE_INFO_T prGlueInfo = NULL;
	P_ADAPTER_T prAdapter = NULL;
	INT_32 i4BytesWritten = 0;
	INT_32 i4Argc = 0;
	PCHAR apcArgv[WLAN_CFG_ARGV_MAX] = { 0 };
	INT_32 i4Ret = 0;
	INT_8 ucTest1xTxStatus;
	UINT_32 u4BufLen = 0;
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;
	INT_8 fgIsTest1xTx;

	prGlueInfo = *((struct _GLUE_INFO_T **) netdev_priv(prNetDev));
	if (!prGlueInfo)
		return -EFAULT;

	if (!pcCommand)
		return -EFAULT;

	DBGLOG(REQ, TRACE, "command is %s\n", pcCommand);
	wlanCfgParseArgument(pcCommand, &i4Argc, apcArgv);
	DBGLOG(REQ, TRACE, "i4Argc is %d\n", i4Argc);

	if (i4Argc != 2) {
		i4BytesWritten += scnprintf(pcCommand + i4BytesWritten,
			i4TotalLen - i4BytesWritten,
			"\nformat:test_1xtx_status [0|1]");
		return i4BytesWritten;
	}

	i4Ret = kstrtou8(apcArgv[1], 0, &ucTest1xTxStatus);
	if (i4Ret) {
		DBGLOG(REQ, ERROR, "parse test_1xtx_status error i4Ret=%d\n", i4Ret);
		return -EFAULT;
	}

	fgIsTest1xTx = ucTest1xTxStatus;
	rStatus = kalIoctl(prGlueInfo, wlanoidSetR1xTxDoneStatus,
			   &fgIsTest1xTx, sizeof(fgIsTest1xTx),
			   FALSE, FALSE, TRUE, FALSE,
			   &u4BufLen);
	if (rStatus != WLAN_STATUS_SUCCESS) {
		DBGLOG(REQ, WARN, "fail to set r1xtxDoneStatus\n");
		return -1;
	}

	return i4BytesWritten;
}

int priv_support_driver_cmd(IN struct net_device *prNetDev, IN OUT struct ifreq *prReq, IN int i4Cmd)
{
	P_GLUE_INFO_T prGlueInfo = NULL;
	int ret = 0;
	char *pcCommand = NULL;
	priv_driver_cmd_t *priv_cmd = NULL;
	int i4BytesWritten = 0;
	int i4TotalLen = 0;

	if (!prReq->ifr_data) {
		ret = -EINVAL;
		goto exit;
	}

	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	if (!prGlueInfo) {
		DBGLOG(REQ, WARN, "No glue info\n");
		ret = -EFAULT;
		goto exit;
	}
	if (prGlueInfo->u4ReadyFlag == 0) {
		ret = -EINVAL;
		goto exit;
	}

	priv_cmd = kzalloc(sizeof(priv_driver_cmd_t), GFP_KERNEL);
	if (!priv_cmd) {
		DBGLOG(REQ, WARN, "%s, alloc mem failed\n", __func__);
		return -ENOMEM;
	}

	if (copy_from_user(priv_cmd, prReq->ifr_data, sizeof(priv_driver_cmd_t))) {
		DBGLOG(REQ, INFO, "%s: copy_from_user fail\n", __func__);
		ret = -EFAULT;
		goto exit;
	}

	i4TotalLen = priv_cmd->total_len;

	if (i4TotalLen <= 0 || i4TotalLen > PRIV_CMD_SIZE) {
		ret = -EINVAL;
		DBGLOG(REQ, INFO, "%s: i4TotalLen invalid\n", __func__);
		goto exit;
	}

	pcCommand = priv_cmd->buf;

	DBGLOG(REQ, INFO, "%s: driver cmd \"%s\" on %s\n", __func__, pcCommand, prReq->ifr_name);

	i4BytesWritten = priv_driver_cmds(prNetDev, pcCommand, i4TotalLen);

	if (i4BytesWritten < 0) {
		DBGLOG(REQ, INFO, "%s: command %s failed; Written is %d\n",
			__func__, pcCommand, i4BytesWritten);
		ret = -EFAULT;
	}

exit:
	kfree(priv_cmd);

	return ret;
}

#if CFG_SUPPORT_BATCH_SCAN
#define CMD_BATCH_SET           "WLS_BATCHING SET"
#define CMD_BATCH_GET           "WLS_BATCHING GET"
#define CMD_BATCH_STOP          "WLS_BATCHING STOP"
#endif

#if CFG_SUPPORT_GET_CH_ENV
#define CMD_CH_ENV_GET			"CH_ENV_GET"
#endif

#if CFG_SUPPORT_802_11K
#define CMD_NEIGHBOR_REQUEST    "NEIGHBOR-REQUEST"
#endif
#if CFG_SUPPORT_802_11V_BSS_TRANSITION_MGT
#define CMD_BSS_TRANSITION_QUERY    "BSS-TRANSITION-QUERY"
#endif


INT_32 priv_driver_cmds(IN struct net_device *prNetDev, IN PCHAR pcCommand, IN INT_32 i4TotalLen)
{
	P_GLUE_INFO_T prGlueInfo = NULL;
	INT_32 i4BytesWritten = 0;
	INT_32 i4CmdFound = 0;

	if (FALSE == GLUE_CHK_PR2(prNetDev, pcCommand))
		return -1;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));

	if (i4CmdFound == 0) {
		i4CmdFound = 1;

		if (strncasecmp(pcCommand, CMD_MIRACAST, strlen(CMD_MIRACAST)) == 0)
			i4BytesWritten = priv_driver_set_miracast(prNetDev, pcCommand, i4TotalLen);
#if CFG_SUPPORT_BATCH_SCAN
		else if (strncasecmp(pcCommand, CMD_BATCH_SET, strlen(CMD_BATCH_SET)) == 0) {
			kalIoctl(prGlueInfo,
				 wlanoidSetBatchScanReq,
				 (PVOID) pcCommand, i4TotalLen, FALSE, FALSE, TRUE, FALSE, &i4BytesWritten);
		} else if (strncasecmp(pcCommand, CMD_BATCH_GET, strlen(CMD_BATCH_GET)) == 0) {
			/* strcpy(pcCommand, "BATCH SCAN DATA FROM FIRMWARE"); */
			/* i4BytesWritten = strlen("BATCH SCAN DATA FROM FIRMWARE") + 1; */
			/* i4BytesWritten = priv_driver_get_linkspeed (prNetDev, pcCommand, i4TotalLen); */

			UINT_32 u4BufLen;
			int i;
			/* int rlen=0; */

			for (i = 0; i < CFG_BATCH_MAX_MSCAN; i++) {
				g_rEventBatchResult[i].ucScanCount = i + 1;	/* for get which mscan */
				kalIoctl(prGlueInfo,
					 wlanoidQueryBatchScanResult,
					 (PVOID)&g_rEventBatchResult[i],
					 sizeof(EVENT_BATCH_RESULT_T), TRUE, TRUE, TRUE, FALSE, &u4BufLen);
			}

#if 0
			DBGLOG(SCN, INFO, "Batch Scan Results, scan count = %u\n", g_rEventBatchResult.ucScanCount);
			for (i = 0; i < g_rEventBatchResult.ucScanCount; i++) {
				prEntry = &g_rEventBatchResult.arBatchResult[i];
				DBGLOG(SCN, INFO, "Entry %u\n", i);
				DBGLOG(SCN, INFO, "	 BSSID = %pM\n", prEntry->aucBssid);
				DBGLOG(SCN, INFO, "	 SSID = %s\n", prEntry->aucSSID);
				DBGLOG(SCN, INFO, "	 SSID len = %u\n", prEntry->ucSSIDLen);
				DBGLOG(SCN, INFO, "	 RSSI = %d\n", prEntry->cRssi);
				DBGLOG(SCN, INFO, "	 Freq = %u\n", prEntry->ucFreq);
			}
#endif

			batchConvertResult(&g_rEventBatchResult[0], pcCommand, i4TotalLen, &i4BytesWritten);

			/* Dump for debug */
			/* print_hex_dump(KERN_INFO, "BATCH", DUMP_PREFIX_ADDRESS, 16, 1, pcCommand,
			i4BytesWritten, TRUE); */

		} else if (strnicmp(pcCommand, CMD_BATCH_STOP, strlen(CMD_BATCH_STOP)) == 0) {
			kalIoctl(prGlueInfo,
				 wlanoidSetBatchScanReq,
				 (PVOID) pcCommand, i4TotalLen, FALSE, FALSE, TRUE, FALSE, &i4BytesWritten);
		}
#endif
#if CFG_SUPPORT_GET_CH_ENV
		else if (strncasecmp(pcCommand, CMD_CH_ENV_GET, strlen(CMD_CH_ENV_GET)) == 0)
			scanEnvResult(prGlueInfo, pcCommand, i4TotalLen, &i4BytesWritten);
#endif

#if 0

		else if (strnicmp(pcCommand, CMD_RSSI, strlen(CMD_RSSI)) == 0) {
			/* i4BytesWritten = wl_android_get_rssi(net, command, i4TotalLen); */
		} else if (strnicmp(pcCommand, CMD_LINKSPEED, strlen(CMD_LINKSPEED)) == 0) {
			i4BytesWritten = priv_driver_get_linkspeed(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_PNOSSIDCLR_SET, strlen(CMD_PNOSSIDCLR_SET)) == 0) {
			/* Do nothing */
		} else if (strnicmp(pcCommand, CMD_PNOSETUP_SET, strlen(CMD_PNOSETUP_SET)) == 0) {
			/* Do nothing */
		} else if (strnicmp(pcCommand, CMD_PNOENABLE_SET, strlen(CMD_PNOENABLE_SET)) == 0) {
			/* Do nothing */
		} else if (strnicmp(pcCommand, CMD_SETSUSPENDOPT, strlen(CMD_SETSUSPENDOPT)) == 0) {
			/* i4BytesWritten = wl_android_set_suspendopt(net, pcCommand, i4TotalLen); */
		} else if (strnicmp(pcCommand, CMD_SETSUSPENDMODE, strlen(CMD_SETSUSPENDMODE)) == 0) {
			i4BytesWritten = priv_driver_set_suspend_mode(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_SETBAND, strlen(CMD_SETBAND)) == 0) {
			i4BytesWritten = priv_driver_set_band(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_GETBAND, strlen(CMD_GETBAND)) == 0) {
			/* i4BytesWritten = wl_android_get_band(net, pcCommand, i4TotalLen); */
		} else if (strnicmp(pcCommand, CMD_COUNTRY, strlen(CMD_COUNTRY)) == 0) {
			i4BytesWritten = priv_driver_set_country(prNetDev, pcCommand, i4TotalLen);
		}
		/* Mediatek private command  */
		else if (strnicmp(pcCommand, CMD_SET_SW_CTRL, strlen(CMD_SET_SW_CTRL)) == 0) {
			i4BytesWritten = priv_driver_set_sw_ctrl(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_GET_SW_CTRL, strlen(CMD_GET_SW_CTRL)) == 0) {
			i4BytesWritten = priv_driver_get_sw_ctrl(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_SET_CFG, strlen(CMD_SET_CFG)) == 0) {
			i4BytesWritten = priv_driver_set_cfg(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_GET_CFG, strlen(CMD_GET_CFG)) == 0) {
			i4BytesWritten = priv_driver_get_cfg(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_SET_CHIP, strlen(CMD_SET_CHIP)) == 0) {
			i4BytesWritten = priv_driver_set_chip_config(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_GET_CHIP, strlen(CMD_GET_CHIP)) == 0) {
			i4BytesWritten = priv_driver_get_chip_config(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_SET_DBG_LEVEL, strlen(CMD_SET_DBG_LEVEL)) == 0) {
			i4BytesWritten = priv_driver_set_dbg_level(prNetDev, pcCommand, i4TotalLen);
		} else if (strnicmp(pcCommand, CMD_GET_DBG_LEVEL, strlen(CMD_GET_DBG_LEVEL)) == 0) {
			i4BytesWritten = priv_driver_get_dbg_level(prNetDev, pcCommand, i4TotalLen);
		}
#if CFG_SUPPORT_BATCH_SCAN
		else if (strnicmp(pcCommand, CMD_BATCH_SET, strlen(CMD_BATCH_SET)) == 0) {
			kalIoctl(prGlueInfo,
				 wlanoidSetBatchScanReq,
				 (PVOID) pcCommand, i4TotalLen, FALSE, FALSE, TRUE, &i4BytesWritten);
		} else if (strnicmp(pcCommand, CMD_BATCH_GET, strlen(CMD_BATCH_GET)) == 0) {
			/* strcpy(pcCommand, "BATCH SCAN DATA FROM FIRMWARE"); */
			/* i4BytesWritten = strlen("BATCH SCAN DATA FROM FIRMWARE") + 1; */
			/* i4BytesWritten = priv_driver_get_linkspeed (prNetDev, pcCommand, i4TotalLen); */

			UINT_32 u4BufLen;
			int i;
			/* int rlen=0; */

			for (i = 0; i < CFG_BATCH_MAX_MSCAN; i++) {
				g_rEventBatchResult[i].ucScanCount = i + 1;	/* for get which mscan */
				kalIoctl(prGlueInfo,
					 wlanoidQueryBatchScanResult,
					 (PVOID)&g_rEventBatchResult[i],
					 sizeof(EVENT_BATCH_RESULT_T), TRUE, TRUE, TRUE, &u4BufLen);
			}

#if 0
			DBGLOG(SCN, INFO, "Batch Scan Results, scan count = %u\n", g_rEventBatchResult.ucScanCount);
			for (i = 0; i < g_rEventBatchResult.ucScanCount; i++) {
				prEntry = &g_rEventBatchResult.arBatchResult[i];
				DBGLOG(SCN, INFO, "Entry %u\n", i);
				DBGLOG(SCN, INFO, "	 BSSID = %pM\n", prEntry->aucBssid);
				DBGLOG(SCN, INFO, "	 SSID = %s\n", prEntry->aucSSID);
				DBGLOG(SCN, INFO, "	 SSID len = %u\n", prEntry->ucSSIDLen);
				DBGLOG(SCN, INFO, "	 RSSI = %d\n", prEntry->cRssi);
				DBGLOG(SCN, INFO, "	 Freq = %u\n", prEntry->ucFreq);
			}
#endif

			batchConvertResult(&g_rEventBatchResult[0], pcCommand, i4TotalLen, &i4BytesWritten);

			/* Dump for debug */
			/* print_hex_dump(KERN_INFO, "BATCH", DUMP_PREFIX_ADDRESS, 16, 1, pcCommand, i4BytesWritten,
			TRUE); */

		} else if (strnicmp(pcCommand, CMD_BATCH_STOP, strlen(CMD_BATCH_STOP)) == 0) {
			kalIoctl(prGlueInfo,
				 wlanoidSetBatchScanReq,
				 (PVOID) pcCommand, i4TotalLen, FALSE, FALSE, TRUE, &i4BytesWritten);
		}
#endif

#endif
		else if (strncasecmp(pcCommand, CMD_GET_1XTX_STATUS, strlen(CMD_GET_1XTX_STATUS)) == 0) {
				i4BytesWritten = priv_driver_get_1xtx_status(prNetDev, pcCommand, i4TotalLen);
		} else if (strncasecmp(pcCommand, CMD_TEST_1XTX_STATUS, strlen(CMD_TEST_1XTX_STATUS)) == 0) {
				i4BytesWritten = priv_driver_test_1xtx_status(prNetDev, pcCommand, i4TotalLen);
		}
		else
			i4CmdFound = 0;
	}

	/* i4CmdFound */
	if (i4CmdFound == 0)
		DBGLOG(REQ, INFO, "Unknown driver command %s - ignored\n", pcCommand);

	if (i4BytesWritten >= 0) {
		if ((i4BytesWritten == 0) && (i4TotalLen > 0)) {
			/* reset the command buffer */
			pcCommand[0] = '\0';
		}

		if (i4BytesWritten >= i4TotalLen) {
			DBGLOG(REQ, INFO,
			       "%s: i4BytesWritten %d > i4TotalLen < %d\n", __func__, i4BytesWritten, i4TotalLen);
			i4BytesWritten = i4TotalLen;
		} else {
			pcCommand[i4BytesWritten] = '\0';
			i4BytesWritten++;
		}
	}

	return i4BytesWritten;

}

static int compat_priv(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra,
	     int (*priv_func)(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra))
{
	struct iw_point *prIwp;
	int ret = 0;
#ifdef CONFIG_COMPAT
	struct compat_iw_point *iwp_compat = NULL;
	struct iw_point iwp;
#endif

	if (!prIwReqData)
		return -EINVAL;

#ifdef CONFIG_COMPAT
	if (prIwReqInfo->flags & IW_REQUEST_FLAG_COMPAT) {
		iwp_compat = (struct compat_iw_point *) &prIwReqData->data;
		iwp.pointer = compat_ptr(iwp_compat->pointer);
		iwp.length = iwp_compat->length;
		iwp.flags = iwp_compat->flags;
		prIwp = &iwp;
	} else
#endif
	prIwp = &prIwReqData->data;


	ret = priv_func(prNetDev, prIwReqInfo, (union iwreq_data *)prIwp, pcExtra);

#ifdef CONFIG_COMPAT
	if (prIwReqInfo->flags & IW_REQUEST_FLAG_COMPAT) {
		iwp_compat->pointer = ptr_to_compat(iwp.pointer);
		iwp_compat->length = iwp.length;
		iwp_compat->flags = iwp.flags;
	}
#endif
	return ret;
}

int
priv_set_int(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_set_int);
}

int
priv_get_int(IN struct net_device *prNetDev,
	     IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_get_int);
}

int
priv_set_ints(IN struct net_device *prNetDev,
	      IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_set_ints);
}

int
priv_get_ints(IN struct net_device *prNetDev,
	      IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_get_ints);
}

int
priv_set_struct(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_set_struct);
}

int
priv_get_struct(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	return compat_priv(prNetDev, prIwReqInfo, prIwReqData, pcExtra, _priv_get_struct);
}

int
priv_set_string(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN char *pcExtra)
{
	return _priv_set_string(prNetDev, prIwReqInfo, prIwReqData, pcExtra);
}

/*----------------------------------------------------------------------------*/
/*!
* \brief Private ioctl driver handler.
*
* \param[in] pDev Net device requested.
* \param[out] pIwReq Pointer to iwreq structure.
* \param[in] cmd Private sub-command.
*
* \retval 0 For success.
* \retval -EFAULT If copy from user space buffer fail.
* \retval -EOPNOTSUPP Parameter "cmd" not recognized.
*
*/
/*----------------------------------------------------------------------------*/
int
priv_set_driver(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	UINT_32 u4SubCmd = 0;
	UINT_16 u2Cmd = 0;

	P_GLUE_INFO_T prGlueInfo = NULL;
	INT_32 i4BytesWritten = 0;

	ASSERT(prNetDev);
	ASSERT(prIwReqData);
	if (!prNetDev || !prIwReqData) {
		DBGLOG(REQ, INFO, "priv_set_driver(): invalid param(0x%p, 0x%p)\n", prNetDev, prIwReqData);
		return -EINVAL;
	}

	u2Cmd = prIwReqInfo->cmd;
	DBGLOG(REQ, TRACE, "prIwReqInfo->cmd %u\n", u2Cmd);

	u4SubCmd = (UINT_32) prIwReqData->data.flags;
	prGlueInfo = *((P_GLUE_INFO_T *) netdev_priv(prNetDev));
	ASSERT(prGlueInfo);
	if (!prGlueInfo) {
		DBGLOG(REQ, INFO, "priv_set_driver(): invalid prGlueInfo(0x%p, 0x%p)\n",
				   prNetDev, *((P_GLUE_INFO_T *) netdev_priv(prNetDev)));
		return -EINVAL;
	}

	/* trick,hack in ./net/wireless/wext-priv.c ioctl_private_iw_point */
	/* because the cmd number is odd (get), the input string will not be copy_to_user */

	DBGLOG(REQ, TRACE, "prIwReqData->data.length %u\n", prIwReqData->data.length);

	/* Use GET type becauase large data by iwpriv. */

	ASSERT(IW_IS_GET(u2Cmd));
	if (prIwReqData->data.length != 0) {
		if (!access_ok(VERIFY_READ, prIwReqData->data.pointer, prIwReqData->data.length)) {
			DBGLOG(REQ, INFO, "%s access_ok Read fail written = %d\n", __func__, i4BytesWritten);
			return -EFAULT;
		}
		if (copy_from_user(pcExtra, prIwReqData->data.pointer, prIwReqData->data.length)) {
			DBGLOG(REQ, INFO,
			       "%s copy_form_user fail written = %d\n", __func__, prIwReqData->data.length);
			return -EFAULT;
		}
	}

	if (pcExtra) {
		pcExtra[2000] = '\0';
		DBGLOG(REQ, INFO, "pcExtra %s\n", pcExtra);
		/* Please check max length in rIwPrivTable */
		DBGLOG(REQ, TRACE, "%s prIwReqData->data.length = %d\n", __func__, prIwReqData->data.length);
		i4BytesWritten = priv_driver_cmds(prNetDev, pcExtra, 2000 /*prIwReqData->data.length */);
		DBGLOG(REQ, TRACE, "%s i4BytesWritten = %d\n", __func__, i4BytesWritten);
	}

	DBGLOG(REQ, TRACE, "pcExtra done\n");

	if (i4BytesWritten > 0) {

		if (i4BytesWritten > 2000)
			i4BytesWritten = 2000;
		prIwReqData->data.length = i4BytesWritten;	/* the iwpriv will use the length */

	} else if (i4BytesWritten == 0) {
		prIwReqData->data.length = i4BytesWritten;
	}

	return 0;

}


int
priv_get_string(IN struct net_device *prNetDev,
		IN struct iw_request_info *prIwReqInfo, IN union iwreq_data *prIwReqData, IN OUT char *pcExtra)
{
	return _priv_get_string(prNetDev, prIwReqInfo, prIwReqData, pcExtra);
}

