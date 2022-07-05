/*
 * Systick.c
 *
 *  Created on: Jun 28, 2022
 *      Author: sara
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


/********************New Types*******************/
typedef enum{
	systick_ok,
	systick_nok
}Systick_t_ErrorStatus;

typedef void (*Systick_cbf_t) (void);

/*********************Defines********************/
#define Systick_Enable			0x00000001
#define Systick_TICKINT_ON		0x00000002
#define Systick_CLKSOURCE_AHB_8	0x00000000
#define Systick_CLKSOURCE_AHB	0x00000004



/*****************Function Prototypes************/

void Systick_Init();

Systick_t_ErrorStatus Systick_SetTickTime_ms(u32 time);

void Systick_Start();

void Systick_Register_cbf(Systick_cbf_t cbf);




#endif /* SYSTICK_H_ */
