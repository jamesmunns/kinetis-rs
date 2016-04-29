/*HEADER**********************************************************************
*
* Copyright 2012-2015 Freescale Semiconductor, Inc.
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
*   This file contains the functions which write and read the SPI memories
*   using the SPI driver in interrupt mode.
*
*
*END************************************************************************/


#include "spi_memory.h"
#include "spi_settings.h"

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_addr_to_buffer
* Comments  : Fills in given address into buffer in correct byte order
*
*END*----------------------------------------------------------------------*/
void memory_addr_to_buffer(uint32_t addr, uint8_t *buffer)
{
    for (int i = SPI_MEMORY_ADDRESS_BYTES; i; i--)
    {
        buffer[i-1] = (uint8_t)(addr & 0xFF);
        addr >>= 8;
    }
}


/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_chip_erase
* Comments  : This function erases the whole memory SPI chip
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_chip_erase (uint32_t spiInstance)
{
    uint8_t buffer[1];

    /* This operation must be write-enabled */
    memory_set_write_latch (spiInstance, TRUE);

    buffer[0] = SPI_MEMORY_CHIP_ERASE;

    /* Write instruction */
    dspi_status_t spiStatus;
    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, buffer, NULL, 1, SPI_TRANSFER_TIMEOUT);
	
    if(spiStatus == kStatus_DSPI_Success)
    {   
        uint8_t statusRegister = 1;
        while ( statusRegister & 1)
        {
            _time_delay (1000);
            spiStatus = memory_read_status (spiInstance, &statusRegister);
            if(spiStatus != kStatus_DSPI_Success) return spiStatus;
        }
    }

    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_set_write_latch
* Comments  : This function sets latch to enable/disable memory write
*             operation
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_set_write_latch (uint32_t spiInstance, bool enable)
{
    uint8_t buffer[1];

    if (enable) buffer[0] = SPI_MEMORY_WRITE_LATCH_ENABLE;
    else buffer[0] = SPI_MEMORY_WRITE_LATCH_DISABLE;

    /* Write instruction */
    dspi_status_t spiStatus;
    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, buffer, NULL, 1, SPI_TRANSFER_TIMEOUT);
   
    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_set_protection
* Comments  : This function sets write protection in memory status register
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_set_protection (uint32_t spiInstance, bool protect)
{
    uint8_t protection;
    uint8_t buffer[2];

    dspi_status_t spiStatus;
    
    /* Must do it twice to ensure right transitions in protection status register */
    for (int i = 0; i < 2; i++)
    {
        /* Each write operation must be enabled in memory */
        spiStatus = memory_set_write_latch (spiInstance, TRUE);
        if(spiStatus != kStatus_DSPI_Success) return spiStatus;

        if (protect) protection = 0xFF;
        else protection = 0x00;
        
        buffer[0] = SPI_MEMORY_WRITE_STATUS;
        buffer[1] = protection;

        /* Write instruction */
        spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, buffer, NULL, 2, SPI_TRANSFER_TIMEOUT);
        if (spiStatus != kStatus_DSPI_Success) return spiStatus;
    }
    
    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_read_status
* Comments  : This function reads memory status register
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_read_status (uint32_t spiInstance, uint8_t *statusRegister)
{
    uint8_t bufferTx[2];
    uint8_t bufferRx[2];
    
    bufferTx[0] = SPI_MEMORY_READ_STATUS;

    /* send command to read mem status register */
    dspi_status_t spiStatus;
    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, bufferTx, bufferRx, 2, SPI_TRANSFER_TIMEOUT);
    if(spiStatus == kStatus_DSPI_Success) *statusRegister = bufferRx[1];
    
    return spiStatus;
}


/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_write_byte
* Comments  : This function writes a data byte to memory
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_write_byte (uint32_t spiInstance, uint32_t addr, unsigned char data)
{
    uint8_t buffer[1 + SPI_MEMORY_ADDRESS_BYTES + 1];

    /* Each write operation must be enabled in memory */
    dspi_status_t spiStatus;
    spiStatus = memory_set_write_latch (spiInstance, TRUE);
    if(spiStatus != kStatus_DSPI_Success) return spiStatus;

    /* Write instruction, address and data to buffer */
    buffer[0] = SPI_MEMORY_WRITE_DATA;
    memory_addr_to_buffer(addr, &(buffer[1]));
    buffer[1 + SPI_MEMORY_ADDRESS_BYTES] = data;

    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, buffer, NULL, 1 + SPI_MEMORY_ADDRESS_BYTES + 1, SPI_TRANSFER_TIMEOUT);

    /* There is 5 ms internal write cycle needed for memory */
    _time_delay (5);
    
    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_read_byte
