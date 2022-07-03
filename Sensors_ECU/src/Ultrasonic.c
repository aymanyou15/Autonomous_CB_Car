/*
 * Ultrasonic.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Ayman_Elgammal
 */

#include "../include/cmsis/stm32f10x.h"
#include "../include/stm32f1-stdperiph/stm32f10x_gpio.h"
#include "../include/stm32f1-stdperiph/stm32f10x_rcc.h"
#include "../include/stm32f1-stdperiph/stm32f10x_tim.h"
#include "../include/stm32f1-stdperiph/misc.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"


#define TIM4_PRESCALER			72
#define TIM4_DELAY_US			100

/* global flag */
//uint8_t Global_flag;

//static void Ultrasonic_RaiseFlag(void);
static void Ultrasonic_Trigger(Ultrasonic_TypeDef* Ultrasonic_Struct);


/* Name: Ultrasonic_vidInit
 * Description: initialize the UltraSonic connected pins
 * Parameters: address of instance structure of type Ultrasonic_TypeDef that contains:
 * 				1- Ultrasonic_TrigChannel: ultraSonic TRIG pin channel,
 * 					it can be TIM_Channel_x where x can be 1, 2, 3, 4
 *
 * 				2- Ultrasonic_TrigTimer: the timer that is used to trigger the ultraSonic,
 * 					it can be TIMx where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TIM peripheral.
 *
 * 				3- Ultrasonic_EchoTimer: the timer that is used to determine echo pulse duration,
 *					it can be TIMx where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TIM peripheral.
 *
 * 				4- Ultrasonic_EchoChannel: the timer channel that is count echo pulse duration
 * 					it can be TIM_Channel_x where x can be 1, 2
 * 	NOTE: this module uses PWM input mode to determine the Echo pulse duration, thus Channel 1 or channel 2 only can be used
 *
 * 				5- Ultrasonic_TrigPin: the trigger connected pin,
 * 					it can be GPIO_Pin_x where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
 *	NOTE: this member should be timer channel pin number that is connected to trigger pin
 *
 *				6- Ultrasonic_TrigPort: the trigger connected port,
 *					it can be GPIOx where x can be (A..G) to select the GPIO peripheral
 *
 * Return: void
 */
