/*
 * Ultrasonic.h
 *
 *  Created on: Jun 22, 2022
 *      Author: Ayman_Elgammal
 */

/* IMPORTANT NOTES:
 * 					1- This module supports HC-SR04 UltraSonic sensor.
 * 					2- The range of the sensor is ( 2 - 400 ) cm with 3mm ranging accuracy.
 * 					3- Distance = Time * Velocity of sound(340 M/S) / 2
 *
 */


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../include/stm32f1-stdperiph/stm32f10x_gpio.h"

/* UltraSonic instance structure */
typedef struct{
	uint16_t Ultrasonic_TrigChannel;		/* the timer channel that is connected to trigger pin */
	TIM_TypeDef* Ultrasonic_TrigTimer;		/* the timer channel that is used for trigger pulse */
	uint16_t Ultrasonic_EchoChannel;		/* the timer channel that is connected to echo pin */
	TIM_TypeDef* Ultrasonic_EchoTimer;		/* the timer that is used to determine pulse duration */
	uint16_t Ultrasonic_TrigPin;			/* the pin which is connected to trigger pin*/
	GPIO_TypeDef* Ultrasonic_TrigPort;		/* the port which is connected to trigger pin*/
}Ultrasonic_TypeDef;


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
void Ultrasonic_vidInit(Ultrasonic_TypeDef* Ultrasonic_InitStruct);


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
uint16_t Ultrasonic_u16eGtDistance(Ultrasonic_TypeDef* Ultrasonic_InitStruct);



#endif /* ULTRASONIC_H_ */
