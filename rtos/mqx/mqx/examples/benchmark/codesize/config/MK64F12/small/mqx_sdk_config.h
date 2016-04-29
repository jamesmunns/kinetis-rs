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
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   SDK RTOS adapter configuration.
*
*END************************************************************************/

#ifndef __mqx_sdk_config_h__
#define __mqx_sdk_config_h__

#ifndef MQX_USE_IO_OLD
  #define MQX_USE_IO_OLD 0
#elif MQX_USE_IO_OLD
  #error This version of MQX does not support legacy IO (FIO). Please force MQX_USE_IO_OLD to 0 in mqx_sdk_config.h
#endif

/* For SDK */
#define CMSIS_ENABLED                           1
#define PLATFORM_SDK_ENABLED                    1
#define MQX_USE_IDLE_TASK                       1

/* User configuration */
#define CODESIZE_USER_CONFIG                    1

#define MQX_ALLOW_TYPED_MEMORY                  0
#define MQX_EXIT_ENABLED                        0
#define MQX_EXTRA_TASK_STACK_ENABLE             0
#define MQX_HAS_DYNAMIC_PRIORITIES              1
#define MQX_HAS_EXCEPTION_HANDLER               0
#define MQX_HAS_EXIT_HANDLER                    0
#define MQX_HAS_TASK_ENVIRONMENT                1
#define MQX_HAS_TICK                            1
#define MQX_HAS_TIME_SLICE                      0
#define MQX_KD_HAS_COUNTER                      1
#define MQX_KERNEL_LOGGING                      0
#define MQX_STD_TIME_API                        0
#define MQX_TAD_RESERVED_ENABLE                 0
#define MQX_TD_HAS_ERROR_CODE                   1
#define MQX_TD_HAS_PARENT                       0
#define MQX_TD_HAS_TASK_TEMPLATE_PTR            1
#define MQX_USE_EVENTS                          0
#define MQX_USE_INTERRUPTS                      1
#define MQX_USE_IO_COMPONENTS                   1
#define MQX_USE_LOGS                            0
#define MQX_USE_LWEVENTS                        1
#define MQX_USE_LWLOGS                          0
#define MQXCFG_ALLOCATOR                        MQX_ALLOCATOR_LWMEM
#define MQX_USE_LWMSGQ                          1
#define MQX_USE_LWTIMER                         0
#define MQXCFG_MEM_COPY                         0 // TODO: [MQX-4410] Must be disable as failed at build of RTCS lib
#define MQX_USE_MEM_ZERO                        0
#define MQXCFG_MEM_COPY_NEON                    0
#define MQX_USE_MESSAGES                        1
#define MQX_USE_MUTEXES                         1
#define MQX_USE_NAME                            0
#define MQX_USE_PARTITIONS                      1
#define MQX_USE_SEMAPHORES                      0
#define MQX_USE_SW_WATCHDOGS                    0
#define MQX_USE_TIMER                           0
#define MQX_USE_UNCACHED_MEM                    0
#define MQXCFG_STATIC_LWLOG                     0 // TODO: [MQX-4408] Must be disable as failed at build app.
#define MQXCFG_ENABLE_FP                        0
#define MQX_TASK_DESTRUCTION                    1
#define MQXCFG_EXCEPTION_HANDLING               1

#define SHELLCFG_USES_MFS                       0
#define SHELLCFG_USES_RTCS                      0

#define RTCSCFG_ENABLE_IP4                      1
#define RTCSCFG_ENABLE_IP6                      0
#define RTCSCFG_ENABLE_ICMP                     0
#define RTCSCFG_ENABLE_IGMP                     0
#define RTCSCFG_ENABLE_IPIP                     0
#define RTCSCFG_ENABLE_NAT                      0 // TODO: Must be disable as failed at build of RTCS lib
#define RTCSCFG_ENABLE_PPP                      0 // TODO: [MQX-4409] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_RIP                      0 // TODO: [MQX-4409] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_SNMP                     0
#define RTCSCFG_ENABLE_UDP                      0
#define RTCSCFG_ENABLE_MLD                      0 // TODO: [MQX-4410] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_STATS                    0
#define RTCSCFG_ENABLE_IP_STATS                 0
#define RTCSCFG_ENABLE_ICMP_STATS               0
#define RTCSCFG_ENABLE_UDP_STATS                0
#define RTCSCFG_ENABLE_TCP_STATS                0
#define RTCSCFG_ENABLE_IPIF_STATS               0
#define RTCSCFG_ENABLE_ARP_STATS                0
#define RTCSCFG_ENABLE_IP6_STATS                0
#define RTCSCFG_ENABLE_ICMP6_STATS              0
#define RTCSCFG_CHECK_ERRORS                    0
#define RTCSCFG_CHECK_MEMORY_ALLOCATION_ERRORS  0
#define RTCSCFG_CHECK_VALIDITY                  0
#define RTCSCFG_CHECK_ADDRSIZE                  0

/* Select one of common configurations according to project settings */
#include "small_ram_config.h"

#endif
