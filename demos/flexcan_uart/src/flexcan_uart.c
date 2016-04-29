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


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "device/fsl_device_registers.h"
#include "fsl_uart_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_flexcan_driver.h"
#include "fsl_pit_driver.h"
#include "fsl_interrupt_manager.h"
#include "board.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
static void pit0_isr_callback(void);


static uint32_t s_uart0Instance = BOARD_DEBUG_UART_INSTANCE;
static uint32_t s_pitInstance = 0;//pit0 is used
volatile uint8_t timeout_flag = false;  //disable timeout event
// Structure of initialize PIT, this will enable PIT module as default
static pit_user_config_t s_pitConfig = {
    .isInterruptEnabled = true,
    .isTimerChained = false,
    //for 115200bps 8N1, 1 charactor is around 87us, here set 4ms timeout
    .periodUs = 4000
};

static uint32_t TX_identifier;
static uint32_t RX_identifier;
//static uint32_t TX_remote_identifier;
//static uint32_t RX_remote_identifier;
static uint32_t TX_mailbox_num;
static uint32_t RX_mailbox_num;
//static uint32_t TX_remote_mailbox_num;
//static uint32_t RX_remote_mailbox_num;
static flexcan_user_config_t flexcan1_data;
static flexcan_id_table_t id_table;
static flexcan_mb_t rx_fifo;
static flexcan_mb_t rx_mb;
static uint8_t s_flexcanInstance = 0;
static flexcan_data_info_t tx_info;
static flexcan_data_info_t rx_info;
static uint32_t number_errors;
extern bool int_mb;
bool int_fifo;

extern semaphore_t irqSync;

#define  gUartbaseAddr  UART1_BASE
#define  gCanbaseAddr	CAN0_BASE

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
//! @brief Init hardware for TWR-K70F120M
static void init_hardware(void)
{
    OSA_Init();
    
    hardware_init();
    
    // clock enable in the pit driver, and disable timer run in debug mode
    PIT_DRV_Init(s_pitInstance,false);
    
    // Init pit timer.
    PIT_DRV_InitChannel(s_pitInstance, 0, &s_pitConfig);
    
    // Register a custom pit0 ISR
    PIT_DRV_InstallCallback(s_pitInstance,0,pit0_isr_callback);
    
    //start pit timer 0
    PIT_DRV_StartTimer(s_pitInstance,0);
    
    // Enable clock gate to FlexCAN 0 module
    CLOCK_SYS_EnableFlexcanClock(s_flexcanInstance);
}