void Ultrasonic_vidInit(Ultrasonic_TypeDef* Ultrasonic_Struct)
{
	GPIO_InitTypeDef GPIO_TrigPin, GPIO_EchoPin;
	TIM_OCInitTypeDef TIM_TrigChannel;
	TIM_ICInitTypeDef TIM_echoTimer;

	if(Ultrasonic_Struct != (void*)0)
	{
		/* initialize Trigger pin structure */
		GPIO_TrigPin.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_TrigPin.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_TrigPin.GPIO_Pin = Ultrasonic_Struct->Ultrasonic_TrigPin;

		/* initialize echo timer */
		TIM_echoTimer.TIM_Channel = Ultrasonic_Struct->Ultrasonic_EchoChannel;
		TIM_echoTimer.TIM_ICFilter = 0x0;
		TIM_echoTimer.TIM_ICPolarity = TIM_ICPolarity_Rising;
		TIM_echoTimer.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		TIM_echoTimer.TIM_ICSelection = TIM_ICSelection_DirectTI;


		/* initialize Echo Pin */
		GPIO_EchoPin.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_EchoPin.GPIO_Speed = GPIO_Speed_50MHz;
		if(Ultrasonic_Struct->Ultrasonic_EchoTimer == TIM1)
		{
			switch(Ultrasonic_Struct->Ultrasonic_EchoChannel)
			{
				case TIM_Channel_1:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_8;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_2:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_9;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_3:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_10;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_4:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_11;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

			}
		}
		if(Ultrasonic_Struct->Ultrasonic_EchoTimer == TIM2)
		{
			switch(Ultrasonic_Struct->Ultrasonic_EchoChannel)
			{
				case TIM_Channel_1:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_3;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* enable echo timer */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_2:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_1;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_3:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_2;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_4:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_3;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* enable echo timer */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

			}
		}
		if(Ultrasonic_Struct->Ultrasonic_EchoTimer == TIM3)
		{
			switch(Ultrasonic_Struct->Ultrasonic_EchoChannel)
			{
				case TIM_Channel_1:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_6;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_2:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_7;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOA, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

				case TIM_Channel_3:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_0;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(TIM3, &TIM_echoTimer);

					break;

				case TIM_Channel_4:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_1;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

			}
		}
		if(Ultrasonic_Struct->Ultrasonic_EchoTimer == TIM4)
		{
			switch(Ultrasonic_Struct->Ultrasonic_EchoChannel)
			{
				case TIM_Channel_1:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_6;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);
					break;

				case TIM_Channel_2:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_7;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);
					break;

				case TIM_Channel_3:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_8;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);
					break;

				case TIM_Channel_4:
					GPIO_EchoPin.GPIO_Pin = GPIO_Pin_9;
					/* enable GPIOA */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

					/* echo Timer clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

					/* initialize echo pin */
					GPIO_Init(GPIOB, &GPIO_EchoPin);

					/* initialize echo timer as PWM input mode */
					TIM_PWMIConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, &TIM_echoTimer);

					break;

			}
		}


		/* enable the trigger port clock */
		if(Ultrasonic_Struct->Ultrasonic_TrigPort == GPIOA)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		}
		else if(Ultrasonic_Struct->Ultrasonic_TrigPort == GPIOB)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		}
		else if(Ultrasonic_Struct->Ultrasonic_TrigPort == GPIOC)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}

		/* enable the trigger timer clock */
		if(Ultrasonic_Struct->Ultrasonic_TrigTimer == TIM1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		}
		else if(Ultrasonic_Struct->Ultrasonic_TrigTimer == TIM2)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		}
		else if(Ultrasonic_Struct->Ultrasonic_TrigTimer == TIM3)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		}
		else if(Ultrasonic_Struct->Ultrasonic_TrigTimer == TIM4)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		}


		/* initialize trigger pin as alternative function */
	GPIO_Init(Ultrasonic_Struct->Ultrasonic_TrigPort, &GPIO_TrigPin);


	/* check parameters */
	if(Ultrasonic_Struct != (void*)0)
	{
		/* initialize the Trigger timer channel */
		TIM_TrigChannel.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_TrigChannel.TIM_OCIdleState = TIM_OCIdleState_Reset;
		TIM_TrigChannel.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_TrigChannel.TIM_OutputState = TIM_OutputState_Enable;


		switch(Ultrasonic_Struct->Ultrasonic_TrigChannel)
		{
			case TIM_Channel_1:
				TIM_OC1Init(Ultrasonic_Struct->Ultrasonic_TrigTimer, &TIM_TrigChannel);
				break;

			case TIM_Channel_2:
				TIM_OC2Init(Ultrasonic_Struct->Ultrasonic_TrigTimer, &TIM_TrigChannel);
				break;

			case TIM_Channel_3:
				TIM_OC3Init(Ultrasonic_Struct->Ultrasonic_TrigTimer, &TIM_TrigChannel);
				break;

			case TIM_Channel_4:
				TIM_OC4Init(Ultrasonic_Struct->Ultrasonic_TrigTimer, &TIM_TrigChannel);
				break;

		}
	}

	/* set one pulse */
	TIM_SelectOnePulseMode(Ultrasonic_Struct->Ultrasonic_TrigTimer, TIM_OPMode_Single);

	/* configure trigger timer prescaler */
	TIM_PrescalerConfig(Ultrasonic_Struct->Ultrasonic_TrigTimer, 72, TIM_PSCReloadMode_Immediate);

	/* set the counter mode to Up counting */
	TIM_CounterModeConfig(Ultrasonic_Struct->Ultrasonic_TrigTimer, TIM_CounterMode_Up);

	}
}



