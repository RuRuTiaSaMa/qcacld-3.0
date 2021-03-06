# We can build either as part of a standalone Kernel build or as
# an external module.  Determine which mechanism is being used
ifeq ($(MODNAME),)
	KERNEL_BUILD := 1
else
	KERNEL_BUILD := 0
endif

ifeq ($(CONFIG_CNSS), y)
ifndef CONFIG_ROME_IF
	#use pci as default interface
	CONFIG_ROME_IF = pci
endif
endif

ifeq ($(KERNEL_BUILD),1)
	# These are provided in external module based builds
	# Need to explicitly define for Kernel-based builds
	MODNAME := wlan
	WLAN_ROOT := drivers/staging/qcacld-3.0
endif

# Make WLAN as open-source driver by default
WLAN_OPEN_SOURCE := 1

ifeq ($(KERNEL_BUILD), 0)
	# These are configurable via Kconfig for kernel-based builds
	# Need to explicitly configure for Android-based builds

	ifeq ($(CONFIG_ARCH_MDM9630), y)
	CONFIG_MOBILE_ROUTER := y
	endif

	ifeq ($(CONFIG_ARCH_MDM9640), y)
	CONFIG_MOBILE_ROUTER := y
	endif

	#Flag to enable Legacy Fast Roaming3(LFR3)
	CONFIG_QCACLD_WLAN_LFR3 := y

	#JB kernel has PMKSA patches, hence enabling this flag
	CONFIG_PRIMA_WLAN_OKC := y

	# JB kernel has CPU enablement patches, so enable
	ifeq ($(CONFIG_ROME_IF),pci)
		CONFIG_PRIMA_WLAN_11AC_HIGH_TP := y
	endif
	ifeq ($(CONFIG_ROME_IF),usb)
		CONFIG_PRIMA_WLAN_11AC_HIGH_TP := n
	endif
	ifeq ($(CONFIG_ROME_IF),sdio)
		CONFIG_PRIMA_WLAN_11AC_HIGH_TP := n
	endif

	ifneq ($(CONFIG_MOBILE_ROUTER), y)
	#Flag to enable TDLS feature
	CONFIG_QCOM_TDLS := y
	endif

	ifeq ($(CONFIG_MOBILE_ROUTER), y)
	CONFIG_QCACLD_FEATURE_GREEN_AP := y
	endif

	#Flag to enable Fast Transition (11r) feature
	CONFIG_QCOM_VOWIFI_11R := y

	ifneq ($(CONFIG_QCA_CLD_WLAN),)
	        ifeq ($(CONFIG_CNSS),y)
		#Flag to enable Protected Managment Frames (11w) feature
		CONFIG_WLAN_FEATURE_11W := y
		#Flag to enable LTE CoEx feature
		CONFIG_QCOM_LTE_COEX := y
			ifneq ($(CONFIG_MOBILE_ROUTER), y)
			#Flag to enable LPSS feature
			CONFIG_WLAN_FEATURE_LPSS := y
			endif
		endif
	endif


        #Flag to enable Protected Managment Frames (11w) feature
        ifeq ($(CONFIG_ROME_IF),usb)
                CONFIG_WLAN_FEATURE_11W := y
        endif
        ifeq ($(CONFIG_ROME_IF),sdio)
                CONFIG_WLAN_FEATURE_11W := y
        endif

	ifneq ($(CONFIG_MOBILE_ROUTER), y)
		#Flag to enable NAN
		CONFIG_QCACLD_FEATURE_NAN := y
	endif

        #Flag to enable Linux QCMBR feature as default feature
        ifeq ($(CONFIG_ROME_IF),usb)
                CONFIG_LINUX_QCMBR :=y
        endif

        ifeq ($(CONFIG_CNSS_EOS),y)
        CONFIG_FEATURE_BMI_2 :=y
        endif

	CONFIG_MPC_UT_FRAMEWORK := y

	#Flag to enable offload packets feature
	CONFIG_WLAN_OFFLOAD_PACKETS := y

	#Flag to enable memdump feature
	CONFIG_WLAN_FEATURE_MEMDUMP := y

	#Flag to enable Fast Path feature
	CONFIG_WLAN_FASTPATH := y

	# Flag to enable NAPI
	CONFIG_WLAN_NAPI := y
	CONFIG_WLAN_NAPI_DEBUG := n

	# Flag to enable FW based TX Flow control
	ifeq ($(CONFIG_CNSS_EOS),y)
		CONFIG_WLAN_TX_FLOW_CONTROL_V2 := y
	else
		CONFIG_WLAN_TX_FLOW_CONTROL_V2 := n
	endif

	# Flag to enable LRO (Large Receive Offload)
	ifeq ($(CONFIG_CNSS_EOS), y)
		ifeq ($(CONFIG_INET_LRO), y)
			CONFIG_WLAN_LRO := y
		else
			CONFIG_WLAN_LRO := n
		endif
	endif
endif

ifneq ($(CONFIG_MOBILE_ROUTER), y)
# To enable ESE upload, dependent config
# CONFIG_QCOM_ESE must be enabled.
CONFIG_QCOM_ESE := y
CONFIG_QCOM_ESE_UPLOAD := y
endif

# Feature flags which are not (currently) configurable via Kconfig

#Whether to build debug version
BUILD_DEBUG_VERSION := 1

#Enable this flag to build driver in diag version
BUILD_DIAG_VERSION := 1

#Do we panic on bug?  default is to warn
PANIC_ON_BUG := 1

#Enable OL debug and wmi unified functions
CONFIG_ATH_PERF_PWR_OFFLOAD := 1

#Disable packet log
CONFIG_REMOVE_PKT_LOG := 0

#Enable 11AC TX
ifeq ($(CONFIG_ROME_IF),pci)
	CONFIG_ATH_11AC_TXCOMPACT := 1
endif
ifeq ($(CONFIG_ROME_IF),usb)
	CONFIG_ATH_11AC_TXCOMPACT := 0
endif

#Enable OS specific IRQ abstraction
CONFIG_ATH_SUPPORT_SHARED_IRQ := 1

#Enable message based HIF instead of RAW access in BMI
ifeq ($(CONFIG_QCA_WIFI_SDIO), 1)
CONFIG_HIF_MESSAGE_BASED := 0
else
CONFIG_HIF_MESSAGE_BASED := 1
endif

#Enable PCI specific APIS (dma, etc)
ifeq ($(CONFIG_ROME_IF),pci)
	CONFIG_HIF_PCI := 1
endif

#Enable pci read/write config functions
ifeq ($(CONFIG_ROME_IF),pci)
	CONFIG_ATH_PCI := 1
endif
ifeq ($(CONFIG_ROME_IF),usb)
#CONFIG_ATH_PCI := 1
endif

ifneq ($(CONFIG_MOBILE_ROUTER), y)
#Enable IBSS support on CLD
CONFIG_QCA_IBSS_SUPPORT := 1
endif

#Enable power management suspend/resume functionality to PCI
CONFIG_ATH_BUS_PM := 1

#Enable FLOWMAC module support
CONFIG_ATH_SUPPORT_FLOWMAC_MODULE := 0

#Enable spectral support
CONFIG_ATH_SUPPORT_SPECTRAL := 0

