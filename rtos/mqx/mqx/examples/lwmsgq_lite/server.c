/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 1989-2008 ARC International
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
*   This file contains the code for the server_task
*
*
*END************************************************************************/

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <lwmsgq.h>
#include "server.h"
#include <task.h>
#include <fsl_debug_console.h>

/* Global parameter structures */
const taskinit_t task_server = {
    .stacksize  = SERVER_TASK_STACK_SIZE,
    .stackaddr  = Server_task_stack,
    .exec       = server_task,
    .priority   = 8,
    .name       = "server_task",
};

extern taskinit_t task_client;

/*FUNCTION-----------------------------------------------------------
*
* Function Name   :  Main
* Comments    :
*
*END*--------------------------------------------------------------*/
int main(void)
{
extern MQX_INITIALIZATION_STRUCT MQX_init_struct;
#if defined(__ICCARM__) /* IAR */
/* Search for last block placed by IAR linker to set heap as big as possible.
** See mqx_main.c for details.*/
    if (NULL == MQX_init_struct.START_OF_HEAP)
    {
        MQX_init_struct.START_OF_HEAP = (__RW_END > __ZI_END) ? __RW_END : __ZI_END;
    }
#endif  /* defined(__ICCARM__) */
    mqx_init((MQX_INITIALIZATION_STRUCT_PTR) &MQX_init_struct);
    create_task(&task_server);
    mqx_start();
}

/*TASK*--------------------------------------------------------
*
* Task Name : server_task
* Comments  : This task initializes the message queues,
*  creates three client tasks, and then waits for a message.
*  After recieving a message, the task returns the message to
*  the sender.
*END*--------------------------------------------------------*/

void server_task
   (
      uint32_t param
   )
{
   _mqx_uint          msg[MSG_SIZE];
   _mqx_uint          i, result;

   result = _lwmsgq_init((void *)server_queue, NUM_MESSAGES, MSG_SIZE);
   if (result != MQX_OK) {
      // lwmsgq_init failed
   } /* Endif */
   result = _lwmsgq_init((void *)client_queue, NUM_MESSAGES, MSG_SIZE);
   if (result != MQX_OK) {
      // lwmsgq_init failed
   } /* Endif */

   /* create the client tasks */
   for(i = 0; i < NUM_CLIENTS; i++){
      task_client.stackaddr = Client_task_stack[i];
      task_client.exec_param  = (void *)i;
      create_task(&task_client);
   }
   while (TRUE) {
      _lwmsgq_receive((void *)server_queue, msg, LWMSGQ_RECEIVE_BLOCK_ON_EMPTY, 0, 0);
      PRINTF(" %c \r\n", msg[0]);

      _lwmsgq_send((void *)client_queue, msg, LWMSGQ_SEND_BLOCK_ON_FULL);
   }

}

/* EOF */
