/*
 * stm32f401cc.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Ayman_Elgammal
 */


#ifndef 	STM32F401CC_H
#define 	STM32F401CC_H


typedef struct{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 Reserved[2];
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 Reserved1[2];
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 Reserved2[2];
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 Reserved3[2];
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 Reserved4[2];
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 Reserved5[2];
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 Reserved6[2];
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 Reserved7;
	u32 RCC_DCKCFGR;

}RCC_t;


typedef struct{
	u32 GPIOx_MODER;
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 GPIOx_AFRL;
	u32 GPIOx_AFRH;

}GPIO_t;


typedef struct{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}SysTick_t;


typedef struct{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}USART_t;


#endif  /* STM32F401CC_H */