#Enable HOST statistics support
CONFIG_SUPPORT_HOST_STATISTICS := 0

#Enable WDI Event support
CONFIG_WDI_EVENT_ENABLE := 1

#Endianess selection
CONFIG_LITTLE_ENDIAN := 1

#Enable TX reclaim support
CONFIG_TX_CREDIT_RECLAIM_SUPPORT := 0

#Enable FTM support
CONFIG_QCA_WIFI_FTM := 1

#Enable Checksum Offload
CONFIG_CHECKSUM_OFFLOAD := 1

#Enable GTK offload
CONFIG_GTK_OFFLOAD := 1

#Enable EXT WOW
ifeq ($(CONFIG_ROME_IF),pci)
	CONFIG_EXT_WOW := 1
endif

#Set this to 1 to catch erroneous Target accesses during debug.
CONFIG_ATH_PCIE_ACCESS_DEBUG := 0

#Enable IPA offload
ifeq ($(CONFIG_IPA), y)
CONFIG_IPA_OFFLOAD := 1
endif

#Enable Signed firmware support for split binary format
CONFIG_QCA_SIGNED_SPLIT_BINARY_SUPPORT := 0

#Enable single firmware binary format
CONFIG_QCA_SINGLE_BINARY_SUPPORT := 0

#Enable collecting target RAM dump after kernel panic
CONFIG_TARGET_RAMDUMP_AFTER_KERNEL_PANIC := 1

#Flag to enable/disable secure firmware feature
CONFIG_FEATURE_SECURE_FIRMWARE := 0

#Flag to enable Stats Ext implementation
CONFIG_FEATURE_STATS_EXT := 1

#Flag to force the inclusion of the 802.11p channels because support
#for these channels has not yet been added to the kernel.
CONFIG_STATICALLY_ADD_11P_CHANNELS := n

ifeq ($(CONFIG_CFG80211),y)
HAVE_CFG80211 := 1
else
ifeq ($(CONFIG_CFG80211),m)
HAVE_CFG80211 := 1
else
HAVE_CFG80211 := 0
endif
endif

############ UAPI ############
UAPI_DIR :=	uapi
UAPI_INC :=	-I$(WLAN_ROOT)/$(UAPI_DIR)/linux

############ COMMON ############
COMMON_DIR :=	core/common
COMMON_INC :=	-I$(WLAN_ROOT)/$(COMMON_DIR)

############ HDD ############
HDD_DIR :=	core/hdd
HDD_INC_DIR :=	$(HDD_DIR)/inc
HDD_SRC_DIR :=	$(HDD_DIR)/src

HDD_INC := 	-I$(WLAN_ROOT)/$(HDD_INC_DIR) \
		-I$(WLAN_ROOT)/$(HDD_SRC_DIR)

HDD_OBJS := 	$(HDD_SRC_DIR)/wlan_hdd_assoc.o \
		$(HDD_SRC_DIR)/wlan_hdd_cfg.o \
		$(HDD_SRC_DIR)/wlan_hdd_debugfs.o \
		$(HDD_SRC_DIR)/wlan_hdd_driver_ops.o \
		$(HDD_SRC_DIR)/wlan_hdd_ftm.o \
		$(HDD_SRC_DIR)/wlan_hdd_hostapd.o \
		$(HDD_SRC_DIR)/wlan_hdd_ioctl.o \
		$(HDD_SRC_DIR)/wlan_hdd_main.o \
		$(HDD_SRC_DIR)/wlan_hdd_ocb.o \
		$(HDD_SRC_DIR)/wlan_hdd_oemdata.o \
		$(HDD_SRC_DIR)/wlan_hdd_power.o \
		$(HDD_SRC_DIR)/wlan_hdd_scan.o \
		$(HDD_SRC_DIR)/wlan_hdd_softap_tx_rx.o \
		$(HDD_SRC_DIR)/wlan_hdd_tx_rx.o \
		$(HDD_SRC_DIR)/wlan_hdd_trace.o \
		$(HDD_SRC_DIR)/wlan_hdd_wext.o \
		$(HDD_SRC_DIR)/wlan_hdd_wmm.o \
		$(HDD_SRC_DIR)/wlan_hdd_wowl.o

ifeq ($(CONFIG_WLAN_LRO), y)
HDD_OBJS +=     $(HDD_SRC_DIR)/wlan_hdd_lro.o
endif

ifeq ($(CONFIG_WLAN_NAPI), y)
HDD_OBJS +=     $(HDD_SRC_DIR)/wlan_hdd_napi.o
endif

ifeq ($(CONFIG_IPA_OFFLOAD), 1)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_ipa.o
endif

ifeq ($(HAVE_CFG80211),1)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_cfg80211.o \
		$(HDD_SRC_DIR)/wlan_hdd_ext_scan.o \
		$(HDD_SRC_DIR)/wlan_hdd_stats.o \
		$(HDD_SRC_DIR)/wlan_hdd_p2p.o
endif

ifeq ($(CONFIG_QCACLD_FEATURE_GREEN_AP),y)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_green_ap.o
endif

ifeq ($(CONFIG_QCACLD_FEATURE_NAN),y)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_nan.o
endif

ifeq ($(CONFIG_QCOM_TDLS),y)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_tdls.o
endif

ifeq ($(CONFIG_MPC_UT_FRAMEWORK),y)
HDD_OBJS +=	$(HDD_SRC_DIR)/wlan_hdd_conc_ut.o
endif

ifeq ($(CONFIG_WLAN_FEATURE_MEMDUMP),y)
HDD_OBJS += $(HDD_SRC_DIR)/wlan_hdd_memdump.o
endif

########### HOST DIAG LOG ###########
HOST_DIAG_LOG_DIR :=	core/utils/host_diag_log

HOST_DIAG_LOG_INC_DIR :=	$(HOST_DIAG_LOG_DIR)/inc
HOST_DIAG_LOG_SRC_DIR :=	$(HOST_DIAG_LOG_DIR)/src

HOST_DIAG_LOG_INC :=	-I$(WLAN_ROOT)/$(HOST_DIAG_LOG_INC_DIR) \
			-I$(WLAN_ROOT)/$(HOST_DIAG_LOG_SRC_DIR)

HOST_DIAG_LOG_OBJS +=	$(HOST_DIAG_LOG_SRC_DIR)/host_diag_log.o

############ EPPING ############
EPPING_DIR :=	core/utils/epping
EPPING_INC_DIR :=	$(EPPING_DIR)/inc
EPPING_SRC_DIR :=	$(EPPING_DIR)/src

EPPING_INC := 	-I$(WLAN_ROOT)/$(EPPING_INC_DIR)

EPPING_OBJS := $(EPPING_SRC_DIR)/epping_main.o \
		$(EPPING_SRC_DIR)/epping_txrx.o \
		$(EPPING_SRC_DIR)/epping_tx.o \
		$(EPPING_SRC_DIR)/epping_rx.o \
		$(EPPING_SRC_DIR)/epping_helper.o \


############ MAC ############
MAC_DIR :=	core/mac
MAC_INC_DIR :=	$(MAC_DIR)/inc
MAC_SRC_DIR :=	$(MAC_DIR)/src

