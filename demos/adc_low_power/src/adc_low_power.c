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

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "adc_low_power.h"


#include <stdio.h>

#include "fsl_debug_console.h"
#include "fsl_gpio_hal.h"
#include "fsl_port_hal.h"
#include "fsl_smc_hal.h"
#include "fsl_adc_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"
#include "board.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADC_0                   (0U)
#define CHANNEL_0				(0U)
#define LED_ON                  (0U)
#define LED_OFF                 (1U)
/*!
* @brief These values are used to get the temperature. DO NOT MODIFY
*/
#define VTEMP25_ADC             (14219U)
#define K                       (10000U)
#define M1                      (250000U)
#define M2                      (311U)

#define UPPER_VALUE_LIMIT       (1U)     /*! This value/10 is going to be added to current Temp to set the upper boundary*/
#define LOWER_VALUE_LIMIT       (1U)     /*! This Value/10 is going to be subtracted from current Temp to set the lower boundary*/
#define UPDATE_BOUNDARIES_TIME  (20U)    /*! This value indicates the number of cycles needed to update boundaries. To know the Time it will take, multiply this value times LPTMR_COMPARE_VALUE*/
#define kAdcChannelTemperature  (26U)

#define USE_STDIO_FUNCTIONS  /* Define this symbol to use STDIO functions */

extern void init_trigger_source(uint32_t instance);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint32_t adcValue = 0;   /*! ADC value */
volatile bool conversionCompleted = false; /*! Conversion is completed Flag */
static adc_state_t gAdcState;
const uint32_t gSimBaseAddr[] = SIM_BASE_ADDRS;
static smc_power_mode_config_t smcConfig;

/*******************************************************************************
 * Code                                                                        *
 ******************************************************************************/


/* ADC Interrupt Handler */
void ADC1IRQHandler(void)
{
    /* Get current ADC value */
    adcValue = ADC_DRV_GetConvValueRAWInt (ADC_0, CHANNEL_0);
    /* Set conversionCompleted flag. This prevents an wrong conversion in main function */
    conversionCompleted = true;
}

/*!
 * @brief enter in VLPS mode
 */
void config_vlps(void)
{
    smc_power_mode_protection_config_t smcProtConfig;

    /* set to allow entering specific modes*/
    smcProtConfig.vlpProt = true;
    SMC_HAL_SetProtection(SMC_BASE, &smcProtConfig);

    /* set power mode to specific Run mode */
#if FSL_FEATURE_SMC_HAS_LPWUI
    smcConfig.lpwuiOption = false;
#endif
    smcConfig.porOption = false;
    smcConfig.powerModeName = kPowerModeVlps;
}

/*!
 * @brief Initialize the ADCx for HW trigger.
 *
 * @param instance The ADC instance number
 */
static int32_t init_adc(uint32_t instance)
{
#if FSL_FEATURE_ADC_HAS_CALIBRATION
    adc_calibration_param_t adcCalibraitionParam;
#endif
    adc_user_config_t adcUserConfig;
    adc_chn_config_t adcChnConfig;

#if FSL_FEATURE_ADC_HAS_CALIBRATION
    /* Auto calibraion. */
    ADC_DRV_GetAutoCalibrationParam(instance, &adcCalibraitionParam);
    ADC_DRV_SetCalibrationParam(instance, &adcCalibraitionParam);
#endif

    /*
     * Initialization ADC for
     * 16bit resolution, interrrupt mode, hw trigger enabled.
     * normal convert speed, VREFH/L as reference,
     * disable continuouse convert mode.
     */
    ADC_DRV_StructInitUserConfigForIntMode(&adcUserConfig);
    adcUserConfig.resolutionMode = kAdcResolutionBitOf16;
    adcUserConfig.hwTriggerEnable = true;
    adcUserConfig.continuousConvEnable = false;
    ADC_DRV_Init(instance, &adcUserConfig, &gAdcState);

    /* Install Callback function into ISR. */
    ADC_DRV_InstallCallback(instance, CHANNEL_0, ADC1IRQHandler);

    adcChnConfig.chnNum = kAdcChannelTemperature;
    adcChnConfig.diffEnable = false;
    adcChnConfig.intEnable = true;
    adcChnConfig.chnMux = kAdcChnMuxOfA;
    /* Configure channel0. */
    ADC_DRV_ConfigConvChn(instance, CHANNEL_0, &adcChnConfig);

    return 0;
}


/* Calculate the current temperature */
uint32_t GetCurrentTempValue(void)
{
    uint32_t currentTemperature = 0;
    currentTemperature = (M1 - (adcValue - VTEMP25_ADC) * M2)/K;
    return currentTemperature;
}

