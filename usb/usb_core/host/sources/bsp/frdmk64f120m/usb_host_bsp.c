/**HEADER********************************************************************
* 
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* Comments:  
*
*END************************************************************************/
#include "adapter.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#define SIM_SOPT2_IRC48MSEL_MASK                 0x30000u
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    #if (defined(CPU_MK22F51212))
#include "MK22F51212/MK22F51212_sim.h"
#include "MK22F51212/MK22F51212_usb.h"
    #endif
#endif

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#define BSP_USB_INT_LEVEL                (4)
#define USB_CLK_RECOVER_IRC_EN (*(volatile unsigned char *)0x40072144)
#define SIM_SOPT2_IRC48MSEL_MASK                 0x30000u

static int32_t bsp_usb_host_io_init
(
   int32_t i
)
{
	
	int32_t ret = 0;
    //Disable MPU so the module can access RAM
    //HW_MPU_CESR_CLR(MPU_CESR, MPU_CESR_VLD_MASK);
     MPU_CESR=0;
    if (i == 0)
    {	
    	/* USB clock divider */
		if(kClockManagerSuccess != CLOCK_SYS_SetDivider(kClockDividerUsbDiv, 4U))
		{
			ret = -1;
		}
		if(kClockManagerSuccess != CLOCK_SYS_SetDivider(kClockDividerUsbFrac, 1U))
		{
			ret = -1;
		}
    	/* PLL/FLL selected as CLK source */
		if(kClockManagerSuccess != CLOCK_SYS_SetSource(kClockUsbSrc, 1U))
		{
			ret = -1;
		}
		if(kClockManagerSuccess != CLOCK_SYS_SetSource(kClockPllfllSel, 1U))
		{
			ret = -1;
		}
		/* USB Clock Gating */
		CLOCK_SYS_EnableUsbClock(i);
		
		/* Enable clock gating to all ports, A, B, C, D, E*/
		CLOCK_SYS_EnablePortClock(1);
		CLOCK_SYS_EnablePortClock(2);
		CLOCK_SYS_EnablePortClock(3);
		CLOCK_SYS_EnablePortClock(4);
		CLOCK_SYS_EnablePortClock(5);


		/* Weak pull downs */
		HW_USB_USBCTRL_WR(USB0_BASE, 0x40);

    }
    else
    {
        ret = -1; //unknow controller
    }

    return ret;
    
}


int32_t bsp_usb_host_init(uint8_t controller_id)
{
    int32_t result = 0;

    result = bsp_usb_host_io_init(controller_id);
    if (result != 0)
        return result;

    if (0 == controller_id)
    {
        /* Do not configure enable USB regulator for host */
        // SIM_SOPT1CFG_REG(SIM_BASE_PTR) |= SIM_SOPT1CFG_URWE_MASK;
        // SIM_SOPT1_REG(SIM_BASE_PTR) |= SIM_SOPT1_USBREGEN_MASK;

        /* reset USB CTRL register */
		HW_USB_USBCTRL_WR(USB0_BASE, 0);

        /* setup interrupt */
		//OS_intr_init(soc_get_usb_vector_number(0), BSP_USB_INT_LEVEL, 0, TRUE);
                OS_intr_init(soc_get_usb_vector_number(0), BSP_USB_INT_LEVEL, 0, TRUE);
    }
    else
    {
        /* unknown controller */
        result = -1;
    }

    return result;
}
#endif
/* EOF */
