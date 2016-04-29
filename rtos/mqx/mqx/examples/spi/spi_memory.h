#ifndef __spi_memory_h__
#define __spi_memory_h__
/*HEADER**********************************************************************
*
* Copyright 2008-2015 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains definitions for the SPI memory example.
*
*
*END************************************************************************/

#include <fsl_spi_master_driver.h>


/* Number of bytes used for addressing within memory */
#define SPI_MEMORY_ADDRESS_BYTES       3

/* Memory page size - maximum bytes per write */
#define SPI_MEMORY_PAGE_SIZE           0x0100   

/* The SPI serial memory instructions */
#define SPI_MEMORY_WRITE_STATUS        0x01
#define SPI_MEMORY_WRITE_DATA          0x02
#define SPI_MEMORY_READ_DATA           0x03
#define SPI_MEMORY_WRITE_LATCH_DISABLE 0x04
#define SPI_MEMORY_READ_STATUS         0x05
#define SPI_MEMORY_WRITE_LATCH_ENABLE  0x06
#define SPI_MEMORY_CHIP_ERASE          0xC7


/* Funtion prototypes */
extern void memory_addr_to_buffer(uint32_t addr, uint8_t *buffer);
extern spi_status_t memory_chip_erase (uint32_t spiInstance);
extern spi_status_t memory_set_write_latch (uint32_t spiInstance, bool enable);
extern spi_status_t memory_set_protection (uint32_t spiInstance, bool protect);
extern spi_status_t memory_read_status (uint32_t spiInstance, uint8_t *statusRegister);
extern spi_status_t memory_write_byte (uint32_t spiInstance, uint32_t addr, unsigned char data);
extern spi_status_t memory_read_byte (uint32_t spiInstance, uint32_t addr, uint8_t *byte);
extern spi_status_t memory_write_data (uint32_t spiInstance, uint32_t addr, uint32_t size, unsigned char *data, uint32_t *nBytes);
extern spi_status_t memory_read_data (uint32_t spiInstance, uint32_t addr, uint32_t size, unsigned char *data);


#endif
