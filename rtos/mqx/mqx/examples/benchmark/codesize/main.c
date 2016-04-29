
/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains MQX only stationery code.
*
*
*END************************************************************************/

/**************************************************************************
**                                                                       **
**                         MQX component structs                         **
**                                                                       **
**************************************************************************/

/* KERNEL structs */
#include "mqx_inc.h"
#include <bsp.h>

QUEUE_STRUCT                    MQX_QUEUE_STRUCT;
QUEUE_ELEMENT_STRUCT            MQX_QUEUE_ELEMENT_STRUCT;
LWSEM_STRUCT                    MQX_LWSEM_STRUCT;
PSP_STACK_START_STRUCT          MQX_PSP_STACK_START_STRUCT;

IDLE_LOOP_STRUCT                MQX_IDLE_LOOP_STRUCT;
TIME_STRUCT                     MQX_TIME_STRUCT;
DATE_STRUCT                     MQX_DATE_STRUCT;
TASK_TEMPLATE_STRUCT            MQX_TASK_TEMPLATE_STRUCT;
MQX_INITIALIZATION_STRUCT       MQX_MQX_INITIALIZATION_STRUCT;

INTERRUPT_TABLE_STRUCT          MQX_INTERRUPT_TABLE_STRUCT;
TD_STRUCT                       MQX_TD_STRUCT;
READY_Q_STRUCT                  MQX_READY_Q_STRUCT;
TASK_QUEUE_STRUCT               MQX_TASK_QUEUE_STRUCT;
KERNEL_DATA_STRUCT              MQX_KERNEL_DATA_STRUCT;

/* EVENT structs */
#if MQX_USE_EVENTS && MQX_USE_NAME
#include "name.h"
#include "event.h"
#include "event_prv.h"
EVENT_COMPONENT_STRUCT          MQX_EVENT_COMPONENT_STRUCT;
EVENT_STRUCT                    MQX_EVENT_STRUCT;
EVENT_CONNECTION_STRUCT         MQX_EVENT_CONNECTION_STRUCT;
#endif

/* LOGS structs */
#if MQX_USE_LOGS
#include <log.h>
#include <log_prv.h>
LOG_ENTRY_STRUCT                MQX_LOG_ENTRY_STRUCT;
LOG_HEADER_STRUCT               MQX_LOG_HEADER_STRUCT;
LOG_COMPONENT_STRUCT            MQX_LOG_COMPONENT_STRUCT;
#endif

/* LWEVENT structs */
#if MQX_USE_LWEVENTS
#include <lwevent.h>
LWEVENT_STRUCT                  MQX_LWEVENT_STRUCT;
#endif

/* LWLOGS structs */
#if MQX_USE_LWLOGS
#include <lwlog.h>
#include <lwlog_prv.h>
LWLOG_ENTRY_STRUCT              MQX_LWLOG_ENTRY_STRUCT;
LWLOG_HEADER_STRUCT             MQX_LWLOG_HEADER_STRUCT;
LWLOG_COMPONENT_STRUCT          MQX_LWLOG_COMPONENT_STRUCT;
#endif

/* LWMEM structs */
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_LWMEM
#include <lwmem.h>
#include <lwmem_prv.h>
LWMEM_POOL_STRUCT               MQX_LWMEM_POOL_STRUCT;
LWMEM_BLOCK_STRUCT              MQX_LWMEM_BLOCK_STRUCT;
#endif

/* LWMSGQ structs */
#if MQX_USE_LWMSGQ
#include <lwmsgq.h>
LWMSGQ_STRUCT                   MQX_LWMSGQ_STRUCT;
#endif

/* LWTIMER structs */
#if MQX_USE_LWTIMER
#include <lwtimer.h>
LWTIMER_STRUCT                  MQX_LWTIMER_STRUCT;
LWTIMER_PERIOD_STRUCT           MQX_LWTIMER_PERIOD_STRUCT;
#endif

/* MEM structs */
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_MEM
#include <mem_prv.h>
STOREBLOCK_STRUCT               MQX_STOREBLOCK_STRUCT;
MEMORY_COMPONENT_STRUCT         MQX_MEMORY_COMPONENT_STRUCT;
MEMPOOL_EXTENSION_STRUCT        MQX_MEMPOOL_EXTENSION_STRUCT;
MEMPOOL_STRUCT                  MQX_MEMPOOL_STRUCT;
#endif

/* MESSAGES structs */
#if MQX_USE_MESSAGES
#include <message.h>
#include <msg_prv.h>
MESSAGE_HEADER_STRUCT           MQX_MESSAGE_HEADER_STRUCT;
MSGPOOL_BLOCK_STRUCT            MQX_MSGPOOL_BLOCK_STRUCT;
MSGPOOL_STRUCT                  MQX_MSGPOOL_STRUCT;
INTERNAL_MESSAGE_STRUCT         MQX_INTERNAL_MESSAGE_STRUCT;
MSGQ_STRUCT                     MQX_MSGQ_STRUCT;
MSG_COMPONENT_STRUCT            MQX_MSG_COMPONENT_STRUCT;
#endif

/* MMU structs */
#if PSP_HAS_MMU
#include <mmu.h>
PSP_MMU_VINIT_STRUCT            MQX_PSP_MMU_VINIT_STRUCT;
#endif

/* MUTEXES structs */
#if MQX_USE_MUTEXES
#include <mutex.h>
#include <mutex_prv.h>
MUTEX_ATTR_STRUCT               MQX_MUTEX_ATTR_STRUCT;
MUTEX_STRUCT                    MQX_MUTEX_STRUCT;
MUTEX_COMPONENT_STRUCT          MQX_MUTEX_COMPONENT_STRUCT;
#endif

/* NAME structs */
#if MQX_USE_NAME
#include "name.h"
#include "name_prv.h"
NAME_STRUCT                     MQX_NAME_STRUCT;
NAME_COMPONENT_STRUCT           MQX_NAME_COMPONENT_STRUCT;
#endif

/* PARTITION structs */
#if MQX_USE_PARTITIONS
#include <partition.h>
#include <partition_prv.h>
PARTPOOL_BLOCK_STRUCT           MQX_PARTPOOL_BLOCK_STRUCT;
PARTPOOL_STRUCT                 MQX_PARTPOOL_STRUCT;
INTERNAL_PARTITION_BLOCK_STRUCT MQX_INTERNAL_PARTITION_BLOCK_STRUCT;
PARTITION_COMPONENT_STRUCT      MQX_PARTITION_COMPONENT_STRUCT;
#endif

/* QUEUE structs */
QUEUE_ELEMENT_STRUCT            MQX_QUEUE_ELEMENT_STRUCT;
QUEUE_STRUCT                    MQX_QUEUE_STRUCT;

/* SEMAPHORE structs */
#if MQX_USE_SEMAPHORES
#include <sem.h>
#include <sem_prv.h>
SEM_COMPONENT_STRUCT            MQX_SEM_COMPONENT_STRUCT;
SEM_STRUCT                      MQX_SEM_STRUCT;
SEM_CONNECTION_STRUCT           MQX_SEM_CONNECTION_STRUCT;
#endif

/* TIMER structs */
#if MQX_USE_TIMER
#include <timer.h>
#include <timer_prv.h>
TIMER_ENTRY_STRUCT              MQX_TIMER_ENTRY_STRUCT;
TIMER_COMPONENT_STRUCT          MQX_TIMER_COMPONENT_STRUCT;
#endif

/* SW_WATCHDOGS structs */
#if MQX_USE_SW_WATCHDOGS
#include <watchdog.h>
#include <watchdog_prv.h>
WATCHDOG_ALARM_TABLE_STRUCT     MQX_WATCHDOG_ALARM_TABLE_STRUCT;
WATCHDOG_COMPONENT_STRUCT       MQX_WATCHDOG_COMPONENT_STRUCT;
#endif

/**************************************************************************
**                                                                       **
**                         NIO component structs                         **
**                                                                       **
**************************************************************************/
#include <nio.h>
NIO_DEV_FN_STRUCT               MQX_NIO_DEV_FN_STRUCT;
NIO_DEV_STRUCT                  MQX_NIO_DEV_STRUCT;

/**************************************************************************
**                                                                       **
**                     MQX_STDLIB component structs                      **
**                                                                       **
**************************************************************************/
#include <stdio.h>
#include <strings.h>
FILE                            MQX_FILE_STRUCT;

/**************************************************************************
**                                                                       **
**                        SHELL component structs                        **
**                                                                       **
**************************************************************************/
#include <shell.h>
#include <fsl_enet_rtcs_adapter.h>
#include <sh_enet.h>
#include <rtcs.h>
#include <sh_rtcs.h>
SHELL_COMMAND_STRUCT            MQX_SHELL_COMMAND_STRUCT;
SHELL_GETOPT_CONTEXT            MQX_SHELL_GETOPT_CONTEXT;

/**************************************************************************
**                                                                       **
**                         MFS component structs                         **
**                                                                       **
**************************************************************************/
#include <mfs.h>
#include <sh_mfs.h>
MFS_FORMAT_DATA                 MQX_MFS_FORMAT_DATA;
MFS_IOCTL_FORMAT_PARAM          MQX_MFS_IOCTL_FORMAT_PARAM;
MFS_INTERNAL_SEARCH             MQX_MFS_INTERNAL_SEARCH;
MFS_SEARCH_DATA                 MQX_MFS_SEARCH_DATA;
MFS_SEARCH_PARAM                MQX_MFS_SEARCH_PARAM;
MFS_RENAME_PARAM                MQX_MFS_RENAME_PARAM;
MFS_FILE_ATTR_PARAM             MQX_MFS_FILE_ATTR_PARAM;
MFS_GET_LFN_STRUCT              MQX_MFS_GET_LFN_STRUCT;
MFS_DATE_TIME_PARAM             MQX_MFS_DATE_TIME_PARAM;

#include <esdhc.h>
ESDHC_COMMAND_STRUCT            MQX_ESDHC_COMMAND_STRUCT;
ESDHC_INIT_STRUCT               MQX_ESDHC_INIT_STRUCT;

#include <part_mgr.h>
PMGR_PART_ENTRY_STRUCT          MQX_PMGR_PART_ENTRY_STRUCT;
PMGR_PART_INFO_STRUCT           MQX_PMGR_PART_INFO_STRUCT;
PART_MGR_STRUCT                 MQX_PART_MGR_STRUCT;

