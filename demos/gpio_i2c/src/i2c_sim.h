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

#ifndef __FSL_I2C_SIM_H__
#define __FSL_I2C_SIM_H__

#include "board.h"

#if defined(__cplusplus)
extern "C" {
#endif
 
#define GPIO_SCL   BOARD_I2C_GPIO_SCL /*!< GPIO SCL */
#define GPIO_SDA   BOARD_I2C_GPIO_SDA /*!< GPIO SDA */

/*!
 * @brief Initialization.
 *
 * @param[in] speed        I2C speed.
 * @param[in] slaveaddr    Slave device address.
 */
void i2c_gpio_init(int32_t speed, int32_t slaveaddr);

/*!
 * @brief Probe to see if a chip is present.
 * Probe to see if a chip is present. Also good for checking for the
 * completion of EEPROM writes since the chip stops responding until
 * the write completes (typically 10mSec).
 *
 * @param[in] addr    I2C slave device address.
 *
 * @return Probe successful or failed.
 */
uint8_t i2c_gpio_probe(uint8_t addr);

/*!
 * @brief Read bytes.
 *
 * This function will read data from i2c slave device.
 *
 * @param[in] chip   Chip number.
 * @param[in] addr   Address in I2C slave device.
 * @param[in] alen   Address len.
 * @param[in] buffer Buffer address that will be read to.
 * @param[in] len    Len of data that will be read.
 *
 * @return Read successful or not.
 */
uint8_t i2c_gpio_read(uint8_t chip, uint32_t addr, int32_t alen, uint8_t *buffer, int32_t len);

/*!
 * @brief Write bytes.
 *
 * This function will write data to i2c slave device.
 *
 * @param[in] chip   Chip address.
 * @param[in] addr   Address in I2C slave device.
 * @param[in] alen   Address len.
 * @param[in] buffer Buffer address that will be write.
 * @param[in] len    Len of data that will be write.
 *
 * @return Write failed times.
 */
uint8_t i2c_gpio_write(uint8_t chip, uint32_t addr, int32_t alen, uint8_t *buffer, int32_t len);

#if defined(__cplusplus)
}
#endif

#endif
