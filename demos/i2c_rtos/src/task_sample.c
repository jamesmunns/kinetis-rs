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

#include "fsl_adc_driver.h"
#include "fsl_interrupt_manager.h"
#include "i2c_rtos.h"

/* These values are used covert temperature. DO NOT MODIFY */
#define VTEMP25_ADC             (14219)
#define K                       (10000)
#define M1                      (250000)
#define M2                      (311)

/* temperature global variable */
static int32_t gTemperature;

/*!
 * task to read ADC for internal temperature
 */
void task_sample(task_param_t param)
{
#if FSL_FEATURE_ADC_HAS_CALIBRATION
    adc_calibration_param_t tempSnseCalibraitionParam;
#endif
    adc_user_config_t tempSnseAdcConfig;
    adc_state_t tempSnseAdcState;
    /* ADC Channel Configuration */
    adc_chn_config_t tempSnseChannelConfig =
    {
        .chnNum = 26,
        .chnMux = kAdcChnMuxOfA,
        .diffEnable = false,
        .intEnable = false
    };
    uint32_t adcValue;

#if FSL_FEATURE_ADC_HAS_CALIBRATION
    /* Auto calibraion. */
    ADC_DRV_GetAutoCalibrationParam(HW_ADC1, &tempSnseCalibraitionParam);
    ADC_DRV_SetCalibrationParam(HW_ADC1, &tempSnseCalibraitionParam);
#endif /* FSL_FEATURE_ADC_HAS_CALIBRATION */
    
	ADC_DRV_StructInitUserConfigForOneTimeTriggerMode(&tempSnseAdcConfig);
    tempSnseAdcConfig.clkSrcMode = kAdcClkSrcOfAsynClk;
    tempSnseAdcConfig.resolutionMode = kAdcResolutionBitOfSingleEndAs16;
    /* Initialize ADC */
    ADC_DRV_Init(HW_ADC1, &tempSnseAdcConfig, &tempSnseAdcState);

    while (1)
    {
        /* ADC starts conversion */
		ADC_DRV_ConfigConvChn(HW_ADC1, 0U, &tempSnseChannelConfig);
        /* poll to complete status and read back result */
		ADC_DRV_WaitConvDone(HW_ADC1, 0U);
		adcValue = ADC_DRV_GetConvValueRAW(HW_ADC1, 0U);
		adcValue = ADC_DRV_ConvRAWData(adcValue, false, tempSnseAdcConfig.resolutionMode);
        /* ADC stop conversion */
		ADC_DRV_PauseConv(HW_ADC1, 0U);
        /* convert to temperature */
        INT_SYS_DisableIRQGlobal();
        gTemperature = (M1 - (adcValue - VTEMP25_ADC) * M2)/K;
        INT_SYS_EnableIRQGlobal();
        /* sleep 4s */
        OSA_TimeDelay(4000);
    }
}

/*!
 * Get the 32bits temperature in byte
 * from the ISR context
 */
uint8_t get_temp_in_byte(uint32_t index)
{
    static uint8_t *pTemp = (uint8_t*)&gTemperature;
    return pTemp[index];
}