/* Name: Ultrasonic_vidGetDistance
 * Description: get the distance in CM
 * Parameters: address of instance structure of type Ultrasonic_TypeDef that contains:
 * 				1- Ultrasonic_TrigChannel: ultraSonic TRIG pin channel,
 * 					it can be TIM_Channel_x where x can be 1, 2, 3, 4
 *
 * 				2- Ultrasonic_TrigTimer: the timer that is used to trigger the ultraSonic,
 * 					it can be TIMx where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TIM peripheral.
 *
 * 				3- Ultrasonic_EchoTimer: the timer that is used to determine echo pulse duration,
 *					it can be TIMx where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TIM peripheral.
 *
 * 				4- Ultrasonic_EchoChannel: the timer channel that is count echo pulse duration
 * 					it can be TIM_Channel_x where x can be 1, 2
 * 	NOTE: this module uses PWM input mode to determine the Echo pulse duration, thus Channel 1 or channel 2 only can be used
 *
 * 				5- Ultrasonic_TrigPin: the trigger connected pin,
 * 					it can be GPIO_Pin_x where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
 *	NOTE: this member should be timer channel pin number that is connected to trigger pin
 *
 *				6- Ultrasonic_TrigPort: the trigger connected port,
 *					it can be GPIOx where x can be (A..G) to select the GPIO peripheral
 *
 * Return: distance is CM
 */
uint16_t Ultrasonic_u16eGtDistance(Ultrasonic_TypeDef* Ultrasonic_Struct)
{
	uint16_t Loc_u16EchoPulseDuration;
	uint16_t Loc_u16Distance = 0;

	/* configure the echo timer prescaler */
	TIM_PrescalerConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, 72, TIM_PSCReloadMode_Immediate);

	/* configure the echo timer counting mode */
	TIM_CounterModeConfig(Ultrasonic_Struct->Ultrasonic_EchoTimer, TIM_CounterMode_Up);

	/* enable the echo timer */
	TIM_Cmd(Ultrasonic_Struct->Ultrasonic_EchoTimer, ENABLE);

	/* send a pulse with 21 us to trigger ultraSonic */
	Ultrasonic_Trigger(Ultrasonic_Struct);


	/* get the captured echo pulse duration */
	Loc_u16EchoPulseDuration = TIM_GetCapture2(Ultrasonic_Struct->Ultrasonic_EchoTimer);

	/* calculate Distance */
	Loc_u16Distance = Loc_u16EchoPulseDuration / 58;

	return Loc_u16Distance;

}


//static void Ultrasonic_RaiseFlag(void)
//{
//	Global_flag = 1;
//}


static void Ultrasonic_Trigger(Ultrasonic_TypeDef* Ultrasonic_Struct)
{

	/* set the compare match and preload values*/
	switch(Ultrasonic_Struct->Ultrasonic_TrigChannel)
	{
		case TIM_Channel_1:
			TIM_SetCompare1(Ultrasonic_Struct->Ultrasonic_TrigTimer, 5);
			TIM_SetAutoreload(Ultrasonic_Struct->Ultrasonic_TrigTimer, 25);
			break;

		case TIM_Channel_2:
			TIM_SetCompare2(Ultrasonic_Struct->Ultrasonic_TrigTimer, 5);
			TIM_SetAutoreload(Ultrasonic_Struct->Ultrasonic_TrigTimer, 25);
			break;

		case TIM_Channel_3:
			TIM_SetCompare3(Ultrasonic_Struct->Ultrasonic_TrigTimer, 5);
			TIM_SetAutoreload(Ultrasonic_Struct->Ultrasonic_TrigTimer, 25);
			break;

		case TIM_Channel_4:
			TIM_SetCompare4(Ultrasonic_Struct->Ultrasonic_TrigTimer, 5);
			TIM_SetAutoreload(Ultrasonic_Struct->Ultrasonic_TrigTimer, 25);
			break;

	}


	/* enable the trigger timer */
	TIM_Cmd(Ultrasonic_Struct->Ultrasonic_TrigTimer, ENABLE);
}
