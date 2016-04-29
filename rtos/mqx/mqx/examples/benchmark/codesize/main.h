#ifndef __main_h_
#define __main_h_
/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
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
* See license agreement file for full license terms including other restrictions.
*****************************************************************************
*
* Comments:
*
*
*END************************************************************************/

#define MAIN_TASK           (10)

/*
** Predefined onfiguration mode, one of following macros must be defined:
** - CSCFG_TINY
** - CSCFG_SMALL
** - CSCFG_TYPICAL
** - CSCFG_MAX
*/
#if (CSCFG_MAX)
    #define IF_MAX(x)           (x)
    #define IF_TYPICAL(x)       (x)
    #define IF_SMALL(x)         (x)
    #define IF_TINY(x)          (x)
#elif (CSCFG_TYPICAL)
    #define IF_MAX(x)
    #define IF_TYPICAL(x)       (x)
    #define IF_SMALL(x)         (x)
    #define IF_TINY(x)          (x)
#elif (CSCFG_SMALL)
    #define IF_MAX(x)
    #define IF_TYPICAL(x)
    #define IF_SMALL(x)         (x)
    #define IF_TINY(x)          (x)
#elif (CSCFG_TINY)
    #define IF_MAX(x)
    #define IF_TYPICAL(x)
    #define IF_SMALL(x)
    #define IF_TINY(x)          (x)
#else
    #error Please define codesize build configuration
#endif

/* Main task prototype */
void Main_task(uint32_t);

#endif
