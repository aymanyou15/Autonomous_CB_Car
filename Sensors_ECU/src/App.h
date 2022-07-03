/*
 * App.h
 *
 *  Created on: Jun 29, 2022
 *      Author: Ayman_Elgammal
 */

#ifndef APP_H_
#define APP_H_

typedef enum{
	Ultrasonic_0 = 0,
	Ultrasonic_1,
	Ultrasonic_2,
	Ultrasonic_3,
	Ultrasonic_4,
	Ultrasonic_5,
}Ultrasonic_enuStates;


void APP_GetSensorsReads(void);


#endif /* APP_H_ */
