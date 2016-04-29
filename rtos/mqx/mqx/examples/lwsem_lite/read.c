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
*   This file contains the read task code.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include "read.h"
#include <task.h>
#include <fsl_debug_console.h>

/* Global parameter structures */
const taskinit_t task_read = {
    .stacksize  = READ_TASK_STACK_SIZE,
    .stackaddr  = Read_task_stack,
    .exec       = read_task,
    .priority   = 8,
    .name       = "read_task",
};

SW_FIFO     fifo;

extern taskinit_t task_write;

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
    create_task(&task_read);
    mqx_start();
}

/*TASK*--------------------------------------------------------
*
* Task Name : read_task
* Comments  : This task creates two semaphores and
*             NUM_WRITER write_tasks. It waits
*             on the read_sem and finally outputs the
*             "data" variable.
*END*--------------------------------------------------------*/

void read_task
   (
      uint32_t initial_data
   )
{
   _task_id  task_id;
   _mqx_uint result;
   _mqx_uint i;
   uint32_t  param;

   /* Create the lightweight semaphores */
   result = _lwsem_create(&fifo.READ_SEM, 0);
   if (result != MQX_OK) {
      PRINTF("\nCreating read_sem failed: 0x%X", result);
      _task_block();
   }

   result = _lwsem_create(&fifo.WRITE_SEM, 1);
   if (result != MQX_OK) {
      PRINTF("\nCreating write_sem failed: 0x%X", result);
      _task_block();
   }

   /* Create the write tasks */
   for(i = 0; i< NUM_WRITERS; i++){
      task_write.stackaddr = Write_task_stack[i];
      param = 'A' + i;
      task_write.exec_param  = (void *)param;
      task_id = create_task(&task_write);
      if(task_id == NULL){
         PRINTF("\r\nWrite task create failed!");
      }
      else{
         PRINTF("\r\nwrite_task created, id 0x%lX", task_id);
      }
   }
   while(TRUE) {
      result = _lwsem_wait(&fifo.READ_SEM);
      if (result != MQX_OK) {
         PRINTF("\r\n_lwsem_wait failed: 0x%X", result);
         _task_block();
      }
      PUTCHAR('\n');
      PUTCHAR('\r');
      PUTCHAR(fifo.DATA);
      _lwsem_post(&fifo.WRITE_SEM);
   }

}

/* EOF */
