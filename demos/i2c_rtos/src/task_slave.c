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
#include "fsl_i2c_slave_driver.h"
#include "fsl_smc_hal.h"
#include "i2c_rtos.h"

/*******************************************************************************
 * Defination
 ******************************************************************************/

/* I2C slave data receive state machine */
typedef enum i2c_slave_rx_state
{
    RX_STATE_IDLE,
    RX_STATE_CMD,
    RX_STATE_DATA,
  
} rx_state_t;

/********************************************************************************
* Variables
******************************************************************************/

static i2c_status_t data_sink(uint8_t sinkByte);
static i2c_status_t data_source(uint8_t * sourceByte);
extern uint8_t get_temp_in_byte(uint32_t index);

static i2c_slave_state_t slaveDev =
{
    .dataSource = data_source,
    .dataSink = data_sink,
    .status = kStatus_I2C_Success,
};  

static volatile uint32_t curCmd = I2C_RTOS_READID_CMD;

/* SMC Power mode configuration variables */
static smc_power_mode_config_t smc_config_data = 
{
    .powerModeName = kPowerModeVlps,
    .stopSubMode = kSmcStopSub0,
#if FSL_FEATURE_SMC_HAS_LPWUI
    .lpwuiOption = false,
    .lpwuiOptionValue = false,
#endif
#if FSL_FEATURE_SMC_HAS_PORPO
    .porOption = true,
    .porOptionValue = false
#endif
};

uint32_t gSlaveId;
static msg_queue_handler_t hMsgQueue;
MSG_QUEUE_DECLARE(mqSlaveData, 10, 1);
#if (defined(FSL_RTOS_BM))
static volatile bool gI2c_data_sink_sync = false;
static volatile uint8_t gI2c_data_received;
#endif
/*******************************************************************************
* Code
******************************************************************************/

static i2c_status_t data_sink(uint8_t sinkByte)
{
    /* we use MSG copy */
    uint32_t revData = sinkByte;
    OSA_MsgQPut(hMsgQueue, &revData);
    /*!
    * FIXME: msg_queue system for BM has serious bug!
    * sometimes, queue elements is not FIFO!. order is wrong.
    * so in BM, use var: gI2c_data_received and gI2c_data_sink_sync to do work around.
    * if this problem fixed. var gI2c_data_received and gI2c_data_sink_sync can be deleted, BM and RTOS can be unified.
    */
#if (defined(FSL_RTOS_BM))
    gI2c_data_received = sinkByte;
    gI2c_data_sink_sync = true;
#endif
    return kStatus_I2C_Success;
}

static i2c_status_t data_source(uint8_t * sourceByte)
{
    static uint32_t prevCmd = I2C_RTOS_READID_CMD;
    static uint8_t index = 0;
    static uint8_t *pSlaveId = (uint8_t*)&gSlaveId;

    if (prevCmd != curCmd)
    {
        index = 0;
        prevCmd = curCmd;
    }
    switch (curCmd)
    {
    case I2C_RTOS_TEMP_CMD:
        *sourceByte = get_temp_in_byte(index);
        if (++index == 4)
        {
            index = 0;
        }
        break;
    case I2C_RTOS_READID_CMD:
        *sourceByte = pSlaveId[index++];
        if (index == 4)
        {
            index = 0;
        }
        break;
    default:
        break;
    }
    return kStatus_I2C_Success;
}

static void handle_cmd(uint8_t *buf, uint8_t cmd)
{
    uint32_t slaveId;
    
    switch (cmd)
    {
    case I2C_RTOS_LIGHT_CMD:
        switch (buf[0])
        {
        case 'R':
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, !buf[1]);
            break; 
        case 'G':
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_GREEN, !buf[1]);
            break; 
        case 'B':
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, !buf[1]);
            break; 
        default:
            break; 
	}
        break;
    case I2C_RTOS_SLEEP_CMD:
        /* check if request from self master */
        slaveId = *(uint32_t *)&buf[0];
        if (slaveId == gSlaveId)
        {
            printf("Can not sleep on yourself\r\n");
            break;
        }
        printf("Master tell me to go sleep..\r\n");
        /* TODO: stop the sys tick, and let OS know change mode */
        /* Enter VLPS mode */
        SMC_HAL_SetMode(SMC_BASE, &smc_config_data);
        printf("Wake up from sleep\r\n");
        break;
    default:
        break;
    }
}

/*!
 * task for slave getting request and put response
 */
void task_slave(task_param_t param)
{
    uint32_t rxData;
    uint32_t i = 0;
    uint32_t rxDataLen = 0;
    uint8_t buf[6];
    uint32_t cmd;
    rx_state_t rxState = RX_STATE_IDLE;

    param = param;

    /* init i2c slave driver */
    I2C_DRV_SlaveInit(I2C_RTOS_SLAVE_INSTANCE, I2C_RTOS_SLAVE_ADDRESS, &slaveDev);
    // Instatll slave callbacks
    I2C_DRV_SlaveInstallDataSource(I2C_RTOS_SLAVE_INSTANCE, data_source);
    I2C_DRV_SlaveInstallDataSink(I2C_RTOS_SLAVE_INSTANCE, data_sink);
    
    hMsgQueue = OSA_MsgQCreate(mqSlaveData, 10, 1);
    if (!hMsgQueue)
    {
        printf("%s:OSA_MsgQCreate failed!\r\n", __func__);
    }

    while(1)
    {
#if (defined(FSL_RTOS_BM))
        if (gI2c_data_sink_sync == true)
        {
        gI2c_data_sink_sync = !gI2c_data_sink_sync;
        rxData = gI2c_data_received;
#else
        if (OSA_MsgQGet(hMsgQueue, &rxData, OSA_WAIT_FOREVER) == kStatus_OSA_Success)
        {
#endif

            /* running state machine */
            switch (rxState)
            {
            case RX_STATE_IDLE:
                if (rxData == I2C_RTOS_MAGIC)
                {
                    rxState = RX_STATE_CMD;
                }
                break;
            case RX_STATE_CMD:
                cmd = rxData;
                switch (rxData)
                {
                case I2C_RTOS_LIGHT_CMD:
                    rxDataLen = 2;
                    rxState = RX_STATE_DATA;
                    break;
                case I2C_RTOS_TEMP_CMD:
                    /* switch to temperature mode */
                    curCmd = cmd;
                    rxState = RX_STATE_IDLE;
                    break;
                case I2C_RTOS_SLEEP_CMD:
                    rxDataLen = 4;
                    rxState = RX_STATE_DATA;
                    break;  
                case I2C_RTOS_READID_CMD:
                    /* switch to read id mode */
                    curCmd = cmd;
                    rxState = RX_STATE_IDLE;
                    break;  
                default: 
                    rxState = RX_STATE_IDLE;
                    break;
                }
                break;
            case RX_STATE_DATA:
                if (rxDataLen)
                {
                    buf[i++] = (uint8_t)rxData;
                    if (i >= (rxDataLen))
                    {
                        i = 0;
                        handle_cmd(buf, cmd);
                        rxState = RX_STATE_IDLE;  
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}
