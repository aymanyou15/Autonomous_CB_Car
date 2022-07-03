/*
 * Mux.c
 *
 *  Created on: Jun 28, 2022
 *      Author: Ayman_Elgammal
 */

/*	IMPORTANT NOTES
 * 					1- This Driver supports 8 channel multiplexer with 3 select pins
 */


#include "../include/cmsis/stm32f10x.h"
#include "../include/stm32f1-stdperiph/stm32f10x_gpio.h"
#include "../include/stm32f1-stdperiph/stm32f10x_rcc.h"
#include "../HAL/Multiplexer/Mux.h"



/* Name: MUX_vidInit
 * Description: initialize the multiplexer pins
 * Arguments: *Mux_Struct: address of structure that contains the GPIO pins and ports that is connected to the MUX select pins
 * 			elements:
 * 					1- Mux_u16Selectpin0: it can be GPIO_Pin_x where x can be (0 ... 15)
 * 					2- Mux_u16Selectpin1: it can be GPIO_Pin_x where x can be (0 ... 15)
 * 					3- Mux_u16Selectpin2: it can be GPIO_Pin_x where x can be (0 ... 15)
 *
 * 					4- Mux_SelectPort0: it can be GPIOx where x can be (A, B, C)
 * 					5- Mux_SelectPort1: it can be GPIOx where x can be (A, B, C)
 * 					6- Mux_SelectPort2: it can be GPIOx where x can be (A, B, C)
 * Return: void
 */
void MUX_vidInit(MUX_TypeDef* Mux_Struct)
{
	/* initialize multiplexer structure */
	GPIO_InitTypeDef Mux_InitPin ={
			.GPIO_Mode = GPIO_Mode_Out_PP,
			.GPIO_Speed = GPIO_Speed_10MHz,
			.GPIO_Pin = Mux_Struct->Mux_u16Selectpin0
	};

	/* check parameters */
	if(Mux_Struct != (void*)0)
	{

		if((Mux_Struct->Mux_SelectPort0 == GPIOA) || (Mux_Struct->Mux_SelectPort1 == GPIOA) || (Mux_Struct->Mux_SelectPort2 == GPIOA))
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		}
		if((Mux_Struct->Mux_SelectPort0 == GPIOB) || (Mux_Struct->Mux_SelectPort1 == GPIOB) || (Mux_Struct->Mux_SelectPort2 == GPIOB))
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		}
		if((Mux_Struct->Mux_SelectPort0 == GPIOC) || (Mux_Struct->Mux_SelectPort1 == GPIOC) || (Mux_Struct->Mux_SelectPort2 == GPIOC))
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}


		/* initialize multiplexer select pins as output */
		GPIO_Init(Mux_Struct->Mux_SelectPort0, &Mux_InitPin);
		Mux_InitPin.GPIO_Pin = Mux_Struct->Mux_u16Selectpin1;
		GPIO_Init(Mux_Struct->Mux_SelectPort1,&Mux_InitPin);
		Mux_InitPin.GPIO_Pin = Mux_Struct->Mux_u16Selectpin2;
		GPIO_Init(Mux_Struct->Mux_SelectPort2, &Mux_InitPin);
	}
}


/* Name: Mux_vidSelectChannel
 * Description: select the desired channel
 * Arguments:
 * 				1- *Mux_Struct: address of structure that contains the GPIO pins and ports that is connected to the MUX select pins
 * 				  		elements:
 *					1- Mux_u16Selectpin0: it can be GPIO_Pin_x where x can be (0 ... 15)
 *					2- Mux_u16Selectpin1: it can be GPIO_Pin_x where x can be (0 ... 15)
 *					3- Mux_u16Selectpin2: it can be GPIO_Pin_x where x can be (0 ... 15)
 *
 *					4- Mux_SelectPort0: it can be GPIOx where x can be (A, B, C)
 *					5- Mux_SelectPort1: it can be GPIOx where x can be (A, B, C)
 *					6- Mux_SelectPort2: it can be GPIOx where x can be (A, B, C)
 * 				2- Mux_Channel: the desired multiplexer channel
 * 						it can be Mux_Channel_x where x can be (0 ... 7)
 * Return: void
 */
void Mux_vidSelectChannel(MUX_TypeDef* Mux_Struct, uint16_t Mux_Channel)
{
	/* check parameters */
	if(Mux_Struct != (void*)0)
	{
		/* write channel first bit value to selectPin0 */
		GPIO_WriteBit(Mux_Struct->Mux_SelectPort0, Mux_Struct->Mux_u16Selectpin0, (Mux_Channel & 0x0001));
		/* write channel first bit value to selectPin1 */
		GPIO_WriteBit(Mux_Struct->Mux_SelectPort1, Mux_Struct->Mux_u16Selectpin1, ((Mux_Channel>>1) & 0x0001));
		/* write channel first bit value to selectPin2 */
		GPIO_WriteBit(Mux_Struct->Mux_SelectPort2, Mux_Struct->Mux_u16Selectpin2, ((Mux_Channel>>2) & 0x0001));
	}
}


