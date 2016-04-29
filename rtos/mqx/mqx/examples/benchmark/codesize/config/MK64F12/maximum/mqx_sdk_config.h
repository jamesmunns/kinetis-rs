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

#define MQX_ALLOW_TYPED_MEMORY                  1
#define MQX_EXIT_ENABLED                        1
#define MQX_EXTRA_TASK_STACK_ENABLE             1
#define MQX_HAS_DYNAMIC_PRIORITIES              1
#define MQX_HAS_EXCEPTION_HANDLER               1
#define MQX_HAS_EXIT_HANDLER                    1
#define MQX_HAS_TASK_ENVIRONMENT                1
#define MQX_HAS_TICK                            1
#define MQX_HAS_TIME_SLICE                      1
#define MQX_KD_HAS_COUNTER                      1
#define MQX_KERNEL_LOGGING                      1
#define MQX_STD_TIME_API                        1
#define MQX_TAD_RESERVED_ENABLE                 1
#define MQX_TD_HAS_ERROR_CODE                   1
#define MQX_TD_HAS_PARENT                       1
#define MQX_TD_HAS_TASK_TEMPLATE_PTR            1
#define MQX_USE_EVENTS                          1
#define MQX_USE_INTERRUPTS                      1
#define MQX_USE_IO_COMPONENTS                   1
#define MQX_USE_LOGS                            1
#define MQX_USE_LWEVENTS                        1
#define MQX_USE_LWLOGS                          1
#define MQX_USE_LWMSGQ                          1
#define MQX_USE_LWTIMER                         1
#define MQXCFG_ALLOCATOR                        MQX_ALLOCATOR_MEM
#define MQXCFG_MEM_COPY                         1 // TODO: [MQX-4410] Must be disable as failed at build of RTCS lib
#define MQX_USE_MEM_ZERO                        1
#define MQXCFG_MEM_COPY_NEON                    1
#define MQX_USE_MESSAGES                        1
#define MQX_USE_MUTEXES                         1
#define MQX_USE_NAME                            1
#define MQX_USE_PARTITIONS                      1
#define MQX_USE_SEMAPHORES                      1
#define MQX_USE_SW_WATCHDOGS                    1
#define MQX_USE_TIMER                           1
#define MQX_USE_UNCACHED_MEM                    1
#define MQXCFG_STATIC_LWLOG                     0 // TODO: [MQX-4408] Must be enable as failed at build app.
#define MQXCFG_ENABLE_FP                        1
#define MQX_TASK_DESTRUCTION                    1
#define MQXCFG_EXCEPTION_HANDLING               1
#define MQX_IS_MULTI_PROCESSOR                  0
#define MQX_USE_IPC                             0

#define SHELLCFG_USES_MFS                       1
#define SHELLCFG_USES_RTCS                      1

#define RTCSCFG_ENABLE_IP4                      1
#define RTCSCFG_ENABLE_IP6                      1
#define RTCSCFG_ENABLE_ICMP                     1
#define RTCSCFG_ENABLE_IGMP                     1
#define RTCSCFG_ENABLE_IPIP                     1
#define RTCSCFG_ENABLE_NAT                      0 // TODO: Must be disable as failed at build of RTCS lib
#define RTCSCFG_ENABLE_PPP                      0 // TODO: [MQX-4409] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_RIP                      1 // TODO: [MQX-4409] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_SNMP                     1
#define RTCSCFG_ENABLE_UDP                      1
#define RTCSCFG_ENABLE_MLD                      0 // TODO: [MQX-4410] Must be disabled as failed at build of RTCS lib
#define RTCSCFG_ENABLE_STATS                    1
#define RTCSCFG_ENABLE_IP_STATS                 1
#define RTCSCFG_ENABLE_ICMP_STATS               1
#define RTCSCFG_ENABLE_UDP_STATS                1
#define RTCSCFG_ENABLE_TCP_STATS                1
#define RTCSCFG_ENABLE_IPIF_STATS               1
#define RTCSCFG_ENABLE_ARP_STATS                1
#define RTCSCFG_ENABLE_IP6_STATS                1
#define RTCSCFG_ENABLE_ICMP6_STATS              1
#define RTCSCFG_CHECK_ERRORS                    1
#define RTCSCFG_CHECK_MEMORY_ALLOCATION_ERRORS  1
#define RTCSCFG_CHECK_VALIDITY                  1
#define RTCSCFG_CHECK_ADDRSIZE                  1

/* Select one of common configurations according to project settings */
#include "maximum_config.h"

/* Enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif
