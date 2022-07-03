/*
 * Mux.h
 *
 *  Created on: Jun 28, 2022
 *      Author: Ayman_Elgammal
 */

#ifndef MUX_H_
#define MUX_H_

/* multiplexer instance structure */
typedef struct{
	uint16_t Mux_u16Selectpin0;
	uint16_t Mux_u16Selectpin1;
	uint16_t Mux_u16Selectpin2;
	GPIO_TypeDef* Mux_SelectPort0;
	GPIO_TypeDef* Mux_SelectPort1;
	GPIO_TypeDef* Mux_SelectPort2;
}MUX_TypeDef;



/* multiplexer channels */
#define Mux_Channel_0		((uint16_t)0)
#define Mux_Channel_1		((uint16_t)1)
#define Mux_Channel_2		((uint16_t)2)
#define Mux_Channel_3		((uint16_t)3)
#define Mux_Channel_4		((uint16_t)4)
#define Mux_Channel_5		((uint16_t)5)
#define Mux_Channel_6		((uint16_t)6)
#define Mux_Channel_7		((uint16_t)7)


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
void MUX_vidInit(MUX_TypeDef* Mux_Struct);


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
void Mux_vidSelectChannel(MUX_TypeDef* Mux_Struct, uint16_t Mux_Channel);



#endif /* MUX_H_ */
