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
# Debug or not
# Release by default.
#-----------------------------------------------
build ?= release

#-----------------------------------------------
# Choose the float point method.
# KV31F51212 can use: NO_FP, SOFT_FP and HARD_FP.
#-----------------------------------------------
CHOOSE_FLOAT = HARD_FP

include $(SDK_ROOT)/mk/common.mk

include $(SDK_ROOT)/platform/hal/subdir.mk

INCLUDES += $(SDK_ROOT)/platform/startup/M$(CHIP)

#-----------------------------------------------
# Predefined symbols
#-----------------------------------------------
DEFINES += -DCPU_MKV31F512VLL12
#-----------------------------------------------
# The name of this lib
#-----------------------------------------------
LIB_NAME = ksdk_hal_lib

include $(SDK_ROOT)/mk/targets.mk

