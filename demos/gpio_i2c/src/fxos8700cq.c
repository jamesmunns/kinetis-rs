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
#include "fxos_api.h"
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "pin_mux.h"
#include "i2c_sim.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

/******************************************************************************
 * Code
 ******************************************************************************/

i2c_status_t fxos_i2c_read(uint32_t instance, i2c_device_t const *chip, uint8_t * addr,
                          uint32_t alen, uint8_t *buf, uint32_t len, uint32_t timeout)
{
    return (i2c_status_t)i2c_gpio_read(chip->address, (uint32_t)(*addr), alen, buf, len);
}

i2c_status_t fxos_i2c_write(uint32_t instance, i2c_device_t const *chip, uint8_t * addr,
                          uint32_t alen, uint8_t *buf, uint32_t len, uint32_t timeout)
{
    return (i2c_status_t)i2c_gpio_write(chip->address, (uint32_t)(*addr), alen, buf, len);
}

int main(void)
{
    int32_t err;
    fxos_dev_t fxos_dev;
    fxos_i2c_interface_t i2c_interface;

    hardware_init();
    dbg_uart_init();

    configure_gpio_i2c_pins(0);

    OSA_Init();

    printf("\r\n== Accelerometer Test ==\r\n\r\n");
    fxos_dev.slave.address = BOARD_ACCEL_I2C_ADDR;
    fxos_dev.slave.baudRate_kbps = 100;
    i2c_interface.i2c_init = i2c_gpio_init;
    i2c_interface.i2c_probe = i2c_gpio_probe;
    i2c_interface.i2c_read = fxos_i2c_read;
    i2c_interface.i2c_write = fxos_i2c_write;
    fxos_dev.i2c = &i2c_interface;
    err = fxos_init(&fxos_dev);
    if (err)
    {
        printf("Failed to initialize the FXOS8700CQ (err=%d)!\r\n", (int)err);
        return 1;
    }

    printf("Reading acceleration data...\r\n");

    while (true)
    {
        /* Read acceleration data. */
        fxos_sensorData_t sensorData;
        int16_t xAccel = 0;
        int16_t yAccel = 0;
        int16_t zAccel = 0;	

        int16_t xMag = 0;
        int16_t yMag = 0;
        int16_t zMag = 0;

        fxos_read_sensor_data(&fxos_dev, &sensorData);

        /* process and align data */
        xAccel = (int16_t)((sensorData.accelXMSB << 8) | (sensorData.accelXLSB));
        xAccel = xAccel >> 2;
        yAccel = (int16_t)((sensorData.accelYMSB << 8) | (sensorData.accelYLSB));
        yAccel = yAccel >> 2;
        zAccel = (int16_t)((sensorData.accelZMSB << 8) | (sensorData.accelZLSB));
        zAccel = zAccel >> 2;

        xMag = (int16_t)((sensorData.magXMSB << 8) | (sensorData.magXLSB));
        yMag = (int16_t)((sensorData.magYMSB << 8) | (sensorData.magYLSB));
        zMag = (int16_t)((sensorData.magZMSB << 8) | (sensorData.magZLSB));

	    /* print data */
	    printf("xAcc = %d, yAcc = %d, zAcc = %d, "
       	        "xMag = %d, yMag = %d, zMag = %d  "
                "                   \r",
                xAccel, yAccel, zAccel, xMag, yMag, zMag);

        /* Delay */
        OSA_TimeDelay(100);
    }
}

/******************************************************************************
 * EOF
 ******************************************************************************/
