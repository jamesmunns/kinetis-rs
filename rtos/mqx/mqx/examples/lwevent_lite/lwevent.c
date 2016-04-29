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
*   This file contains the source for the lwevent example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include <task.h>
#include <fsl_debug_console.h>

/* Task stack size*/
#define SERVICE_TASK_STACK_SIZE   MQX_REQUIRED_STACK_SIZE(1000)
#define ISR_TASK_STACK_SIZE       MQX_REQUIRED_STACK_SIZE(1000)

/* Function prototypes */
extern void simulated_ISR_task(uint32_t);
extern void service_task(uint32_t);

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

/* User stack size */
uint8_t  Isr_task_stack[ISR_TASK_STACK_SIZE];
uint8_t  Service_task_stack[SERVICE_TASK_STACK_SIZE];

/* Global parameter structures */
const taskinit_t task_service = {
    .stacksize  = SERVICE_TASK_STACK_SIZE,
    .stackaddr  = Service_task_stack,
    .exec       = service_task,
    .priority   = 8,
    .name       = "service_task",

};

const taskinit_t task_isr = {
    .stacksize  = ISR_TASK_STACK_SIZE,
    .stackaddr  = Isr_task_stack,
    .exec       = simulated_ISR_task,
    .priority   = 9,
    .name       = "simulated_ISR_task",
};

/* LW Event Definitions */
LWEVENT_STRUCT lwevent;

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
    create_task(&task_service);
    mqx_start();
}

/*TASK*-----------------------------------------------------
*
* Task Name    : simulated_ISR_task
* Comments     :
*    This task opens a connection to the event group. After
*    delaying, it sets the event bits.
*END*-----------------------------------------------------*/

void simulated_ISR_task
   (
      uint32_t initial_data
   )
{

   while (TRUE) {
      _time_delay_ticks(200);
      if (_lwevent_set(&lwevent,0x01) != MQX_OK) {
         PRINTF("\nSet Event failed");
         _task_block();
      }
   }
}

/*TASK*-----------------------------------------------------
*
* Task Name    : service_task
* Comments     :
*    This task creates an event group and the simulated_ISR_task
*    task. It opens a connection to the event group and waits.
*    After the appropriate event bit has been set, it clears
*    the event bit and prints "Tick."
*END*-----------------------------------------------------*/

void service_task
   (
      uint32_t initial_data
   )
{
   _task_id second_task_id;
   _int_install_unexpected_isr();
   /* create lwevent group */
   if (_lwevent_create(&lwevent,0) != MQX_OK) {
      PRINTF("\nMake event failed");
      _task_block();
   }

   /* Create the ISR task */
   second_task_id = create_task(&task_isr);
   if (second_task_id == MQX_NULL_TASK_ID) {
      PRINTF("Could not create simulated_ISR_task \n");
      _task_block();
   }

   while (TRUE) {
      if (_lwevent_wait_ticks(&lwevent,1,TRUE,0) != MQX_OK) {
         PRINTF("\nEvent Wait failed");
         _task_block();
      }

      if (_lwevent_clear(&lwevent,0x01) != MQX_OK) {
         PRINTF("\nEvent Clear failed");
         _task_block();
      }
      PRINTF(" Tick \r\n");
   }
}

/* EOF */
