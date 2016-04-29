INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)

# this file was generated
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mqx)


SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)


ENABLE_LANGUAGE(ASM)
STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)


# -----------------------------------------------
# common settings
# -----------------------------------------------

# common asm flags
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m0plus")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Xassembler --no-warn")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -std=gnu99")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wall")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mthumb")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -gdwarf-2")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -gstrict-dwarf")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g2")

# common asm defines
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DCPU_MKV10Z32VLF7=1")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DFSL_RTOS_MQX=1")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DMQX_DISABLE_CONFIG_CHECK=1")

# common c compiler flags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus")
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
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCPU_MKV10Z32VLF7=1")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFSL_RTOS_MQX=1")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMQX_DISABLE_CONFIG_CHECK=1")
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

    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/compiler/gcc_arm")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/cpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/startup")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/mcu/MKV10Z7")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/board/frdmkv10z")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../examples/frdmkv10z")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/fs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_dummy")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_mem")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_null")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_pipe")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_serial")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tfs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tty")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/tad")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx_stdlib/source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx_stdlib/source/stdio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/include")
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
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/core/M0")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/frdmkv10z.armgcc/debug/mqx)
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

    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/compiler/gcc_arm")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/cpu")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/startup")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/mcu/MKV10Z7")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/board/frdmkv10z")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../examples/frdmkv10z")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/fs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_dummy")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_mem")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_null")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_pipe")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_serial")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tfs")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tty")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/tad")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx_stdlib/source/include")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../mqx_stdlib/source/stdio")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/include")
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
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/core/M0")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/frdmkv10z.armgcc/release/mqx)
ENDIF()


ADD_LIBRARY(lib_mqx.a STATIC
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/compiler/gcc_arm/asm_mac.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/compiler/gcc_arm/comp.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/compiler/gcc_arm/comp.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/core/M0/psp_prv.inc"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/core/M0/boot.S"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/core/M0/dispatch.S"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/types.inc"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_gkis.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_kisr.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_pvta.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_unx.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_vtab.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/int_xcpt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/ipsum.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/mem_copy.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/mem_zero.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_dati.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_gelms.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_hoti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_iinit.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_mat1.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_mat2.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_mat3.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_miti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_msti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_mstiq.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_nsti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_psti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_seti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_supp.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tiad.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tida.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tihr.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_timn.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tims.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tinm.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tins.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tiol.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tipr.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tips.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tise.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tisu.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tius.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_tkti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_usti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/sc_irdyq.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/stack_bu.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/stack_de.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/stack_st.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_abi.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_comp.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_math.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_rev.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_supp.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_time.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psptypes.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/psp_cpu.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/cortex.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/kinetis_mpu.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/cortex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/nvic.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/nvic.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/kinetis.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/psp/cortex_m/cpu/kinetis_fcan.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include/core_cm0plus.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include/core_cmFunc.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/CMSIS/Include/core_cmInstr.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common/small_ram_config.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common/lite_config.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common/verif_enabled_config.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/common/mqx_cnfg.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/mcu/MKV10Z7/mqx_sdk_config.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/board/frdmkv10z/user_config.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/event.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/gen_rev.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/eds.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/edserial.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/edserprv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/eds_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/event.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/event_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/charq.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/klog.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/log.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/log_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwsem.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwevent.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwevent_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwlog.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwlog_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwmem.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/tlsf.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/tlsfbits.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/tlsf_adaptation.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/tlsf_adaptation_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwmem_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwmsgq.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwmsgq_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwtimer.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/lwtimer_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mem_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/message.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mmu.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_cpudef.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_inc.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_ioc.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_str.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mqx_macros.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/msg_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mutex.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/mutex_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/name.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/name_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/partition.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/partition_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/pcb.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/queue.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/sem.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/sem_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/timer.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/timer_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/watchdog.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/watchdog_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/idletask.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/inittask.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/int.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwsem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/mem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/tlsf.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/tlsf_adaptation.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/mqx.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/sched.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/task.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include/task.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/time.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/taskq.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/name.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/klog.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/log.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwevent.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwlog.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwmem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwmsgq.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/lwtimer.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/msg.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/msgq.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/msgpool.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src/nio.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/nio.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src/nio_prv.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src/errno.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src/nio_std_adpt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/src/nio_posix.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/unistd.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/ioctl.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/fcntl.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/fs/fs_supp.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/fs/fs_supp.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_dummy/src/nio_dummy.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_dummy/nio_dummy.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_mem/src/nio_mem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_mem/nio_mem.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_null/src/nio_null.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_null/nio_null.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_pipe/src/nio_pipe.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_pipe/nio_pipe.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_serial/src/nio_serial.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_serial/nio_serial.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tfs/src/nio_tfs.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tfs/nio_tfs.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tty/src/nio_tty.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/nio/drivers/nio_tty/nio_tty.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/string/strnlen.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/string/str_utos.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/mutex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/partition.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/queue.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/sem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/startup/system_MKV10Z7.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/startup/system_MKV10Z7.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/startup.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/tad/tad.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/tad/tad.h"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/timer.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../source/kernel/watchdog.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../platform/devices/MKV10Z7/startup/gcc/startup_MKV10Z7.S"
)


IF(CMAKE_BUILD_TYPE MATCHES "debug")
    ADD_CUSTOM_COMMAND(TARGET lib_mqx.a POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../bat/mqx_frdmkv10z.sh ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/frdmkv10z.armgcc/debug/mqx armgcc)
ENDIF()
IF(CMAKE_BUILD_TYPE MATCHES "release")
    ADD_CUSTOM_COMMAND(TARGET lib_mqx.a POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../bat/mqx_frdmkv10z.sh ${CMAKE_CURRENT_SOURCE_DIR}/../../../.. ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/frdmkv10z.armgcc/release/mqx armgcc)
ENDIF()


