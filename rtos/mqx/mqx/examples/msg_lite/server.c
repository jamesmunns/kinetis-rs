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

/* declaration of a global message pool */
_pool_id   message_pool;
_pool_id fp_message_pool;

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
* Comments  : This task creates a message queue for itself,
*  creates a message pool, creates three client tasks, and
*  then waits for a message.  After recieving a message,
*  the task returns the message to the sender.
*END*--------------------------------------------------------*/


void server_task
   (
      uint32_t param
   )
{
   SERVER_MESSAGE_PTR msg_ptr;
   _mqx_uint          i;
   _queue_id          server_qid;
   bool               result;
   _task_id           task_id;

   /* open a message queue */
   server_qid = _msgq_open(SERVER_QUEUE, 0);

   if (server_qid == 0) {
      PRINTF("\nCould not open the server message queue\n");
      _task_block();
   }

   /* create a message pool */
   message_pool = _msgpool_create(sizeof(SERVER_MESSAGE),
      NUM_CLIENTS, 0, 0);

   if (message_pool == MSGPOOL_NULL_POOL_ID) {
      PRINTF("\nCount not create a message pool\n");
      _task_block();
   }

   /* create the client tasks */
   for (i = 0; i < NUM_CLIENTS; i++) {
      task_client.exec_param = (void *)i;
      task_client.stackaddr = Client_task_stack[i];
      task_id = create_task(&task_client);
      if (task_id == NULL) {
         PRINTF("\nCould not create a client task\n");
         _task_block();
      }
   }

   while (TRUE) {
      msg_ptr = _msgq_receive(server_qid, 0);

      if (msg_ptr == NULL) {
         PRINTF("\nCould not receive a message\n");
         _task_block();
      }

      PRINTF(" %c \r\n", msg_ptr->DATA[0]);

      /* return the message */
      msg_ptr->HEADER.TARGET_QID = msg_ptr->HEADER.SOURCE_QID;
      msg_ptr->HEADER.SOURCE_QID = server_qid;

      result = _msgq_send(msg_ptr);

      if (result != TRUE) {
         PRINTF("\nCould not send a message\n");
         _task_block();
      }
   }
}

/* EOF */
