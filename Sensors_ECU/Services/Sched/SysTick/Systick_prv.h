/*
 * Systick_prv.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Ayman_Elgammal
 */

#ifndef SYSTICK_PRV_H_
#define SYSTICK_PRV_H_

/* SYSTICK_RUNNING_MODE options */
#define SYSTICK_MULTI_SHOT		0
#define SYSTICK_SINGLE_SHOT		1


/* count flag mask */
#define SYSTICK_COUNTFLAG_MASK		0X00010000

/* sysTick base Address */
#define SYSTICK_BASE_ADDRESS		0xE000E010

/* SysTick enable mask */
#define SYSTICK_ENABLE_MASK		0X00000001

/* SysTick Maximum reload value  (0X00FFFFFF)*/
#define SYSTICK_MAX_RELOAD		16777215

#endif /* SYSTICK_PRV_H_ */
