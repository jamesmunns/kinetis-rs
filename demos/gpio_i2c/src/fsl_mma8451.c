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

#include "fsl_mma8451.h"
#include "i2c_sim.h"

#include <stdio.h>
#include <string.h>

/*!
 * @brief I2C related constants for the MMA8451.
 */
enum _mma8451_i2c_constants
{
    kMMA8451_I2C_Address = 0x38,
    kMMA8451_I2C_Address_With_SAO_Set = 0x3a
};

/******************************************************************************
 * Code
 ******************************************************************************/
uint8_t mma8451_read_register(const mma8451_device_t * device, uint8_t reg_addr)
{
    uint8_t buf[1];

    i2c_gpio_read(device->address.address, reg_addr, 1, buf, 1);

    return buf[0];
}

int32_t mma8451_write_register(const mma8451_device_t * device, uint8_t reg_addr, uint8_t reg_val)
{
    uint8_t buf[1];
    buf[0] = reg_val;

    return i2c_gpio_write(device->address.address, reg_addr, 1, buf, sizeof(buf));
}

int32_t mma8451_init(mma8451_device_t *device, uint8_t i2c_addr, uint32_t baud_kbps)
{
    uint8_t val = 0;
    
    /* Init device struct. */
    memset(device, 0, sizeof(*device));
    
    device->address.address = i2c_addr;
    device->address.baudRate_kbps = baud_kbps;

    i2c_gpio_init(device->address.baudRate_kbps, device->address.address);

    if (i2c_gpio_probe(device->address.address))
    {
        printf("MMA8451: Chip address not presented at: %x\r\n", device->address.address);
        return 1;
    }

    /* Read WHO_AM_I register. */
    val = mma8451_read_register(device, kMMA8451_WHO_AM_I);
    if (val != kMMA8451_WHO_AM_I_Device_ID)
    {
        printf("MMA8451: Unexpected result from WHO_AM_I (0x%02x)\r\n", val);
        return 1;
    }

    /* Put the mma8451 into standby mode */
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val &= (uint8_t)(~(0x01));
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);

    /* Set the range, -8g to 8g */
    val = mma8451_read_register(device, kMMA8451_XYZ_DATA_CFG);
    val &= (uint8_t)(~0x03);
    val |= 0x02;
    mma8451_write_register(device, kMMA8451_XYZ_DATA_CFG, val);

    /* Set the F_MODE, disable FIFO */
    val = mma8451_read_register(device, kMMA8451_F_SETUP);
    val &= 0x3F;
    mma8451_write_register(device, kMMA8451_F_SETUP, val);

    /* Put the mma8451 into active mode */
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val |= 0x01;
    val &= (uint8_t)(~0x02);               /* set F_READ to 0 */
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);
    
    return 0;
}

static int16_t mma8451_get_accel_xyz(const mma8451_device_t * device, uint8_t reg_addr_h, uint8_t reg_addr_l)
{
    uint8_t ucVal1 = 0;
    uint8_t ucVal2 = 0;
    uint16_t iTemp = 0;
    int sign = 1;
    
    ucVal1 = mma8451_read_register(device, reg_addr_h);
    ucVal2 = mma8451_read_register(device, reg_addr_l);
    sign = (ucVal1 & 0x80) ? (-1) : 1;
    iTemp = ucVal1 & 0x7F;
    iTemp = (iTemp << 6) + ((ucVal2) >> 2);
    if (sign == -1)             /* 2's completement */
    {
        iTemp = ((uint16_t)(~iTemp + 1)) & 0x1FFF;
    }
    iTemp *= sign;
    
    return iTemp;
}

int32_t mma8451_get_acceleration(const mma8451_device_t * device, acceleration_t *accel)
{
    
    uint8_t ucStatus = 0;
    int32_t x_sum = 0,
            y_sum = 0,
            z_sum = 0;

    if (!accel)
    {
        return 0;
    }
    
    do
    {
        ucStatus = mma8451_read_register(device, kMMA8451_STATUS);
    } while (!(ucStatus & 0x08));

    x_sum = mma8451_get_accel_xyz(device, kMMA8451_OUT_X_MSB, kMMA8451_OUT_X_LSB);
    y_sum = mma8451_get_accel_xyz(device, kMMA8451_OUT_Y_MSB, kMMA8451_OUT_Y_LSB);
    z_sum = mma8451_get_accel_xyz(device, kMMA8451_OUT_Z_MSB, kMMA8451_OUT_Z_LSB);

    accel->x = x_sum / 128;
    accel->y = y_sum / 128;
    accel->z = z_sum / 128;

    return 0;
}

/******************************************************************************
 * EOF
 ******************************************************************************/
