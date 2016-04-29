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
*   This file contains the source for the lightweight log example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <lwlog.h>
#include <task.h>
#include <fsl_debug_console.h>

#define MY_LOG     1

/* Task stack size*/
#define MAIN_TASK_STACK_SIZE    MQX_REQUIRED_STACK_SIZE(2000)

extern void main_task(uint32_t initial_data);

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

#if MQXCFG_STATIC_LWLOG == 1
    #error "MQXCFG_STATIC_LWLOG must be set to zero in in mqx_sdk_config.h for this demo."
#endif

#if MQX_USE_LWLOGS == 0
    #error "MQX_USE_LWLOGS must be set to non-zero in in mqx_sdk_config.h for this demo."
#endif

/* User stack size */
uint8_t  Main_task_stack[MAIN_TASK_STACK_SIZE];

/* Global parameter structures */
const taskinit_t task_main = {
    .stacksize  = MAIN_TASK_STACK_SIZE,
    .stackaddr  = Main_task_stack,
    .exec       = main_task,
    .priority   = 8,
    .name       = "main_task",
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
    create_task(&task_main);
    mqx_start();
}

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*   This task logs 10 keystroke entries in a lightweight log,
*   then prints out the log.
*END*-----------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
   LWLOG_ENTRY_STRUCT entry;
   _mqx_uint          result;
   _mqx_uint          i;
   unsigned char              c;

   /* Create the lightweight log component */
   result = _lwlog_create_component();
   if (result != MQX_OK) {
      PRINTF("Main task: _lwlog_create_component failed.");
      _task_block();
   }

   /* Create a log */
   result = _lwlog_create(MY_LOG, 10, 0);
   if (result != MQX_OK) {
      PRINTF("Main task: _lwlog_create failed.");
      _task_block();
   }

   /* Write data to the log */
   PRINTF("Enter 10 characters:\r\n");
   for (i = 0; i < 10; i++) {
      c = debug_getchar();
      result = _lwlog_write(MY_LOG, (_mqx_max_type)c,
         (_mqx_max_type)i, 0, 0, 0, 0, 0);
      if (result != MQX_OK) {
         PRINTF("Main task: _lwlog_write failed.");
      }
   }

   /* Read data from the log */
   PRINTF("\nLog contains:\r\n");
   while (_lwlog_read(MY_LOG, LOG_READ_OLDEST_AND_DELETE,
      &entry) == MQX_OK)
   {
      PRINTF("Time: ");
#if MQX_LWLOG_TIME_STAMP_IN_TICKS
      _psp_print_ticks((PSP_TICK_STRUCT_PTR)&entry.TIMESTAMP);
#else
      PRINTF("%ld.%03ld%03ld", entry.SECONDS, entry.MILLISECONDS,
         entry.MICROSECONDS);
#endif
      PRINTF(", c = %c, i=%d\r\n", (unsigned char)entry.DATA[0] & 0xff,
         (_mqx_uint)entry.DATA[1]);
   }

   /* Destroy the lightweight log */
   _lwlog_destroy(MY_LOG);

   _task_block();

}

/* EOF */