#include <sdcard.h>
#include <sdcard_esdhc.h>
SDCARD_CONST_INIT_STRUCT        MQX_SDCARD_CONST_INIT_STRUCT;
SDCARD_INIT_STRUCT              MQX_SDCARD_INIT_STRUCT;

/**************************************************************************
**                                                                       **
**                        RTCS component structs                         **
**                                                                       **
**************************************************************************/

BOOTP_DATA_STRUCT               MQX_BOOTP_DATA_STRUCT;
IPCP_DATA_STRUCT                MQX_IPCP_DATA_STRUCT;
DHCPSRV_DATA_STRUCT             MQX_DHCPSRV_DATA_STRUCT;
TCPIP_PARM                      MQX_TCPIP_PARM;
PING_PARAM_STRUCT               MQX_PING_PARAM_STRUCT;
addrinfo                        MQX_addrinfo;

#include <ip_if.h>
IP_DNS_ENTRY                    MQX_IP_DNS_ENTRY;
IP_IF                           MQX_IP_IF;

#if RTCSCFG_ENABLE_MLD
#include <mld.h>
MLD_HEADER                      MQX_MLD_HEADER;
MLD_RA_OPTION_HEADER            MQX_MLD_RA_OPTION_HEADER;
#endif

#include <ftpsrv.h>
FTPSRV_AUTH_STRUCT              MQX_FTPSRV_AUTH_STRUCT;
FTPSRV_PARAM_STRUCT             MQX_FTPSRV_PARAM_STRUCT;

#include <ftpc.h>
FTPc_CONTEXT_STRUCT             MQX_FTPc_CONTEXT_STRUCT;
FTPc_COMMAND_STRUCT             MQX_FTPc_COMMAND_STRUCT;

#include <tftpcln.h>
TFTPCLN_PARAM_STRUCT            MQX_TFTPCLN_PARAM_STRUCT;

#include <tftpsrv.h>
TFTPSRV_PARAM_STRUCT            MQX_TFTPSRV_PARAM_STRUCT;

#if SHELLCFG_USES_RTCS
const SHELL_COMMAND_STRUCT Telnetsrv_shell_commands[] =
{
    { "exit",      NULL },
    { "gethbn",    NULL },
    { "getrt",     NULL },
    { "help",      NULL },
    { "ipconfig",  NULL },
    { "netstat",   NULL },
    { "pause",     NULL },
#if RTCSCFG_ENABLE_ICMP
    { "ping",      NULL },
#endif
    { "telnet",    NULL },
#if RTCSCFG_ENABLE_UDP
    { "tftp",      NULL },
#endif
    { "walkrt",    NULL },
    { "?",         NULL },
    { NULL,        NULL }
};
const FTPc_COMMAND_STRUCT FTPc_commands[] =
{
    { "ascii",        NULL },
    { "binary",       NULL },
    { "bye",          NULL },
    { "cd",           NULL },
    { "close",        NULL },
    { "delete",       NULL },
    { "get",          NULL },
    { "help",         NULL },
    { "ls",           NULL },
    { "mkdir",        NULL },
    { "open",         NULL },
    { "pass",         NULL },
    { "put",          NULL },
    { "pwd",          NULL },
    { "remotehelp",   NULL },
    { "rename",       NULL },
    { "rmdir",        NULL },
    { "user",         NULL },
    { NULL,   NULL }
};
#endif

/**************************************************************************
**                                                                       **
**                           MQX task template                           **
**                                                                       **
**************************************************************************/
#include "main.h"

/* Sanity check if include search path redirection works properly in the Makefiles */
#ifndef CODESIZE_USER_CONFIG
#error This application and BSP/PSP libraries must be built with specific mqx_sdk_config file
#endif

const TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    /* Task number, Entry point, Stack, Priority, String,               Auto? */
    {    MAIN_TASK,   Main_task,  1500,        9, "main", MQX_AUTO_START_TASK },
    {            0,           0,     0,        0,      0,                   0 }
};