//! @brief main function.
void main(void)
{
    uint8_t ch0[8], ch1[8], ch2[8], *ch; //ch0 and ch1 for uart receiving buffer, ch2 for uart transfer buffer
    uint8_t node_type; //var used to store the node type input from the console
    uint32_t remainingReceiveByteCount, receivedByteCount;
    uart_status_t status;
    uint32_t result;
    uint32_t rx_fifo_id[8]; //though rx fifo is not used in this demo, keep it for future useage
    uint32_t temp,i,j;
    
    init_hardware();
    
    dbg_uart_init();
    
    number_errors = 0;
    
    flexcan1_data.max_num_mb = 16;
    flexcan1_data.num_id_filters = kFlexCanRxFifoIDFilters_8;
    flexcan1_data.is_rx_fifo_needed = false; //disable fifo here
    
    id_table.is_extended_mb = false;
    id_table.is_remote_mb = false;
    rx_fifo_id[0] = 0x666;
    rx_fifo_id[1] = 0x667;
    rx_fifo_id[2] = 0x676;
    rx_fifo_id[3] = 0x66E;
    rx_fifo_id[4] = 0x66F;
    for (i = 5; i < 8; i++)
    {    
        rx_fifo_id[i] = 0x6E6;
    }
    id_table.id_filter = rx_fifo_id;
    
    /* Select mailbox number */
    RX_mailbox_num = 8;
    TX_mailbox_num = 9;
    //   RX_remote_mailbox_num = 10;
    //   TX_remote_mailbox_num = 11;
    
    printf("\r\n*********FlexCAN : SCI2CAN demo *********");
    printf("\r\n   Message format: Standard (11 bit id)");
    printf("\r\n   Message buffer 8 used for Rx.");
    printf("\r\n   Message buffer 9 used for Tx.");
    printf("\r\n   OSJTAG Port used for Serial Console.");
    printf("\r\n   Interrupt Mode: Enabled");
    printf("\r\n   Operation Mode: TX and RX --> Normal");
    printf("\r\n*****************************************\r\n");
    
    do{
        printf("Please select local node as A or B:\r\n");
        printf("Node:");
        node_type=getchar();
        printf("%c",node_type);
        printf("\r\n");
    }while((node_type!='A') && (node_type!='B') && (node_type!='a') && (node_type!='b'));
    if((node_type=='A') || (node_type=='a'))
    {
        RX_identifier = 0x123;
        TX_identifier = 0x321;
        //      RX_remote_identifier = 0x0F0;
        //      TX_remote_identifier = 0x00F;
        rx_fifo_id[0] = 0x123; //set rx fifo id
    }
    else
    {
        RX_identifier = 0x321;
        TX_identifier = 0x123;
        //      RX_remote_identifier = 0x00F;
        //     TX_remote_identifier = 0x0F0;
        rx_fifo_id[0] = 0x321; //set rx fifo id
    }
    
    result = FLEXCAN_DRV_Init(s_flexcanInstance, &flexcan1_data, true);
    if (result)
    {
        number_errors++;
        printf("\r\nFLEXCAN initilization failed. result: 0x%lx", result);
        return;
    }
    
    result = FLEXCAN_DRV_SetBitrate(s_flexcanInstance, kFlexCanBitrate_1M);
    if (result)
    {
        number_errors++;
        printf("\r\nFLEXCAN set bitrate failed. result: 0x%lx", result);
        return;
    }
    
    FLEXCAN_DRV_SetMaskType(s_flexcanInstance, kFlexCanRxMask_Global);
    
    if (flexcan1_data.is_rx_fifo_needed)
    {
        result = FLEXCAN_DRV_SetRxFifoGlobalMask(s_flexcanInstance, kFlexCanMbId_Std, 0x7FF);
        if (result)
        {
            number_errors++;
            printf("\r\nFLEXCAN set rx fifo global mask failed. result: 0x%lx", result);
            return;
        }
    }
    
    //rx_mb
    result = FLEXCAN_DRV_SetRxMbGlobalMask(s_flexcanInstance, kFlexCanMbId_Std, 0x123);
    if (result)
    {
        number_errors++;
        printf("\r\nFLEXCAN set rx MB global mask failed. result: 0x%lx", result);
        return;
    }
    
    //FlexCAN reveive config
    rx_info.msg_id_type = kFlexCanMbId_Std;
    rx_info.data_length = 1;
    
    if (flexcan1_data.is_rx_fifo_needed)
    {
        // Configure RX FIFO fields
        result = FLEXCAN_DRV_ConfigRxFifo(s_flexcanInstance, &flexcan1_data, kFlexCanRxFifoIdElementFormat_A,
                                          &id_table);
        if (result)
        {
            number_errors++;
            printf("\r\nFlexCAN RX FIFO configuration failed. result: 0x%lx", result);
            return;
        }
    }
    
    // Configure RX MB fields
    result = FLEXCAN_DRV_ConfigRxMb(s_flexcanInstance, &flexcan1_data, RX_mailbox_num, &rx_info,
                                    RX_identifier);
    if (result)
    {
        number_errors++;
        printf("\r\nFlexCAN RX MB configuration failed. result: 0x%lx", result);
        return;
    }
    
    //FlexCAN transfer config
    tx_info.msg_id_type = kFlexCanMbId_Std;
    tx_info.data_length = 8;
    
    result = FLEXCAN_DRV_ConfigTxMb(s_flexcanInstance, &flexcan1_data, TX_mailbox_num, &tx_info, TX_identifier);
    if (result)
    {
        printf("\nTransmit MB config error. Error Code: 0x%lx", result);
    }
    
    int_mb = int_fifo = false;
    
    ch = ch0;
    UART_DRV_ReceiveData(s_uart0Instance,ch,8);
    while(1)
    {
        if(UART_HAL_GetStatusFlag(gUartbaseAddr,kUartRxActiveEdgeDetect)) //check if start bit detected
        {
            UART_HAL_ClearStatusFlag(gUartbaseAddr,kUartRxActiveEdgeDetect);
            PIT_DRV_StopTimer(s_pitInstance,0);
            PIT_DRV_StartTimer(s_pitInstance,0);
            
            if(!(timeout_flag)) //if timeout event is disabled
            {
                timeout_flag = 0xff; //enable timeout event
            }
        }
        
        status = UART_DRV_GetReceiveStatus(s_uart0Instance,&remainingReceiveByteCount); //get receive status
        
        receivedByteCount =  8 - remainingReceiveByteCount;
        
        if((status==kStatus_UART_Success) || ((status==kStatus_UART_RxBusy) && (timeout_flag==true))) //if receiving complete or still in receiving but timeout event happens
        {
            if(receivedByteCount) //if has received something
            {
                if(timeout_flag==true)
                {
                    UART_DRV_AbortReceivingData(s_uart0Instance); //cancle the receiving
                    
                    timeout_flag = 0xff; //re-enable timeout event
                }
                ch = (ch==ch0)? ch1:ch0; //switch receiving buffer
                UART_DRV_ReceiveData(s_uart0Instance,ch,8);//restart the receiving process
                
                tx_info.data_length = receivedByteCount; //number of bytes to be sent
                result = FLEXCAN_DRV_Send(s_flexcanInstance, &flexcan1_data, TX_mailbox_num, &tx_info, TX_identifier,
                                          (ch==ch1)?ch0:ch1);
                if (result)
                {
                    number_errors++;
                    printf("\r\nTransmit send configuration failed. result: 0x%lx", result);
                    return;
                }
            }
        }
        
        if(int_mb) //if message buffer interrupt happens
        {
            OSA_SemaCreate(&irqSync, 0); //reset irpSync as the flexcan isr signals it.
            // Lock RX MB
            result = FLEXCAN_HAL_LockRxMb(gCanbaseAddr, &flexcan1_data, RX_mailbox_num);
            if(result)
            {
                printf("\r\nFlexCAN RX MB Lock failed. result: 0x%lx", result);
                return;
            }
            
            // Get RX MB field values
            result = FLEXCAN_HAL_GetMb(gCanbaseAddr, &flexcan1_data, RX_mailbox_num, &rx_mb);
            if(result)
            {
                printf("\r\nFlexCAN Get RX MB field failed. result: 0x%lx", result);
                return;
            }
            temp = ((rx_mb.cs) >> 16) & 0xF;
            for(j=0;j<temp;j++)
            {
                ch2[j] = rx_mb.data[j];
            }
            UART_DRV_SendData(s_uart0Instance,ch2,temp);
            // Unlock RX message buffer and RX FIFO
            FLEXCAN_HAL_UnlockRxMb(gCanbaseAddr);
            int_mb = false;
        }
        
        if(int_fifo) //if rx fifo interrupt happens
        {
            OSA_SemaCreate(&irqSync, 0); //reset irpSync as the flexcan isr signals it.
            // Lock RX FIFO
            result = FLEXCAN_HAL_LockRxMb(gCanbaseAddr, &flexcan1_data, 0);
            if(result)
            {
                printf("\r\nFlexCAN RX FIFO Lock failed. result: 0x%lx", result);
                return;
            }
            
            // Get RX FIFO field values
            result = FLEXCAN_HAL_ReadFifo(gCanbaseAddr, &rx_fifo);
            if(result)
            {
                printf("\r\nFlexCAN Get RX FIFO field failed. result: 0x%lx", result);
                return;
            }
            
            temp = ((rx_fifo.cs) >> 16) & 0xF;
            for(j=0;j<temp;j++)
            {
                ch2[j] = rx_fifo.data[j];
            }
            UART_DRV_SendData(s_uart0Instance,ch2,temp);
            // Unlock RX message buffer and RX FIFO
            FLEXCAN_HAL_UnlockRxMb(gCanbaseAddr);
            int_fifo = false;
        }
        
        if(number_errors)
        {
            printf("\r\nFlexCAN demo failed!!");
            return;
        }
    }
}


static void pit0_isr_callback(void)
{
    // Set timeout_flag
    if(timeout_flag==0xff)
    {    
        timeout_flag = true;
    }
    // Clear interrupt flag.
    PIT_HAL_ClearIntFlag(PIT_BASE,0);
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
