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


#include "fsl_gpio_driver.h"

#include "i2c_sim.h"
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_clock_manager.h"

#define I2C_INIT \
    do \
    { \
        GPIO_DRV_SetPinDir(GPIO_SCL, kGpioDigitalOutput); \
        GPIO_DRV_SetPinDir(GPIO_SDA, kGpioDigitalOutput); \
        GPIO_DRV_SetPinOutput(GPIO_SCL); \
        GPIO_DRV_SetPinOutput(GPIO_SDA); \
    } while (0)

#define I2C_ACTIVE do { } while (0)

#define I2C_TRISTATE do { } while (0)

#define I2C_READ GPIO_DRV_ReadPinInput(GPIO_SDA)

#define I2C_SDA_DIR(dir) GPIO_DRV_SetPinDir(GPIO_SDA, dir)

#define I2C_SDA(bit) GPIO_DRV_WritePinOutput(GPIO_SDA, bit)

#define I2C_SCL(bit) GPIO_DRV_WritePinOutput(GPIO_SCL, bit)

#ifndef BOARD_I2C_DELAY
    #error "No board I2C Delay macro defined!"
#else
    #define I2C_DELAY BOARD_I2C_DELAY
#endif

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define RETRIES        0

#define I2C_ACK        0        /* PD_SDA level to ack a byte */
#define I2C_NOACK      1        /* PD_SDA level to noack a byte */

////////////////////////////////////////////////////////////////////////////////
// Local functions
////////////////////////////////////////////////////////////////////////////////
/* static void  send_reset(void); */
static void  send_start(void);
static void  send_stop(void);
static void  send_ack(int32_t ack);
static int32_t write_byte(uint8_t data);
static uint8_t read_byte(int32_t ack);

/*!
 * @brief Send START.
 *
 * Send START. High -> Low on SDA while SCL is High.
 */
static void send_start(void)
{  
    I2C_DELAY;
    I2C_SDA(1);
    I2C_ACTIVE;
    I2C_DELAY;
    I2C_SCL(1);
    I2C_DELAY;
    I2C_SDA(0);
    I2C_DELAY;
}

/*!
 * @brief Send STOP.
 *
 * Send STOP. STOP: Low -> High on SDA while SCL is High.
 */
static void send_stop(void)
{
    I2C_SCL(0);
    I2C_DELAY;
    I2C_SDA(0);
    I2C_ACTIVE;
    I2C_DELAY;
    I2C_SCL(1);
    I2C_DELAY;
    I2C_SDA(1);
    I2C_DELAY;
    I2C_TRISTATE;
}

/*!
 * @brief Send ACK.
 *
 * Send ACK. Ack should be I2C_ACK or I2C_NOACK.
 */
static void send_ack(int32_t ack)
{
    I2C_SCL(0);
    I2C_DELAY;
    I2C_ACTIVE;
    I2C_SDA(ack);
    I2C_DELAY;
    I2C_SCL(1);
    I2C_DELAY;
    I2C_DELAY;
    I2C_SCL(0);
    I2C_DELAY;
}

/*-----------------------------------------------------------------------
 * Send 8 bits and look for an acknowledgement.
 */
/*!
 * @brief Send 8 bits and look for an acknowledgement.
 *
 * @param[in] data      Data that will be write.
 *
 * @return Ackledge value. Not a nack is an ack.
 */
static int32_t write_byte(uint8_t data)
{
    int32_t j;
    int32_t nack;

    I2C_ACTIVE;
    for (j = 0; j < 8; j++)
    {
        I2C_SCL(0);
        I2C_DELAY;
        I2C_SDA(data & 0x80);
        I2C_DELAY;
        I2C_SCL(1);
        I2C_DELAY;
        I2C_DELAY;

        data <<= 1;
    }

    /* Look for an <ACK>(negative logic) and return it. */
    I2C_SCL(0);
    I2C_DELAY;
    I2C_SDA(1);
    I2C_SDA_DIR(kGpioDigitalInput);
    I2C_TRISTATE;
    I2C_DELAY;
    I2C_SCL(1);
    I2C_DELAY;
    I2C_DELAY;
    nack = I2C_READ;
    I2C_SCL(0);
    I2C_DELAY;
    I2C_ACTIVE;
    I2C_SDA_DIR(kGpioDigitalOutput);

    return (nack);    /* not a nack is an ack */
}