MAC_INC := 	-I$(WLAN_ROOT)/$(MAC_INC_DIR) \
		-I$(WLAN_ROOT)/$(MAC_SRC_DIR)/dph \
		-I$(WLAN_ROOT)/$(MAC_SRC_DIR)/include \
		-I$(WLAN_ROOT)/$(MAC_SRC_DIR)/pe/include \
		-I$(WLAN_ROOT)/$(MAC_SRC_DIR)/pe/lim

MAC_CFG_OBJS := $(MAC_SRC_DIR)/cfg/cfg_api.o \
		$(MAC_SRC_DIR)/cfg/cfg_debug.o \
		$(MAC_SRC_DIR)/cfg/cfg_param_name.o \
		$(MAC_SRC_DIR)/cfg/cfg_proc_msg.o \
		$(MAC_SRC_DIR)/cfg/cfg_send_msg.o

MAC_DPH_OBJS :=	$(MAC_SRC_DIR)/dph/dph_hash_table.o

MAC_LIM_OBJS := $(MAC_SRC_DIR)/pe/lim/lim_aid_mgmt.o \
		$(MAC_SRC_DIR)/pe/lim/lim_admit_control.o \
		$(MAC_SRC_DIR)/pe/lim/lim_api.o \
		$(MAC_SRC_DIR)/pe/lim/lim_assoc_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_debug.o \
		$(MAC_SRC_DIR)/pe/lim/lim_ft.o \
		$(MAC_SRC_DIR)/pe/lim/lim_ibss_peer_mgmt.o \
		$(MAC_SRC_DIR)/pe/lim/lim_link_monitoring_algo.o \
		$(MAC_SRC_DIR)/pe/lim/lim_p2p.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_action_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_assoc_req_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_assoc_rsp_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_auth_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_beacon_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_cfg_updates.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_deauth_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_disassoc_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_message_queue.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_mlm_req_messages.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_mlm_rsp_messages.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_probe_req_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_probe_rsp_frame.o \
		$(MAC_SRC_DIR)/pe/lim/lim_process_sme_req_messages.o \
		$(MAC_SRC_DIR)/pe/lim/lim_prop_exts_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_scan_result_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_security_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_send_management_frames.o \
		$(MAC_SRC_DIR)/pe/lim/lim_send_messages.o \
		$(MAC_SRC_DIR)/pe/lim/lim_send_sme_rsp_messages.o \
		$(MAC_SRC_DIR)/pe/lim/lim_ser_des_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_session.o \
		$(MAC_SRC_DIR)/pe/lim/lim_session_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_sme_req_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_sta_hash_api.o \
		$(MAC_SRC_DIR)/pe/lim/lim_timer_utils.o \
		$(MAC_SRC_DIR)/pe/lim/lim_trace.o \
		$(MAC_SRC_DIR)/pe/lim/lim_utils.o

ifeq ($(CONFIG_QCOM_ESE),y)
ifneq ($(CONFIG_QCOM_ESE_UPLOAD),y)
MAC_LIM_OBJS += $(MAC_SRC_DIR)/pe/lim/limProcessEseFrame.o
endif
endif

ifeq ($(CONFIG_QCOM_TDLS),y)
MAC_LIM_OBJS += $(MAC_SRC_DIR)/pe/lim/lim_process_tdls.o
endif

MAC_SCH_OBJS := $(MAC_SRC_DIR)/pe/sch/sch_api.o \
		$(MAC_SRC_DIR)/pe/sch/sch_beacon_gen.o \
		$(MAC_SRC_DIR)/pe/sch/sch_beacon_process.o \
		$(MAC_SRC_DIR)/pe/sch/sch_debug.o \
		$(MAC_SRC_DIR)/pe/sch/sch_message.o

MAC_RRM_OBJS :=	$(MAC_SRC_DIR)/pe/rrm/rrm_api.o

MAC_OBJS := 	$(MAC_CFG_OBJS) \
		$(MAC_DPH_OBJS) \
		$(MAC_LIM_OBJS) \
		$(MAC_SCH_OBJS) \
		$(MAC_RRM_OBJS)

############ SAP ############
SAP_DIR :=	core/sap
SAP_INC_DIR :=	$(SAP_DIR)/inc
SAP_SRC_DIR :=	$(SAP_DIR)/src

SAP_INC := 	-I$(WLAN_ROOT)/$(SAP_INC_DIR) \
		-I$(WLAN_ROOT)/$(SAP_SRC_DIR)

SAP_OBJS :=	$(SAP_SRC_DIR)/sap_api_link_cntl.o \
		$(SAP_SRC_DIR)/sap_ch_select.o \
		$(SAP_SRC_DIR)/sap_fsm.o \
		$(SAP_SRC_DIR)/sap_module.o

############ DFS ############ 350
DFS_DIR :=	$(SAP_DIR)/dfs
DFS_INC_DIR :=	$(DFS_DIR)/inc
DFS_SRC_DIR :=	$(DFS_DIR)/src

DFS_INC :=	-I$(WLAN_ROOT)/$(DFS_INC_DIR) \
		-I$(WLAN_ROOT)/$(DFS_SRC_DIR)

DFS_OBJS :=	$(DFS_SRC_DIR)/dfs_bindetects.o \
		$(DFS_SRC_DIR)/dfs.o \
		$(DFS_SRC_DIR)/dfs_debug.o\
		$(DFS_SRC_DIR)/dfs_fcc_bin5.o\
		$(DFS_SRC_DIR)/dfs_init.o\
		$(DFS_SRC_DIR)/dfs_misc.o\
		$(DFS_SRC_DIR)/dfs_nol.o\
		$(DFS_SRC_DIR)/dfs_phyerr_tlv.o\
		$(DFS_SRC_DIR)/dfs_process_phyerr.o\
		$(DFS_SRC_DIR)/dfs_process_radarevent.o\
		$(DFS_SRC_DIR)/dfs_staggered.o

############ SME ############
SME_DIR :=	core/sme
SME_INC_DIR :=	$(SME_DIR)/inc
SME_SRC_DIR :=	$(SME_DIR)/src

SME_INC := 	-I$(WLAN_ROOT)/$(SME_INC_DIR) \
		-I$(WLAN_ROOT)/$(SME_SRC_DIR)/csr

SME_CSR_OBJS := $(SME_SRC_DIR)/csr/csr_api_roam.o \
		$(SME_SRC_DIR)/csr/csr_api_scan.o \
		$(SME_SRC_DIR)/csr/csr_cmd_process.o \
		$(SME_SRC_DIR)/csr/csr_link_list.o \
		$(SME_SRC_DIR)/csr/csr_neighbor_roam.o \
		$(SME_SRC_DIR)/csr/csr_util.o

ifeq ($(CONFIG_QCOM_ESE),y)
ifneq ($(CONFIG_QCOM_ESE_UPLOAD),y)
SME_CSR_OBJS += $(SME_SRC_DIR)/csr/csrEse.o
endif
endif

ifeq ($(CONFIG_QCOM_TDLS),y)
SME_CSR_OBJS += $(SME_SRC_DIR)/csr/csr_tdls_process.o
endif

SME_QOS_OBJS := $(SME_SRC_DIR)/qos/sme_qos.o

