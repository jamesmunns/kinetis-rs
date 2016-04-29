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
*   This file contains the source for the mutex example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <mutex.h>
#include <task.h>
#include <fsl_debug_console.h>

#define MAIN_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(1000)
#define PRINT_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(1000)

extern void main_task(uint32_t );
extern void print_task(uint32_t );

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

#if MQX_HAS_DYNAMIC_PRIORITIES == 0
    #error "MQX_HAS_DYNAMIC_PRIORITIES must be set to 1 in mqx_sdk_config.h for this demo."
#endif

/* User stack size */
uint8_t  main_task_task_stack[MAIN_TASK_STACK_SIZE];
uint8_t  print_task1_task_stack[PRINT_TASK_STACK_SIZE];
uint8_t  print_task2_task_stack[PRINT_TASK_STACK_SIZE];

MUTEX_STRUCT   print_mutex;

/* Global parameter structures */
const taskinit_t task_Main_task = {
    .stacksize  = MAIN_TASK_STACK_SIZE,
    .stackaddr  = main_task_task_stack,
    .exec       = main_task,
    .name       = "main",
    .priority   = 8,
};

taskinit_t task_Print_task = {
    .stacksize  = PRINT_TASK_STACK_SIZE,
    .exec       = print_task,
    .name       = "print",
    .priority   = 9,
    .time_slice = 3,
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

/*TASK*--------------------------------------------------------
*
* Task Name : main_task
* Comments  : This task creates a mutex and then two
*             instances of the print task.
*END*--------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
   MUTEX_ATTR_STRUCT mutexattr;
   _task_id   created_task;
   char*            strings1[] = { "1: ", "Hello from Print task 1\n" };
   char*            strings2[] = { "2: ", "Print task 2 is alive\n" };

   /* Initialize mutex attributes */
   if (_mutatr_init(&mutexattr) != MQX_OK) {
      PRINTF("Initialize mutex attributes failed.\n");
      _task_block();
   }

   /* Initialize the mutex */
   if (_mutex_init(&print_mutex, &mutexattr) != MQX_OK) {
      PRINTF("Initialize print mutex failed.\n");
      _task_block();
   }
   /* Create the print tasks */
   task_Print_task.exec_param = (void *)(strings1);
   task_Print_task.stackaddr  = print_task1_task_stack;

   created_task = create_task(&task_Print_task);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: SENDER task creation failed\n");
      _task_block();
   }

   task_Print_task.exec_param = (void *)(strings2);
   task_Print_task.stackaddr  = print_task2_task_stack;

   created_task = create_task(&task_Print_task);
   if (created_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: SENDER task creation failed\n");
      _task_block();
   }

   _task_block();
}

/*TASK*--------------------------------------------------------
*
* Task Name : print_task
* Comments  : This task prints a message. It uses a mutex to
*             ensure I/O is not interleaved.
*END*--------------------------------------------------------*/

void print_task
   (
      uint32_t initial_data
   )
{
   char **strings = (char **)initial_data;

   while(TRUE) {
      if (_mutex_lock(&print_mutex) != MQX_OK) {
         PRINTF("Mutex lock failed.\n");
         _task_block();
      }

      /*
       * The yield in between the PRINTF calls just returnes back,
       * as the other task is blocked waiting for the mutex.
       * Both strings are always printed together on a single line.
       */
      PRINTF("%s",strings[0]);
      _sched_yield();
      PRINTF("%s",strings[1]);

      _mutex_unlock(&print_mutex);

      /* Passes control to the other task (which then obtains the mutex) */
      _sched_yield();
   }
}

/* EOF */
