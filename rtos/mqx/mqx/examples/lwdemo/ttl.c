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
*   This file contains source for the Lightweight MQX demo test.
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include "lwdemo.h"

/*   Task Templates  */ 
const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index, Function,  Stack, Priority,  Name,        Attributes,          Param, Time Slice */
    { LWSEMB,     LWSemB,    0x300,    10,     "LWSemB",    0,                   0,     0 },
    { LWSEMA,     LWSemA,    0x300,     9,     "LWSemA",    0,                   0,     0 },
    { LWEVENTB,   LWEventB,  0x300,     9,     "LWEventB",  0,                   0,     0 },
    { LWEVENTA,   LWEventA,  0x300,     9,     "LWEventA",  0,                   0,     0 },
    { SENDER,     Sender,    0x300,    10,     "Sender",    0,                   0,     0 },
    { RESPONDER,  Responder, 0x300,     9,     "Responder", 0,                   0,     0 },
    { MAIN_TASK,  main_task, 0xC00,    11,     "main_task", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

/* End of File */
