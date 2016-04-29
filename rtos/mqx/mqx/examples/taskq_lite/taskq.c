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
*   This file contains the source for the task queue example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <task.h>
#include <fsl_debug_console.h>

#define SERVICE_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(2000)
#define SIMULATED_ISR_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(2000)

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

extern void simulated_ISR_task(uint32_t);
extern void service_task(uint32_t);

/* User stack size */
uint8_t  Service_task_task_stack[SERVICE_TASK_STACK_SIZE];
uint8_t  Simulated_ISR_task_task_stack[SIMULATED_ISR_TASK_STACK_SIZE];

/* Global parameter structures */
const taskinit_t task_Service_task = {
    .stacksize  = SERVICE_TASK_STACK_SIZE,
    .stackaddr  = Service_task_task_stack,
    .exec       = service_task,
    .priority   = 8,
    .name       = "service",
};

const taskinit_t task_Simulated_ISR_task = {
    .stacksize  = SIMULATED_ISR_TASK_STACK_SIZE,
    .stackaddr  = Simulated_ISR_task_task_stack,
    .exec       = simulated_ISR_task,
    .priority   = 8,
    .name       = "simulated_ISR",
};

void     *my_task_queue;

/*FUNCTION-----------------------------------------------------------
*
* Function Name   :  Main
* Comments    : initialize MQX kernel and create service_task
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
    create_task(&task_Service_task);
    mqx_start();
}

/*TASK*-----------------------------------------------------
*
* Task Name : simulated_ISR_task
* Comments  :
*   This task pauses and then resumes the task queue.
*END*-----------------------------------------------------*/

void simulated_ISR_task
   (
      uint32_t initial_data
   )
{
   while (TRUE) {
      _time_delay_ticks(200);
      _taskq_resume(my_task_queue, FALSE);
   }
}

/*TASK*-----------------------------------------------------
*
* Task Name : service_task
* Comments  :
*    This task creates a task queue and the simulated_ISR_task
*    task. Then it enters an infinite loop, printing "Tick" and
*    suspending the task queue.
*END*-----------------------------------------------------*/

void service_task
   (
      uint32_t initial_data
   )
{
   _task_id second_task_id;

   /* create a task queue */
   my_task_queue = _taskq_create(MQX_TASK_QUEUE_FIFO);
   if (my_task_queue == NULL) {
      _task_block();
   }

   /* create the ISR task */
   second_task_id = create_task(&task_Simulated_ISR_task);
   if (second_task_id == MQX_NULL_TASK_ID) {
      PRINTF ("\n Could not create simulated_ISR_task\n");
      _task_block();
   }

   while (TRUE) {
      PRINTF(" Tick \n");
      _taskq_suspend(my_task_queue);
   }
}

/* EOF */
