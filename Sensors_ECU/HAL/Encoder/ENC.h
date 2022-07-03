/*
 * ENC.h
 *
 *  Created on: Jun 24, 2022
 *      Author: سابق و لاحق
 */

#ifndef ENC_H_
#define ENC_H_

#include "ENC_cfg.h"

/*Encoder Pin Configuration*/
typedef struct{
	uint32_t ENC_u32Port;
	uint64_t ENC_u64Pin;
}ENC_tstrCfg;

/*ENC_u32Port values in ENC_tstrCfg struct*/
#define ENC_u32PORTA		RCC_APB2Periph_GPIOA
#define ENC_u32PORTB		RCC_APB2Periph_GPIOB
#define ENC_u32PORTC		RCC_APB2Periph_GPIOC

/*ENC_u32Pin values in ENC_tstrCfg struct*/
#define ENC_u64PIN_0 		(((uint64_t)EXTI_Line0<<32)|((uint16_t)GPIO_Pin_0<<16)|((uint8_t)EXTI0_IRQn<<8)|(uint8_t)GPIO_PinSource0)
#define ENC_u64PIN_1 		(((uint64_t)EXTI_Line1<<32)|((uint16_t)GPIO_Pin_1<<16)|((uint8_t)EXTI1_IRQn<<8)|(uint8_t)GPIO_PinSource1)
#define ENC_u64PIN_2 		(((uint64_t)EXTI_Line2<<32)|((uint16_t)GPIO_Pin_2<<16)|((uint8_t)EXTI2_IRQn<<8)|(uint8_t)GPIO_PinSource2)
#define ENC_u64PIN_3 		(((uint64_t)EXTI_Line3<<32)|((uint16_t)GPIO_Pin_3<<16)|((uint8_t)EXTI3_IRQn<<8)|(uint8_t)GPIO_PinSource3)
#define ENC_u64PIN_4 		(((uint64_t)EXTI_Line4<<32)|((uint16_t)GPIO_Pin_4<<16)|((uint8_t)EXTI4_IRQn<<8)|(uint8_t)GPIO_PinSource4)
#define ENC_u64PIN_5 		(((uint64_t)EXTI_Line5<<32)|((uint16_t)GPIO_Pin_5<<16)|((uint8_t)EXTI5_IRQn<<8)|(uint8_t)GPIO_PinSource5)
#define ENC_u64PIN_6 		(((uint64_t)EXTI_Line6<<32)|((uint16_t)GPIO_Pin_6<<16)|((uint8_t)EXTI6_IRQn<<8)|(uint8_t)GPIO_PinSource6)
#define ENC_u64PIN_7 		(((uint64_t)EXTI_Line7<<32)|((uint16_t)GPIO_Pin_7<<16)|((uint8_t)EXTI7_IRQn<<8)|(uint8_t)GPIO_PinSource7)
#define ENC_u64PIN_8 		(((uint64_t)EXTI_Line8<<32)|((uint16_t)GPIO_Pin_8<<16)|((uint8_t)EXTI8_IRQn<<8)|(uint8_t)GPIO_PinSource8)
#define ENC_u64PIN_9 		(((uint64_t)EXTI_Line9<<32)|((uint16_t)GPIO_Pin_9<<16)|((uint8_t)EXTI9_IRQn<<8)|(uint8_t)GPIO_PinSource9)
#define ENC_u64PIN_10		(((uint64_t)EXTI_Line10<<32)|((uint16_t)GPIO_Pin_10<<16)|((uint8_t)EXTI10_IRQn<<8)|(uint8_t)GPIO_PinSource10)
#define ENC_u64PIN_11		(((uint64_t)EXTI_Line11<<32)|((uint16_t)GPIO_Pin_11<<16)|((uint8_t)EXTI11_IRQn<<8)|(uint8_t)GPIO_PinSource11)
#define ENC_u64PIN_12		(((uint64_t)EXTI_Line12<<32)|((uint16_t)GPIO_Pin_12<<16)|((uint8_t)EXTI12_IRQn<<8)|(uint8_t)GPIO_PinSource12)
#define ENC_u64PIN_13		(((uint64_t)EXTI_Line13<<32)|((uint16_t)GPIO_Pin_13<<16)|((uint8_t)EXTI13_IRQn<<8)|(uint8_t)GPIO_PinSource13)
#define ENC_u64PIN_14		(((uint64_t)EXTI_Line14<<32)|((uint16_t)GPIO_Pin_14<<16)|((uint8_t)EXTI14_IRQn<<8)|(uint8_t)GPIO_PinSource14)
#define ENC_u64PIN_15		(((uint64_t)EXTI_Line15<<32)|((uint16_t)GPIO_Pin_15<<16)|((uint8_t)EXTI15_IRQn<<8)|(uint8_t)GPIO_PinSource15)

/*
 * Function Name: ENC_vidInit
 *
 * Input Args: No "void"
 *
 * Return: No "void"
 *
 * Description: Initializes the Encoder module by initializing the external interrupt and Timer6
 */
void ENC_vidInit(void);

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
uint16_t ENC_u16GetRPM(void);

#endif /* ENC_H_ */