/*!
 * @brief Read one byte.
 *
 * if ack == I2C_ACK, ACK the byte so can continue reading, else
 * send I2C_NOACK to end the read.
 *
 * @param[in] ack    Ack data that to be sent.
 *
 * @return Read data byte.
 */
static uint8_t read_byte(int32_t ack)
{
    uint32_t  data;
    int32_t  j;

    /* Read 8 bits, MSB first. */
    I2C_TRISTATE;
    I2C_SDA_DIR(kGpioDigitalInput);
    I2C_DELAY;
    data = 0;
    for (j = 0; j < 8; j++)
    {
        I2C_SCL(0);
        I2C_DELAY;
        I2C_DELAY;
        I2C_SCL(1);
        I2C_DELAY;
        data <<= 1;
        data |= I2C_READ;
        I2C_DELAY;
    }
    I2C_SCL(0);
    I2C_SDA_DIR(kGpioDigitalOutput);
    send_ack(ack);

    return (data);
}

////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Initialization.
 *
 * @param[in] speed    I2C speed.
 * @param[in] slaveaddr    Slave device address.
 */
void i2c_gpio_init(int32_t speed, int32_t slaveaddr)
{
    I2C_INIT;
}

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
uint8_t i2c_gpio_probe(uint8_t addr)
{
    int32_t rc;

    /*
     * perform 1 byte write transaction with just address byte
     * (fake write)
     */
    send_start();
    /*
     * Our address is by default shifted left by 1
     */
    /* rc = write_byte((addr << 1) | 0); */
    rc = write_byte((addr) | 0);
    send_stop();

    return (rc ? 1 : 0);
}

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
uint8_t i2c_gpio_read(uint8_t chip, uint32_t addr, int32_t alen, uint8_t *buffer, int32_t len)
{
    int32_t shift;

    /*
     * Do the addressing portion of a write cycle to set the
     * chip's address pointer.  If the address length is zero,
     * don't do the normal write cycle to set the address pointer,
     * there is no address pointer in this chip.
     */
    send_start();
    if (alen > 0)
    {
        /* 
         * Our address is by default shifted left by 1
         */
        /* if (write_byte(chip << 1)) */
        if (write_byte(chip | 0))
        {
            /* write cycle */
            send_stop();
            return (1);
        }
        shift = (alen - 1) * 8;
        while (alen-- > 0)
        {
            if (write_byte(addr >> shift))
            {
                return (1);
            }
            shift -= 8;
        }

        /*
         * Some I2C chips need a stop/start sequence here,
         * other chips don't work with a full stop and need
         * only a start.  Default behaviour is to send the
         * stop/start sequence.
         */
        /* send_stop(); */
        send_start();
    }

    /*
     * Send the chip address again, this time for a read cycle.
     * Then read the data.  On the last byte, we do a NACK instead
     * of an ACK(len == 0) to terminate the read.
     * Our address is by default shifted left by 1
     */
    /* write_byte((chip << 1) | 1); */
    write_byte(chip | 1);    /* read cycle */
    while (len-- > 0)
    {
        *buffer++ = read_byte(len == 0);
    }
    send_stop();

    return (0);
}

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
uint8_t i2c_gpio_write(uint8_t chip, uint32_t addr, int32_t alen, uint8_t *buffer, int32_t len)
{
    int32_t shift, failures = 0;

    send_start();
    /*
     * Our address is by default shifted left by 1
     */
    /* if (write_byte(chip << 1)) */
    if (write_byte(chip | 0))
    {
        /* write cycle */
        send_stop();
        return (1);
    }
    shift = (alen - 1) * 8;
    while (alen-- > 0)
    {
        if (write_byte(addr >> shift))
        {
            return (1);
        }
        shift -= 8;
    }

    while (len-- > 0)
    {
        if (write_byte(*buffer++))
        {
            failures++;
        }
    }
    send_stop();

    return (failures);
}
