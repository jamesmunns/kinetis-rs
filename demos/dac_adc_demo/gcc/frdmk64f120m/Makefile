#-----------------------------------------------
# setup variables
# ----------------------------------------------

SDK_ROOT := $(abspath ../../../..)

#-----------------------------------------------
# set board infomation
#-----------------------------------------------
BOARD := frdmk64f120m
CHIP  := K64F12
CPU   := cortex-m4

APP_NAME = dac_adc_demo
#-----------------------------------------------
# Debug or Release
# Release by default
#-----------------------------------------------
build ?= release

#-----------------------------------------------
# Sram target or flash target
# flash target by defult.
#-----------------------------------------------
target ?= flash

#-----------------------------------------------
# Choose the float point method.
# K22F51212 can use: NO_FP, SOFT_FP and HARD_FP.
#-----------------------------------------------
CHOOSE_FLOAT ?= HARD_FP

include $(SDK_ROOT)/mk/common.mk

#-----------------------------------------------
# include library. Only the name of the lib is 
# needed here, the targets.mk will convert it
# to correct library file. e.g. if platform_lib
# is added here, targets.mk will convert it to
# $(OUTPUT_ROOT)/lib/<CHIP>/platform.a
#-----------------------------------------------
ifeq "$(build)" "debug"
LINK_LIB_NAME := $(SDK_ROOT)/lib/ksdk_platform_lib/gcc/$(CHIP)/Debug/ksdk_platform_lib.a
else
LINK_LIB_NAME := $(SDK_ROOT)/lib/ksdk_platform_lib/gcc/$(CHIP)/Release/ksdk_platform_lib.a
endif

#-----------------------------------------------
# Include path. Add the include paths like this:
# INCLUDES += ./include/
#-----------------------------------------------
INCLUDES += $(SDK_ROOT)/platform/startup/M$(CHIP) \
			$(SDK_ROOT)/platform/system/clock \
			$(SDK_ROOT)/platform/osa \
			$(SDK_ROOT)/platform/utilities \
			$(SDK_ROOT)/platform/drivers/adc   \
			$(SDK_ROOT)/platform/drivers/adc/common \
            $(SDK_ROOT)/platform/drivers/can   \
            $(SDK_ROOT)/platform/drivers/clock \
            $(SDK_ROOT)/platform/drivers/dac \
            $(SDK_ROOT)/platform/drivers/dac/common \
            $(SDK_ROOT)/platform/drivers/dspi \
            $(SDK_ROOT)/platform/drivers/dspi/common \
            $(SDK_ROOT)/platform/drivers/dspi/dspi_master  \
            $(SDK_ROOT)/platform/drivers/dspi/dspi_slave \
            $(SDK_ROOT)/platform/drivers/edma  \
            $(SDK_ROOT)/platform/drivers/edma/common  \
            $(SDK_ROOT)/platform/drivers/enet  \
            $(SDK_ROOT)/platform/drivers/flash \
            $(SDK_ROOT)/platform/drivers/flextimer \
            $(SDK_ROOT)/platform/drivers/gpio \
            $(SDK_ROOT)/platform/drivers/gpio/common \
            $(SDK_ROOT)/platform/drivers/i2c/ \
            $(SDK_ROOT)/platform/drivers/i2c/common \
            $(SDK_ROOT)/platform/drivers/i2c/i2c_master \
            $(SDK_ROOT)/platform/drivers/i2c/i2c_slave \
            $(SDK_ROOT)/platform/drivers/interrupt \
            $(SDK_ROOT)/platform/drivers/khci \
            $(SDK_ROOT)/platform/drivers/lpuart \
            $(SDK_ROOT)/platform/drivers/lpuart/common \
            $(SDK_ROOT)/platform/drivers/pit \
            $(SDK_ROOT)/platform/drivers/rtc \
            $(SDK_ROOT)/platform/drivers/sai \
            $(SDK_ROOT)/platform/drivers/sai/common \
            $(SDK_ROOT)/platform/drivers/sdhc \
            $(SDK_ROOT)/platform/drivers/smc \
            $(SDK_ROOT)/platform/drivers/soundcard \
            $(SDK_ROOT)/platform/drivers/spi \
            $(SDK_ROOT)/platform/drivers/uart  \
            $(SDK_ROOT)/platform/drivers/uart/common  \
            $(SDK_ROOT)/platform/drivers/wdog \
            $(SDK_ROOT)/platform/hal/adc \
            $(SDK_ROOT)/platform/hal/can \
            $(SDK_ROOT)/platform/hal/dac \
            $(SDK_ROOT)/platform/hal/dmamux \
            $(SDK_ROOT)/platform/hal/dspi \
            $(SDK_ROOT)/platform/hal/edma \
            $(SDK_ROOT)/platform/hal/enet \
            $(SDK_ROOT)/platform/hal/flextimer \
            $(SDK_ROOT)/platform/hal/gpio \
            $(SDK_ROOT)/platform/hal/i2c \
            $(SDK_ROOT)/platform/hal/lpuart \
            $(SDK_ROOT)/platform/hal/mcg \
            $(SDK_ROOT)/platform/hal/osc \
            $(SDK_ROOT)/platform/hal/pit \
            $(SDK_ROOT)/platform/hal/pmc \
            $(SDK_ROOT)/platform/hal/port      \
            $(SDK_ROOT)/platform/hal/rtc \
            $(SDK_ROOT)/platform/hal/sai \
            $(SDK_ROOT)/platform/hal/sdhc \
            $(SDK_ROOT)/platform/hal/sim \
            $(SDK_ROOT)/platform/hal/smc \
            $(SDK_ROOT)/platform/hal/uart      \
            $(SDK_ROOT)/platform/hal/wdog \
            $(SDK_ROOT)/boards/$(BOARD) \
            $(SDK_ROOT)/boards/common/sgtl5000

