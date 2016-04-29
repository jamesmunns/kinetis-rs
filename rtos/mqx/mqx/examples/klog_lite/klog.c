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
*   This file contains the source for the kernel log example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <log.h>
#include <klog.h>
#include <task.h>
#include <fsl_debug_console.h>

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

#if MQX_KERNEL_LOGGING == 0
    #error "MQX_KERNEL_LOGGING must be set to non-zero in mqx_sdk_config.h for this demo."
#endif

#if MQX_USE_LOGS == 0
    #error "MQX_USE_LOGS must be set to non-zero in mqx_sdk_config.h for this demo."
#endif

#if MQXCFG_STATIC_KLOG == 1
    #error "MQXCFG_STATIC_KLOG must be set to zero in mqx_sdk_config.h for this demo."
#endif

#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_NONE
    #error "MQXCFG_ALLOCATOR must be set to non-zero in mqx_sdk_config.h for this demo."
#endif

#if MQXCFG_STATIC_LWLOG == 1
    #error "MQXCFG_STATIC_LWLOG must be set to zero in mqx_sdk_config.h for this demo."
#endif

#if MQX_USE_LWLOGS == 0
    #error "MQX_USE_LWLOGS must be set to non-zero in mqx_sdk_config.h for this demo."
#endif

/* TASK STACK SIZE*/
#define MAIN_TASK_STACK_SIZE    MQX_REQUIRED_STACK_SIZE(1500)

/* Function prototype*/
extern void main_task(uint32_t initial_data);

/* User stack size */
uint8_t  Main_task_stack[MAIN_TASK_STACK_SIZE];

/* Global parameter structures */
const taskinit_t task_Main = {
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
    create_task(&task_Main);
    mqx_start();
}


/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*   This task logs timer interrupts to the kernel log,
*   then prints out the log.
*END*-----------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
   _mqx_uint result;
   _mqx_uint i;

   /* Create the kernel log */
   result = _klog_create(2*1024, 0);
   if (result != MQX_OK) {
      PRINTF("Main task: _klog_create failed %08x", result);
      _task_block();
   }

   /* Enable kernel logging */
   _klog_control(KLOG_ENABLED | KLOG_CONTEXT_ENABLED |
      KLOG_INTERRUPTS_ENABLED| KLOG_SYSTEM_CLOCK_INT_ENABLED |
      KLOG_FUNCTIONS_ENABLED | KLOG_TIME_FUNCTIONS |
      KLOG_INTERRUPT_FUNCTIONS, TRUE);

   /* Write data into kernel log */
   for (i = 0; i < 10; i++) {
      _time_delay_ticks(5 * i);
   }

   /* Disable kernel logging */
   _klog_control(0xFFFFFFFF, FALSE);

   /* Read data from the kernel log */
   PRINTF("\r\nKernel log contains:\r\n");
   while (_klog_display()){
   }

   _task_block();

}
