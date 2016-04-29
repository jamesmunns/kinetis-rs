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
*   This file contains the source for a simple example of an
*   application that writes and reads the SPI memory using the SPI driver.
*   It's already configured for onboard SPI flash where available.
*
*
*END************************************************************************/


#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include "fsl_debug_console.h"
#include <fsl_dspi_master_driver.h>
#include <fsl_dspi_shared_function.h>


#include "spi_memory.h"
#include "spi_settings.h"


/* The SPI serial memory test addresses */
#define SPI_MEMORY_ADDR1               0x0000F0 /* test address 1 */
#define SPI_MEMORY_ADDR2               0x0001F0 /* test address 2 */
#define SPI_MEMORY_ADDR3               0x0002F0 /* test address 3 */

/* Test strings */
#define TEST_BYTE_1       0xBA
#define TEST_BYTE_2       0xA5
#define TEST_STRING_SHORT "Hello,World!"
#define TEST_STRING_LONG  "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz1234567890"

unsigned char send_buffer[SPI_MEMORY_PAGE_SIZE];
unsigned char recv_buffer[sizeof(TEST_STRING_LONG)];


/* DEBUG */
#define SPI_DEBUG_STATUS            1
#define SPI_DEBUG_BYTE              1
#define SPI_DEBUG_WRITE_DATA_SHORT  1
#define SPI_DEBUG_WRITE_DATA_LONG   1



/* Task IDs */
#define MAIN_TASK  6

extern void main_task(uint32_t);


const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index,   Function,   Stack,  Priority, Name,     Attributes,          Param, Time Slice */
    { MAIN_TASK,    main_task,  2000,   9,        "main",   MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};


/*TASK*-----------------------------------------------------
*
* Task Name    : main_task
* Comments     :
*
*END*-----------------------------------------------------*/

