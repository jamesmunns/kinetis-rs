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
*   This file contains the source for the isr example program.
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <task.h>
#include <fsl_debug_console.h>

/* TASK STACK SIZE*/
#define MAIN_TASK_STACK_SIZE    MQX_REQUIRED_STACK_SIZE(2000)

extern void main_task(uint32_t);
extern void new_tick_isr(void *);

#if MQX_COMMON_CONFIG != MQX_LITE_CONFIG
    #error "MQX_COMMON_CONFIG must be set to MQX_LITE_CONFIG in mqx_sdk_config.h for this demo."
#endif

#if MQXCFG_ALLOCATOR == MQX_ALLOCATOR_NONE
    #error "MQXCFG_ALLOCATOR must be set to non-zero in mqx_sdk_config.h for this demo."
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

typedef struct my_isr_struct
{
   void                 *OLD_ISR_DATA;
   void      (_CODE_PTR_ OLD_ISR)(void *);
   _mqx_uint             TICK_COUNT;
} MY_ISR_STRUCT, * MY_ISR_STRUCT_PTR;

/*ISR*-----------------------------------------------------------
*
* ISR Name : new_tick_isr
* Comments :
*   This ISR replaces the existing timer ISR, then calls the
*   old timer ISR.
*END*-----------------------------------------------------------*/

void new_tick_isr
   (
      void   *user_isr_ptr
   )
{
   MY_ISR_STRUCT_PTR  isr_ptr;

   isr_ptr = (MY_ISR_STRUCT_PTR)user_isr_ptr;
   isr_ptr->TICK_COUNT++;

   /* Chain to the previous notifier */
   (*isr_ptr->OLD_ISR)(isr_ptr->OLD_ISR_DATA);
}

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*   This task installs a new ISR to replace the timer ISR.
*   It then waits for some time, finally printing out the
*   number of times the ISR ran.
*END*-----------------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
   MY_ISR_STRUCT_PTR  isr_ptr;

   isr_ptr = _mem_alloc_zero((_mem_size)sizeof(MY_ISR_STRUCT));

   isr_ptr->TICK_COUNT   = 0;
   isr_ptr->OLD_ISR_DATA =
      _int_get_isr_data(BSP_SYSTIMER_INTERRUPT_VECTOR);
   isr_ptr->OLD_ISR      =
      _int_get_isr(BSP_SYSTIMER_INTERRUPT_VECTOR);

   _int_install_isr(BSP_SYSTIMER_INTERRUPT_VECTOR, new_tick_isr,
      isr_ptr);

   _time_delay_ticks(200);

   PRINTF("\r\nTick count = %d\r\n", isr_ptr->TICK_COUNT);

   _task_block();

}
