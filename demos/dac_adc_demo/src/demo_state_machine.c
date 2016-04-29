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
 *
 */

/*******************************************************************************
 * Standard C Included Files
 ******************************************************************************/
#include <stdio.h>
/*******************************************************************************
 * SDK Included Files
 ******************************************************************************/
#include "fsl_os_abstraction.h"
/*******************************************************************************
 * Application Included Files
 ******************************************************************************/
#include "demo_state_machine.h"
 /*******************************************************************************
 * Global Variables
 ******************************************************************************/
dac_user_config_t *g_dacConfig;

adc_user_config_t *g_adcConfig;
adc_chn_config_t *g_chnConfig;

adc_calibration_param_t g_adcCalibraitionParam;
adc_state_t g_adcState;

demo_state_t g_demoState = kStart;

demo_machine_t g_demoMachine[] =
{
    { kStart       ,  demo_start    },
    { kConfigDevice,  device_config },
    { kSetDAC      ,  dac_set       },
    { kWait        ,  wait_state    },
    { kGetADC      ,  adc_get       },
    { kDeinitDevice,  device_deinit },
    { kEndState    ,  demo_end      },
    { kStop        ,  NULL          }
};
/*******************************************************************************
 * Function Definitions
 ******************************************************************************/
uint8_t demo_start(demo_state_t *prevState)
{
    volatile uint8_t msg;

    OSA_Init();

    #if defined(__GNUC__)
    setvbuf(stdin, NULL, _IONBF, 0);
    #endif

    printf("\r\nDAC ADC Demo!\r\n");

    printf("\r\n********************************************");
    printf("\r\n The Following pins are used for this demo.\r\n");
    printf("\r\n********************************************\r\n");

#if defined(TWR_K64F120M)
    printf("\r\n*************************************");
    printf("\r\n  DAC Out                            ");
    printf("\r\n-------------------------------------");
    printf("\r\n  DAC0_OUT (J11A-A32)                ");
    printf("\r\n*************************************");
    printf("\r\n  ADC In                             ");
    printf("\r\n-------------------------------------");
    printf("\r\n  PTB4/ADC1_SE10 (J11A-B27)          ");
    printf("\r\n*************************************");
    printf("\r\n\r\n");
#elif defined(FRDM_K64F120M)
    printf("\r\n*************************************");
    printf("\r\n  DAC Out                            ");
    printf("\r\n-------------------------------------");
    printf("\r\n  DAC0_OUT (J4-11)                   ");
    printf("\r\n*************************************");
    printf("\r\n  ADC In                             ");
    printf("\r\n-------------------------------------");
    printf("\r\n  PTB2/ADC0_SE12 (J4-2) (A0)         ");
    printf("\r\n*************************************");
    printf("\r\n\r\n");
#elif defined(TWR_K22F120M) || defined(TWR_K22F120M128R) || defined(TWR_K22F120M256R)
    printf("\r\n*************************************");
    printf("\r\n  DAC Out                            ");
    printf("\r\n-------------------------------------");
    printf("\r\n  DAC0_OUT (J24A-A32)                ");
    printf("\r\n*************************************");
    printf("\r\n  ADC In                             ");
    printf("\r\n-------------------------------------");
    printf("\r\n  PTB0/ADC0_SE8 (J24A-B27)           ");
    printf("\r\n*************************************");
    printf("\r\n\r\n");
#elif defined(FRDM_K22F120M)
    printf("\r\n*************************************");
    printf("\r\n  DAC Out                            ");
    printf("\r\n-------------------------------------");
    printf("\r\n  DAC0_OUT (J24-11)                  ");
    printf("\r\n*************************************");
    printf("\r\n  ADC In                             ");
    printf("\r\n-------------------------------------");
    printf("\r\n  PTB0/ADC0_SE8 (J24-2) (A0)         ");
    printf("\r\n*************************************");
    printf("\r\n\r\n");
#elif defined(TWR_KV31F120M) || defined(TWR_KV31F120M128R) || defined(TWR_KV31F120M256R)
    printf("\r\n*************************************");
    printf("\r\n  DAC Out                            ");
    printf("\r\n-------------------------------------");
    printf("\r\n  DAC0_OUT (J16A-A32)                ");
    printf("\r\n*************************************");
    printf("\r\n  ADC In                             ");
    printf("\r\n-------------------------------------");
    printf("\r\n  PTE2/ADC1_SE6a (J16A-B27)          ");
    printf("\r\n*************************************");
    printf("\r\n\r\n");
    printf("\r\n\r\n");
#endif

    printf("\r\nPress spacebar to start demo.\r\n");

    msg = 'A';

    while(msg != ' ')
    {
        msg = getchar();
    }

    printf("\r\nDemo begin...\r\n" );

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Set next state. */
    g_demoState = kConfigDevice;

    return msg;
}

