/*******************************************************************************
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.                           *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without modifi-  *
 * cation, are permitted provided that the following conditions are met:       *
 *                                                                             *
 * o Redistributions of source code must retain the above copyright notice,    *
 * this list of conditions and the following disclaimer.                       *
 *                                                                             *
 * o Redistributions in binary form must reproduce the above copyright notice, *
 * this list of conditions and the following disclaimer in the documentation   *
 * and/or other materials provided with the distribution.                      *
 *                                                                             *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its    *
 *   contributors may be used to endorse or promote products derived from this *
 *   software without specific prior written permission.                       *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  *
 * POSSIBILITY OF SUCH DAMAGE.                                                 *
 *                                                                             *
 *******************************************************************************/


#ifndef __LOWPOWER_ADC_H__
#define __LOWPOWER_ADC_H__

#include <stdint.h>


/*!
* @brief Boundaries struct
*/
typedef struct lowPowerAdcBoundaries
{
    uint32_t upperBoundary;
    uint32_t lowerBoundary;
} lowPowerAdcBoundaries_t;


/*!
 * @brief Initialize Clock Manager for PORT, ADC, and LPTIMER.
 */
void init_hardware(void);

/*!
 * @brief Low Power Timer Interrupt handler. Clear LPT Compare flag.
 */
void LowPowerTimerIRQHandler(void);

/*!
 * @brief ADC Interrupt handler. Get current ADC value and set conversionCompleted flag.
 */
void ADC1IRQHandler(void);

/*!
 * @brief Initialize Low Power Timer. Use 1 kHz LPO with no preescaler and enable LPT interrupt.
 */
void InitLowPowerTmr(void);

/*!
 * @brief Calculate current temperature.
 *
 * @return uint32_t Returns current temperature.
 */
uint32_t GetCurrentTempValue(void);

/*!
 * @brief Calculate current temperature.
 *
 * @param updateBoundariesCounter Indicate number of values into tempArray.
 *
 * @param tempArray Store temperature value.
 *
 * @return lowPowerAdcBoundaries_t Returns upper and lower temperature boundaries.
 */
lowPowerAdcBoundaries_t TempSensorCalibration(uint32_t updateBoundariesCounter,
                                                     uint32_t *tempArray);

#endif /* __LOWPOWER_ADC_H__ */

/*******************************************************************************
 * EOF
 *******************************************************************************/