SME_CMN_OBJS := $(SME_SRC_DIR)/common/sme_api.o \
		$(SME_SRC_DIR)/common/sme_ft_api.o \
		$(SME_SRC_DIR)/common/sme_power_save.o \
		$(SME_SRC_DIR)/common/sme_trace.o

SME_OEM_DATA_OBJS := $(SME_SRC_DIR)/oem_data/oem_data_api.o

SME_P2P_OBJS = $(SME_SRC_DIR)/p2p/p2p_api.o

SME_RRM_OBJS := $(SME_SRC_DIR)/rrm/sme_rrm.o

ifeq ($(CONFIG_QCACLD_FEATURE_NAN),y)
SME_NAN_OBJS = $(SME_SRC_DIR)/nan/nan_api.o
endif

SME_OBJS :=	$(SME_CMN_OBJS) \
		$(SME_CSR_OBJS) \
		$(SME_OEM_DATA_OBJS) \
		$(SME_P2P_OBJS) \
		$(SME_QOS_OBJS) \
		$(SME_RRM_OBJS) \
		$(SME_NAN_OBJS)

############ NLINK ############
NLINK_DIR     :=	core/utils/nlink
NLINK_INC_DIR :=	$(NLINK_DIR)/inc
NLINK_SRC_DIR :=	$(NLINK_DIR)/src

NLINK_INC     := 	-I$(WLAN_ROOT)/$(NLINK_INC_DIR)
NLINK_OBJS    :=	$(NLINK_SRC_DIR)/wlan_nlink_srv.o

############ PTT ############
PTT_DIR     :=	core/utils/ptt
PTT_INC_DIR :=	$(PTT_DIR)/inc
PTT_SRC_DIR :=	$(PTT_DIR)/src

PTT_INC     := 	-I$(WLAN_ROOT)/$(PTT_INC_DIR)
PTT_OBJS    :=	$(PTT_SRC_DIR)/wlan_ptt_sock_svc.o

############ WLAN_LOGGING ############
WLAN_LOGGING_DIR     :=	core/utils/logging
WLAN_LOGGING_INC_DIR :=	$(WLAN_LOGGING_DIR)/inc
WLAN_LOGGING_SRC_DIR :=	$(WLAN_LOGGING_DIR)/src

WLAN_LOGGING_INC     := -I$(WLAN_ROOT)/$(WLAN_LOGGING_INC_DIR)
WLAN_LOGGING_OBJS    := $(WLAN_LOGGING_SRC_DIR)/wlan_logging_sock_svc.o

############ SYS ############
SYS_DIR :=	core/mac/src/sys

SYS_INC := 	-I$(WLAN_ROOT)/$(SYS_DIR)/common/inc \
		-I$(WLAN_ROOT)/$(SYS_DIR)/legacy/src/platform/inc \
		-I$(WLAN_ROOT)/$(SYS_DIR)/legacy/src/system/inc \
		-I$(WLAN_ROOT)/$(SYS_DIR)/legacy/src/utils/inc

SYS_COMMON_SRC_DIR := $(SYS_DIR)/common/src
SYS_LEGACY_SRC_DIR := $(SYS_DIR)/legacy/src
SYS_OBJS :=	$(SYS_COMMON_SRC_DIR)/wlan_qct_sys.o \
		$(SYS_LEGACY_SRC_DIR)/platform/src/sys_wrapper.o \
		$(SYS_LEGACY_SRC_DIR)/system/src/mac_init_api.o \
		$(SYS_LEGACY_SRC_DIR)/system/src/sys_entry_func.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/dot11f.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/log_api.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/mac_trace.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/parser_api.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/utils_api.o \
		$(SYS_LEGACY_SRC_DIR)/utils/src/utils_parser.o

############ CDF (Connectivity driver framework) ############
CDF_DIR :=	core/cdf
CDF_INC_DIR :=	$(CDF_DIR)/inc
CDF_SRC_DIR :=	$(CDF_DIR)/src

CDF_INC := 	-I$(WLAN_ROOT)/$(CDF_INC_DIR) \
		-I$(WLAN_ROOT)/$(CDF_SRC_DIR)

CDF_OBJS :=	$(CDF_SRC_DIR)/cdf_event.o \
		$(CDF_SRC_DIR)/cdf_list.o \
		$(CDF_SRC_DIR)/cdf_lock.o \
		$(CDF_SRC_DIR)/cdf_memory.o \
		$(CDF_SRC_DIR)/cdf_threads.o \
		$(CDF_SRC_DIR)/cdf_mc_timer.o \
		$(CDF_SRC_DIR)/cdf_trace.o \
		$(CDF_SRC_DIR)/cdf_nbuf.o \
		$(CDF_SRC_DIR)/cdf_defer.o

############ CDS (Connectivity driver services) ############
CDS_DIR :=	core/cds
CDS_INC_DIR :=	$(CDS_DIR)/inc
CDS_SRC_DIR :=	$(CDS_DIR)/src

CDS_INC := 	-I$(WLAN_ROOT)/$(CDS_INC_DIR) \
		-I$(WLAN_ROOT)/$(CDS_SRC_DIR)

CDS_OBJS :=	$(CDS_SRC_DIR)/cds_api.o \
		$(CDS_SRC_DIR)/cds_reg_service.o \
		$(CDS_SRC_DIR)/cds_mq.o \
		$(CDS_SRC_DIR)/cds_packet.o \
		$(CDS_SRC_DIR)/cds_regdomain.o \
		$(CDS_SRC_DIR)/cds_sched.o \
		$(CDS_SRC_DIR)/cds_concurrency.o \
		$(CDS_SRC_DIR)/cds_utils.o


########### BMI ###########
BMI_DIR := core/bmi

BMI_INC := -I$(WLAN_ROOT)/$(BMI_DIR)/inc

ifneq ($(CONFIG_ICNSS), y)
BMI_OBJS := $(BMI_DIR)/src/bmi.o \
            $(BMI_DIR)/src/ol_fw.o
ifeq ($(CONFIG_FEATURE_BMI_2), y)
BMI_OBJS += $(BMI_DIR)/src/bmi_2.o
else
BMI_OBJS += $(BMI_DIR)/src/bmi_1.o
endif
endif
########### WMI ###########
WMI_DIR := core/wmi

WMI_INC := -I$(WLAN_ROOT)/$(WMI_DIR)

WMI_OBJS := $(WMI_DIR)/wmi_unified.o \
	    $(WMI_DIR)/wmi_tlv_helper.o

########### FWLOG ###########
FWLOG_DIR := core/utils/fwlog

FWLOG_INC := -I$(WLAN_ROOT)/$(FWLOG_DIR)

FWLOG_OBJS := $(FWLOG_DIR)/dbglog_host.o

############ TXRX ############
TXRX_DIR :=     core/dp/txrx
TXRX_INC :=     -I$(WLAN_ROOT)/$(TXRX_DIR)

