/*
 * Copyright (c) 2013-2014, Freescale Semiconductor, Inc.
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
#include "fsl_mma8451.h"
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "pin_mux.h"
#include "fsl_os_abstraction.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

extern void init_hardware(void);

/******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    int32_t err;
    mma8451_device_t dev;
    char buf[128] = { 0 };

    hardware_init();
    dbg_uart_init();

    configure_gpio_i2c_pins(0);

    OSA_Init();

    printf("\r\n== Accelerometer Test ==\r\n\r\n");

    /*
     *Init MMA8451 driver. Pass true to indicate that the SAO signal is high.
     * Pass false to indicate that the SA0 is low.
     */
    err = mma8451_init(&dev, BOARD_ACCEL_I2C_ADDR, 100);
    if (err)
    {
        printf("Failed to initialize the MMA8451 (err=%d)!\r\n", (int)err);
        return -1;
    }

    printf("Reading acceleration data...\r\n");

    while (true)
    {
        /* Read acceleration data. */
        acceleration_t accel;
        err = mma8451_get_acceleration(&dev, &accel);
        if (err)
        {
            printf("Failed to read acceleration data (err=%d)!\r\n", (int)err);
            return -1;
        }

        /*
         * Having problems with float format specifiers, so we're just converting to
         * decimal before printing.
         */
        sprintf(buf, "x=%d, y=%d, z=%d                \r",
                (int)accel.x, (int)accel.y, (int)accel.z);
        printf("%s", buf);

        /* Delay */
        OSA_TimeDelay(100);
    }
}

/******************************************************************************
 * EOF
 ******************************************************************************/