void main_task
   (
      uint32_t initial_data
   )
{
  
    uint32_t dataLength, numBytes;
    uint8_t statusRegister;
    dspi_status_t spiStatus;
  
    printf ("\n-------------- SPI driver example --------------\n\n");
    printf ("This example application demonstrates usage of SPI driver.\n");
    printf ("It transfers data to/from external memory over SPI bus.\n");
    printf ("\n");
    
 
    /* Setting SPI config structure */
    dspi_master_user_config_t userConfig;
    userConfig.isChipSelectContinuous = true;
    userConfig.isSckContinuous = false;
    userConfig.pcsPolarity = kDspiPcs_ActiveLow;
    userConfig.whichCtar = kDspiCtar0;
    userConfig.whichPcs = kDspiPcs0;
        
    /* Init the DSPI module */
    dspi_master_state_t dspiMasterState;
    dspi_status_t status = DSPI_DRV_MasterInit(SPI_INSTANCE, &dspiMasterState, &userConfig);
    
    /* Define bus configuration */
    dspi_device_t spiDevice;
    spiDevice.dataBusConfig.bitsPerFrame = 8;
    spiDevice.dataBusConfig.clkPhase = kDspiClockPhase_FirstEdge;
    spiDevice.dataBusConfig.clkPolarity = kDspiClockPolarity_ActiveHigh;
    spiDevice.dataBusConfig.direction = kDspiMsbFirst;
    spiDevice.bitsPerSec =  500000;
        
    /* Configure the SPI bus */
    uint32_t calculatedBaudRate;
    status = DSPI_DRV_MasterConfigureBus(SPI_INSTANCE, &spiDevice, &calculatedBaudRate);
	
    /* Configure timing delays 200ns, it is optional, useful for slower peripheral diveces or "fine tune" SPI timings */
    uint32_t delayInNanosec = 200;
    uint32_t calculatedDelay;
    /* Set pcs to sck delay */
    DSPI_DRV_MasterSetDelay(SPI_INSTANCE, kDspiPcsToSck, delayInNanosec, &calculatedDelay);
    /* Set last sck to pcs delay */
    DSPI_DRV_MasterSetDelay(SPI_INSTANCE, kDspiLastSckToPcs, delayInNanosec, &calculatedDelay);
    /* Set delay after transfer */
    DSPI_DRV_MasterSetDelay(SPI_INSTANCE, kDspiAfterTransfer, delayInNanosec, &calculatedDelay);
 
    /* Configure pins for SPI */
    configure_spi_pins(SPI_INSTANCE);
    
    /* SPI use interrupt, must be installed in MQX and file fsl_dspi_irq.c must not be included in project */
    int32_t IRQNumber = g_dspiIrqId[SPI_INSTANCE];
    _int_install_isr(IRQNumber, (INT_ISR_FPTR)DSPI_DRV_MasterIRQHandler, (void*)SPI_INSTANCE);
    
    
#if SPI_DEBUG_STATUS
    
    /* Read status */
    printf ("Read memory status register ... ");
    
    spiStatus = memory_read_status (SPI_INSTANCE, &statusRegister);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    else printf ("0x%02x\n", statusRegister);
    
    /* Disable protection */
    printf ("Write unprotect memory\n");
    spiStatus = memory_set_protection (SPI_INSTANCE, FALSE);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    
    /* Read status */
    printf ("Read memory status register ... ");
    spiStatus = memory_read_status (SPI_INSTANCE, &statusRegister);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    else printf ("0x%02x\n", statusRegister);
       
    /* Erase memory before tests */
    printf ("Erase whole memory chip ... ");
    spiStatus = memory_chip_erase (SPI_INSTANCE);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    else printf ("Erased\n\n");

#endif

#if SPI_DEBUG_BYTE

    /* Write byte to memory */
    printf ("Write byte at address 0x%06x:\n0x%02x\n", SPI_MEMORY_ADDR1, TEST_BYTE_1);
    spiStatus = memory_write_byte (SPI_INSTANCE, SPI_MEMORY_ADDR1, TEST_BYTE_1);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    
  
    /* Read byte from memory */    
    printf ("Read byte from address 0x%06x:\n", SPI_MEMORY_ADDR1);
    uint8_t rxByte;
    spiStatus = memory_read_byte (SPI_INSTANCE, SPI_MEMORY_ADDR1, &rxByte);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    else 
    {
        printf ("0x%02x\n", rxByte);
        printf ("Compare write/read bytes ... ");
        
        if (TEST_BYTE_1 == rxByte)
        {
            printf ("OK\n");
        }
        else
        {
            printf ("ERROR\n");
        }
    }
    printf ("\n");

#endif

#if SPI_DEBUG_WRITE_DATA_SHORT

    /* Write string to memory */
    dataLength = strlen(TEST_STRING_SHORT);
    printf ("Write data at address 0x%06x:\n%s\n", SPI_MEMORY_ADDR2, TEST_STRING_SHORT);
    spiStatus = memory_write_data (SPI_INSTANCE, SPI_MEMORY_ADDR2, dataLength, (unsigned char *)TEST_STRING_SHORT, &numBytes);
    if((numBytes != dataLength) || spiStatus != kStatus_DSPI_Success) printf ("Error");

    /* Read data */
    printf ("Read data from address 0x%06x:\n", SPI_MEMORY_ADDR2);
    spiStatus = memory_read_data (SPI_INSTANCE, SPI_MEMORY_ADDR2, dataLength, recv_buffer, &numBytes);
    if((numBytes != dataLength) || spiStatus != kStatus_DSPI_Success) printf ("Error");
    else 
    {
        printf("%s\n", recv_buffer);
        printf ("Compare write/read data ... ");
        /* Test result */
        if (0 != memcmp (TEST_STRING_SHORT, recv_buffer, dataLength))
        {
            printf ("ERROR\n");
        }
        else
        {
            printf ("OK\n");
        }
    }
    printf ("\n");

#endif

#if SPI_DEBUG_WRITE_DATA_LONG

    /* Page write to memory */
    dataLength = strlen(TEST_STRING_LONG);
    printf ("Write data at address 0x%06x:\n%s\n",SPI_MEMORY_ADDR3, TEST_STRING_LONG);
    spiStatus = memory_write_data (SPI_INSTANCE, SPI_MEMORY_ADDR3, dataLength, (unsigned char *)TEST_STRING_LONG, &numBytes);
    if((numBytes != dataLength) || spiStatus != kStatus_DSPI_Success) printf ("Error\n");

    /* Read data */
    printf ("Read data from address 0x%06x:\n", SPI_MEMORY_ADDR3);
    spiStatus = memory_read_data (SPI_INSTANCE, SPI_MEMORY_ADDR3, dataLength, recv_buffer, &numBytes);
    if((numBytes != dataLength) || spiStatus != kStatus_DSPI_Success) printf ("Error\n");
    else 
    {
        printf("%s\n", recv_buffer);
        printf ("Compare write/read data ... ");
        
        /* Test result */
        if (0 != memcmp (TEST_STRING_LONG, recv_buffer, dataLength))
        {
            printf ("ERROR\n");
        }
        else
        {
            printf ("OK\n");
        }
    }
    printf ("\n");

#endif

    /* Test simultaneous write and read */
    memset (send_buffer, 0, sizeof (send_buffer));
    memset (recv_buffer, 0, sizeof (recv_buffer));
    send_buffer[0] = SPI_MEMORY_READ_DATA;
    
    memory_addr_to_buffer(SPI_MEMORY_ADDR1, send_buffer+1);

    uint8_t buffer_length = 10;

    spiStatus = DSPI_DRV_MasterTransferBlocking(SPI_INSTANCE, NULL, send_buffer, recv_buffer, buffer_length, SPI_TRANSFER_TIMEOUT);
    if(spiStatus != kStatus_DSPI_Success) printf ("SPI Error");
    else 
    {
        printf ("Simultaneous write and read - memory read from 0x%08x (%d):\n", SPI_MEMORY_ADDR1, buffer_length);
        printf ("Write: ");
        for (int i = 0; i < buffer_length; i++)
        {
            printf ("0x%02x ", send_buffer[i]);
        }
        
        printf ("\nRead: ");
        for (int i = 0; i < buffer_length; i++)
        {
            printf ("0x%02x ", recv_buffer[i]);
        }
        
        if (TEST_BYTE_1 == (unsigned char)recv_buffer[1 + SPI_MEMORY_ADDRESS_BYTES])
        {
            printf ("\nSimultaneous read/write (data == 0x%02x) ... OK\n", (unsigned char)recv_buffer[1 + SPI_MEMORY_ADDRESS_BYTES]);
        }
        else
        {
            printf ("\nSimultaneous read/write (data == 0x%02x) ... ERROR\n", (unsigned char)recv_buffer[1 + SPI_MEMORY_ADDRESS_BYTES]);
        }
    }
    /* Deinit the SPI */
    DSPI_DRV_MasterDeinit(SPI_INSTANCE);

    printf ("\n-------------- End of example --------------\n\n");
    
   _task_block();
}

/* EOF */