/* Calculate the average temperature and set boundaries */
lowPowerAdcBoundaries_t TempSensorCalibration(uint32_t updateBoundariesCounter,
                                                     uint32_t *tempArray)
{
    uint32_t avgTemp = 0;
    lowPowerAdcBoundaries_t boundaries;

    for(int i = 0; i < updateBoundariesCounter; i++)
    {
        avgTemp += tempArray[i];
    }
    /* Get average temperature */
    avgTemp /= updateBoundariesCounter;

    /* Set upper boundary*/
    boundaries.upperBoundary = avgTemp + UPPER_VALUE_LIMIT;

    /* Set lower boundary */
    boundaries.lowerBoundary = avgTemp - LOWER_VALUE_LIMIT;

    return boundaries;
}

int main(void)
{
    uint32_t currentTemperature = 0;
    uint32_t updateBoundariesCounter = 0;
    uint32_t tempArray[UPDATE_BOUNDARIES_TIME * 2];
    lowPowerAdcBoundaries_t boundaries;

    /* Init hardware for TWR-K70F120M */
    hardware_init();

    /* Initialize GPIO pins */
    GPIO_DRV_Init(accelIntPins, ledPins);

    /* Configure the UART TX/RX pins */
    configure_uart_pins(BOARD_DEBUG_UART_INSTANCE);

    /* Call this function to initialize the console UART.  This function
       enables the use of STDIO functions (printf, scanf, etc.) */
    dbg_uart_init();

    /* Configure SMC module to entry to vlps mode */
    config_vlps();

    /* Initialize ADC */
    if (init_adc(ADC_0))
    {
        printf("Failed to do the ADC init\n");
        return -1;
    }

    /* Show the currentTemperature value */
        printf("\r\n ADC LOW POWER DEMO \r\n\n\n");
    printf("\r\nThe Low Power ADC project is designed to work with the Tower System or in a stand alone setting. \n\n");
    printf("\r 1. Set your target board in a place where the temperature is constant.  \n");
#ifndef FREEDOM
    printf("\r 2. Wait until the green LED light turns on. \n");
#else
    printf("\r 2. Wait until the white LED light turns on. \n");
#endif
    printf("\r 3. Increment or decrement the temperature to see the changes. \n");

	/* setup the HW trigger source */
    init_trigger_source(ADC_0);

    /* Warm up microcontroller and allow to set first boundaries*/
    while(updateBoundariesCounter < (UPDATE_BOUNDARIES_TIME * 2))
    {
        while(!conversionCompleted);
        currentTemperature = GetCurrentTempValue();
        tempArray[updateBoundariesCounter] = currentTemperature;
        updateBoundariesCounter++;
        conversionCompleted = false;
    }

    /* Temp Sensor Calibration */
    boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
    updateBoundariesCounter = 0;

#ifndef FREEDOM
    /* Green LED is turned on indicating calibration is done */
    GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_GREEN, LED_ON);
#endif
    for(;;)
    {
        /* Prevents the use of wrong values */
        while(!conversionCompleted)
        {}

        /* Get current Temperature Value */
        currentTemperature = GetCurrentTempValue();

        /* Store temperature values that are going to be use to calculate average temperature */
        tempArray[updateBoundariesCounter] = currentTemperature;

#ifdef FREEDOM

        /* Select which LED is going to be turned on and off */
        if(currentTemperature > boundaries.upperBoundary)
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_ON);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_OFF);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_GREEN, LED_OFF);
        }
        else if(currentTemperature < boundaries.lowerBoundary)
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_OFF);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_ON);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_GREEN, LED_OFF);
        }
        else
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_ON);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_ON);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_GREEN, LED_ON);
        }

#else

        /* Show how fast is each cycle */
        GPIO_DRV_TogglePinOutput(BOARD_GPIO_LED_GREEN);

        /* Select which LED is going to be turned on and off */
        if(currentTemperature > boundaries.upperBoundary)
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_ON);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_OFF);
        }
        else if(currentTemperature < boundaries.lowerBoundary)
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_OFF);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_ON);
        }
        else
        {
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_RED, LED_OFF);
            GPIO_DRV_WritePinOutput(BOARD_GPIO_LED_BLUE, LED_OFF);
        }
#endif

        /* Call update function */
        if(updateBoundariesCounter >= (UPDATE_BOUNDARIES_TIME))
        {
            boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
            updateBoundariesCounter = 0;
        }
        else
        {
            updateBoundariesCounter++;
        }

        /* Clear conversionCompleted flag */
        conversionCompleted = false;

        /* Entry to Low Power Mode */
        SMC_HAL_SetMode(SMC_BASE, &smcConfig);
    }
}
/* END OF CODE */