#-----------------------------------------------
# Startup files
#-----------------------------------------------
STARTUP_ROOT := $(SDK_ROOT)/platform/startup
STARTUP_SOURCES := $(STARTUP_ROOT)/startup.c \
				   $(STARTUP_ROOT)/M$(CHIP)/system_M$(CHIP).c \
				   $(STARTUP_ROOT)/M$(CHIP)/gcc/startup_M$(CHIP).S \

#-----------------------------------------------
# Application files
# 
# - List the relative file paths to each of the 
#   required source files.  For example --
#-----------------------------------------------
#APP_SOURCES := ../../src/cpu_identify_MK22F12.c \
#			   ../../src/hardware_init_MK22F12.c \
#			   ../../src/main.c \
#			   ../../src/mini_shell.c \
#------------------------------------------------------------------
APP_SOURCES  := $(wildcard $(APPS_ROOT)/$(APP_NAME)/src/*.c)

#-----------------------------------------------
# Board related files, e.g. platform_pins.c
#-----------------------------------------------
BOARD_SOURCES := $(wildcard $(BOARD_ROOT)/*.c)

#-----------------------------------------------
# Add all sources needed here
#-----------------------------------------------
SOURCES = $(STARTUP_SOURCES) $(APP_SOURCES) $(BOARD_SOURCES) \
		  $(SDK_ROOT)/platform/utilities/src/fsl_debug_console.c

#-----------------------------------------------
# Add all pre-defined symbols here
#-----------------------------------------------
DEFINES += -DCPU_MK64FN1M0VMD12 \
           -DFRDM_K64F120M

#-----------------------------------------------
# Link file
# Input only the name of the link file here,
# the targets.mk will convert it to
# platform/linker/gcc/<CHIP>/$(LD_FILE_NAME)
# e.g, if LD_FILE_NAME is set to K22FN512xxx12_flash.ld
# the link file platform/linker/gcc/K22FN51212/K22FN512xxx12_flash.ld
# will be used
#-----------------------------------------------
ifeq "$(target)" "sram"
LD_FILE_NAME := $(LD_FILE_ROOT)/$(CHIP)/K64FN1Mxxx12_ram.ld
else
LD_FILE_NAME := $(LD_FILE_ROOT)/$(CHIP)/K64FN1Mxxx12_flash.ld
endif

#-----------------------------------------------
# The start entry, if entry is not defined,
# _start of gcc library will be used by default.
#-----------------------------------------------
entry ?=
ifneq "$(entry)" ""
DEFINES += -D__START=$(entry)
endif

#-----------------------------------------------
# Define the stack size and heap size.
#-----------------------------------------------
stack ?= 0x400
heap  ?= 0x1000
DEFINES += -D__STACK_SIZE=$(stack) \
           -D__HEAP_SIZE=$(heap)

include $(SDK_ROOT)/mk/targets.mk 

