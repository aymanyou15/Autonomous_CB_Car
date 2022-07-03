/*
 * ENC_prv.h
 *
 *  Created on: Jun 24, 2022
 *      Author: سابق و لاحق
 */

#ifndef ENC_PRV_H_
#define ENC_PRV_H_


#define ENC_u64PINS_MASK				0x000000FF

#define ENC_u8EXTI_LINE_BIT_OFFSET		32
#define ENC_u8GPIO_PIN_BIT_OFFSET		16

#define ENC_u8EXTI_IRQ_BIT_OFFSET		8

#define ZERO							0

#define ONE_SECOND						1000
#define SIXTY_SECONDS					60

#define FLAG_SET						1
#define FLAG_RESET						0

void ENC_vid1MsPassed(void);
void ENC_vidPulseNotif(void);

#endif /* ENC_PRV_H_ */
