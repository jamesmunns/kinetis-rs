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
#include <assert.h>
#include <mqx.h>
#include <bsp.h>
#include <fsl_interrupt_manager.h>

#define MAIN_TASK 10
#define SW_IRQ PORTA_IRQn
#define NUMBER_OF_INTERRUPTS 10

void main_task(uint32_t initial_data);

const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index, Function,  Stack, Priority, Name,        Attributes,          Param, Time Slice */
    { MAIN_TASK,  main_task, 1000,  8,        "Main",      MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};


typedef struct my_isr_struct
{
   void                 *OLD_ISR_DATA;
   INT_ISR_FPTR          OLD_ISR;
   _mqx_uint             COUNTER;
} MY_ISR_STRUCT, * MY_ISR_STRUCT_PTR;

uint32_t g_counter = 0;
MY_ISR_STRUCT  g_isr_data;

/*ISR*-----------------------------------------------------------
*
* ISR Name : new_tick_isr
* Comments : Interrupt routine to demonstrate _int_install_isr 
* functionality.
*END*-----------------------------------------------------------*/

void new_isr(void *user_isr_ptr)
{
   MY_ISR_STRUCT_PTR  isr_ptr;

   isr_ptr = (MY_ISR_STRUCT_PTR)user_isr_ptr;
   isr_ptr->COUNTER++;
   /* It is common to chain interrupts */
   /* isr_ptr->OLD_ISR(isr_ptr->OLD_ISR_DATA); */
}

/*ISR*-----------------------------------------------------------
*
* ISR Name : new_kernel_isr
* Comments : Interrupt routine to demonstrate _int_install_kernel_isr 
* functionality.
*END*-----------------------------------------------------------*/
void new_kernel_isr(void)
{
    g_counter++;
}

/*TASK*----------------------------------------------------------
*
* Task Name : main_task
* Comments  :
*   This task demonstrate interrupt installations in MQX.
*END*-----------------------------------------------------------*/

void main_task(uint32_t initial_data)
{

    INT_ISR_FPTR old_isr;
    INT_KERNEL_ISR_FPTR old_kernel_isr;

    /* Enable interrupt for SW_IRQ*/
    INT_SYS_EnableIRQ(SW_IRQ);

    /** Demonstration of mqx interrupt installation. Works with vector table placed in RW as well as RO memory **/
    g_isr_data.COUNTER      = 0;
    g_isr_data.OLD_ISR_DATA = _int_get_isr_data(SW_IRQ);
    g_isr_data.OLD_ISR      = _int_get_isr(SW_IRQ);

    /* Install MQX isr routine. This function does not change vector table */
    old_isr = _int_install_isr(SW_IRQ, new_isr, &g_isr_data);

    /* Check if _int_install_isr returns the same  as _int_get_isr*/
    assert(old_isr == g_isr_data.OLD_ISR);

    /* Call software interrupt 10 times every 10ms */
    for(int i = 0; i < NUMBER_OF_INTERRUPTS; i++)
    {
        NVIC_SetPendingIRQ(SW_IRQ);
        _time_delay_ticks(10);
    }

    printf("\ncounter = %d\n", g_isr_data.COUNTER);
    /* Install previous isr with previous data to mqx */
    old_isr = _int_install_isr(SW_IRQ, g_isr_data.OLD_ISR, g_isr_data.OLD_ISR_DATA);
    assert(old_isr == new_isr);

    /** Demonstration of mqx interrupt kernel installation. Works with vector table placed in RW memory only**/
    /* Ensure that ram vector table is enabled by linker symbol __ram_vector_table__ set to 1 */
    /* Install MQX kernel isr routine. This function changes vector table if placed in rw memory */
    old_kernel_isr = _int_install_kernel_isr(SW_IRQ, new_kernel_isr);

    for(int i = 0; i < NUMBER_OF_INTERRUPTS; i++)
    {
        NVIC_SetPendingIRQ(SW_IRQ);
        _time_delay_ticks(10);
    }

    printf("\ng_counter = %d\n", g_counter);
    /* Put previous isr to vector table */
    old_kernel_isr = _int_install_kernel_isr(PORTA_IRQn, old_kernel_isr);
    assert(old_kernel_isr);

    _task_block();
}

/* EOF */
