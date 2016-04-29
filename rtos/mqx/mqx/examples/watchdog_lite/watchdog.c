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
*   This file contains the source for the watchdog example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <watchdog.h>
#include <task.h>
#include <fsl_debug_console.h>

#define MAIN_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(4000)
#define TEST_TASK_STACK_SIZE MQX_REQUIRED_STACK_SIZE(4000)

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

extern void main_task(uint32_t);
extern void test_task(uint32_t);
extern void handle_watchdog_expiry(void *);

/* User stack size */
uint8_t  main_task_task_stack[MAIN_TASK_STACK_SIZE];
uint8_t  test_task_task_stack[TEST_TASK_STACK_SIZE];

/* Global parameter structures */
const taskinit_t task_main_task = {
    .stacksize  = MAIN_TASK_STACK_SIZE,
    .stackaddr  = main_task_task_stack,
    .exec       = main_task,
    .priority   = 8,
    .name       = "Main",
};

const taskinit_t task_test_task = {
    .stacksize  = TEST_TASK_STACK_SIZE,
    .stackaddr  = test_task_task_stack,
    .exec       = test_task,
    .priority   = 9,
    .name       = "Test",
};

LWSEM_STRUCT shutdown_sem;

/*FUNCTION-----------------------------------------------------------
*
* Function Name   :  Main
* Comments    : Create an initial task.
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
    create_task(&task_main_task);
    mqx_start();
}

/*FUNCTION*------------------------------------------------------
*
* Function Name  : handle_watchdog_expiry
* Returned Value : none
* Comments       :
*     This function is called when a watchdog has expired.
*END*-----------------------------------------------------------*/

void handle_watchdog_expiry
   (
      void   *td_ptr
   )
{
  _lwsem_post(&shutdown_sem);
}

/*FUNCTION*------------------------------------------------------
*
* Function Name  : waste_time
* Returned Value : input value times 10
* Comments       :
*     This function loops the specified number of times,
*     essentially wasting time.
*END*-----------------------------------------------------------*/

static _mqx_uint waste_time
   (
      _mqx_uint n
   )
{
   _mqx_uint        i;
   volatile uint32_t result;

   result = 0;
   for (i = 0; i < n; i++) {
      result += 1;
   }
   return result * 10;
}


/*TASK*----------------------------------------------------------
*
* Task Name : test_task
* Comments  :
*   This task creates a watchdog, then loops, performing
*   work for longer and longer periods until the watchdog fires.
*END*-----------------------------------------------------------*/

void test_task
   (
      uint32_t initial_data
   )
{
   MQX_TICK_STRUCT ticks;
   _mqx_uint       result;
   _mqx_uint       n;

   _time_init_ticks(&ticks, 10);

   result = _watchdog_create_component(BSP_SYSTIMER_INTERRUPT_VECTOR,
      handle_watchdog_expiry);
   if (result != MQX_OK) {
      PRINTF("\nError creating watchdog component.");
      _task_block();
   }

   n = 100;
   while (TRUE) {
      result = _watchdog_start_ticks(&ticks);
      n = waste_time(n);
      _watchdog_stop();
      PRINTF("\n %d", n);
   }

}

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*   This task creates test task and waits until on semaphore from watchdog.
*   In case the watchdog fires, it performs action:
*          (prints "Watchdog expired" and shutdown mqx)
*
*END*-----------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
  _task_id test_task;

   _lwsem_create(&shutdown_sem, 0);
   test_task = create_task(&task_test_task);
   if (test_task == MQX_NULL_TASK_ID) {
      PRINTF("Error: TEST task creation failed\n");
      _task_block();
   }


   _lwsem_wait(&shutdown_sem);
   _task_destroy(test_task);

   PRINTF("\nWatchdog expired");

   _task_block();
}
/* EOF */
