/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : pin_mux.c
**     Project     : twrk21d50m-pin
**     Processor   : MK21DN512VMB5
**     Component   : PinSettings
**     Version     : Component 01.007, Driver 1.2, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-06-08, 20:07, # CodeGen: 9
**     Abstract    :
**
**     Settings    :
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc.
**     All Rights Reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file pin_mux.c
** @version 1.2
** @brief
**
*/
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

/* MODULE pin_mux. */

#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "pin_mux.h"

void configure_gpio_pins(uint32_t instance)
{
    switch(instance)
    {
        case PORTA_IDX:                      /* HW_PORTA */
            break;
        case PORTB_IDX:                      /* HW_PORTB */
            break;
        case PORTC_IDX:                      /* HW_PORTC */
            /* Affects PORTC_PCR4 register */
            PORT_HAL_SetPassiveFilterCmd(PORTC,4u,true);
            PORT_HAL_SetMuxMode(PORTC,4u,kPortMuxAsGpio);
            PORT_HAL_SetPullMode(PORTC,4u,kPortPullUp);
            PORT_HAL_SetPullCmd(PORTC,4u,true);
            /* Affects PORTC_PCR5 register */
            PORT_HAL_SetPassiveFilterCmd(PORTC,5u,true);
            PORT_HAL_SetMuxMode(PORTC,5u,kPortMuxAsGpio);
            PORT_HAL_SetPullMode(PORTC,5u,kPortPullUp);
            PORT_HAL_SetPullCmd(PORTC,5u,true);
            /* Affects PORTC_PCR6 register */
            PORT_HAL_SetPassiveFilterCmd(PORTC,6u,true);
            PORT_HAL_SetMuxMode(PORTC,6u,kPortMuxAsGpio);
            PORT_HAL_SetPullMode(PORTC,6u,kPortPullUp);
            PORT_HAL_SetPullCmd(PORTC,6u,true);
            /* Affects PORTC_PCR7 register */
            PORT_HAL_SetPassiveFilterCmd(PORTC,7u,true);
            PORT_HAL_SetMuxMode(PORTC,7u,kPortMuxAsGpio);
            PORT_HAL_SetPullMode(PORTC,7u,kPortPullUp);
            PORT_HAL_SetPullCmd(PORTC,7u,true);
            break;
        case PORTD_IDX:                      /* HW_PORTB */
            /* Affects PORTD_PCR4 register */
            PORT_HAL_SetMuxMode(PORTD,4u,kPortMuxAsGpio);
            /* Affects PORTD_PCR5 register */
            PORT_HAL_SetMuxMode(PORTD,5u,kPortMuxAsGpio);
            /* Affects PORTD_PCR6 register */
            PORT_HAL_SetMuxMode(PORTD,6u,kPortMuxAsGpio);
            /* Affects PORTD_PCR7 register */
            PORT_HAL_SetMuxMode(PORTD,7u,kPortMuxAsGpio);
            break;
        case PORTE_IDX:                      /* HW_PORTE */
            break;
        default:
            break;
    }
}

void configure_i2c_pins(uint32_t instance)
{
    switch(instance)
    {
        case I2C0_IDX:                       /* I2C0 */
            /* Affects PORTD_PCR2 register */
            PORT_HAL_SetMuxMode(PORTD,2u,kPortMuxAlt4);
            PORT_HAL_SetOpenDrainCmd(PORTD,2u,true);
            /* Affects PORTD_PCR3 register */
            PORT_HAL_SetMuxMode(PORTD,3u,kPortMuxAlt4);
            PORT_HAL_SetOpenDrainCmd(PORTD,3u,true);
            break;
        default:
            break;
    }
}

void configure_i2s_pins(uint32_t instance)
{
    // TODO: I2S are still not wired to elevator
}
void configure_rtc_pins(uint32_t instance)
{
    // TODO: PTE0 - RTC_CLKOUT conflicts with UART1
}

void configure_spi_pins(uint32_t instance)
{
    switch(instance)
    {
        case SPI0_IDX:                       /* SPI0 */
            /* Affects PORTC_PCR4 register */
            PORT_HAL_SetMuxMode(PORTC,4u,kPortMuxAlt2);
            /* Affects PORTC_PCR5 register */
            PORT_HAL_SetMuxMode(PORTC,5u,kPortMuxAlt2);
            /* Affects PORTC_PCR6 register */
            PORT_HAL_SetMuxMode(PORTC,6u,kPortMuxAlt2);
            /* Affects PORTC_PCR7 register */
            PORT_HAL_SetMuxMode(PORTC,7u,kPortMuxAlt2);

            break;
        case SPI1_IDX:                       /* SPI1 */
            /* Affects PORTB_PCR10 register */
            PORT_HAL_SetMuxMode(PORTB,10u,kPortMuxAlt2);
            /* Affects PORTB_PCR11 register */
            PORT_HAL_SetMuxMode(PORTB,11u,kPortMuxAlt2);
            /* Affects PORTB_PCR16 register */
            PORT_HAL_SetMuxMode(PORTB,16u,kPortMuxAlt2);
            /* Affects PORTB_PCR17 register */
            PORT_HAL_SetMuxMode(PORTB,17u,kPortMuxAlt2);
        default:
            break;
    }
}

void configure_uart_pins(uint32_t instance)
{
    switch(instance)
    {
        // TODO: UART0 conflicts with LEDs
        case UART0_IDX:                      /* UART0 */
            break;
        case UART1_IDX:                      /* UART1 */
            /* Affects PORTE_PCR0 register */
            PORT_HAL_SetMuxMode(PORTE,0u,kPortMuxAlt3);
            /* Affects PORTE_PCR1 register */
            PORT_HAL_SetMuxMode(PORTE,1u,kPortMuxAlt3);
            break;
        default:
            break;
    }
}

void configure_spi_cs0_pins(uint32_t instance)
{
    PORT_HAL_SetMuxMode(PORTC,4u,kPortMuxAsGpio);
}

/* Setup FTM pins to drive LED */
void configure_ftm_pins(uint32_t instance)
{
    switch(instance)
    {
        case FTM0_IDX:                       /* FTM0 */
            /* Affects PORTD_PCR6 register */
            PORT_HAL_SetDriveStrengthMode(PORTD,6u,kPortLowDriveStrength);
            PORT_HAL_SetMuxMode(PORTD,6u,kPortMuxAlt4);
            PORT_HAL_SetSlewRateMode(PORTD,6u,kPortSlowSlewRate);
            break;
        default:
            break;
    }
}

void configure_cmp_pins(uint32_t instance)
{
    switch (instance)
    {
        // TODO: CMP conflicts with SWs and UART1
        case 1U:
            break;
        default:
            break;
    }
}

/* END pin_mux. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/