TXRX_OBJS := $(TXRX_DIR)/ol_txrx.o \
                $(TXRX_DIR)/ol_cfg.o \
                $(TXRX_DIR)/ol_rx.o \
                $(TXRX_DIR)/ol_rx_fwd.o \
                $(TXRX_DIR)/ol_txrx.o \
                $(TXRX_DIR)/ol_rx_defrag.o \
                $(TXRX_DIR)/ol_tx_desc.o \
                $(TXRX_DIR)/ol_tx.o \
                $(TXRX_DIR)/ol_rx_reorder_timeout.o \
                $(TXRX_DIR)/ol_rx_reorder.o \
                $(TXRX_DIR)/ol_rx_pn.o \
                $(TXRX_DIR)/ol_tx_queue.o \
                $(TXRX_DIR)/ol_txrx_peer_find.o \
                $(TXRX_DIR)/ol_txrx_event.o \
                $(TXRX_DIR)/ol_txrx_encap.o \
                $(TXRX_DIR)/ol_tx_send.o

ifeq ($(CONFIG_WLAN_TX_FLOW_CONTROL_V2), y)
TXRX_OBJS +=     $(TXRX_DIR)/ol_txrx_flow_control.o
endif

############ OL ############
OL_DIR :=     core/dp/ol
OL_INC :=     -I$(WLAN_ROOT)/$(OL_DIR)/inc

############ PKTLOG ############
PKTLOG_DIR :=      core/utils/pktlog
PKTLOG_INC :=      -I$(WLAN_ROOT)/$(PKTLOG_DIR)/include

PKTLOG_OBJS :=	$(PKTLOG_DIR)/pktlog_ac.o \
		$(PKTLOG_DIR)/pktlog_internal.o \
		$(PKTLOG_DIR)/linux_ac.o

############ HTT ############
HTT_DIR :=      core/dp/htt
HTT_INC :=      -I$(WLAN_ROOT)/$(HTT_DIR)

HTT_OBJS := $(HTT_DIR)/htt_tx.o \
            $(HTT_DIR)/htt.o \
            $(HTT_DIR)/htt_t2h.o \
            $(HTT_DIR)/htt_h2t.o \
            $(HTT_DIR)/htt_fw_stats.o \
            $(HTT_DIR)/htt_rx.o

############## HTC ##########
HTC_DIR := core/htc
HTC_INC := -I$(WLAN_ROOT)/$(HTC_DIR)

HTC_OBJS := $(HTC_DIR)/htc.o \
            $(HTC_DIR)/htc_send.o \
            $(HTC_DIR)/htc_recv.o \
            $(HTC_DIR)/htc_services.o

########### HIF ###########
HIF_DIR := core/hif
HIF_CE_DIR := $(HIF_DIR)/src/ce
HIF_CNSS_STUB_DIR := $(HIF_DIR)/src/icnss_stub

ifeq ($(CONFIG_HIF_PCI), 1)
HIF_PCIE_DIR := $(HIF_DIR)/src/pcie
else
HIF_SNOC_DIR := $(HIF_DIR)/src/snoc
endif

HIF_INC := -I$(WLAN_ROOT)/$(HIF_DIR)/inc \
				-I$(WLAN_ROOT)/$(HIF_DIR)/src \
				-I$(WLAN_ROOT)/$(HIF_CE_DIR) \
				-I$(WLAN_ROOT)/$(HIF_CNSS_STUB_DIR)

ifeq ($(CONFIG_HIF_PCI), 1)
HIF_INC += -I$(WLAN_ROOT)/$(HIF_PCIE_DIR)
else
HIF_INC += -I$(WLAN_ROOT)/$(HIF_SNOC_DIR)
endif

HIF_OBJS := $(HIF_DIR)/src/ath_procfs.o \
		$(HIF_CE_DIR)/ce_diag.o \
		$(HIF_CE_DIR)/ce_main.o \
		$(HIF_CE_DIR)/ce_service.o \
		$(HIF_CE_DIR)/ce_tasklet.o \
		$(HIF_DIR)/src/hif_main.o \
		$(HIF_DIR)/src/mp_dev.o \
		$(HIF_DIR)/src/regtable.o

ifeq ($(CONFIG_CNSS), y)
HIF_OBJS += $(HIF_CNSS_STUB_DIR)/icnss_stub.o \
		$(HIF_CE_DIR)/ce_bmi.o
endif

ifeq ($(CONFIG_WLAN_NAPI), y)
HIF_OBJS += $(HIF_DIR)/src/hif_napi.o
endif

ifeq ($(CONFIG_HIF_PCI), 1)
HIF_PCIE_OBJS := $(HIF_PCIE_DIR)/if_pci.o

HIF_OBJS += $(HIF_PCIE_OBJS)
else
HIF_SNOC_OBJS := $(HIF_SNOC_DIR)/if_snoc.o

HIF_OBJS += $(HIF_SNOC_OBJS)
endif

############ WMA ############
WMA_DIR :=	core/wma

WMA_INC_DIR :=  $(WMA_DIR)/inc
WMA_SRC_DIR :=  $(WMA_DIR)/src

WMA_INC :=	-I$(WLAN_ROOT)/$(WMA_INC_DIR) \
		-I$(WLAN_ROOT)/$(WMA_SRC_DIR)

WMA_OBJS :=	$(WMA_SRC_DIR)/wma_main.o \
		$(WMA_SRC_DIR)/wma_scan_roam.o \
		$(WMA_SRC_DIR)/wma_dev_if.o \
		$(WMA_SRC_DIR)/wma_mgmt.o \
		$(WMA_SRC_DIR)/wma_power.o \
		$(WMA_SRC_DIR)/wma_data.o \
		$(WMA_SRC_DIR)/wma_utils.o \
		$(WMA_SRC_DIR)/wma_features.o \
		$(WMA_SRC_DIR)/wma_dfs_interface.o \
		$(WMA_SRC_DIR)/wma_ocb.o \
		$(WMA_SRC_DIR)/wlan_qct_wma_legacy.o

ifeq ($(CONFIG_MPC_UT_FRAMEWORK),y)
WMA_OBJS +=	$(WMA_SRC_DIR)/wma_utils_ut.o
endif

TARGET_INC :=	-I$(WLAN_ROOT)/target/inc

LINUX_INC :=	-Iinclude/linux

INCS :=		$(HDD_INC) \
		$(EPPING_INC) \
		$(LINUX_INC) \
		$(MAC_INC) \
		$(SAP_INC) \
		$(SME_INC) \
		$(SYS_INC) \
		$(CDF_INC) \
		$(CDS_INC) \
		$(DFS_INC)

INCS +=		$(WMA_INC) \
		$(UAPI_INC) \
		$(COMMON_INC) \
		$(WMI_INC) \
		$(FWLOG_INC) \
		$(TXRX_INC) \
		$(OL_INC) \
		$(PKTLOG_INC) \
		$(HTT_INC) \
		$(HTC_INC) \
		$(DFS_INC)

INCS +=		$(HIF_INC) \
		$(BMI_INC)

INCS +=		$(TARGET_INC)

INCS +=		$(NLINK_INC) \
		$(PTT_INC) \
		$(WLAN_LOGGING_INC)

ifeq ($(CONFIG_REMOVE_PKT_LOG), 0)
INCS +=		$(PKTLOG_INC)
endif

ifeq ($(BUILD_DIAG_VERSION), 1)
INCS +=		$(HOST_DIAG_LOG_INC)
endif

