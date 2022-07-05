/*
 * Systick.c
 *
 *  Created on: Jun 28, 2022
 *      Author: sara
 */



#include "Std_types.h"
#include "Bit_utils.h"
#include "Systick.h"
#include "Systick_cfg.h"


#define STK_CTRL	*((pu32) 0xE000E010)
#define STK_LOAD	*((pu32) 0xE000E014)
#define STK_VAL		*((pu32) 0xE000E018)

#define STK_CALIB		*((pu32) 0xE000E01C)

static Systick_cbf_t Appfunc;


/*
 * Purpose : Initialize the Systick timer according to the configured clock source
 *
 * Arguments : none
 *
 * Return : none
 */
void Systick_Init()
{
	STK_CTRL = Systick_TICKINT | Systick_CLKSOURCE ;
}


/*
 * Purpose : it set the time needed to be counted in ms , this fucntion takes u32 value and return error status
 *
 * Argument : u32 value range from 1ms --> 2ms
 *
 * Return : Error status
 */
Systick_t_ErrorStatus Systick_SetTickTime_ms(u32 time)
{
	Systick_t_ErrorStatus Error = systick_ok;
	u32 value ;
	switch (Systick_CLKSOURCE)
	{
	case Systick_CLKSOURCE_AHB:
		value = time*Systick_SystemClock/1000;
		break;

	case Systick_CLKSOURCE_AHB_8:
		value = time*(Systick_SystemClock/8)/1000;
		break;
	}

	if(value > 0x00FFFFFF)
	{
		Error = systick_nok;
	}
	else
	{
		STK_LOAD = value;
	}

	return Error;
}


/*
 * Purpose : drive systick to start counting down
 *
 * Arguments : none
 *
 * Return : none
 */
void Systick_Start()
{
	STK_CTRL |= Systick_Enable;
}


/*
 * Purpose : set the call back function to call when interrupt happen
 *
 * Argument : pointer to function that will be called
 *
 * Return : none
 */
void Systick_Register_cbf(Systick_cbf_t cbf)
{
	Appfunc = cbf;
}

/*
 * Purpose :during interrupt
 */
void SysTick_Handler (void)
{
	if(Appfunc)
	{
		Appfunc();
	}
}
