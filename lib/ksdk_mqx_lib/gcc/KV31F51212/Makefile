#-----------------------------------------------
# setup variables
# ----------------------------------------------

SDK_ROOT := $(abspath ../../../..)

#-----------------------------------------------
# set chip infomation
# CPU type: cortex-m0, cortex-m0plus,
# cortex-m1, cortex-m3, cortex-m4, 
#-----------------------------------------------
CHIP := KV31F51212
CPU := cortex-m4

#-----------------------------------------------
# Choose the float point method.
# cortex-m4 can use: NO_FP, SOFT_FP and HARD_FP.
# Other cortex-m series should only use NO_FP.
#-----------------------------------------------
CHOOSE_FLOAT = HARD_FP

#-----------------------------------------------
# Debug or not
# Release by default.
#-----------------------------------------------
build ?= release

include $(SDK_ROOT)/mk/common.mk

include $(SDK_ROOT)/platform/hal/subdir.mk
include $(SDK_ROOT)/platform/drivers/subdir.mk
include $(SDK_ROOT)/platform/system/subdir.mk

SOURCES += $(SDK_ROOT)/platform/osa/src/fsl_os_abstraction_mqx.c
INCLUDES += $(SDK_ROOT)/platform/osa \
            $(SDK_ROOT)/rtos/mqx/mqx/source/psp/cortex_m/compiler/gcc_arm \
            $(SDK_ROOT)/rtos/mqx/config/common \
            $(SDK_ROOT)/rtos/mqx/config/mcu/mkv31f120m \
            $(SDK_ROOT)/rtos/mqx/mqx/source/include \
            $(SDK_ROOT)/rtos/mqx/mqx/source/psp/cortex_m

INCLUDES += $(SDK_ROOT)/platform/startup/M$(CHIP)

#-----------------------------------------------
# Predefined symbols
#-----------------------------------------------
DEFINES += -DCPU_MKV31F512VLL12 \
		   -DFSL_RTOS_MQX

#-----------------------------------------------
# The name of this lib
#-----------------------------------------------
LIB_NAME = ksdk_platform_lib

include $(SDK_ROOT)/mk/targets.mk