OBJS :=		$(HDD_OBJS) \
		$(EPPING_OBJS) \
		$(MAC_OBJS) \
		$(SAP_OBJS) \
		$(SME_OBJS) \
		$(SYS_OBJS) \
		$(CDF_OBJS) \
		$(CDS_OBJS) \
		$(DFS_OBJS)

OBJS +=		$(WMA_OBJS) \
		$(TXRX_OBJS) \
		$(WMI_OBJS) \
		$(FWLOG_OBJS) \
		$(HTC_OBJS) \
		$(DFS_OBJS)

OBJS +=		$(HIF_OBJS) \
		$(BMI_OBJS) \
		$(HTT_OBJS)

OBJS +=		$(WLAN_LOGGING_OBJS)
OBJS +=		$(NLINK_OBJS)
OBJS +=		$(PTT_OBJS)

ifeq ($(CONFIG_REMOVE_PKT_LOG), 0)
OBJS +=		$(PKTLOG_OBJS)
endif

ifeq ($(BUILD_DIAG_VERSION), 1)
OBJS +=		$(HOST_DIAG_LOG_OBJS)
endif


EXTRA_CFLAGS += $(INCS)

CDEFINES :=	-DANI_LITTLE_BYTE_ENDIAN \
		-DANI_LITTLE_BIT_ENDIAN \
		-DQC_WLAN_CHIPSET_QCA_CLD \
		-DDOT11F_LITTLE_ENDIAN_HOST \
		-DANI_COMPILER_TYPE_GCC \
		-DANI_OS_TYPE_ANDROID=6 \
		-DWLAN_PERF \
		-DPTT_SOCK_SVC_ENABLE \
		-Wall\
		-Werror\
		-D__linux__ \
		-DHAL_SELF_STA_PER_BSS=1 \
		-DWLAN_FEATURE_VOWIFI_11R \
		-DWLAN_FEATURE_NEIGHBOR_ROAMING \
		-DWLAN_FEATURE_NEIGHBOR_ROAMING_DEBUG \
		-DWLAN_FEATURE_VOWIFI_11R_DEBUG \
		-DFEATURE_WLAN_WAPI \
		-DFEATURE_OEM_DATA_SUPPORT\
		-DSOFTAP_CHANNEL_RANGE \
		-DWLAN_AP_STA_CONCURRENCY \
		-DFEATURE_WLAN_SCAN_PNO \
		-DWLAN_FEATURE_PACKET_FILTERING \
		-DWLAN_FEATURE_VOWIFI \
		-DWLAN_FEATURE_11AC \
		-DWLAN_FEATURE_P2P_DEBUG \
		-DWLAN_ENABLE_AGEIE_ON_SCAN_RESULTS \
		-DWLANTL_DEBUG\
		-DWLAN_NS_OFFLOAD \
		-DWLAN_SOFTAP_VSTA_FEATURE \
		-DWLAN_FEATURE_GTK_OFFLOAD \
		-DWLAN_WAKEUP_EVENTS \
		-DFEATURE_WLAN_RA_FILTERING\
	        -DWLAN_KD_READY_NOTIFIER \
		-DWLAN_NL80211_TESTMODE \
		-DFEATURE_WLAN_LPHB \
		-DFEATURE_WLAN_PAL_TIMER_DISABLE \
		-DFEATURE_WLAN_PAL_MEM_DISABLE \
		-DQCA_SUPPORT_TX_THROTTLE \
		-DWMI_INTERFACE_EVENT_LOGGING \
		-DATH_SUPPORT_WAPI \
		-DWLAN_FEATURE_LINK_LAYER_STATS \
		-DWLAN_LOGGING_SOCK_SVC_ENABLE \
		-DFEATURE_WLAN_EXTSCAN \
		-DFEATURE_WLAN_LFR \
		-DWLAN_FEATURE_MBSSID \
		-DCONFIG_160MHZ_SUPPORT

ifeq (y,$(filter y,$(CONFIG_CNSS_EOS) $(CONFIG_ICNSS)))
CDEFINES += -DQCA_WIFI_3_0
CDEFINES += -DQCA_WIFI_3_0_EMU
endif

ifeq (y,$(filter y,$(CONFIG_CNSS_ADRASTEA) $(CONFIG_ICNSS)))
CDEFINES += -DQCA_WIFI_3_0_ADRASTEA
CDEFINES += -DADRASTEA_SHADOW_REGISTERS
CDEFINES += -DADRASTEA_RRI_ON_DDR
endif

ifeq ($(CONFIG_WLAN_FASTPATH), y)
CDEFINES +=	-DWLAN_FEATURE_FASTPATH
endif

ifeq ($(CONFIG_WLAN_NAPI), y)
CDEFINES += -DFEATURE_NAPI
ifeq ($(CONFIG_WLAN_NAPI_DEBUG), y)
CDEFINES += -DFEATURE_NAPI_DEBUG
endif
endif

ifeq ($(CONFIG_FEATURE_BMI_2), y)
CDEFINES += -DFEATURE_BMI_2
endif

ifeq ($(CONFIG_ARCH_MSM), y)
CDEFINES += -DMSM_PLATFORM
endif

CDEFINES +=	-DQCA_SUPPORT_TXRX_LOCAL_PEER_ID

ifeq ($(CONFIG_WLAN_TX_FLOW_CONTROL_V2), y)
CDEFINES +=	-DQCA_LL_TX_FLOW_CONTROL_V2
CDEFINES +=	-DQCA_LL_TX_FLOW_GLOBAL_MGMT_POOL
else
ifeq ($(CONFIG_ROME_IF),pci)
CDEFINES +=	-DQCA_LL_LEGACY_TX_FLOW_CONTROL
endif
endif

ifeq ($(CONFIG_DEBUG_LL),y)
CDEFINES +=    	-DQCA_PKT_PROTO_TRACE
endif

ifneq ($(CONFIG_QCA_CLD_WLAN),)
CDEFINES += -DWCN_PRONTO
CDEFINES += -DWCN_PRONTO_V1
endif

ifeq ($(BUILD_DEBUG_VERSION),1)
CDEFINES +=	-DWLAN_DEBUG \
		-DTRACE_RECORD \
		-DLIM_TRACE_RECORD \
		-DSME_TRACE_RECORD \
		-DHDD_TRACE_RECORD \
		-DPE_DEBUG_LOGW \
		-DPE_DEBUG_LOGE \
		-DDEBUG
endif

ifeq ($(CONFIG_SLUB_DEBUG_ON),y)
CDEFINES += -DTIMER_MANAGER
CDEFINES += -DMEMORY_DEBUG
endif

ifeq ($(HAVE_CFG80211),1)
CDEFINES += -DWLAN_FEATURE_P2P
CDEFINES += -DWLAN_FEATURE_WFD
ifeq ($(CONFIG_QCOM_VOWIFI_11R),y)
CDEFINES += -DKERNEL_SUPPORT_11R_CFG80211
CDEFINES += -DUSE_80211_WMMTSPEC_FOR_RIC
endif
endif

ifeq ($(CONFIG_QCOM_ESE),y)
CDEFINES += -DFEATURE_WLAN_ESE
CDEFINES += -DQCA_COMPUTE_TX_DELAY
CDEFINES += -DQCA_COMPUTE_TX_DELAY_PER_TID
ifeq ($(CONFIG_QCOM_ESE_UPLOAD),y)
CDEFINES += -DFEATURE_WLAN_ESE_UPLOAD
endif
endif

