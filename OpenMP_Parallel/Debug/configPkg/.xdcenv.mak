#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/omp_1_02_00_05/packages;C:/ti/bios_6_35_04_50/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/uia_1_02_00_07/packages;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv6/ccs_base
override XDCROOT = C:/ti/xdctools_3_25_04_88
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/omp_1_02_00_05/packages;C:/ti/bios_6_35_04_50/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/uia_1_02_00_07/packages;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv6/ccs_base;C:/ti/xdctools_3_25_04_88/packages;..
HOSTOS = Windows
endif
