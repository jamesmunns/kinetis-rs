INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)

# this file was generated
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mqx_stdlib)


SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)


ENABLE_LANGUAGE(ASM)
STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)


# -----------------------------------------------
# common settings
# -----------------------------------------------

# common asm flags
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m4")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mfloat-abi=soft")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Xassembler --no-warn")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -std=gnu99")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wall")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mthumb")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -gdwarf-2")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -gstrict-dwarf")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g2")

# common asm defines
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DCPU_MKW24D512VHA5=1")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DFSL_RTOS_MQX=1")

# common c compiler flags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m4")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=soft")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-missing-braces")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-2")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gstrict-dwarf")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-delete-null-pointer-checks")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g2")

# common c compiler defines
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCPU_MKW24D512VHA5=1")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFSL_RTOS_MQX=1")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_AEABI_LC_CTYPE=C")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__STRICT_ANSI__=1")


IF(CMAKE_BUILD_TYPE MATCHES "debug")
# -----------------------------------------------
# special settings for 'debug'
# -----------------------------------------------

#   asm defines
    SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -D_DEBUG=1")

#   c compiler flags
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

#   c compiler defines
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DEBUG=1")

    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/compiler/gcc_arm")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/cpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5/startup")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/mcu/MKW24D5")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/board/usbkw24d512")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../examples/usbkw24d512")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/src")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/fs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_dummy")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_mem")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_null")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_pipe")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_serial")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_tfs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_tty")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/tad")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/hal/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/src/mpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/src/uart")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/utilities/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../middleware/filesystem/mfs/source/mfs_sdcard/nio_esdhc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../..")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/osa/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/system/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/core/M4")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/usbkw24d512.armgcc/debug/mqx_stdlib)
ENDIF()
IF(CMAKE_BUILD_TYPE MATCHES "release")
# -----------------------------------------------
# special settings for 'release'
# -----------------------------------------------

#   asm defines
    SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DNDEBUG=1")

#   c compiler flags
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")

#   c compiler defines
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG=1")

    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/compiler/gcc_arm")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/cpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5/startup")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/mcu/MKW24D5")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/board/usbkw24d512")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../examples/usbkw24d512")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/src")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/fs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_dummy")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_mem")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_null")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_pipe")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_serial")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_tfs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/nio/drivers/nio_tty")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/tad")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKW24D5/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/hal/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/src/mpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/drivers/src/uart")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/utilities/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../middleware/filesystem/mfs/source/mfs_sdcard/nio_esdhc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../..")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/osa/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/system/inc")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx/source/psp/cortex_m/core/M4")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/usbkw24d512.armgcc/release/mqx_stdlib)
ENDIF()


ADD_LIBRARY(lib_mqx_stdlib.a STATIC
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/std_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/stdio.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/strings.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/buf_prv.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/buf_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/err.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fclose.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fflush.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fopen.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fp_prv.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fp_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fread.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/fwrite.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/get.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/pos.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/print.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/print_prv.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/print_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/put.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/scan.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/scan_prv.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/scan_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/stdio/stdio.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/strings/strings.c"
)


IF(CMAKE_BUILD_TYPE MATCHES "debug")
    ADD_CUSTOM_COMMAND(TARGET lib_mqx_stdlib.a POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../bat/mqx_stdlib_usbkw24d512.sh ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/usbkw24d512.armgcc/debug/mqx_stdlib armgcc)
ENDIF()
IF(CMAKE_BUILD_TYPE MATCHES "release")
    ADD_CUSTOM_COMMAND(TARGET lib_mqx_stdlib.a POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../bat/mqx_stdlib_usbkw24d512.sh ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/usbkw24d512.armgcc/release/mqx_stdlib armgcc)
ENDIF()