* Comments  : This function reads a data byte from memory
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_read_byte (uint32_t spiInstance, uint32_t addr, uint8_t *byte)
{
    uint8_t bufferTx[1 + SPI_MEMORY_ADDRESS_BYTES + 1];
    uint8_t bufferRx[1 + SPI_MEMORY_ADDRESS_BYTES + 1];

    /* Read instruction, address */
    bufferTx[0] = SPI_MEMORY_READ_DATA;
    memory_addr_to_buffer(addr, &(bufferTx[1]));

    /* Write instruction and address */
    dspi_status_t spiStatus;
    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, bufferTx, bufferRx, 1 + SPI_MEMORY_ADDRESS_BYTES + 1, SPI_TRANSFER_TIMEOUT);
    if(spiStatus == kStatus_DSPI_Success) *byte = bufferRx[1 + SPI_MEMORY_ADDRESS_BYTES];

    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_write_data
* Comments  : This function writes data buffer to memory using page write
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_write_data (uint32_t spiInstance, uint32_t addr, uint32_t size, unsigned char *data, uint32_t *nBytes)
{
	
    uint32_t count = size;
    uint8_t buffer[1 + SPI_MEMORY_ADDRESS_BYTES + SPI_MEMORY_PAGE_SIZE];

    *nBytes = 0;
    
    dspi_status_t spiStatus = kStatus_DSPI_Success;
    
    while (count > 0)
    {
        /* Each write operation must be enabled in memory */
        spiStatus = memory_set_write_latch (spiInstance, TRUE);
        if(spiStatus != kStatus_DSPI_Success) return spiStatus;

        uint32_t len = count;
        uint32_t offset = addr & (SPI_MEMORY_PAGE_SIZE - 1);
        /* Number bytes to end page from address addr */
        uint32_t bytesToEndPage = SPI_MEMORY_PAGE_SIZE - offset;
        if (len > bytesToEndPage) len = bytesToEndPage;
        count -= len;

        /* Write instruction, address */
        buffer[0] = SPI_MEMORY_WRITE_DATA;
        memory_addr_to_buffer(addr, &(buffer[1]));
        
        /* Copy data do buffer */
        memcpy(buffer+4, data, len);
        //for (int i=0; i<len; i++)
          //  buffer[4+i] = data[i];
        
        spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, buffer, NULL, 1 + SPI_MEMORY_ADDRESS_BYTES + len, SPI_TRANSFER_TIMEOUT);
	if (spiStatus != kStatus_DSPI_Success) return spiStatus;

	/* Count of written bytes */
        *nBytes += len;

        /* Move to next block */
        addr += len;
        data += len;

        /* There is 5 ms internal write cycle needed for memory */
        _time_delay (5);
    }

    return spiStatus;
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : memory_read_data
* Comments  : This function reads data from memory into given buffer
* Return:
*         Status of SPI transfer
*
*END*----------------------------------------------------------------------*/
dspi_status_t memory_read_data (uint32_t spiInstance, uint32_t addr, uint32_t size, unsigned char *data, uint32_t *nBytes)
{
    *nBytes = 0;
    
    uint8_t *bufferTx = (uint8_t*)OSA_MemAlloc(1 + SPI_MEMORY_ADDRESS_BYTES + size);
    uint8_t *bufferRx = (uint8_t*)OSA_MemAlloc(1 + SPI_MEMORY_ADDRESS_BYTES + size);
    if(bufferTx == NULL || bufferRx == NULL) return kStatus_DSPI_Success;

    /* Read instruction, address */
    bufferTx[0] = SPI_MEMORY_READ_DATA;
    memory_addr_to_buffer(addr, &(bufferTx[1]));

    dspi_status_t spiStatus;
    spiStatus = DSPI_DRV_MasterTransferBlocking(spiInstance, NULL, bufferTx, bufferRx, 1 + SPI_MEMORY_ADDRESS_BYTES + size, SPI_TRANSFER_TIMEOUT);

    if (spiStatus != kStatus_DSPI_Success) return spiStatus;
    else
    {
        memcpy(data, bufferRx + 1 + SPI_MEMORY_ADDRESS_BYTES, size);
        *nBytes = size;
    }

    OSA_MemFree(bufferTx);
    OSA_MemFree(bufferRx);

    return spiStatus;
}

