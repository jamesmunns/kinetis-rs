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
*   This file contains the code for the main task.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <sem.h>
#include "main.h"

SW_FIFO      fifo;

/* Task's static stack */
uint8_t  main_task_task_stack[MAIN_TASK_STACK_SIZE];
uint8_t  write_task_task_stack[NUM_WRITERS][WRITE_TASK_STACK_SIZE];
uint8_t  read_task_task_stack[READ_TASK_STACK_SIZE];

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

#if MQX_HAS_DYNAMIC_PRIORITIES == 0
    #error "MQX_HAS_DYNAMIC_PRIORITIES must be set to 1 in mqx_sdk_config.h for this demo."
#endif

/* Global parameter structures */
const taskinit_t task_Main_task = {
    .stacksize  = MAIN_TASK_STACK_SIZE,
    .stackaddr  = main_task_task_stack,
    .exec       = main_task,
    .name       = "main",
    .priority   = 8,
};

const taskinit_t task_Read_task = {
    .stacksize  = READ_TASK_STACK_SIZE,
    .stackaddr  = read_task_task_stack,
    .exec       = read_task,
    .name       = "read",
    .priority   = 8,
};

taskinit_t task_Write_task = {
    .stacksize  = WRITE_TASK_STACK_SIZE,
    .exec       = write_task,
    .name       = "write",
    .priority   = 8,
};

/*FUNCTION-----------------------------------------------------------
*
* Function Name   :  Main
* Comments    : Create task in MQX kernel.
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
    create_task(&task_Main_task);
    mqx_start();
}

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*     This task initializes three semaphores, creates NUM_WRITERS
*     write_task's, and creates one read_task.
*END*----------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
   _task_id   task_id;
   _mqx_uint  i;

   fifo.READ_INDEX  = 0;
   fifo.WRITE_INDEX = 0;

   /* Create the semaphores */
   if (_sem_create_component(3,1,6) != MQX_OK) {
      PRINTF("\nCreate semaphore component failed");
      _task_block();
   }
   if (_sem_create("sem.write", ARRAY_SIZE, 0) != MQX_OK) {
      PRINTF("\nCreating write semaphore failed");
      _task_block();
   }
   if (_sem_create("sem.read", 0, 0) != MQX_OK) {
      PRINTF("\nCreating read semaphore failed");
      _task_block();
   }
   if (_sem_create("sem.index", 1, 0) != MQX_OK) {
      PRINTF("\nCreating index semaphore failed");
      _task_block();
   }

   /* Create the tasks */
   for (i = 0; i < NUM_WRITERS; i++) {
      task_Write_task.exec_param = (void *)(i);
      task_Write_task.stackaddr  = write_task_task_stack[i];
      task_id = create_task(&task_Write_task);
      PRINTF("\nwrite_task created, id 0x%lx", task_id);
   }

   task_id = create_task(&task_Read_task);
   PRINTF("\nread_task created, id 0x%lX", task_id);

   _task_block();

}

/* EOF */