#normally, TDLS negative behavior is not needed
ifeq ($(CONFIG_QCOM_TDLS),y)
CDEFINES += -DFEATURE_WLAN_TDLS
endif

ifeq ($(CONFIG_QCACLD_WLAN_LFR3),y)
CDEFINES += -DWLAN_FEATURE_ROAM_OFFLOAD
endif

ifeq ($(CONFIG_PRIMA_WLAN_OKC),y)
CDEFINES += -DFEATURE_WLAN_OKC
endif

ifeq ($(CONFIG_PRIMA_WLAN_11AC_HIGH_TP),y)
CDEFINES += -DWLAN_FEATURE_11AC_HIGH_TP
endif

ifeq ($(BUILD_DIAG_VERSION),1)
CDEFINES += -DFEATURE_WLAN_DIAG_SUPPORT
CDEFINES += -DFEATURE_WLAN_DIAG_SUPPORT_CSR
CDEFINES += -DFEATURE_WLAN_DIAG_SUPPORT_LIM
ifeq ($(CONFIG_HIF_PCI), 1)
CDEFINES += -DCONFIG_ATH_PROCFS_DIAG_SUPPORT
endif
endif

ifeq ($(CONFIG_HIF_USB), 1)
CDEFINES += -DCONFIG_ATH_PROCFS_DIAG_SUPPORT
CDEFINES += -DQCA_SUPPORT_OL_RX_REORDER_TIMEOUT
CDEFINES += -DCONFIG_ATH_PCIE_MAX_PERF=0 -DCONFIG_ATH_PCIE_AWAKE_WHILE_DRIVER_LOAD=0 -DCONFIG_DISABLE_CDC_MAX_PERF_WAR=0
CDEFINES += -DQCA_TX_HTT2_SUPPORT
endif

# enable the MAC Address auto-generation feature
CDEFINES += -DWLAN_AUTOGEN_MACADDR_FEATURE

ifeq ($(CONFIG_WLAN_FEATURE_11W),y)
CDEFINES += -DWLAN_FEATURE_11W
endif

ifeq ($(CONFIG_QCOM_LTE_COEX),y)
CDEFINES += -DFEATURE_WLAN_CH_AVOID
endif

ifeq ($(CONFIG_WLAN_FEATURE_LPSS),y)
CDEFINES += -DWLAN_FEATURE_LPSS
endif

ifeq ($(PANIC_ON_BUG),1)
CDEFINES += -DPANIC_ON_BUG
endif

ifeq ($(WLAN_OPEN_SOURCE), 1)
CDEFINES += -DWLAN_OPEN_SOURCE
endif

ifeq ($(CONFIG_FEATURE_STATS_EXT), 1)
CDEFINES += -DWLAN_FEATURE_STATS_EXT
endif

ifeq ($(CONFIG_QCACLD_FEATURE_NAN),y)
CDEFINES += -DWLAN_FEATURE_NAN
endif

ifeq ($(CONFIG_QCA_IBSS_SUPPORT), 1)
CDEFINES += -DQCA_IBSS_SUPPORT
endif

#Enable OL debug and wmi unified functions
ifeq ($(CONFIG_ATH_PERF_PWR_OFFLOAD), 1)
CDEFINES += -DATH_PERF_PWR_OFFLOAD
endif

#Disable packet log
ifeq ($(CONFIG_REMOVE_PKT_LOG), 1)
CDEFINES += -DREMOVE_PKT_LOG
endif

#Enable 11AC TX
ifeq ($(CONFIG_ATH_11AC_TXCOMPACT), 1)
CDEFINES += -DATH_11AC_TXCOMPACT
endif

#Enable OS specific IRQ abstraction
ifeq ($(CONFIG_ATH_SUPPORT_SHARED_IRQ), 1)
CDEFINES += -DATH_SUPPORT_SHARED_IRQ
endif

#Enable message based HIF instead of RAW access in BMI
ifeq ($(CONFIG_HIF_MESSAGE_BASED), 1)
CDEFINES += -DHIF_MESSAGE_BASED
endif

#Enable PCI specific APIS (dma, etc)
ifeq ($(CONFIG_HIF_PCI), 1)
CDEFINES += -DHIF_PCI
endif

#Enable USB specific APIS
ifeq ($(CONFIG_HIF_USB), 1)
CDEFINES += -DHIF_USB
CDEFINES += -DCONFIG_HL_SUPPORT
endif

#Enable FW logs through ini
CDEFINES += -DCONFIG_FW_LOGS_BASED_ON_INI

#Enable pci read/write config functions
ifeq ($(CONFIG_ATH_PCI), 1)
CDEFINES += -DATH_PCI
endif

#Enable power management suspend/resume functionality
ifeq ($(CONFIG_ATH_BUS_PM), 1)
CDEFINES += -DATH_BUS_PM
endif

#Enable FLOWMAC module support
ifeq ($(CONFIG_ATH_SUPPORT_FLOWMAC_MODULE), 1)
CDEFINES += -DATH_SUPPORT_FLOWMAC_MODULE
endif

#Enable spectral support
ifeq ($(CONFIG_ATH_SUPPORT_SPECTRAL), 1)
CDEFINES += -DATH_SUPPORT_SPECTRAL
endif

#Enable WDI Event support
ifeq ($(CONFIG_WDI_EVENT_ENABLE), 1)
CDEFINES += -DWDI_EVENT_ENABLE
endif

#Endianess selection
ifeq ($(CONFIG_LITTLE_ENDIAN), 1)
AH_LITTLE_ENDIAN=1234
CDEFINES += -DAH_BYTE_ORDER=$(AH_LITTLE_ENDIAN)
else
AH_BIG_ENDIAN=4321
CDEFINES += -DAH_BYTE_ORDER=$(AH_BIG_ENDIAN)
CDEFINES += -DBIG_ENDIAN_HOST
endif

#Enable TX reclaim support
ifeq ($(CONFIG_TX_CREDIT_RECLAIM_SUPPORT), 1)
CDEFINES += -DTX_CREDIT_RECLAIM_SUPPORT
endif

#Enable FTM support
ifeq ($(CONFIG_QCA_WIFI_FTM), 1)
CDEFINES += -DQCA_WIFI_FTM
endif

#Enable Checksum Offload support
ifeq ($(CONFIG_CHECKSUM_OFFLOAD), 1)
CDEFINES += -DCHECKSUM_OFFLOAD
endif

#Enable Checksum Offload support
ifeq ($(CONFIG_IPA_OFFLOAD), 1)
CDEFINES += -DIPA_OFFLOAD
endif

ifneq ($(CONFIG_ARCH_MDM9630), y)
ifeq ($(CONFIG_ARCH_MDM9640), y)
CDEFINES += -DQCA_CONFIG_SMP
endif
endif

#Enable GTK Offload
ifeq ($(CONFIG_GTK_OFFLOAD), 1)
CDEFINES += -DWLAN_FEATURE_GTK_OFFLOAD
CDEFINES += -DIGTK_OFFLOAD
endif

