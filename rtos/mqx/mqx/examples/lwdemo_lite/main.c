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
*   Task Code -  Main
*
*END************************************************************************/

//#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <task.h>
#include <lwevent.h>
#include <lwmsgq.h>
#if MQX_KERNEL_LOGGING
    #include <klog.h>
#endif
#if MQX_USE_LOGS
    #include <log.h>
#endif
#include "lwdemo.h"
#include "fsl_debug_console.h"

/* Global parameter structures */
const taskinit_t task1 = {
    .stacksize  = MAIN_TASK_STACK_SIZE,
    .stackaddr  = main_task_task_stack,
    .exec       = main_task,
    .priority   = 11,
    .name       = "main_task",
};

const taskinit_t task_Sender = {
    .stacksize  = SENDER_STACK_SIZE,
    .stackaddr  = Sender_task_stack,
    .exec       = Sender,
    .priority   = 10,
    .name       = "Sender",
};

const taskinit_t task_LWSemA = {
    .stacksize  = LWSEMA_STACK_SIZE,
    .stackaddr  = LWSemA_task_stack,
    .exec       = LWSemA,
    .priority   = 9,
    .name       = "LWSemA",
};

const taskinit_t task_LWSemB = {
    .stacksize  = LWSEMB_STACK_SIZE,
    .stackaddr  = LWSemB_task_stack,
    .exec       = LWSemB,
    .priority   = 10,
    .name       = "LWSemB",
};

const taskinit_t task_LWEventA = {
    .stacksize  = LWEVENTA_STACK_SIZE,
    .stackaddr  = LWEventA_task_stack,
    .exec       = LWEventA,
    .priority   = 9,
    .name       = "LWEventA",
};

const taskinit_t task_LWEventB = {
    .stacksize  = LWEVENTB_STACK_SIZE,
    .stackaddr  = LWEventB_task_stack,
    .exec       = LWEventB,
    .priority   = 10,
    .name       = "LWEventB",
};

/*FUNCTION-----------------------------------------------------------
*
* Function Name   :  Main
* Comments    :
*
*END*--------------------------------------------------------------*/
int main(void)
{
extern MQX_INITIALIZATION_STRUCT MQX_init_struct;
#if defined(__ICCARM__) /* IAR */
/* Search for last block placed by IAR linker to set heap as big as possible.
** See mqx_main.c for details.*/
    if (NULL == MQX_init_struct.START_OF_HEAP)
    {
        MQX_init_struct.START_OF_HEAP = (__RW_END > __ZI_END) ? __RW_END : __ZI_END;
    }
#endif  /* defined(__ICCARM__) */
    mqx_init((MQX_INITIALIZATION_STRUCT_PTR) &MQX_init_struct);
    create_task(&task1);
    mqx_start();
}


/*TASK---------------------------------------------------------------
*
* Task Name   :  main_task
* Comments    :
*
*END*--------------------------------------------------------------*/
void main_task
   (
      uint32_t   parameter
   )
{
   _mqx_uint                 msg[MSG_SIZE];
   _task_id                  created_task;
#if MQX_USE_LOGS || MQX_KERNEL_LOGGING
   _mqx_uint                 log_result;
#endif
   _mqx_uint                 result;

   _int_install_unexpected_isr();
   PRINTF("\nMQX %s\n",_mqx_version);
   PRINTF("Hello from main_task().");

#if MQX_USE_LOGS
   /* create the log component */
   log_result = _log_create_component();
   if (log_result != MQX_OK) {
      PRINTF("Error: log component could not be created\n");
   } /* endif */
#endif
   /* create lwevent group */
   result = _lwevent_create(&lwevent,0);
   if (result != MQX_OK) {
      PRINTF("Error: event component could not be created\n");
   } /* endif */

   /* create a lwsem */
   result = _lwsem_create(&lwsem, 10);
   if (result != MQX_OK) {
      /* semaphore component could not be created */
   } /* endif */

   _lwmsgq_init((void *)main_queue, NUM_MESSAGES, MSG_SIZE);
   _lwmsgq_init((void *)sender_queue, NUM_MESSAGES, MSG_SIZE);
   _lwmsgq_init((void *)responder_queue, NUM_MESSAGES, MSG_SIZE);

   created_task = create_task(&task_Sender);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: SENDER task creation failed\n");
   }

   created_task = create_task(&task_LWSemA);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: LWSEMA task creation failed\n");
   }

   created_task = create_task(&task_LWSemB);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: LWSEMB task creation failed\n");
   }

   created_task = create_task(&task_LWEventA);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: LWEVENTA task creation failed\n");
   }

   created_task = create_task(&task_LWEventB);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: LWEVENTB task creation failed\n");
   }

#if MQX_KERNEL_LOGGING == 1
   /* create log number 0 */
   log_result = _klog_create(200, 0);
   if (log_result != MQX_OK) {
      PRINTF("Error: log 0 could not be created\n");
   } /* endif */

   /* define kernel logging */
   _klog_control(0xFFFFFFFF, FALSE);
   _klog_control(
      KLOG_ENABLED                  |
      KLOG_FUNCTIONS_ENABLED        |
      KLOG_INTERRUPTS_ENABLED       |
      KLOG_SYSTEM_CLOCK_INT_ENABLED |
      KLOG_CONTEXT_ENABLED          |
      KLOG_TASKING_FUNCTIONS        |
      KLOG_ERROR_FUNCTIONS          |
      KLOG_MESSAGE_FUNCTIONS        |
      KLOG_INTERRUPT_FUNCTIONS      |
      KLOG_MEMORY_FUNCTIONS         |
      KLOG_TIME_FUNCTIONS           |
      KLOG_EVENT_FUNCTIONS          |
      KLOG_NAME_FUNCTIONS           |
      KLOG_MUTEX_FUNCTIONS          |
      KLOG_SEMAPHORE_FUNCTIONS      |
      KLOG_WATCHDOG_FUNCTIONS,
      TRUE
      );
#endif

   while ( TRUE ) {
      _lwmsgq_send((void *)sender_queue, msg, LWMSGQ_SEND_BLOCK_ON_FULL);
      _lwmsgq_receive((void *)main_queue, msg, LWMSGQ_RECEIVE_BLOCK_ON_EMPTY, 0, 0);
   }
}
