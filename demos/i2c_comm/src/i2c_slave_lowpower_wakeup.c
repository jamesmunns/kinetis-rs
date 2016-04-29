/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "board.h"
#include "fsl_i2c_slave_driver.h"
#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"
#include "fsl_gpio_driver.h"
#include "fsl_uart_hal.h"
#include "fsl_smc_hal.h"
#include "fsl_os_abstraction.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

#define UPPER_VALUE_LIMIT       (1)     /*! This value/10 is going to be added to current Temp to set the upper boundary*/
#define LOWER_VALUE_LIMIT       (1)     /*! This Value/10 is going to be subtracted from current Temp to set the lower boundary*/
#define LPTMR_COMPARE_VALUE     (500)   /*! Low Power Timer interrupt time in miliseconds */
#define UPDATE_BOUNDARIES_TIME  (20)    /*! This value indicates the number of cycles needed to update boundaries. To know the Time it will take, multiply this value times LPTMR_COMPARE_VALUE*/

static void LED_turnoff_master(void)
{
    GPIO_DRV_SetPinOutput(kGpioLED1);
}
static void LED_toggle_slave(void)
{
    GPIO_DRV_TogglePinOutput(kGpioLED2);
}
static void LED_turnon_slave(void)
{
    GPIO_DRV_ClearPinOutput(kGpioLED2);
}
static void LED_turnoff_slave(void)
{
    GPIO_DRV_SetPinOutput(kGpioLED2);
}

enum _subaddress_index_e
{
    Subaddress_Index_0 = 0x00,
    Subaddress_Index_1 = 0x01,
    Subaddress_Index_2 = 0x02,
    Subaddress_Index_3 = 0x03,
    Subaddress_Index_4 = 0x04,
    Subaddress_Index_5 = 0x05,
    Subaddress_Index_6 = 0x06,
    Subaddress_Index_7 = 0x07,
    Invalid_Subaddress_Index,
    Max_Subaddress_Index
};


//u8SinkData is received from I2C master
uint8_t u8SinkData      = 0x00;
//u8SourceData will be sent to I2C master
uint8_t u8SourceData    = 0xCD;

uint8_t u8SubaddressIndex = Invalid_Subaddress_Index;
uint8_t u8SlaveDataBuffer[Max_Subaddress_Index]   = {'I', '2', 'C', '-', 'C', 'O', 'M', 'M', };

static i2c_status_t data_sink(uint8_t sinkByte)
{
    if (u8SubaddressIndex == Invalid_Subaddress_Index)
    {
        //the first byte received is subaddress
        if (sinkByte < Invalid_Subaddress_Index)
        {
            u8SubaddressIndex = sinkByte;
        }

        LED_toggle_slave();
    }
    else
    {
        //the seconde byte received is data
        u8SlaveDataBuffer[u8SubaddressIndex] = sinkByte;

        //reset index as invalid for the next data tx/rx circle.
        u8SubaddressIndex = Invalid_Subaddress_Index;

        LED_toggle_slave();
    }

    return kStatus_I2C_Success;
}

static i2c_status_t data_source(uint8_t * sourceByte)
{

    *sourceByte = u8SlaveDataBuffer[u8SubaddressIndex];

    //reset index as invalid for the next data tx/rx circle.
    u8SubaddressIndex = Invalid_Subaddress_Index;

    LED_toggle_slave();

    return kStatus_I2C_Success;
}

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
    uint8_t slaveAddress = 0x3A;
    i2c_slave_state_t slave;
    

    // Low Power Configuration
    smc_power_mode_config_t smcConfig;
    smc_power_mode_protection_config_t smcProtConfig;

    /* Init struct.*/
    memset(&smcConfig, 0, sizeof(smcConfig));
    memset(&smcProtConfig, 0, sizeof(smcProtConfig));

    hardware_init();
    
    dbg_uart_init();
    
    OSA_Init();

    GPIO_DRV_Init(0, ledPins);

    // Initiate I2C instance module
    I2C_DRV_SlaveInit(BOARD_I2C_COMM_INSTANCE, slaveAddress, &slave);

    // Instatll slave callbacks
    I2C_DRV_SlaveInstallDataSource(BOARD_I2C_COMM_INSTANCE, data_source);
    I2C_DRV_SlaveInstallDataSink(BOARD_I2C_COMM_INSTANCE, data_sink);

    printf("\r\n====== I2C Slave ======\r\n\r\n");

    //turn LED_slave on to indicate I2C slave status is waiting for date receiving.
    LED_turnon_slave();
    LED_turnoff_master();
    OSA_TimeDelay(50);

    printf("\r\n I2C slave enters low power mode...\r\n");

    // set to allow entering specific modes
    smcProtConfig.vlpProt = true;
    SMC_HAL_SetProtection(SMC_BASE, &smcProtConfig);
   
    // set power mode to specific Run mode
#if FSL_FEATURE_SMC_HAS_LPWUI
    smcConfig.lpwuiOption = true;
    smcConfig.lpwuiOptionValue = kSmcLpwuiEnabled;
#endif
    smcConfig.porOption = false;
    smcConfig.powerModeName = kPowerModeWait;

    // Entry to Low Power Mode
    SMC_HAL_SetMode(SMC_BASE, &smcConfig);

    //LED_slave is still on during low power mode until I2C master send data to slave.
    //Turn off LED_slave to indicate MCU wake up by I2C address matching interrupt
    LED_turnoff_slave();
    printf("\r\n I2C slave wakes up from low power mode by I2C address matching.\r\n");

    while(1);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////