uint8_t device_config(demo_state_t *prevState)
{
    /* Allocate memory for configuration structures to avoid memory overwrites. */
    g_dacConfig = (dac_user_config_t *)OSA_MemAlloc(sizeof(dac_user_config_t));
    g_adcConfig = (adc_user_config_t *)OSA_MemAlloc(sizeof(adc_user_config_t));
    g_chnConfig = (adc_chn_config_t *)OSA_MemAlloc(sizeof(adc_chn_config_t));

    /*****************************************
     * Configre DAC for software triggering. *
     *****************************************/

    /* Set config for basic operation. */ 
    DAC_DRV_StructInitUserConfigNormal(g_dacConfig);

    /* Init DAC with basic configuration. */
    DAC_DRV_Init(DAC_INSTANCE, g_dacConfig);

    /******************
     * Configure ADC. *
     ******************/

    /* Calibrate ADC. */
    ADC_DRV_GetAutoCalibrationParam(ADC_INSTANCE, &g_adcCalibraitionParam);
    ADC_DRV_SetCalibrationParam(ADC_INSTANCE, &g_adcCalibraitionParam);

    /* Confiure ADC for blocking mode. */
    ADC_DRV_StructInitUserConfigForBlockingMode(g_adcConfig);
    ADC_DRV_Init(ADC_INSTANCE, g_adcConfig, &g_adcState);

    /* Trigger channel. */
    g_chnConfig->chnNum = ADC_CHANNEL;
    g_chnConfig->diffEnable= false;
    g_chnConfig->intEnable = false;
    g_chnConfig->chnMux = kAdcChnMuxOfDefault;
    ADC_DRV_ConfigConvChn(ADC_INSTANCE, 0U, g_chnConfig);

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Set next state. */
    g_demoState = kSetDAC;

    return 0;
}

uint8_t dac_set(demo_state_t *prevState)
{
    uint8_t msg;

    printf("\r\n\r\nSelect DAC output level:\r\n\t1. 1.0 V\r\n\t2. 1.5 V\r\n\t3. 2.0 V\r\n\t4. 2.5 V\r\n\t5. 3.0 V\r\n-> ");

    msg = ' ';

    while((msg < '1') || (msg > '5'))
    {
        printf("\b");
        msg = getchar();
        printf("%c", msg);
    }

    switch(msg)
    {
        case '1':
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, DAC_1_0_VOLTS);
            break;

        case '2':
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, DAC_1_5_VOLTS);
            break;

        case '3':
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, DAC_2_0_VOLTS);
            break;

        case '4':
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, DAC_2_5_VOLTS);
            break;

        case '5':
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, DAC_3_0_VOLTS);
            break;

        default:
            /* Set DAC output */
            DAC_DRV_Output(DAC_INSTANCE, 0U);
            break;
    }

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Set next state. */
    g_demoState = kWait;

    return msg;
}

uint8_t wait_state(demo_state_t *prevState)
{

    switch(*prevState)
    {

        case kSetDAC:

            /* Wait for 500 us. */
            OSA_TimeDelay(200);

            /* Set next state. */
            g_demoState = kGetADC;

            break;

        case kGetADC:

            /* Wait for 500 us. */
            OSA_TimeDelay(200);

            /* Set next state. */
            g_demoState = kSetDAC;

            break;

        default:

            /* Wait for 500 us. */
            OSA_TimeDelay(200);

            break;
    }

    return 0;
}

uint8_t adc_get(demo_state_t *prevState)
{
    uint8_t msg;
    uint16_t adcData;
    float voltRead;
    uint8_t voltOne;
    uint8_t voltTenth;
    uint8_t voltHundreth;

    /* Get ADC input. */
    ADC_DRV_WaitConvDone(ADC_INSTANCE, 0U);

    adcData = ADC_DRV_GetConvValueRAW(ADC_INSTANCE, 0U);

    adcData = ADC_DRV_ConvRAWData(adcData, false, kAdcResolutionBitOfSingleEndAs12);

    printf("\r\n\r\nADC Value: %d\r\n", adcData);

    /* Convert ADC value to a voltage based on 3.3V VREFH on board. */
    voltRead = (float)adcData * (VREF_BRD / SE_12BIT);

    /* Get the firtst digit before decimal place. */
    voltOne = (uint8_t)voltRead;

    /* Get the first digit after the decimal place. */
    voltTenth = (uint8_t)((voltRead - voltOne) * 10);

    /* Get the second digit after the decimal place. */
    voltHundreth = (uint8_t)((((voltRead - voltOne) * 10) - voltTenth) * 10);

    printf("\r\nADC Voltage: %d.%d%d\r\n", voltOne, voltTenth, voltHundreth);

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Determine what to do next based on user's request. */
    printf("\r\n\r\nWhat next?:\r\n\t1. Test another DAC output value.\r\n\t2. Terminate demo.\r\n-> ");

    msg = ' ';

    while((msg < '1') || (msg > '2'))
    {
        printf("\b");
        msg = getchar();
        printf("%c", msg);
    }

    /* Set next state. */
    if(msg == '1')
    {
        g_demoState = kWait;
    }
    else
    {
        g_demoState = kDeinitDevice;

        /* Pause the conversion after testing. */
        ADC_DRV_PauseConv(ADC_INSTANCE, 0U);
    }

    return msg;
}

uint8_t device_deinit(demo_state_t *prevState)
{
    /* De initialize DAC & ADC */
    DAC_DRV_Deinit(DAC_INSTANCE);
    ADC_DRV_Deinit(ADC_INSTANCE);

    /* Free allocated memory. */
    OSA_MemFree(g_dacConfig);
    OSA_MemFree(g_adcConfig);
    OSA_MemFree(g_chnConfig);

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Set next state. */
    g_demoState = kEndState;

    return 0;
}

uint8_t demo_end(demo_state_t *prevState)
{
    printf("\r\nDemo terminated. Reset device to begin again.\r\n");

    /* Set previous state to current state. */
    *prevState = g_demoState;

    /* Set next state. */
    g_demoState = kStop;

    return 0;
}
/******************************************************************************
 * EOF
 ******************************************************************************/