/*FUNCTION*----------------------------------------------------------------
*
* Function name: structs
* Comments     :
*   This function calls _mem_free to deallocated all declared structs.
*
*END*--------------------------------------------------------------------*/
static void structs(void)
{
    /* KERNEL structs */
    _mem_free((void *)& MQX_QUEUE_STRUCT);
    _mem_free((void *)& MQX_QUEUE_ELEMENT_STRUCT);
    _mem_free((void *)& MQX_LWSEM_STRUCT);
    _mem_free((void *)& MQX_PSP_STACK_START_STRUCT);

    _mem_free((void *)& MQX_IDLE_LOOP_STRUCT);
    _mem_free((void *)& MQX_TIME_STRUCT);
    _mem_free((void *)& MQX_DATE_STRUCT);
    _mem_free((void *)& MQX_TASK_TEMPLATE_STRUCT);
    _mem_free((void *)& MQX_MQX_INITIALIZATION_STRUCT);;

    _mem_free((void *)& MQX_INTERRUPT_TABLE_STRUCT);
    _mem_free((void *)& MQX_TD_STRUCT);
    _mem_free((void *)& MQX_READY_Q_STRUCT);
    _mem_free((void *)& MQX_TASK_QUEUE_STRUCT);
    _mem_free((void *)& MQX_KERNEL_DATA_STRUCT);

    /* EVENT structs */
#if MQX_USE_EVENTS && MQX_USE_NAME
    _mem_free((void *)& MQX_EVENT_COMPONENT_STRUCT);
    _mem_free((void *)& MQX_EVENT_STRUCT);
    _mem_free((void *)& MQX_EVENT_CONNECTION_STRUCT);
#endif

    /* LOGS structs */
#if MQX_USE_LOGS
    _mem_free((void *)& MQX_LOG_ENTRY_STRUCT);
    _mem_free((void *)& MQX_LOG_HEADER_STRUCT);
    _mem_free((void *)& MQX_LOG_COMPONENT_STRUCT);
#endif

    /* LWEVENT structs */
#if MQX_USE_LWEVENTS
    _mem_free((void *)& MQX_LWEVENT_STRUCT);
#endif

    /* LWLOGS structs */
#if MQX_USE_LWLOGS
    _mem_free((void *)& MQX_LWLOG_ENTRY_STRUCT);
    _mem_free((void *)& MQX_LWLOG_HEADER_STRUCT);
    _mem_free((void *)& MQX_LWLOG_COMPONENT_STRUCT);
#endif

    /* LWMEM structs */
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_LWMEM
    _mem_free((void *)& MQX_LWMEM_POOL_STRUCT);
    _mem_free((void *)& MQX_LWMEM_BLOCK_STRUCT);
#endif

    /* LWMSGQ structs */
#if MQX_USE_LWMSGQ
    _mem_free((void *)& MQX_LWMSGQ_STRUCT);
#endif

    /* LWTIMER structs */
#if MQX_USE_LWTIMER
    _mem_free((void *)& MQX_LWTIMER_STRUCT);
    _mem_free((void *)& MQX_LWTIMER_PERIOD_STRUCT);
#endif

    /* MEM structs */
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_MEM
    _mem_free((void *)& MQX_STOREBLOCK_STRUCT);
    _mem_free((void *)& MQX_MEMORY_COMPONENT_STRUCT);
    _mem_free((void *)& MQX_MEMPOOL_EXTENSION_STRUCT);
    _mem_free((void *)& MQX_MEMPOOL_STRUCT);
#endif

    /* MESSAGES structs */
#if MQX_USE_MESSAGES
    _mem_free((void *)& MQX_MESSAGE_HEADER_STRUCT);
    _mem_free((void *)& MQX_MSGPOOL_BLOCK_STRUCT);
    _mem_free((void *)& MQX_MSGPOOL_STRUCT);
    _mem_free((void *)& MQX_INTERNAL_MESSAGE_STRUCT);
    _mem_free((void *)& MQX_MSGQ_STRUCT);
    _mem_free((void *)& MQX_MSG_COMPONENT_STRUCT);
#endif

    /* MMU structs */
#if PSP_HAS_MMU
    _mem_free((void *)& MQX_PSP_MMU_VINIT_STRUCT);
#endif

    /* MUTEXES structs */
#if MQX_USE_MUTEXES
    _mem_free((void *)& MQX_MUTEX_ATTR_STRUCT);
    _mem_free((void *)& MQX_MUTEX_STRUCT);
    _mem_free((void *)& MQX_MUTEX_COMPONENT_STRUCT);
#endif

    /* NAME structs */
#if MQX_USE_NAME
    _mem_free((void *)& MQX_NAME_STRUCT);
    _mem_free((void *)& MQX_NAME_COMPONENT_STRUCT);
#endif

    /* PARTITION structs */
#if MQX_USE_PARTITIONS
    _mem_free((void *)& MQX_PARTPOOL_BLOCK_STRUCT);
    _mem_free((void *)& MQX_PARTPOOL_STRUCT);
    _mem_free((void *)& MQX_INTERNAL_PARTITION_BLOCK_STRUCT);
    _mem_free((void *)& MQX_PARTITION_COMPONENT_STRUCT);
#endif

    /* QUEUE structs */
    _mem_free((void *)& MQX_QUEUE_ELEMENT_STRUCT);
    _mem_free((void *)& MQX_QUEUE_STRUCT);

    /* SEMAPHORE structs */
#if MQX_USE_SEMAPHORES
    _mem_free((void *)& MQX_SEM_COMPONENT_STRUCT);
    _mem_free((void *)& MQX_SEM_STRUCT);
    _mem_free((void *)& MQX_SEM_CONNECTION_STRUCT);
#endif

    /* TIMER structs */
#if MQX_USE_TIMER
    _mem_free((void *)& MQX_TIMER_ENTRY_STRUCT);
    _mem_free((void *)& MQX_TIMER_COMPONENT_STRUCT);
#endif

    /* SW_WATCHDOGS structs */
#if MQX_USE_SW_WATCHDOGS
    _mem_free((void *)& MQX_WATCHDOG_ALARM_TABLE_STRUCT);
    _mem_free((void *)& MQX_WATCHDOG_COMPONENT_STRUCT);
#endif

    /* NIO */
    _mem_free((void *)& MQX_NIO_DEV_FN_STRUCT);
    _mem_free((void *)& MQX_NIO_DEV_STRUCT);

    /* STDLIB */
    _mem_free((void *)& MQX_FILE_STRUCT);

    /* SHELL */
    _mem_free((void *)& MQX_SHELL_COMMAND_STRUCT);
    _mem_free((void *)& MQX_SHELL_GETOPT_CONTEXT);

    /* MFS */
    _mem_free((void *)& MQX_MFS_FORMAT_DATA);
    _mem_free((void *)& MQX_MFS_IOCTL_FORMAT_PARAM);
    _mem_free((void *)& MQX_MFS_INTERNAL_SEARCH);
    _mem_free((void *)& MQX_MFS_SEARCH_DATA);
    _mem_free((void *)& MQX_MFS_SEARCH_PARAM);
    _mem_free((void *)& MQX_MFS_RENAME_PARAM);
    _mem_free((void *)& MQX_MFS_FILE_ATTR_PARAM);
    _mem_free((void *)& MQX_MFS_GET_LFN_STRUCT);
    _mem_free((void *)& MQX_MFS_DATE_TIME_PARAM);

    _mem_free((void *)& MQX_ESDHC_COMMAND_STRUCT);
    _mem_free((void *)& MQX_ESDHC_INIT_STRUCT);

    _mem_free((void *)& MQX_PMGR_PART_ENTRY_STRUCT);
    _mem_free((void *)& MQX_PMGR_PART_INFO_STRUCT);
    _mem_free((void *)& MQX_PART_MGR_STRUCT);

    _mem_free((void *)& MQX_SDCARD_CONST_INIT_STRUCT);
    _mem_free((void *)& MQX_SDCARD_INIT_STRUCT);

    /* RTCS */
    _mem_free((void *)& MQX_BOOTP_DATA_STRUCT);
    _mem_free((void *)& MQX_IPCP_DATA_STRUCT);
    _mem_free((void *)& MQX_DHCPSRV_DATA_STRUCT);
    _mem_free((void *)& MQX_TCPIP_PARM);
    _mem_free((void *)& MQX_PING_PARAM_STRUCT);
    _mem_free((void *)& MQX_addrinfo);

    _mem_free((void *)& MQX_IP_DNS_ENTRY);
    _mem_free((void *)& MQX_IP_IF);

#if RTCSCFG_ENABLE_MLD
    _mem_free((void *)& MQX_MLD_HEADER);
    _mem_free((void *)& MQX_MLD_RA_OPTION_HEADER);
#endif

    _mem_free((void *)& MQX_FTPSRV_AUTH_STRUCT);
    _mem_free((void *)& MQX_FTPSRV_PARAM_STRUCT);

    _mem_free((void *)& MQX_FTPc_CONTEXT_STRUCT);
    _mem_free((void *)& MQX_FTPc_COMMAND_STRUCT);

    _mem_free((void *)& MQX_TFTPCLN_PARAM_STRUCT);

    _mem_free((void *)& MQX_TFTPSRV_PARAM_STRUCT);

#if SHELLCFG_USES_RTCS
    _mem_free((void *)& Telnetsrv_shell_commands);
    _mem_free((void *)& FTPc_commands);
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: event
* Comments     :
*   This function calls EVENT API functions with certain parameters
*   in order to verify the code size of EVENT components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void event(void)
{
#if MQX_USE_EVENTS && MQX_USE_NAME
    void *handle = NULL;
    _mqx_uint value = 0;

    IF_SMALL(_event_create_component(1, 1, 1));
    IF_SMALL(_event_create_auto_clear("e"));
    IF_SMALL(_event_create("e"));
    IF_SMALL(_event_destroy("e"));
    IF_SMALL(_event_open("e", &handle));
    IF_SMALL(_event_close(handle));
    IF_SMALL(_event_set(handle, 0));
    IF_SMALL(_event_clear(handle, 0));
    IF_SMALL(_event_wait_all_ticks(handle, 0, 0));
    IF_SMALL(_event_wait_any_ticks(handle, 0, 0));

    IF_TYPICAL(_event_create_fast(1));
    IF_TYPICAL(_event_create_fast_auto_clear(1));
    IF_TYPICAL(_event_destroy_fast(1));
    IF_TYPICAL(_event_wait_all(handle, 0, 0));
    IF_TYPICAL(_event_wait_any(handle, 0, 0));

    IF_MAX(_event_get_value(handle, &value));
    IF_MAX(_event_get_wait_count(handle));
    IF_MAX(_event_open_fast(1, &handle));
    IF_MAX(_event_test(&handle));
    IF_MAX(_event_wait_all_for(handle, 0, NULL));
    IF_MAX(_event_wait_all_until(handle, 0, NULL));
    IF_MAX(_event_wait_any_for(handle, 0, NULL));
    IF_MAX(_event_wait_any_until(handle, 0, NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: isr
* Comments     :
*   This function is used as parameter for INTERRUPT functions
*
*END*--------------------------------------------------------------------*/
static void isr(void *p) {}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: kisr
* Comments     :
*   This function is used as parameter for INTERRUPT functions
*
*END*--------------------------------------------------------------------*/
static void kisr(void) {}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: interrupts
* Comments     :
*   This function calls INTERRUPT API functions with certain parameters
*   in order to verify the code size of INTERRUPT components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void interrupts(void)
{
#if MQX_USE_INTERRUPTS
    _mqx_max_type vt = 0;
    void *m = NULL;

    IF_TINY(_int_disable());
    IF_TINY(_int_enable());
    IF_TINY(_int_init(0, 0));
    IF_TINY(_int_install_default_isr(_int_default_isr));
    IF_TINY(_int_default_isr(0));
    IF_TINY(_int_install_isr(0, isr, 0));
    IF_TINY(_int_get_vector_table());
    IF_TINY(_int_set_vector_table(vt));

    IF_SMALL(_int_get_isr(0));
    IF_SMALL(_int_get_isr_data(0));
    IF_SMALL(_int_set_isr_data(1, m));

#if MQXCFG_EXCEPTION_HANDLING
    IF_TYPICAL(_int_install_exception_isr());
    IF_TYPICAL(_int_exception_isr(0));
#endif

    IF_TYPICAL(_int_install_unexpected_isr());
    IF_TYPICAL(_int_unexpected_isr(0));

    IF_MAX(_int_install_kernel_isr(0, kisr));
    
#if MQXCFG_EXCEPTION_HANDLING
    IF_MAX(_int_get_exception_handler(1));
    IF_MAX(_int_set_exception_handler(1, NULL));
#endif

    IF_MAX(_int_get_default_isr());
    IF_MAX(_int_get_isr_depth());
    IF_MAX(_int_get_kernel_isr(0));

#if MQX_EXIT_ENABLED
    IF_MAX(_int_get_previous_vector_table());
#endif
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: klog
* Comments     :
*   This function calls KLOG API functions with certain parameters
*   in order to verify the code size of KLOG components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void klog(void)
{
#if MQX_KERNEL_LOGGING
#if !MQXCFG_STATIC_KLOG
    IF_SMALL(_klog_create(0, 0));
#endif
    IF_SMALL(_klog_create_at(0, 0, NULL));
    IF_SMALL(_klog_control(0, 0));
    IF_SMALL(_klog_log(0, 0, 0, 0, 0, 0));

    IF_TYPICAL(_klog_display());
    IF_TYPICAL(_klog_enable_logging_task(0));
    IF_TYPICAL(_klog_disable_logging_task(0));

    IF_MAX(_klog_get_interrupt_stack_usage(NULL, NULL));
    IF_MAX(_klog_get_task_stack_usage(0, NULL, NULL));
    IF_MAX(_klog_show_stack_usage());
    IF_MAX(_klog_log_function(NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: log
* Comments     :
*   This function calls LOG API functions with certain parameters
*   in order to verify the code size of LOG components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void log(void)
{
#if MQX_USE_LOGS
    LOG_ENTRY_STRUCT l = {0};
    _mqx_uint log = 0;

    IF_SMALL(_log_create(0, 0, 0));
    IF_SMALL(_log_create_component());
    IF_SMALL(_log_read(0, 0, 0, &l));
    IF_SMALL(_log_write(0, 1, 0));

    IF_TYPICAL(_log_disable(0));
    IF_TYPICAL(_log_enable(0));

    IF_MAX(_log_reset(0));
    IF_MAX(_log_test(&log));
    IF_MAX(_log_destroy(0));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwevent
* Comments     :
*   This function calls LWEVENT API functions with certain parameters
*   in order to verify the code size of LWEVENT components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwevent(void)
{
#if MQX_USE_LWEVENTS
    IF_TINY(_lwevent_create(NULL, 0));
    IF_TINY(_lwevent_clear(NULL, 0));
    IF_TINY(_lwevent_set(NULL, 0));
    IF_TINY(_lwevent_set_auto_clear(NULL, 0));
    IF_TINY(_lwevent_wait_ticks(NULL, 0, 0, 0));
    IF_TINY(_lwevent_destroy(NULL));

    IF_TYPICAL(_lwevent_wait_for(NULL, 0, 0, 0));
    IF_TYPICAL(_lwevent_wait_until(NULL, 0, 0, 0));

    IF_MAX(_lwevent_test(NULL, NULL));
    IF_MAX(_lwevent_get_signalled());
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwlog
* Comments     :
*   This function calls LWLOG API functions with certain parameters
*   in order to verify the code size of LWLOG components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwlog(void)
{
#if MQX_USE_LWLOGS
    LWLOG_ENTRY_STRUCT l = {0};
    _mqx_uint lwlog = 0;

#if MQXCFG_STATIC_LWLOG
    IF_SMALL(_lwlog_create(0, 0, 0));
#endif
    IF_SMALL(_lwlog_create_at(0, 0, 0, NULL));
    IF_SMALL(_lwlog_create_component());
    IF_SMALL(_lwlog_write(1, 1, 2, 3, 4, 5, 6, 7));
    IF_SMALL(_lwlog_read(0, 0, &l));
    IF_SMALL(_lwlog_destroy(0));

    IF_TYPICAL(_lwlog_disable(0));
    IF_TYPICAL(_lwlog_enable(0));

    IF_MAX(_lwlog_reset(0));
    IF_MAX(_lwlog_test(&lwlog));
    IF_MAX(_lwlog_calculate_size(0));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwmem
* Comments     :
*   This function calls LWMEM API functions with certain parameters
*   in order to verify the code size of LWMEM components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwmem(void)
{
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_LWMEM
    IF_TINY(_lwmem_create_pool(NULL, NULL, 0));
    IF_TINY(_lwmem_alloc(0));
    IF_TINY(_lwmem_alloc_system(0));
    IF_TINY(_lwmem_free(NULL));

    IF_TYPICAL(_lwmem_alloc_at(0, NULL));
    IF_TYPICAL(_lwmem_alloc_align(0, 0));
    IF_TYPICAL(_lwmem_alloc_zero(0));
    IF_TYPICAL(_lwmem_alloc_system_align(0, 0));
    IF_TYPICAL(_lwmem_alloc_system_zero(0));
    IF_TYPICAL(_lwmem_realloc(NULL, 0));
    IF_TYPICAL(_lwmem_alloc_from(NULL, 0));
    IF_TYPICAL(_lwmem_alloc_align_from(NULL, 0, 0));
    IF_TYPICAL(_lwmem_alloc_zero_from(NULL, 0));
    IF_TYPICAL(_lwmem_alloc_system_align_from(NULL, 0, 0));
    IF_TYPICAL(_lwmem_alloc_system_from(NULL, 0));
    IF_TYPICAL(_lwmem_alloc_system_zero_from(NULL, 0));

    IF_MAX(_lwmem_get_system_pool_id());
    IF_MAX(_lwmem_transfer(NULL, 0, 0));
    IF_MAX(_lwmem_get_highwater());
    IF_MAX(_lwmem_get_free());
    IF_MAX(_lwmem_get_free_from(NULL));
#if MQX_ALLOW_TYPED_MEMORY
    IF_MAX(_lwmem_set_type(NULL, 0));
    IF_MAX(_lwmem_get_type(NULL));
#endif
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwmsgq
* Comments     :
*   This function calls LWMSGQ API functions with certain parameters
*   in order to verify the code size of LWMSGQ components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwmsgq(void)
{
#if MQX_USE_LWMSGQ
    IF_TINY(_lwmsgq_init(NULL, 0, 0));
    IF_TINY(_lwmsgq_deinit(NULL));
    IF_TINY(_lwmsgq_send(NULL, NULL, 0));
    IF_TINY(_lwmsgq_receive(NULL, NULL, 0, 0, NULL));
#endif
}


/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwsem
* Comments     :
*   This function calls LWSEM API functions with certain parameters
*   in order to verify the code size of LWSEM components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwsem(void)
{
    LWSEM_STRUCT lwsem = {0};
    void *p = NULL;

    IF_TINY(_lwsem_create(&lwsem, 1));
    IF_TINY(_lwsem_destroy(&lwsem));
    IF_TINY(_lwsem_post(&lwsem));
    IF_TINY(_lwsem_wait_ticks(&lwsem, 1));

    IF_TYPICAL(_lwsem_wait(&lwsem));
    IF_TYPICAL(_lwsem_poll(&lwsem));

    IF_MAX(_lwsem_wait_for(&lwsem, NULL));
    IF_MAX(_lwsem_wait_until(&lwsem, NULL));
    IF_MAX(_lwsem_test(&p, &p));
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: lwtimer
* Comments     :
*   This function calls LWTIMER API functions with certain parameters
*   in order to verify the code size of LWTIMER components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void lwtimer(void)
{
#if MQX_USE_LWTIMER
    IF_SMALL(_lwtimer_add_timer_to_queue(NULL, NULL, 0, (void (_CODE_PTR_)(void *))NULL, NULL));
    IF_SMALL(_lwtimer_create_periodic_queue(NULL, 0, 0));

    IF_MAX(_lwtimer_cancel_period(NULL));
    IF_MAX(_lwtimer_cancel_timer(NULL));
    IF_MAX(_lwtimer_test(NULL, NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: mem
* Comments     :
*   This function calls MEM API functions with certain parameters
*   in order to verify the code size of MEM components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void mem(void)
{
#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_MEM
    IF_SMALL(_mem_create_pool(NULL, 0));
    IF_SMALL(_mem_alloc(0));
    IF_SMALL(_mem_free(NULL));

    IF_TYPICAL(_mem_alloc_at(0, NULL));
    IF_TYPICAL(_mem_alloc_align(0, 0));
    IF_TYPICAL(_mem_alloc_zero(0));
    IF_TYPICAL(_mem_alloc_system(0));
    IF_TYPICAL(_mem_alloc_system_align(0, 0));
    IF_TYPICAL(_mem_alloc_system_zero(0));
    IF_TYPICAL(_mem_realloc(NULL, 0));
    IF_TYPICAL(_mem_free_part(NULL, 0));
    IF_TYPICAL(_mem_alloc_from(NULL, 0));
    IF_TYPICAL(_mem_alloc_align_from(NULL, 0, 0));
    IF_TYPICAL(_mem_alloc_zero_from(NULL, 0));
    IF_TYPICAL(_mem_alloc_system_align_from(NULL, 0, 0));
    IF_TYPICAL(_mem_alloc_system_from(NULL, 0));
    IF_TYPICAL(_mem_alloc_system_zero_from(NULL, 0));

    IF_MAX(_mem_extend(NULL, 0));
    IF_MAX(_mem_extend_pool(NULL, NULL, 0));
    IF_MAX(_mem_get_highwater());
    IF_MAX(_mem_get_error());
    IF_MAX(_mem_get_error_pool(NULL));
    IF_MAX(_mem_get_highwater_pool(NULL));
    IF_MAX(_mem_get_size(NULL));
    IF_MAX(_mem_get_system_pool_id());
    IF_MAX(_mem_sum_ip(0, 0, NULL));
    IF_MAX(_mem_swap_endian(NULL, NULL));
    IF_MAX(_mem_swap_endian_len(NULL, NULL, 0));
    IF_MAX(_mem_test());
    IF_MAX(_mem_test_all(NULL));
    IF_MAX(_mem_test_pool(NULL));
    IF_MAX(_mem_test_and_set(NULL));
    IF_MAX(_mem_transfer(NULL, 0, 0));
#if MQX_USE_UNCACHED_MEM && PSP_HAS_DATA_CACHE
    IF_MAX(_mem_alloc_uncached(0));
    IF_MAX(_mem_alloc_align_uncached(0, 0));
    IF_MAX(_mem_alloc_system_uncached(0));
    IF_MAX(_mem_alloc_system_zero_uncached(0));
#endif
    IF_MAX(_mem_set_type(NULL, 0));
    IF_MAX(_mem_get_type(NULL));
#if MQXCFG_MEM_COPY || (MQXCFG_MEM_COPY_NEON && PSP_HAS_FPU)
    IF_MAX(_mem_copy(NULL, NULL, 0));
#endif
#if MQX_USE_MEM_ZERO
    IF_MAX(_mem_zero(NULL, 0));
#endif
#if MQXCFG_MEM_COPY_NEON && PSP_HAS_FPU
    IF_MAX(neon_copy_offset_0(NULL, NULL, 0));
    IF_MAX(neon_copy_offset_1(NULL, NULL, 0));
    IF_MAX(neon_copy_offset_2(NULL, NULL, 0));
    IF_MAX(neon_copy_offset_3(NULL, NULL, 0));
#endif
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: msg_func
* Comments     :
*   This function is used as parameter for MESSAGE functions
*
*END*--------------------------------------------------------------------*/
static void msg_func(void *p) {}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: message
* Comments     :
*   This function calls MESSAGE API functions with certain parameters
*   in order to verify the code size of MESSAGE components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void message(void)
{
#if MQX_USE_MESSAGES
    void (_CODE_PTR_  *f)(void *) = NULL;
    MESSAGE_HEADER_STRUCT_PTR m = NULL;
    void *n = NULL;
    _pool_id  p = 0;
    _queue_id q = 0;
    unsigned char c[4] = {0};

    IF_SMALL(_msg_alloc(p));
    IF_SMALL(_msg_create_component());
    IF_SMALL(_msg_free(m));
    IF_SMALL(_msgpool_create(0, 0, 0, 0));
    IF_SMALL(_msgq_open(0, 0));
    IF_SMALL(_msgq_close(q));
    IF_SMALL(_msgq_receive_ticks(q, 0));
    IF_SMALL(_msgq_receive(q, 0));
    IF_SMALL(_msgq_send(m));

    IF_TYPICAL(_msg_alloc_system(0));
    IF_TYPICAL(_msg_available(p));
    IF_TYPICAL(_msgpool_create_system(0, 0, 0, 0));
    IF_TYPICAL(_msgpool_destroy(p));
    IF_TYPICAL(_msgq_get_count(q));
    IF_TYPICAL(_msgq_open_system(0, 0, msg_func, 0));
    IF_TYPICAL(_msgq_poll(q));
    IF_TYPICAL(_msgq_send_urgent(m));
    IF_TYPICAL(_msgq_send_priority(m, 1));
    IF_TYPICAL(_msgq_set_notification_function(q, (void (_CODE_PTR_)(void *))NULL, m));

    IF_MAX(_msg_swap_endian_data(c, m));
    IF_MAX(_msg_swap_endian_header(m));
    IF_MAX(_msgpool_test(&n, &n));
    IF_MAX(_msgq_get_id(0, 0));
    IF_MAX(_msgq_get_owner(q));
    IF_MAX(_msgq_get_notification_function(q, f, &n));
    IF_MAX(_msgq_peek(q));
    IF_MAX(_msgq_receive_for(q, NULL));
    IF_MAX(_msgq_receive_until(q, NULL));
    IF_MAX(_msgq_send_broadcast(m, &q, p));
    IF_MAX(_msgq_send_queue(m, q));
    IF_MAX(_msgq_test(&n, &n));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: mmu
* Comments     :
*   This function calls MMU API functions with certain parameters
*   in order to verify the code size of MMU components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void mmu(void)
{
#if PSP_HAS_MMU
    IF_MAX(_mmu_add_region(NULL, 0, 0));
    IF_MAX(_mmu_disable());
    IF_MAX(_mmu_enable());
    IF_MAX(_mmu_init(NULL));
    IF_MAX(_mmu_add_vregion(NULL, NULL, 0, 0));
    IF_MAX(_mmu_get_vpage_size());
    IF_MAX(_mmu_get_vmem_attributes(NULL, NULL, NULL, NULL, NULL));
    IF_MAX(_mmu_set_vmem_attributes(NULL, 0, 0));
    IF_MAX(_mmu_vinit(0, NULL));
    IF_MAX(_mmu_venable());
    IF_MAX(_mmu_vdisable());
    IF_MAX(_mmu_vtop(NULL, NULL));
    IF_MAX(_mmu_add_vcontext(0, NULL, 0, 0));
    IF_MAX(_mmu_create_vcontext(0));
    IF_MAX(_mmu_create_vtask(0, 0, NULL, NULL, 0, 0));
    IF_MAX(_mmu_destroy_vcontext(0));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: mqx
* Comments     :
*   This function calls MQX API functions with certain parameters
*   in order to verify the code size of MQX components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void mqx(void)
{
    IF_TINY(_mqx_get_kernel_data());
    IF_TINY(_mqx_get_initialization());
    IF_TINY(_mqx_get_system_task_id());
    IF_TINY(_mqx_set_cpu_type(0));
#if MQX_USE_IDLE_TASK
    IF_TINY(_mqx_idle_task(0));
#endif

    IF_TYPICAL(_mqx_exit(1));
    IF_TYPICAL(_mqx_fatal_error(0));
    IF_TYPICAL(_mqx_get_cpu_type());
#if MQX_KD_HAS_COUNTER
    IF_TYPICAL(_mqx_get_counter());
#endif
    IF_TYPICAL(_mqx_get_idle_loop_count(NULL));
    IF_TYPICAL(_mqx_set_exit_handler((void (_CODE_PTR_)(void))NULL));
    IF_TYPICAL(_mqx_get_exit_handler());

#if MQX_TAD_RESERVED_ENABLE
    IF_MAX(_mqx_get_tad_data(NULL));
    IF_MAX(_mqx_set_tad_data(NULL, NULL));
#endif
#if MQX_USE_IO_COMPONENTS
    IF_MAX(_mqx_get_io_component_handle(0));
    IF_MAX(_mqx_set_io_component_handle(0, NULL));
    IF_MAX(_mqx_link_io_component_handle(0, NULL, NULL));
    IF_MAX(_mqx_unlink_io_component_handle(0, NULL, NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: mutex
* Comments     :
*   This function calls MUTEX API functions with certain parameters
*   in order to verify the code size of MUTEX components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void mutex(void)
{
#if MQX_USE_MUTEXES
     MUTEX_ATTR_STRUCT a = {0};
     MUTEX_STRUCT      m = {0};
     void              *mp = NULL;
     _mqx_uint         p = 0;

    IF_SMALL(_mutatr_init(&a));
    IF_SMALL(_mutex_create_component());
    IF_SMALL(_mutex_init(&m, &a));
    IF_SMALL(_mutex_lock(&m));
    IF_SMALL(_mutex_unlock(&m));
    IF_SMALL(_mutex_destroy(&m));
    IF_SMALL(_mutatr_destroy(&a));

    IF_TYPICAL(_mutatr_set_sched_protocol(&a, p));
    IF_TYPICAL(_mutatr_set_wait_protocol(&a, p));
    IF_TYPICAL(_mutex_try_lock(&m));
    IF_TYPICAL(_mutatr_set_priority_ceiling(&a, p));
    IF_TYPICAL(_mutatr_set_spin_limit(&a, p));
    IF_TYPICAL(_mutex_set_priority_ceiling(&m, p, &p));

    IF_MAX(_mutatr_get_priority_ceiling(&a, &p));
    IF_MAX(_mutatr_get_sched_protocol(&a, &p));
    IF_MAX(_mutatr_get_spin_limit(&a, &p));
    IF_MAX(_mutatr_get_wait_protocol(&a, &p));
    IF_MAX(_mutatr_get_priority_ceiling(&a, &p));
    IF_MAX(_mutex_get_priority_ceiling(&m, &p));
    IF_MAX(_mutex_get_wait_count(&m));
    IF_MAX(_mutex_test(&mp));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: name
* Comments     :
*   This function calls NAME API functions with certain parameters
*   in order to verify the code size of NAME components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void name(void)
{
#if MQX_USE_NAME
    _mqx_max_type   value = 0;
    void            *mp = NULL;
    char            s[4] = {0};

    IF_SMALL(_name_create_component(0, 0, 0));
    IF_SMALL(_name_add("", 0));
    IF_SMALL(_name_delete(""));
    IF_SMALL(_name_find("", &value));

    IF_MAX(_name_find_by_number(0, s));
    IF_MAX(_name_test(&mp, &mp));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: part
* Comments     :
*   This function calls PART API functions with certain parameters
*   in order to verify the code size of PART components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void part(void)
{
#if MQX_USE_PARTITIONS
   _partition_id p = 0;
   void          *m = 0;
   _task_id      t = 0;

    IF_SMALL(_partition_alloc(p));
    IF_SMALL(_partition_create_component());
    IF_SMALL(_partition_create(0, 0, 0, 0));
    IF_SMALL(_partition_free(m));
    IF_SMALL(_partition_destroy(p));

    IF_TYPICAL(_partition_create_at(0, 0, 0));
    IF_TYPICAL(_partition_alloc_system(p));
    IF_TYPICAL(_partition_alloc_system_zero(p));
    IF_TYPICAL(_partition_alloc_zero(p));
    IF_TYPICAL(_partition_extend(p, 0, 0));

    IF_MAX(_partition_calculate_size(0,0));
    IF_MAX(_partition_calculate_blocks(0,0));
    IF_MAX(_partition_get_free_blocks(p));
    IF_MAX(_partition_get_max_used_blocks(p));
    IF_MAX(_partition_get_total_blocks(p));
    IF_MAX(_partition_get_block_size(p));
    IF_MAX(_partition_get_total_size(p));
    IF_MAX(_partition_get_number_of());
    IF_MAX(_partition_test(&p, &m, &m));
    IF_MAX(_partition_transfer(m, t));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: psp
* Comments     :
*   This function calls PSP API functions with certain parameters
*   in order to verify the code size of PSP components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void psp(void)
{
#if MQX_HAS_TICK
    IF_TINY(_psp_add_ticks(NULL, NULL, NULL));
    IF_TINY(_psp_subtract_ticks(NULL, NULL, NULL));
    IF_TINY(_psp_subtract_ticks_int32(NULL, NULL, NULL));
    IF_TINY(_psp_normalize_ticks(NULL));
#if 0 /* TODO: Hasn't been implemented */
    _psp_mul_ticks_by_32(NULL, 0, NULL);
#endif

    IF_TYPICAL(_psp_ticks_to_milliseconds(NULL, NULL));
    IF_TYPICAL(_psp_ticks_to_milliseconds_truncate(NULL, NULL));
    IF_TYPICAL(_psp_msecs_to_ticks(0, NULL));
    IF_TYPICAL(_psp_msecs_to_ticks_quick(0, NULL));
    IF_TYPICAL(_psp_get_elapsed_milliseconds());
    IF_TYPICAL(_psp_ticks_to_time(NULL, NULL));
    IF_TYPICAL(_psp_time_to_ticks(NULL, NULL));

    IF_MAX(_psp_ticks_to_days(NULL, NULL));
    IF_MAX(_psp_ticks_to_hours(NULL, NULL));
    IF_MAX(_psp_ticks_to_minutes(NULL, NULL));
    IF_MAX(_psp_ticks_to_seconds(NULL, NULL));
    IF_MAX(_psp_ticks_to_microseconds(NULL, NULL));
    IF_MAX(_psp_ticks_to_microseconds_truncate(NULL, NULL));
    IF_MAX(_psp_ticks_to_nanoseconds(NULL, NULL));
    IF_MAX(_psp_ticks_to_nanoseconds_truncate(NULL, NULL));
    IF_MAX(_psp_ticks_to_picoseconds(NULL, NULL));
    IF_MAX(_psp_ticks_to_picoseconds_truncate(NULL, NULL));

    IF_MAX(_psp_days_to_ticks(0, NULL));
    IF_MAX(_psp_hours_to_ticks(0, NULL));
    IF_MAX(_psp_minutes_to_ticks(0, NULL));
    IF_MAX(_psp_seconds_to_ticks(0, NULL));
    IF_MAX(_psp_usecs_to_ticks(0, NULL));
    IF_MAX(_psp_nsecs_to_ticks(0, NULL));
    IF_MAX(_psp_psecs_to_ticks(0, NULL));
    IF_MAX(_psp_print_ticks(NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: queues
* Comments     :
*   This function calls QUEUES API functions with certain parameters
*   in order to verify the code size of QUEUES components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void queues(void)
{
    QUEUE_STRUCT q = {0};
    void         *m = NULL;

    IF_TINY(_queue_init(&q, 1));
    IF_TINY(_queue_enqueue(&q, m));
    IF_TINY(_queue_dequeue(&q));
    IF_TINY(_queue_unlink(&q, m));

    IF_TYPICAL(_queue_get_size(&q));
    IF_TYPICAL(_queue_head(&q));
    IF_TYPICAL(_queue_next(&q, m));
    IF_TYPICAL(_queue_insert(&q, m, m));
    IF_TYPICAL(_queue_is_empty(&q));
    IF_TYPICAL(_queue_test(&q, m));
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: sched
* Comments     :
*   This function calls SCHED API functions with certain parameters
*   in order to verify the code size of SCHED components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void sched(void)
{
    MQX_TICK_STRUCT ticks = {0};
    _task_id        t = 0;
    _mqx_uint       p = 0;
    uint32_t        u = 0;

    IF_TINY(_sched_yield());
    IF_TINY(_sched_get_max_priority(0));
    IF_TINY(_sched_get_min_priority(0));

#if MQX_HAS_TIME_SLICE
    IF_TYPICAL(_sched_set_rr_interval(t, 1));
    IF_TYPICAL(_sched_set_rr_interval_ticks(t, &ticks, &ticks));
#endif

#if MQX_HAS_TIME_SLICE
    IF_MAX(_sched_get_rr_interval(t, &u));
    IF_MAX(_sched_get_rr_interval_ticks(t, &ticks));
    IF_MAX(_sched_set_policy(t, 1));
#endif
    IF_MAX(_sched_get_policy(t, &p));
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: sem
* Comments     :
*   This function calls API functions with certain parameters
*   in order to verify the code size of SEM components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void sem(void)
{
#if MQX_USE_SEMAPHORES
    void   *sem = NULL;

    IF_SMALL(_sem_create("", 0, 0));
    IF_SMALL(_sem_destroy("", 0));
    IF_SMALL(_sem_create_component(0, 0, 0));
    IF_SMALL(_sem_open("", &sem));
    IF_SMALL(_sem_close(sem));
    IF_SMALL(_sem_post(sem));
    IF_SMALL(_sem_wait_ticks(sem, 0));

    IF_TYPICAL(_sem_wait(sem, 0));
    IF_TYPICAL(_sem_wait_for(sem, NULL));
    IF_TYPICAL(_sem_wait_until(sem, NULL));

    IF_MAX(_sem_open_fast(1, &sem));
    IF_MAX(_sem_create_fast(1, 0, 0));
    IF_MAX(_sem_destroy_fast(1, 0));
    IF_MAX(_sem_get_wait_count(sem));
    IF_MAX(_sem_test(&sem));
    IF_MAX(_sem_get_value(sem));
#endif
}



/*FUNCTION*----------------------------------------------------------------
*
* Function name: task
* Comments     :
*   This function calls TASK MESSAGE API functions with certain parameters
*   in order to verify the code size of TASK components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void task(void)
{
    _task_id  t = 0;
    _mqx_uint p = 0;
    void      *m = NULL;

    IF_TINY(_task_block());
    IF_TINY(_task_create(0, 0, 0));
    IF_TINY(_task_create_blocked(0, 0, 0));
    IF_TINY(_task_destroy(t));
    IF_TINY(_task_get_td(t));
    IF_TINY(_task_get_template_index(""));
    IF_TINY(_task_get_priority(t, &p));
    IF_TINY(_task_set_priority(t, p, &p));

    IF_SMALL(_task_set_error(0));
    IF_SMALL(_task_get_error());
    IF_SMALL(_task_ready(m));
#if MQX_HAS_DYNAMIC_PRIORITIES
#endif
    IF_SMALL(_task_stop_preemption());
    IF_SMALL(_task_start_preemption());

    IF_TYPICAL(_task_restart(t, NULL, 0));
    IF_TYPICAL(_task_abort(t));
    IF_TYPICAL(_task_create_at(0, 0, 0, NULL, 0));
    IF_TYPICAL(_task_allow_preemption());
    IF_TYPICAL(_task_get_template_ptr(0));

    IF_MAX(_task_check_stack());
#if PSP_HAS_FPU
    IF_MAX(_task_disable_fp());
    IF_MAX(_task_enable_fp());
#endif
#if MQX_TD_HAS_PARENT
    IF_MAX(_task_get_creator());
#endif
#if MQX_HAS_TASK_ENVIRONMENT
    IF_MAX(_task_get_environment(t));
    IF_MAX(_task_set_environment(t, m));
#endif
#if MQXCFG_EXCEPTION_HANDLING
    IF_MAX(_task_get_exception_handler(t));
    IF_MAX(_task_set_exception_handler(t, (void (_CODE_PTR_)(uint32_t,void *))NULL));
#endif
#if MQX_TD_HAS_ERROR_CODE
    IF_MAX(_task_get_error_ptr());
#endif
#if MQX_HAS_EXIT_HANDLER
    IF_MAX(_task_get_exit_handler(t));
    IF_MAX(_task_set_exit_handler(t, (void (_CODE_PTR_)(void))NULL));
#endif
    IF_MAX(_task_get_id());
    IF_MAX(_task_get_id_from_td(NULL));
#if MQX_TD_HAS_TASK_TEMPLATE_PTR
    IF_MAX(_task_get_id_from_name(""));
    IF_MAX(_task_get_index_from_id(t));
#endif
    IF_MAX(_task_get_parameter());
    IF_MAX(_task_get_parameter_for(t));
    IF_MAX(_task_get_processor(t));
    IF_MAX(_task_set_parameter(0));
    IF_MAX(_task_set_parameter_for(0, t));
#if MQX_EXTRA_TASK_STACK_ENABLE
    IF_MAX(_task_reserve_space(0));
    IF_MAX(_task_get_reserved_base());
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: taskq
* Comments     :
*   This function calls TASKQ API functions with certain parameters
*   in order to verify the code size of TASKQ components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void taskq(void)
{
#if MQXCFG_ALLOCATOR
    void *tq = NULL;
    _task_id t = 0;

    IF_TINY(_taskq_create(0));
    IF_TINY(_taskq_resume(tq, 0));
    IF_TINY(_taskq_suspend(tq));
    IF_TINY(_taskq_destroy(tq));

    IF_TYPICAL(_taskq_get_value(tq));

    IF_MAX(_taskq_suspend_task(t, tq));
    IF_MAX(_taskq_test(&tq, &tq));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: time
* Comments     :
*   This function calls TIME API functions with certain parameters
*   in order to verify the code size of TIME components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void time(void)
{
    MQX_TICK_STRUCT ticks = {0};
    TIME_STRUCT     time = {0};
    void            *m = 0;
    _task_id        t = 0;

    /* All PSP_* time functions except this one are called by other APIs */
    PSP_GET_ELAPSED_MILLISECONDS();

    IF_TINY(_time_delay_ticks(0));
    IF_TINY(_time_dequeue(t));
    IF_TINY(_time_get_ticks(&ticks));
    IF_TINY(_time_set_hwticks_per_tick(0));
    IF_TINY(_time_set_ticks(&ticks));
    IF_TINY(_time_init_ticks(NULL, 0));
    IF_TINY(_time_notify_kernel());

    IF_SMALL(_time_diff_ticks(NULL, NULL, NULL));
    IF_SMALL(_time_diff_ticks_int32(NULL, NULL, NULL));
    IF_SMALL(_time_get_elapsed_ticks(&ticks));
    IF_SMALL(_time_get_elapsed_ticks_fast(NULL));
    IF_SMALL(_time_get_hwticks_per_tick());

    IF_TYPICAL(_time_get(&time));
    IF_TYPICAL(_time_get_elapsed(&time));
    IF_TYPICAL(_time_diff(NULL, NULL, NULL));
    IF_TYPICAL(_time_delay(0));
    IF_TYPICAL(_time_delay_for(NULL));
    IF_TYPICAL(_time_delay_until(NULL));
    IF_TYPICAL(_time_set(&time));
    IF_TYPICAL(_time_diff_milliseconds(NULL, NULL, NULL));

    IF_MAX(_time_to_ticks(&time, &ticks));
    IF_MAX(_time_add_day_to_ticks(NULL, 0));
    IF_MAX(_time_add_hour_to_ticks(NULL, 0));
    IF_MAX(_time_add_min_to_ticks(NULL, 0));
    IF_MAX(_time_add_msec_to_ticks(NULL, 0));
    IF_MAX(_time_add_nsec_to_ticks(NULL, 0));
    IF_MAX(_time_add_sec_to_ticks(NULL, 0));
    IF_MAX(_time_add_usec_to_ticks(NULL, 0));
    IF_MAX(_time_add_psec_to_ticks(NULL, 0));
    IF_MAX(_time_dequeue_td(m));
    IF_MAX(_time_set_ticks_per_sec(0));
    IF_MAX(_time_from_date(m, &time));
    IF_MAX(_time_diff_days(NULL, NULL, NULL));
    IF_MAX(_time_diff_hours(NULL, NULL, NULL));
    IF_MAX(_time_diff_minutes(NULL, NULL, NULL));
    IF_MAX(_time_diff_nanoseconds(NULL, NULL, NULL));
    IF_MAX(_time_diff_picoseconds(NULL, NULL, NULL));
    IF_MAX(_time_diff_seconds(NULL, NULL, NULL));
    IF_MAX(_time_diff_microseconds(NULL, NULL, NULL));
    IF_MAX(_time_get_hwticks());
    IF_MAX(_time_get_microseconds());
    IF_MAX(_time_get_nanoseconds());
    IF_MAX(_time_get_resolution());
    IF_MAX(_time_get_ticks_per_sec());
    IF_MAX(_time_set_hwtick_function((uint32_t (_CODE_PTR_)(void *))NULL, NULL));
    IF_MAX(_time_set_resolution(0));
    IF_MAX(_time_set_timer_vector(0));
    IF_MAX(_time_to_date(&time, m));
    IF_MAX(_ticks_to_time(&ticks, &time));
#if MQX_STD_TIME_API
    IF_MAX(mktime(NULL));
    IF_MAX(gmtime_r(NULL, NULL));
    IF_MAX(timegm(NULL));
    IF_MAX(localtime_r(NULL, NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: timer_func
* Comments     :
*   This function is used as parameter for TIMER functions
*
*END*--------------------------------------------------------------------*/
static void timer_func(uint32_t x1, void* x2, MQX_TICK_STRUCT_PTR x3) {}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: timer_func2
* Comments     :
*   This function is used as parameter for TIMER functions
*
*END*--------------------------------------------------------------------*/
static void timer_func2(uint32_t x1, void* x2, uint32_t x3, uint32_t x4) {}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: timer
* Comments     :
*   This function calls TIMER API functions with certain parameters
*   in order to verify the code size of TIMER components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void timer(void)
{
#if MQX_USE_TIMER
    TIME_STRUCT time = {0};

    IF_SMALL(_timer_create_component(1, 4000));
    IF_SMALL(_timer_start_periodic_every_ticks(timer_func, 0, 0, 0));

    IF_TYPICAL(_timer_start_oneshot_after_ticks(timer_func, 0, 0, 0));
    IF_TYPICAL(_timer_start_oneshot_after(timer_func2, 0, 0, 0));
    IF_TYPICAL(_timer_start_periodic_every(timer_func2, 0, 0, 0));
    IF_TYPICAL(_timer_cancel(0));

    IF_MAX(_timer_start_oneshot_at(timer_func2, 0, 0, NULL));
    IF_MAX(_timer_start_oneshot_at_ticks(timer_func, 0, 0, NULL));
    IF_MAX(_timer_start_periodic_at(timer_func2, NULL, 0, &time, 0));
    IF_MAX(_timer_start_periodic_at_ticks(timer_func, 0, 0, NULL, 0));
    IF_MAX(_timer_test(NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: err_func
* Comments     :
*   This function is used as parameter for WATCHDOG functions
*
*END*--------------------------------------------------------------------*/
static void err_func(void *p) {}


/*FUNCTION*----------------------------------------------------------------
*
* Function name: watchdog
* Comments     :
*   This function calls WATCHDOG API functions with certain parameters
*   in order to verify the code size of WATCHDOG components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void watchdog(void)
{
#if MQX_USE_SW_WATCHDOGS
    IF_TYPICAL(_watchdog_create_component(0, err_func));
    IF_TYPICAL(_watchdog_stop());
    IF_TYPICAL(_watchdog_start_ticks(0));

    IF_MAX(_watchdog_start(0));
    IF_MAX(_watchdog_test(NULL,NULL));
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: nio_func
* Comments     :
*   This function calls NIO API functions with certain parameters
*   in order to verify the code size of NIO components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void nio_func(int ar, ...)
{
    va_list varg;
    va_start(varg, ar);

    IF_SMALL(_nio_init(0, NULL));
    IF_SMALL(_nio_dev_install("", NULL, NULL, NULL));
    IF_SMALL(_nio_dev_uninstall("", NULL));
    IF_SMALL(_nio_dev_uninstall_force("", NULL));
    IF_SMALL(_nio_open("", 0, NULL));
    IF_SMALL(_nio_read(0, NULL, 0, NULL));
    IF_SMALL(_nio_write(0, NULL, 0, NULL));
    IF_SMALL(_nio_lseek(0, 0, 0, NULL));
    IF_SMALL(_nio_vioctl(0, NULL, 0, varg));
    IF_SMALL(_nio_close(0, NULL));

    va_end(varg);
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: stdlib_func
* Comments     :
*   This function calls MQX_STDLIB API functions with certain parameters
*   in order to verify the code size of MQX_STDLIB components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void stdlib_func(int ar, ...)
{
    va_list varg;
    va_start(varg, ar);

    IF_SMALL(strcasecmp(NULL, NULL));
    IF_SMALL(strncasecmp(NULL, NULL, 0));

    IF_TYPICAL(fopen(NULL, NULL));
    IF_TYPICAL(fclose(NULL));
    IF_TYPICAL(fread(NULL, 0, 0, NULL));
    IF_TYPICAL(fwrite(NULL, 0, 0, NULL));
    IF_TYPICAL(fgetc(NULL));
    IF_TYPICAL(fputc(0, NULL));
    IF_TYPICAL(fgets(NULL, 0, NULL));
    IF_TYPICAL(fputs(NULL, NULL));
    IF_TYPICAL(fscanf(NULL, "%d", 0));
    IF_TYPICAL(fprintf(NULL, "%d", 0));
    IF_TYPICAL(fseek(NULL, 0, 0));
    IF_TYPICAL(feof(NULL));
    IF_TYPICAL(ferror(NULL));
    IF_TYPICAL(fflush(NULL));

    IF_MAX(fdopen(0 , NULL));
    IF_MAX(fgetpos(NULL, NULL));
    IF_MAX(fsetpos(NULL, NULL));
    IF_MAX(ftell(NULL));
    IF_MAX(clearerr(NULL));
    IF_MAX(getc(NULL));
    IF_MAX(getchar());
    IF_MAX(gets(NULL));
    IF_MAX(printf("%d", 0));
    IF_MAX(putc(0, NULL));
    IF_MAX(putchar(0));
    IF_MAX(puts(NULL));
    IF_MAX(rewind(NULL));
    IF_MAX(scanf("%d", 0));
    IF_MAX(snprintf(NULL, 0, "%d", 0));
    IF_MAX(sprintf(NULL, "%d", 0));
    IF_MAX(sscanf(NULL, "%d", 0));
    IF_MAX(ungetc(0, NULL));
    IF_MAX(vfprintf(NULL, NULL, varg));
    IF_MAX(vprintf(NULL, varg));
    IF_MAX(vsnprintf(NULL, 0, NULL,varg));
    IF_MAX(vsprintf(NULL, NULL, varg));

    va_end(varg);
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: shell_func
* Comments     :
*   This function calls SHELL API functions with certain parameters
*   in order to verify the code size of SHELL components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void shell_func(void)
{
    const SHELL_COMMAND_STRUCT commands[] = {0};
    _enet_address enet_add;

    /* MQX Shell */
    IF_SMALL(Shell(commands, NULL));
    IF_SMALL(Shell_parse_command_line(NULL, NULL));
    IF_SMALL(Shell_command_list(0, NULL));
    IF_SMALL(Shell_exit(0, NULL));

    IF_TYPICAL(Shell_parse_number(NULL, NULL));
    IF_TYPICAL(Shell_abort(0, NULL));
    IF_TYPICAL(Shell_help(0, NULL));
    IF_TYPICAL(Shell_kill(0, NULL));
    IF_TYPICAL(Shell_pause(0, NULL));

    IF_MAX(Shell_check_help_request(0, NULL, NULL));
    IF_MAX(Shell_parse_uint_32(NULL, NULL));
    IF_MAX(Shell_parse_uint_16(NULL, NULL));
    IF_MAX(Shell_parse_int_32(NULL, NULL));
    IF_MAX(Shell_parse_hexnum(NULL, NULL));
    IF_MAX(Shell_getopt_init(NULL));
    IF_MAX(Shell_getopt(0, NULL, NULL, NULL));

    /* MFS Shell */
#if SHELLCFG_USES_MFS
    IF_SMALL(Shell_sh(0, NULL));
    IF_TYPICAL(Shell_get_current_filesystem(NULL));
    IF_TYPICAL(Shell_set_current_filesystem(NULL, 0));
    IF_TYPICAL(Shell_create_prefixed_filename(NULL, NULL, NULL));
    IF_MAX(Shell_get_current_filesystem_name(NULL));
    IF_MAX(Shell_set_current_filesystem_by_name(NULL, NULL));
#endif

    /* RTCS Shell */
#if SHELLCFG_USES_RTCS
    IF_SMALL(Shell_parse_ip_address(NULL, NULL));
    IF_SMALL(Shell_parse_netmask(NULL, NULL));
    IF_SMALL(Shell_parse_enet_address(0, enet_add));
    IF_SMALL(Shell_netstat(0, NULL));
    IF_SMALL(Shell_ping(0, NULL));

    IF_TYPICAL(Shell_FTP_client(0, NULL));
    IF_TYPICAL(Shell_telnetcln(0, NULL));
    IF_TYPICAL(Shell_tftpcln(0, NULL));
    IF_TYPICAL(Shell_ftpsrv(0, NULL));
    IF_TYPICAL(Shell_tftpsrv(0, NULL));
    IF_TYPICAL(Shell_telnetsrv(0, NULL));

    IF_MAX(Shell_get_host_by_name(0, NULL));
    IF_MAX(Shell_getname(0, NULL));
    IF_MAX(Shell_echosrv(0, NULL));
    IF_MAX(Shell_echo(0, NULL));

#if RTCSCFG_ENABLE_SNMP && RTCSCFG_ENABLE_UDP
    IF_MAX(Shell_SNMPd(0, NULL));
#endif

    IF_MAX(Shell_type(0, NULL));
    IF_MAX(Shell_walkroute(0, NULL));
    IF_MAX(Shell_gate(0, NULL));
    IF_MAX(Shell_getroute(0, NULL));
    IF_MAX(Shell_smtp (0, NULL));
    IF_MAX(Shell_arpdisp(0, NULL));
    IF_MAX(Shell_arpadd(0, NULL));
    IF_MAX(Shell_arpdel(0, NULL));
    IF_MAX(Shell_sendto(0, NULL));
    IF_MAX(Shell_ipconfig(0, NULL));
    IF_MAX(Shell_Clock_server_start(0, NULL));
#if RTCSCFG_ENABLE_NAT
    IF_MAX(Shell_nat(0, NULL));
    IF_MAX(Shell_dnat(0, NULL));
    IF_MAX(Shell_natinfo(0, NULL));
    IF_MAX(Shell_natinit(0, NULL));
    IF_MAX(Shell_dnat_delet_rule(0, NULL));
    IF_MAX(Shell_dhcptest(0, NULL));
#endif
#if RTCSCFG_ENABLE_PPP
    IF_MAX(Shell_ppp(0, NULL));
#endif
#if 0 /* TODO: Consider removing as following functions require IO_OLD */
    IF_MAX(Shell_iwconfig(0, NULL));
#endif
#endif
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: mfs_func
* Comments     :
*   This function calls MFS API functions with certain parameters
*   in order to verify the code size of MFS components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void mfs_func(int ar, ...)
{
    va_list varg;
    va_start(varg, ar);

    /* MFS general */
    IF_SMALL(_io_mfs_install(0, NULL, 0));
    IF_SMALL(_io_mfs_dir_open(0, NULL, NULL));
    IF_SMALL(_io_mfs_uninstall(NULL));
    IF_SMALL(_io_mfs_dir_read(NULL, NULL, 0));
    IF_SMALL(_io_mfs_dir_close(NULL));
    IF_SMALL(MFS_Error_text(0));
    IF_SMALL(MFS_alloc_path(NULL));
    IF_SMALL(MFS_alloc_2paths(NULL,NULL));
    IF_SMALL(MFS_free_path(NULL));

    /* Partition manager */
    IF_TYPICAL(_io_part_mgr_install(0, NULL, 0));
    IF_TYPICAL(_io_part_mgr_init(NULL, NULL, NULL));
    IF_TYPICAL(_io_part_mgr_deinit(NULL, NULL));
    IF_TYPICAL(_io_part_mgr_open(NULL, NULL, 0, NULL, NULL));
    IF_TYPICAL(_io_part_mgr_close(NULL, NULL, NULL));
    IF_TYPICAL(_io_part_mgr_read(NULL, NULL, NULL, 0, NULL));
    IF_TYPICAL(_io_part_mgr_write(NULL, NULL, NULL, 0, NULL));
    IF_TYPICAL(_io_part_mgr_lseek(NULL, NULL, 0, 0, NULL));
    IF_TYPICAL(_io_part_mgr_ioctl(NULL, NULL, NULL, 0, varg));
    IF_TYPICAL(_io_part_mgr_uninstall(NULL));
    IF_MAX(_pmgr_check_part_type(0));
    IF_MAX(_pmgr_validate_mbr(NULL));
    IF_MAX(_pmgr_get_part_info(NULL, NULL));
    IF_MAX(_pmgr_set_part_info(NULL, NULL));
    IF_MAX(_pmgr_clear_part_info(NULL, 0));
    IF_MAX(_pmgr_disk_to_host(NULL, NULL));
    IF_MAX(_pmgr_host_to_disk(NULL, NULL));

    /* SDCARD ESHDC */
    IF_MAX(_io_sdcard_esdhc_init(NULL));
    IF_MAX(_io_sdcard_esdhc_read_block(NULL, NULL, 0, 0));
    IF_MAX(_io_sdcard_esdhc_write_block(NULL, NULL, 0, 0));

    /* MFS Shell */
#if SHELLCFG_USES_MFS
    IF_TYPICAL(Shell_create(0, NULL));
    IF_TYPICAL(Shell_compare(0, NULL));
    IF_TYPICAL(Shell_flush_cache(0, NULL));
    IF_TYPICAL(Shell_cache(0, NULL));
    IF_TYPICAL(Shell_cd(0, NULL));
    IF_TYPICAL(Shell_copy(0, NULL));
    IF_TYPICAL(Shell_del(0, NULL));
    IF_TYPICAL(Shell_format(0, NULL));
    IF_TYPICAL(Shell_write(0, NULL));
    IF_TYPICAL(Shell_read(0, NULL));
    IF_TYPICAL(Shell_mkdir(0, NULL));
    IF_TYPICAL(Shell_pwd(0, NULL));
    IF_TYPICAL(Shell_rename(0, NULL));
    IF_TYPICAL(Shell_dir(0, NULL));
    IF_TYPICAL(Shell_rmdir(0, NULL));
    IF_MAX(Shell_df(0, NULL));
    IF_MAX(Shell_di(0, NULL));
    IF_MAX(Shell_dirent(0, NULL));
    IF_MAX(Shell_disect(0, NULL));
    IF_MAX(Shell_type(0, NULL));
#if 0 /* TODO: Hasn't been implemented */
    IF_MAX(Shell_use(0, NULL));
#endif
    IF_MAX(Shell_write_test(0, NULL));
    IF_MAX(Shell_read_test(0, NULL));
    IF_MAX(Shell_append_test(0, NULL));
#endif

    va_end(varg);
}

/*FUNCTION*----------------------------------------------------------------
*
* Function name: rtcs_func
* Comments     :
*   This function calls RTCS API functions with certain parameters
*   in order to verify the code size of RTCS components.
*   The number of APIs depends on configuration setting, consists of:
*   - TINY
*   - SMALL
*   - TYPICAL
*   - MAXIMUM
*
*END*--------------------------------------------------------------------*/
static void rtcs_func(void)
{
#if RTCSCFG_ENABLE_IGMP && RTCSCFG_ENABLE_IP4
    IF_MAX(IGMP_init());
#endif
    IF_TYPICAL(UDP_init());
    IF_TYPICAL(TCP_Init());
#if RTCSCFG_ENABLE_RIP && RTCSCFG_ENABLE_IP4
    IF_MAX(RIP_init());
#endif
    IF_TYPICAL(inet_aton(NULL, NULL));
    IF_TYPICAL(inet_addr(NULL));
#if RTCSCFG_ENABLE_UDP
    IF_TYPICAL(DHCPSRV_init(NULL, 0, 0));
    IF_TYPICAL(SNTP_init(NULL, 0, 0, 0, 0));
#endif
#if RTCSCFG_ENABLE_SNMP && RTCSCFG_ENABLE_UDP
    IF_TYPICAL(SNMP_init(NULL, 0, 0));
    IF_TYPICAL(SNMP_stop());
#if RTCSCFG_ENABLE_IP4
    IF_TYPICAL(SNMP_init_with_traps(NULL, 0, 0, NULL));
#endif
#endif
    IF_TYPICAL(RTCS_delay(0));
#if RTCSCFG_ENABLE_ICMP
    IF_TYPICAL(RTCS_ping(NULL));
#endif
#if RTCSCFG_ENABLE_UDP
    IF_TYPICAL(SNTP_oneshot(0, 0));
#endif
    IF_MAX(MIB1213_init());
    IF_MAX(MIBMQX_init());
#if 0 /* TODO: Hasn't been implemented */
    IF_MAX(EDS_init(NULL, 0, 0));
    IF_MAX(EDS_stop());
    IF_MAX(EDS_task(0));
#endif
    IF_TYPICAL(RTCS_if_bind_BOOTP(NULL, NULL));
    IF_TYPICAL(RTCS_create());
    IF_TYPICAL(RTCS_gate_add(0, 0, 0));
    IF_TYPICAL(RTCS_gate_add_metric(0, 0, 0, 0));
    IF_TYPICAL(RTCS_gate_remove(0, 0, 0));
    IF_TYPICAL(RTCS_gate_remove_metric(0, 0, 0, 0));
    IF_TYPICAL(RTCS_get_route(0, 0));
    IF_TYPICAL(RTCS_walk_route());
#if RTCSCFG_ENABLE_SNMP && RTCSCFG_ENABLE_IP4
    IF_MAX(RTCS_trap_target_add(0));
    IF_MAX(RTCS_trap_target_remove(0));
#endif
#if RTCSCFG_ENABLE_PPP
    IF_MAX(IPCP_get_local_addr(NULL));
    IF_MAX(IPCP_get_peer_addr(NULL));
    IF_MAX(RTCS_if_bind_IPCP(NULL, NULL));
#endif
    IF_TYPICAL(RTCS_resolve_ip_address(NULL, NULL, NULL, 0));
    IF_MAX(RTCS_log_error(0, 0, 0, 0, 0));
#if RTCSCFG_ENABLE_UDP
    IF_MAX(DHCPSRV_ippool_add(0, 0, NULL, NULL, 0));
#endif
#if RTCSCFG_ENABLE_IPIP && RTCSCFG_ENABLE_IP4
    IF_MAX(IPIP_init());
    IF_MAX(RTCS_tunnel_add(0, 0, 0, 0, 0, 0, 0)); /* IPIP_insert */
    IF_MAX(RTCS_tunnel_remove(0, 0, 0, 0, 0, 0, 0)); /* IPIP_delete */
#endif
    IF_TYPICAL(inet_pton(0, NULL, NULL, 0));
    IF_TYPICAL(inet_ntop(0, NULL, NULL, 0));
    IF_MAX(strlcpy(NULL, NULL, 0));
    IF_MAX(freeaddrinfo(NULL));
    IF_TYPICAL(getnameinfo(NULL, 0, NULL, 0, NULL, 0, 0));
    IF_TYPICAL(getaddrinfo(NULL, NULL, NULL, NULL));
    IF_MAX(RTCS_set_primary_dns_suffix(NULL));
    IF_MAX(RTCS_get_primary_dns_suffix());

    /* MLD protocol */
#if RTCSCFG_ENABLE_IP6 & RTCSCFG_ENABLE_MLD
    IF_MAX(mld_join(NULL, NULL));
    IF_MAX(mld_leave(NULL, NULL));
    IF_MAX(mld_report_all(NULL));
    IF_MAX(mld_query_receive(NULL));
#endif

    /* RTCS Statistics */
#if RTCSCFG_ENABLE_IP_STATS
    IF_MAX(IP_stats());
#endif
#if RTCSCFG_ENABLE_ICMP_STATS
    IF_MAX(ICMP_stats());
#endif
#if RTCSCFG_ENABLE_UDP_STATS
    IF_MAX(UDP_stats());
#endif
#if RTCSCFG_ENABLE_TCP_STATS
    IF_MAX(TCP_stats());
#endif
#if RTCSCFG_ENABLE_IPIF_STATS
    IF_MAX(IPIF_stats(NULL));
#endif
#if RTCSCFG_ENABLE_ARP_STATS
    IF_MAX(ARP_stats(NULL));
#endif
#if RTCSCFG_ENABLE_IP6_STATS
    IF_MAX(IP6_stats());
#endif
#if RTCSCFG_ENABLE_ICMP6_STATS
    IF_MAX(ICMP6_stats());
#endif

    /* HTTP Server APIs */
    IF_TYPICAL(HTTPSRV_init(NULL));
    IF_TYPICAL(HTTPSRV_release(0));
    IF_MAX(HTTPSRV_cgi_write(NULL));
    IF_MAX(HTTPSRV_cgi_read(0, NULL, 0));
    IF_MAX(HTTPSRV_ssi_write(0, NULL, 0));

    /* FTP Server APIs */
    IF_TYPICAL(FTPSRV_init(NULL));
    IF_TYPICAL(FTPSRV_release(0));

    /* ECHO Server APIs */
    IF_MAX(ECHOSRV_init(NULL));
    IF_MAX(ECHOSRV_release(NULL));

    /* TFTP APIs */
    IF_TYPICAL(TFTPSRV_init(NULL));
    IF_TYPICAL(TFTPSRV_release(0));
#if RTCSCFG_ENABLE_UDP
    IF_MAX(TFTPCLN_connect(NULL));
    IF_MAX(TFTPCLN_disconnect(0));
    IF_MAX(TFTPCLN_get(0, NULL, NULL));
    IF_MAX(TFTPCLN_put(0, NULL, NULL));
    IF_MAX(TFTPCLN_connect(NULL));
    IF_MAX(TFTPCLN_disconnect(0));
    IF_MAX(TFTPCLN_get(0, NULL, NULL));
    IF_MAX(TFTPCLN_put(0, NULL, NULL));
#endif
#if 0 /* TODO: Hasn't been implemented */
    IF_MAX(TFTPSRV_service_request(NULL));
    IF_MAX(TFTPSRV_service_transaction(NULL, NULL));
    IF_MAX(TFTPSRV_close_transaction(NULL, NULL));
    IF_MAX(TFTPSRV_service_timer(NULL));
    IF_MAX(TFTPSRV_build_ACK(NULL));
    IF_MAX(TFTPSRV_build_DATA(NULL));
    IF_MAX(TFTPSRV_send(NULL));
    IF_MAX(TFTPSRV_timer_start(NULL, NULL, 0));
    IF_MAX(TFTPSRV_timer_cancel(NULL, NULL));
    IF_MAX(TFTPSRV_open_device(0, NULL, NULL, NULL));
#endif
}

/*TASK*-----------------------------------------------------
*
* Task Name    : Main_task
* Comments     :
*
*END*-----------------------------------------------------*/

void Main_task(uint32_t initial_data)
{
    structs();
    event();
    interrupts();
    klog();
    log();
    lwevent();
    lwlog();
    lwmem();
    lwmsgq();
    lwsem();
    lwtimer();
    mem();
    message();
    mmu();
    mqx();
    mutex();
    name();
    part();
    psp();
    queues();
    sched();
    sem();
    task();
    taskq();
    time();
    timer();
    watchdog();
    nio_func(0);
    stdlib_func(0);
    shell_func();
    mfs_func(0);
    rtcs_func();
}
