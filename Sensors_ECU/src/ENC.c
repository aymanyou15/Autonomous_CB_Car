/*
 * ENC.c
 *
 *  Created on: Jun 24, 2022
 *      Author: سابق و لاحق
 */

#include <stdint.h>
#include <diag/trace.h>
#include "../system/include/cmsis/stm32f10x.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_tim.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_rcc.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_gpio.h"
#include "../system/include/stm32f1-stdperiph/misc.h"
#include "../HAL/Encoder/ENC.h"
#include "../HAL/Encoder/ENC_prv.h"


extern ENC_tstrCfg ENC_strCfgArr[ENC_u8ENCODERS_NUM];

static volatile uint16_t ENC_u16PulsesCounter;
static volatile uint16_t ENC_u16Ms;
static uint16_t ENC_u16RPM;
static uint8_t ENC_u8TimerTrigger;

/*
 * Function Name: ENC_vidInit
 *
 * Input Args: No "void"
 *
 * Return: No "void"
 *
 * Description: Initializes the Encoder module by initializing the external interrupt and Timer2
 */
void ENC_vidInit(void)
{
	uint8_t Loc_u8Iterator;
	/*NVIC configuration for the external interrupt*/
	NVIC_InitTypeDef Loc_strNVIC_EXTICfg = {
			.NVIC_IRQChannelPreemptionPriority = 0,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE
	};
	/*NVIC configuration for the timer2*/
	NVIC_InitTypeDef Loc_strNVIC_TIMCfg = {
			.NVIC_IRQChannel = TIM2_IRQn,
			.NVIC_IRQChannelPreemptionPriority = 0,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE
	};
	/*Pin configuration*/
	GPIO_InitTypeDef Loc_strPinCfg = {
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IN_FLOATING
	};
	/*External Interrupt configuration*/
	EXTI_InitTypeDef Loc_strEXTICfg = {
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE
	};
	/*Timer Configuration*/
	TIM_TimeBaseInitTypeDef Loc_strTIMCfg = {
			.TIM_Prescaler = 1,
			.TIM_CounterMode = TIM_CounterMode_Up,
			.TIM_Period = 36000,
			.TIM_ClockDivision = TIM_CKD_DIV1,
			.TIM_RepetitionCounter = 0
	};
	/*Initializing the NVIC for the external interrupt*/
	NVIC_Init(&Loc_strNVIC_TIMCfg);
	/*Enabling AFIO peripheral for controlling the external interrupt*/
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN,ENABLE);
	/*Applying the configuration to the timer and the external interrupt*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator < ENC_u8ENCODERS_NUM ; Loc_u8Iterator++)
	{
		/*Setting the GPIO pin to be configured*/
		Loc_strPinCfg.GPIO_Pin = (uint16_t)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin >> ENC_u8GPIO_PIN_BIT_OFFSET);
		/*Setting the EXTI Line IRQ number to be configured*/
		Loc_strNVIC_EXTICfg.NVIC_IRQChannel = (IRQn_Type)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin >> ENC_u8EXTI_IRQ_BIT_OFFSET);
		/*Enabling GPIO Peripheral for the external interrupt pin*/
		RCC_APB2PeriphClockCmd(ENC_strCfgArr[Loc_u8Iterator].ENC_u32Port,ENABLE);
		/*Getting the External interrupt line from the Cfg array*/
		Loc_strEXTICfg.EXTI_Line = (uint32_t)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin >> ENC_u8EXTI_LINE_BIT_OFFSET);
		/*Applying external interrupt configuration*/
		EXTI_Init(&Loc_strEXTICfg);
		/*Initializing the NVIC for the timer2*/
		NVIC_Init(&Loc_strNVIC_EXTICfg);

		/*Initializing the GPIO related to the chosen pin and configuring the external interrupt pin*/
		switch(ENC_strCfgArr[Loc_u8Iterator].ENC_u32Port)
		{
			case ENC_u32PORTA:
				GPIO_Init((GPIO_TypeDef*)GPIOA_BASE,&Loc_strPinCfg);
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,(uint8_t)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin));
				break;
			case ENC_u32PORTB:
				GPIO_Init((GPIO_TypeDef*)GPIOB_BASE,&Loc_strPinCfg);
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,(uint8_t)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin));
				break;
			case ENC_u32PORTC:
				GPIO_Init((GPIO_TypeDef*)GPIOC_BASE,&Loc_strPinCfg);
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,(uint8_t)(ENC_strCfgArr[Loc_u8Iterator].ENC_u64Pin));
				break;
		}
	}
	/*Enabling Timer2*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	/*Initializing Timer2*/
	TIM_TimeBaseInit((TIM_TypeDef*)TIM2_BASE,&Loc_strTIMCfg);
	TIM_ClearFlag((TIM_TypeDef*)TIM2_BASE,TIM_FLAG_Update);
	/*Enabling Timer2 update Interrupt*/
	TIM_ITConfig((TIM_TypeDef*)TIM2_BASE,TIM_IT_Update,ENABLE);
	/*Registering call back function when Timer2 update interrupt occurs*/
	TIM_RegisterCbfOnUpdate(ENC_vid1MsPassed);
	/*Registering call back function when external interrupt occurs interrupt occurs*/
	EXTI_RegisterCbfOnPulse(ENC_vidPulseNotif);
}

/*
 * Function Name: ENC_vidGetRPM
 *
 * Input Args: No "void"
 *
 * Return: uint16_t "RPM value"
 *
 * Description: returns the calculated RPM Value
 *
 */
uint16_t ENC_u16GetRPM(void)
{
	return ENC_u16RPM;
}

/*
 * Function Name: ENC_vid1MsPassed
 *
 * Input Args: No "void"
 *
 * Return: No "void"
 *
 * Description: Call back function called by the timer module every 1ms
 */
void ENC_vid1MsPassed(void)
{
	ENC_u16Ms++;
	/*Checking if 1 Sec passed or not*/
	if(ENC_u16Ms == ONE_SECOND)
	{
		/*Setting Timer2 counter to 0*/
		TIM_SetCounter((TIM_TypeDef*)TIM2_BASE,0);
		trace_printf("%d \n",ENC_u16GetRPM());
		/*Calculating the RPM*/
		ENC_u16RPM = (ENC_u16PulsesCounter * SIXTY_SECONDS) / ENC_u16ENCODER_PPR;
		/* Checking if The number of counters equals zero to disable the timer and setting the flag to 0 and this meaning
		 * there is no pulses on the EXTI pin during the last second */
		if(ENC_u16PulsesCounter == ZERO)
		{
			TIM_Cmd((TIM_TypeDef*)TIM2_BASE,DISABLE);
			ENC_u8TimerTrigger = FLAG_RESET;
		}
		/*Setting the pulses counter to 0*/
		ENC_u16PulsesCounter = ZERO;
		/*Setting the Milliseconds counter to 0*/
		ENC_u16Ms = ZERO;
	}
}

/*
 * Function Name: ENC_vidPulseNotif
 *
 * Input Args: No "void"
 *
 * Return: No "void"
 *
 * Description: Call back function called by the External interrupt module when pulse is detected on the EXTI pin
 */
void ENC_vidPulseNotif(void)
{
	/*Enable the timer if a pulse is detected after 1 second of No pulses*/
	if(!ENC_u8TimerTrigger)
	{
		TIM_Cmd((TIM_TypeDef*)TIM2_BASE,ENABLE);
		/*Setting the flag to 1 to avoid enabling the timer again*/
		ENC_u8TimerTrigger = FLAG_SET;
	}
	/*Incrementing the pulses counter*/
	ENC_u16PulsesCounter++;
}
