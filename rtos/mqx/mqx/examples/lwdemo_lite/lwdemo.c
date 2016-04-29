/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 1989-2008 ARC International
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
*   This file contains source for the Lightweight MQX demo test.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include <lwmsgq.h>
#include "lwdemo.h"

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

/* User tasks stack definitions */
uint8_t  LWSemB_task_stack[LWSEMA_STACK_SIZE];
uint8_t  LWSemA_task_stack[LWSEMA_STACK_SIZE];
uint8_t  LWEventB_task_stack[LWEVENTB_STACK_SIZE];
uint8_t  LWEventA_task_stack[LWEVENTA_STACK_SIZE];
uint8_t  Sender_task_stack[SENDER_STACK_SIZE];
uint8_t  Responder_task_stack[RESPONDER_STACK_SIZE];
uint8_t  main_task_task_stack[MAIN_TASK_STACK_SIZE];

/* Use light weight events */
LWEVENT_STRUCT lwevent;

/* Use light weight semaphores */
LWSEM_STRUCT lwsem;

/* Use light weight message queues */
uint32_t main_queue[sizeof(LWMSGQ_STRUCT)/sizeof(uint32_t) +
   NUM_MESSAGES * MSG_SIZE];
uint32_t sender_queue[sizeof(LWMSGQ_STRUCT)/sizeof(uint32_t) +
   NUM_MESSAGES * MSG_SIZE];
uint32_t responder_queue[sizeof(LWMSGQ_STRUCT)/sizeof(uint32_t) +
   NUM_MESSAGES * MSG_SIZE];
