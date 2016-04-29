/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef FSL_RTOS_MQX
#include <stdio.h>
#endif
#include "i2c_rtos.h"


/*******************************************************************************
 * Definition
 ******************************************************************************/

/* task prio */
#define TASK_MASTER_PRIO         6
#if USE_RTOS
#define TASK_SLAVE_PRIO          4
#define TASK_SAMPLE_PRIO         5
#endif

/* task size */
#define TASK_MASTER_STACK_SIZE   2048
#if USE_RTOS
#define TASK_SLAVE_STACK_SIZE    512
#define TASK_SAMPLE_STACK_SIZE   512
#endif

extern uint32_t gSlaveId;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* task declare */
extern void task_master(task_param_t param);
#if USE_RTOS
extern void task_slave(task_param_t param);
extern void task_sample(task_param_t param);
#if defined(FSL_RTOS_MQX)
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
#endif
#endif
/********************************************************************************
 * Variables
 ******************************************************************************/
/* task define */
OSA_TASK_DEFINE(task_master, TASK_MASTER_STACK_SIZE);
#if USE_RTOS
OSA_TASK_DEFINE(task_slave, TASK_SLAVE_STACK_SIZE);
OSA_TASK_DEFINE(task_sample, TASK_SAMPLE_STACK_SIZE);
#endif

#if defined(FSL_RTOS_MQX)
#define MAIN_TASK        8
void main_task(uint32_t param);
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   { MAIN_TASK, main_task, 0xC00, 20, "main_task", MQX_AUTO_START_TASK},
   { 0L,        0L,        0L,    0L,  0L,         0L }
};
#endif

#if defined(FSL_RTOS_MQX)
void main_task(uint32_t param)
#else
int main(void)
#endif
{
	/* SMC Power mode protection configurations */
    smc_power_mode_protection_config_t smc_power_prot_cfg =
    {
        .vlpProt = true,
        .llsProt = false,
        .vllsProt = false
    };

    hardware_init();
    GPIO_DRV_Init(NULL, ledPins);

	/* Configure the power mode protection */
    SMC_HAL_SetProtection(SMC_BASE, &smc_power_prot_cfg);

    /* get cpu uid low value for slave */
#if USE_RTOS
    gSlaveId = HW_SIM_UIDL_RD(SIM_BASE);
#endif

    OSA_Init();

    NVIC_SetPriority(I2C0_IRQn, 6);
    NVIC_SetPriority(I2C1_IRQn, 6);
#if defined(FSL_RTOS_MQX)
    OSA_InstallIntHandler(I2C0_IRQn, I2C0_IRQHandler);
    OSA_InstallIntHandler(I2C1_IRQn, I2C1_IRQHandler);
#endif

    dbg_uart_init();

#if USE_RTOS
    if (OSA_TaskCreate(task_slave,
                    "slave",
                    TASK_SLAVE_STACK_SIZE,
                    task_slave_stack,
                    TASK_SLAVE_PRIO,
                    (task_param_t)0,
                    false,
                    &task_slave_task_handler))
    {
#ifndef FSL_RTOS_MQX
        return 1;
#endif
    }
    if (OSA_TaskCreate(task_sample,
                    "sample",
                    TASK_SAMPLE_STACK_SIZE,
                    task_sample_stack,
                    TASK_SAMPLE_PRIO,
                    (task_param_t)0,
                    false,
                    &task_sample_task_handler))
    {
#ifndef FSL_RTOS_MQX
        return 1;
#endif
    }
#endif
    
    /* create app tasks */
    if (OSA_TaskCreate(task_master,
                    "master",
                    TASK_MASTER_STACK_SIZE,
                    task_master_stack,
                    TASK_MASTER_PRIO,
                    (task_param_t)0,
                    false,
                    &task_master_task_handler))
    {
#ifndef FSL_RTOS_MQX
        return 1;
#endif
    }

    OSA_Start();

    for(;;) {}                    /* Should not achieve here */
}