#Enable GTK Offload
ifeq ($(CONFIG_EXT_WOW), 1)
CDEFINES += -DWLAN_FEATURE_EXTWOW_SUPPORT
endif

#Mark it as SMP Kernel
ifeq ($(CONFIG_SMP),y)
CDEFINES += -DQCA_CONFIG_SMP
endif

ifeq ($(CONFIG_WLAN_FEATURE_RX_WAKELOCK), y)
CDEFINES += -DWLAN_FEATURE_HOLD_RX_WAKELOCK
endif

#Enable Channel Matrix restriction for all targets
CDEFINES += -DWLAN_ENABLE_CHNL_MATRIX_RESTRICTION

#features specific to mobile router use case
ifeq ($(CONFIG_MOBILE_ROUTER), y)

#enable MCC TO SCC switch
CDEFINES += -DFEATURE_WLAN_MCC_TO_SCC_SWITCH

#enable wlan auto shutdown feature
CDEFINES += -DFEATURE_WLAN_AUTO_SHUTDOWN

#enable for MBSSID
CDEFINES += -DWLAN_FEATURE_MBSSID

#enable AP-AP ACS Optimization
CDEFINES += -DFEATURE_WLAN_AP_AP_ACS_OPTIMIZE

#Enable 4address scheme
CDEFINES += -DFEATURE_WLAN_STA_4ADDR_SCHEME

#Disable STA-AP Mode DFS support
CDEFINES += -DFEATURE_WLAN_STA_AP_MODE_DFS_DISABLE

#Enable OBSS feature
CDEFINES += -DQCA_HT_2040_COEX

#Disable HT40 in 2.4GHZ STA mode
CDEFINES += -DQCA_HT_20_24G_STA_ONLY

else #CONFIG_MOBILE_ROUTER

#Open P2P device interface only for non-Mobile router use cases
CDEFINES += -DWLAN_OPEN_P2P_INTERFACE

#Enable 2.4 GHz social channels in 5 GHz only mode for p2p usage
CDEFINES += -DWLAN_ENABLE_SOCIAL_CHANNELS_5G_ONLY

endif #CONFIG_MOBILE_ROUTER

#Green AP feature
ifeq ($(CONFIG_QCACLD_FEATURE_GREEN_AP),y)
CDEFINES += -DFEATURE_GREEN_AP
endif

#Enable RX Full re-order OL feature only "LL and NON-MDM9630 platform"
ifneq ($(CONFIG_ARCH_MDM9630), y)
ifeq ($(CONFIG_HIF_PCI), 1)
CDEFINES += -DWLAN_FEATURE_RX_FULL_REORDER_OL
endif
endif

#Enable Signed firmware support for split binary format
ifeq ($(CONFIG_QCA_SIGNED_SPLIT_BINARY_SUPPORT), 1)
CDEFINES += -DQCA_SIGNED_SPLIT_BINARY_SUPPORT
endif

#Enable single firmware binary format
ifeq ($(CONFIG_QCA_SINGLE_BINARY_SUPPORT), 1)
CDEFINES += -DQCA_SINGLE_BINARY_SUPPORT
endif

#Enable collecting target RAM dump after kernel panic
ifeq ($(CONFIG_TARGET_RAMDUMP_AFTER_KERNEL_PANIC), 1)
CDEFINES += -DTARGET_RAMDUMP_AFTER_KERNEL_PANIC
endif

#Enable/disable secure firmware feature
ifeq ($(CONFIG_FEATURE_SECURE_FIRMWARE), 1)
CDEFINES += -DFEATURE_SECURE_FIRMWARE
endif

ifeq ($(CONFIG_ATH_PCIE_ACCESS_DEBUG), 1)
CDEFINES += -DCONFIG_ATH_PCIE_ACCESS_DEBUG
endif

# Some kernel include files are being moved.  Check to see if
# the old version of the files are present

ifneq ($(wildcard $(srctree)/arch/$(SRCARCH)/mach-msm/include/mach/msm_smd.h),)
CDEFINES += -DEXISTS_MSM_SMD
endif

ifneq ($(wildcard $(srctree)/arch/$(SRCARCH)/mach-msm/include/mach/msm_smsm.h),)
CDEFINES += -DEXISTS_MSM_SMSM
endif

# Enable feature support fo Linux version QCMBR
ifeq ($(CONFIG_LINUX_QCMBR),y)
CDEFINES += -DLINUX_QCMBR
endif


# Enable full rx re-order offload for adrastea
ifeq (y, $(filter y, $(CONFIG_CNSS_ADRASTEA) $(CONFIG_ICNSS)))
CDEFINES += -DWLAN_FEATURE_RX_FULL_REORDER_OL
endif

# NOTE: CONFIG_64BIT_PADDR requires CONFIG_HELIUMPLUS
ifeq (y,$(filter y,$(CONFIG_CNSS_EOS) $(CONFIG_ICNSS)))
CONFIG_HELIUMPLUS := y
CONFIG_64BIT_PADDR := y
CONFIG_FEATURE_TSO := y
CONFIG_FEATURE_TSO_DEBUG := y
ifeq ($(CONFIG_HELIUMPLUS),y)
CDEFINES += -DHELIUMPLUS_PADDR64
CDEFINES += -DHELIUMPLUS
ifeq ($(CONFIG_64BIT_PADDR),y)
CDEFINES += -DHTT_PADDR64
endif
endif
endif

ifeq ($(CONFIG_FEATURE_TSO),y)
CDEFINES += -DFEATURE_TSO
endif
ifeq ($(CONFIG_FEATURE_TSO_DEBUG),y)
CDEFINES += -DFEATURE_TSO_DEBUG
endif

ifeq ($(CONFIG_WLAN_LRO), y)
CDEFINES += -DFEATURE_LRO
endif

ifeq ($(CONFIG_MOBILE_ROUTER), y)
CDEFINES += -DFEATURE_AP_MCC_CH_AVOIDANCE
endif

ifeq ($(CONFIG_MPC_UT_FRAMEWORK), y)
CDEFINES += -DMPC_UT_FRAMEWORK
endif

ifeq ($(CONFIG_WLAN_OFFLOAD_PACKETS),y)
CDEFINES += -DWLAN_FEATURE_OFFLOAD_PACKETS
endif

ifeq ($(CONFIG_WLAN_FEATURE_MEMDUMP),y)
CDEFINES += -DWLAN_FEATURE_MEMDUMP
endif

ifeq ($(CONFIG_STATICALLY_ADD_11P_CHANNELS),y)
CDEFINES += -DFEATURE_STATICALLY_ADD_11P_CHANNELS
endif

KBUILD_CPPFLAGS += $(CDEFINES)

# Currently, for versions of gcc which support it, the kernel Makefile
# is disabling the maybe-uninitialized warning.  Re-enable it for the
# WLAN driver.  Note that we must use EXTRA_CFLAGS here so that it
# will override the kernel settings.
ifeq ($(call cc-option-yn, -Wmaybe-uninitialized),y)
EXTRA_CFLAGS += -Wmaybe-uninitialized
endif

# Module information used by KBuild framework
obj-$(CONFIG_QCA_CLD_WLAN) += $(MODNAME).o
$(MODNAME)-y := $(OBJS)
