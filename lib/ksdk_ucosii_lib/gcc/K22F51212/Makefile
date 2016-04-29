#-----------------------------------------------
# setup variables
# ----------------------------------------------

SDK_ROOT := $(abspath ../../../..)

#-----------------------------------------------
# set chip infomation
# CPU type: cortex-m0, cortex-m0plus,
# cortex-m1, cortex-m3, cortex-m4, 
#-----------------------------------------------
CHIP := K22F51212
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

SOURCES += $(SDK_ROOT)/platform/osa/src/fsl_os_abstraction_ucosii.c
INCLUDES += $(SDK_ROOT)/platform/osa \
			$(UCOSII_ROOT)/src/config \
            $(UCOSII_ROOT)/src/uCOS-II/Source \
            $(UCOSII_ROOT)/src/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU \
            $(UCOSII_ROOT)/src/uC-LIB \
            $(UCOSII_ROOT)/src/uC-CPU \
            $(UCOSII_ROOT)/src/uC-CPU/ARM-Cortex-M4/GNU

INCLUDES += $(SDK_ROOT)/platform/startup/M$(CHIP)

#-----------------------------------------------
# Predefined symbols
#-----------------------------------------------
DEFINES += -DCPU_MK22FN512VDC12 \
		   -DFSL_RTOS_UCOSII
#-----------------------------------------------
# The name of this lib
#-----------------------------------------------
LIB_NAME = ksdk_ucosii_lib

include $(SDK_ROOT)/mk/targets.mk

