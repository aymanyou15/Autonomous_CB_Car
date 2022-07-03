/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"
#include "../HAL/Multiplexer/Mux.h"
#include "../HAL/Encoder/ENC.h"
#include "../Services/Sched/sched.h"
#include "App.h"


#define APP_u8CMD_FORWARD		'F'
#define APP_u8CMD_BACKWARD		'B'
#define APP_u8CMD_LEFT			'L'
#define APP_u8CMD_RIGHT			'R'
#define APP_u8CMD_FORWARD_L		'G'
#define APP_u8CMD_BACKWARD_L	'H'
#define APP_u8CMD_FORWARD_R		'I'
#define APP_u8CMD_BACKWARD_R	'J'
#define APP_u8CMD_MAXSPEED		'Q'


// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


	Ultrasonic_TypeDef Global_Ultrasonic = {
			.Ultrasonic_TrigPort = GPIOB,
			.Ultrasonic_TrigPin = GPIO_Pin_1,
			.Ultrasonic_TrigTimer = TIM3,
			.Ultrasonic_TrigChannel = TIM_Channel_4,
			.Ultrasonic_EchoTimer = TIM1,
			.Ultrasonic_EchoChannel = TIM_Channel_1
	};

	MUX_TypeDef Global_Mux ={
			.Mux_SelectPort0 = GPIOB,
			.Mux_u16Selectpin0 = GPIO_Pin_14,

			.Mux_SelectPort1 = GPIOB,
			.Mux_u16Selectpin1 = GPIO_Pin_13,

			.Mux_SelectPort2 = GPIOB,
			.Mux_u16Selectpin2 = GPIO_Pin_12
	};




///********** Sensor ECU ***********/

CanTxMsg CAN_Tx_UltrasonicMessage;
CanTxMsg CAN_Tx_EncoderMessage;
CanTxMsg CAN_Tx_MotorControlMessage;
CanTxMsg CAN_Tx_LightControlMessage;

void Runnable_CAN_Tx_UltrasonicMessage(void);
void Runnable_CAN_Tx_EncoderMessage(void);
void Runnable_CAN_Tx_MotorControlMessage(void);
void Runnable_CAN_Tx_LightControlMessage(void);


int main(void)
{


	/* Bluetooth initialization */
	GPIO_InitTypeDef Loc_strTxPinCfg = {
				.GPIO_Mode = GPIO_Mode_AF_PP,
				.GPIO_Pin = GPIO_Pin_2,
				.GPIO_Speed = GPIO_Speed_10MHz
		};
		GPIO_InitTypeDef Loc_strRxPinCfg = {
				.GPIO_Mode = GPIO_Mode_IN_FLOATING,
				.GPIO_Pin = GPIO_Pin_3,
				.GPIO_Speed = GPIO_Speed_10MHz
		};
		USART_InitTypeDef Loc_strUSARTCfg;
		USART_ClockInitTypeDef Loc_strUSARTClkInit;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		GPIO_Init(GPIOA,&Loc_strTxPinCfg);
		GPIO_Init(GPIOA,&Loc_strRxPinCfg);
		USART_StructInit(&Loc_strUSARTCfg);
		USART_Init(USART2,&Loc_strUSARTCfg);
		USART_ClockStructInit(&Loc_strUSARTClkInit);
		USART_ClockInit(USART2,&Loc_strUSARTClkInit);
		USART_Cmd(USART2,ENABLE);

/********* Common CAN initialization *********/

	GPIO_InitTypeDef GPIO_InitStruct_CAN_RX;
	GPIO_InitTypeDef GPIO_InitStruct_CAN_TX;
	CAN_InitTypeDef  CAN_InitStruct;

	GPIO_InitStruct_CAN_RX.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct_CAN_RX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_CAN_RX.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_InitStruct_CAN_TX.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct_CAN_TX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct_CAN_TX.GPIO_Mode = GPIO_Mode_AF_PP;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_Init(GPIOB, &GPIO_InitStruct_CAN_RX);

	GPIO_Init(GPIOB, &GPIO_InitStruct_CAN_TX);

	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap2_CAN1, DISABLE);

	CAN_StructInit(&CAN_InitStruct); // freq:72MHZ  1st_Segment:15  2nd segment:2  prescale:4

	CAN_Init(CAN1, &CAN_InitStruct);

	CAN_DBGFreeze(CAN1, DISABLE);



	/********** Sensor ECU ***********/



	Runnable_t CAN_Tx_UltrasonicMessageRunnable;
	Runnable_t CAN_Tx_EncoderMessageRunnable;
	Runnable_t CAN_Tx_MotorControlMessageRunnable;
	Runnable_t CAN_Tx_LightControlMessageRunnable;



	CAN_Tx_UltrasonicMessageRunnable.Callback=Runnable_CAN_Tx_UltrasonicMessage;
	CAN_Tx_UltrasonicMessageRunnable.CyclicTimeMs=450;

	CAN_Tx_EncoderMessageRunnable.Callback=Runnable_CAN_Tx_EncoderMessage;
	CAN_Tx_EncoderMessageRunnable.CyclicTimeMs=1100;

	CAN_Tx_MotorControlMessageRunnable.Callback=Runnable_CAN_Tx_MotorControlMessage;
	CAN_Tx_MotorControlMessageRunnable.CyclicTimeMs=100;

	CAN_Tx_LightControlMessageRunnable.Callback=Runnable_CAN_Tx_LightControlMessage;
	CAN_Tx_LightControlMessageRunnable.CyclicTimeMs=200;

	CanTxMsg CAN_Tx_InitMessage;
		u8 UltrasonicReadings[6]={0};

		u8 EncoderReading = 0;
		u8 FrontLight=0;
		u8 BackLight=0;
		u8 MotorSignal=0;

		CanRxMsg CAN_Rx_InitMessage;

		CAN_FilterInitTypeDef CAN_FilterInitMessage;

		CAN_FilterInitMessage.CAN_FilterActivation = ENABLE;
		CAN_FilterInitMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
		CAN_FilterInitMessage.CAN_FilterIdHigh = 0x07F<<5;
		CAN_FilterInitMessage.CAN_FilterIdLow = 0X0000;
		CAN_FilterInitMessage.CAN_FilterMaskIdHigh = 0x7ff<<5;
		CAN_FilterInitMessage.CAN_FilterMaskIdLow = 0X0000;
		CAN_FilterInitMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterInitMessage.CAN_FilterNumber = 0; // 0 to 13??
		CAN_FilterInitMessage.CAN_FilterScale = CAN_FilterScale_32bit;

		CAN_Rx_InitMessage.StdId=0;
		CAN_Rx_InitMessage.ExtId=0;
		CAN_Rx_InitMessage.RTR=0;
		CAN_Rx_InitMessage.IDE=0;
		CAN_Rx_InitMessage.DLC=0;
		CAN_Rx_InitMessage.Data[0]=0;
		CAN_Rx_InitMessage.Data[1]=0;
		CAN_Rx_InitMessage.Data[2]=0;
		CAN_Rx_InitMessage.Data[3]=0;
		CAN_Rx_InitMessage.Data[4]=0;
		CAN_Rx_InitMessage.Data[5]=0;
		CAN_Rx_InitMessage.Data[6]=0;
		CAN_Rx_InitMessage.Data[7]=0;
		CAN_Rx_InitMessage.FMI=0;

		CAN_Tx_InitMessage.StdId = 0x07F;
		CAN_Tx_InitMessage.ExtId = 0;
		CAN_Tx_InitMessage.IDE = CAN_Id_Standard;
		CAN_Tx_InitMessage.RTR = CAN_RTR_Data;
		CAN_Tx_InitMessage.DLC = 1;
		CAN_Tx_InitMessage.Data[0] = 0x00;
		CAN_Tx_InitMessage.Data[1] = 0x00;
		CAN_Tx_InitMessage.Data[2] = 0x00;
		CAN_Tx_InitMessage.Data[3] = 0x00;
		CAN_Tx_InitMessage.Data[4] = 0x00;
		CAN_Tx_InitMessage.Data[5] = 0x00;
		CAN_Tx_InitMessage.Data[6] = 0x00;
		CAN_Tx_InitMessage.Data[7] = 0x00;

		CAN_Tx_UltrasonicMessage.StdId = 0X1FF;
		CAN_Tx_UltrasonicMessage.ExtId = 0;
		CAN_Tx_UltrasonicMessage.IDE = CAN_Id_Standard;
		CAN_Tx_UltrasonicMessage.RTR = CAN_RTR_Data;
		CAN_Tx_UltrasonicMessage.DLC = 6;
		CAN_Tx_UltrasonicMessage.Data[0] = UltrasonicReadings[0];
		CAN_Tx_UltrasonicMessage.Data[1] = UltrasonicReadings[1];
		CAN_Tx_UltrasonicMessage.Data[2] = UltrasonicReadings[2];
		CAN_Tx_UltrasonicMessage.Data[3] = UltrasonicReadings[3];
		CAN_Tx_UltrasonicMessage.Data[4] = UltrasonicReadings[4];
		CAN_Tx_UltrasonicMessage.Data[5] = UltrasonicReadings[5];

		CAN_Tx_EncoderMessage.StdId = 0X3FF;
		CAN_Tx_EncoderMessage.ExtId = 0;
		CAN_Tx_EncoderMessage.IDE = CAN_Id_Standard;
		CAN_Tx_EncoderMessage.RTR = CAN_RTR_Data;
		CAN_Tx_EncoderMessage.DLC = 1;
		CAN_Tx_EncoderMessage.Data[0] =  EncoderReading;

		CAN_Tx_LightControlMessage.StdId = 0X7FF;
		CAN_Tx_LightControlMessage.ExtId = 0;
		CAN_Tx_LightControlMessage.IDE = CAN_Id_Standard;
		CAN_Tx_LightControlMessage.RTR = CAN_RTR_Data;
		CAN_Tx_LightControlMessage.DLC = 2;
		CAN_Tx_LightControlMessage.Data[0] =  FrontLight;
		CAN_Tx_LightControlMessage.Data[1] =  BackLight;

		CAN_Tx_MotorControlMessage.StdId = 0x0FF;
		CAN_Tx_MotorControlMessage.ExtId = 0;
		CAN_Tx_MotorControlMessage.IDE = CAN_Id_Standard;
		CAN_Tx_MotorControlMessage.RTR = CAN_RTR_Data;
		CAN_Tx_MotorControlMessage.DLC = 1;
		CAN_Tx_MotorControlMessage.Data[0] = MotorSignal;



	    CAN_FilterInit(&CAN_FilterInitMessage);

		char MailBoxNum= CAN_TxStatus_NoMailBox;
		char status= CAN_TxStatus_Failed;
		MailBoxNum=	CAN_Transmit(CAN1, &CAN_Tx_InitMessage);
		while(status!= CAN_TxStatus_Ok){
			status=CAN_TransmitStatus(CAN1,MailBoxNum);
		}
		while(!(CAN_MessagePending(CAN1, CAN_FIFO0)));
		CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_InitMessage);
		CAN_FIFORelease(CAN1, CAN_FIFO0);


		Sched_RegisterRunnable(&CAN_Tx_UltrasonicMessageRunnable, 1);
		Sched_RegisterRunnable(&CAN_Tx_EncoderMessageRunnable, 2);
		Sched_RegisterRunnable(&CAN_Tx_MotorControlMessageRunnable, 0);
		Sched_RegisterRunnable(&CAN_Tx_LightControlMessageRunnable, 3);


		ENC_vidInit();

	/* initialize the UltraSonics */
	Ultrasonic_vidInit(&Global_Ultrasonic);

	/* initialize the multiplexer */
	MUX_vidInit(&Global_Mux);


	/* initializing the scheduler with 5 MS tick time */
	Sched_vidInit();

	/* register a call back function */
	Sched_RegisterCallBackFunction(APP_GetSensorsReads);

	/* start the scheduler */
	Sched_vidStart();

}

void APP_GetSensorsReads(void)
{

	static Ultrasonic_enuStates ultrasonic_States;

	uint16_t temp = 5000;
	uint16_t Loc_u16Timeout = 5000;
	uint16_t Loc_u16ReceivedCmd = 0;


//	  /* select the channel_1 to connect to ultraSonic_1 */
//	  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_0);
//
//	  /* select the channel_1 to connect to ultraSonic_1 */
//	  Mux_vidSelectChannel(&Global_DeMux, Mux_Channel_0);
//
//	  /* get the distance from ultraSonic_1 */
//	  var =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

	  /* print the distance */
//	  trace_printf("distance1 =   %d   CM\n", var);

	CAN_Tx_EncoderMessage.Data[0] = ENC_u16GetRPM();

	/* Delay */
		while(temp--);
		temp = 5000;
		while(temp--);
		temp = 5000;
		while(temp--);
		temp = 5000;
		while(temp--);
		temp = 5000;

		while(!USART_GetFlagStatus(USART2,USART_FLAG_RXNE) && Loc_u16Timeout--);
//		trace_printf("%c\n",USART_ReceiveData(USART2));
		Loc_u16ReceivedCmd = USART_ReceiveData(USART2);

		/* check the received data */
		if(Loc_u16ReceivedCmd == APP_u8CMD_FORWARD || Loc_u16ReceivedCmd == APP_u8CMD_BACKWARD || Loc_u16ReceivedCmd == APP_u8CMD_LEFT
				|| Loc_u16ReceivedCmd == APP_u8CMD_RIGHT || Loc_u16ReceivedCmd == APP_u8CMD_FORWARD_L || Loc_u16ReceivedCmd == APP_u8CMD_BACKWARD_L
				|| Loc_u16ReceivedCmd == APP_u8CMD_FORWARD_R || Loc_u16ReceivedCmd == APP_u8CMD_BACKWARD_R || Loc_u16ReceivedCmd == APP_u8CMD_MAXSPEED
				|| (Loc_u16ReceivedCmd > 0 && Loc_u16ReceivedCmd <= 9))
		{
			CAN_Tx_MotorControlMessage.Data[0] = Loc_u16ReceivedCmd;
		}
		else if(Loc_u16ReceivedCmd == 'W' || Loc_u16ReceivedCmd == 'w' || Loc_u16ReceivedCmd == 'U' || Loc_u16ReceivedCmd == 'u')
		{
			CAN_Tx_LightControlMessage.Data[0] = Loc_u16ReceivedCmd;
		}


	/* check the state
	 * state means the ultraSonic which measures distance
	 */
	switch(ultrasonic_States)
	{
		case Ultrasonic_0:
			  /* select the channel_1 to connect to ultraSonic_1 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_0);

			  /* get the distance from ultraSonic_1 */
			  CAN_Tx_UltrasonicMessage.Data[0]=  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance1 =   %d   CM\n", Sensors_strReadings.Ultrasonic_FR);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_1;

			  break;

		case Ultrasonic_1:
			  /* select the channel_2 to connect to ultraSonic_2 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_1);

			  /* get the distance from ultraSonic_2 */
			  CAN_Tx_UltrasonicMessage.Data[1] =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance2 =   %d   CM\n", Sensors_strReadings.Ultrasonic_F);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_2;

			  break;

		case Ultrasonic_2:
			  /* select the channel_3 to connect to ultraSonic_3 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_2);


			  /* get the distance from ultraSonic_1 */
			  CAN_Tx_UltrasonicMessage.Data[2] =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance3 =   %d   CM\n", Sensors_strReadings.Ultrasonic_FL);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_3;

			  break;

		case Ultrasonic_3:
			  /* select the channel_4 to connect to ultraSonic_4 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_3);


			  /* get the distance from ultraSonic_1 */
			  CAN_Tx_UltrasonicMessage.Data[3] =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance4 =   %d   CM\n", Sensors_strReadings.Ultrasonic_BR);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_4;

			  break;

		case Ultrasonic_4:
			  /* select the channel_5 to connect to ultraSonic_5 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_4);


			  /* get the distance from ultraSonic_1 */
			  CAN_Tx_UltrasonicMessage.Data[4] =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance5 =   %d   CM\n", Sensors_strReadings.Ultrasonic_B);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_5;

			  break;

		case Ultrasonic_5:
			  /* select the channel_6 to connect to ultraSonic_6 */
			  Mux_vidSelectChannel(&Global_Mux, Mux_Channel_5);


			  /* get the distance from ultraSonic_1 */
			  CAN_Tx_UltrasonicMessage.Data[5] =  Ultrasonic_u16eGtDistance(&Global_Ultrasonic);

			  /* print the distance */
//			  trace_printf("distance6 =   %d   CM\n", Sensors_strReadings.Ultrasonic_BL);

			  /* the next state */
			  ultrasonic_States = Ultrasonic_1;

			  break;

	}

}

/********** Sensor ECU ***********/

void Runnable_CAN_Tx_UltrasonicMessage(void){
	char MailBoxNum= CAN_TxStatus_NoMailBox;
	char status= CAN_TxStatus_Failed;
	MailBoxNum=	CAN_Transmit(CAN1, &CAN_Tx_UltrasonicMessage);
	while(status!= CAN_TxStatus_Ok){
		status=CAN_TransmitStatus(CAN1,MailBoxNum);
	}
}

void Runnable_CAN_Tx_EncoderMessage(void){

	char MailBoxNum= CAN_TxStatus_NoMailBox;
	char status= CAN_TxStatus_Failed;
	MailBoxNum=	CAN_Transmit(CAN1, &CAN_Tx_EncoderMessage);
	while(status!= CAN_TxStatus_Ok){
		status=CAN_TransmitStatus(CAN1,MailBoxNum);
	}

}
void Runnable_CAN_Tx_MotorControlMessage(void){
	char MailBoxNum= CAN_TxStatus_NoMailBox;
	char status= CAN_TxStatus_Failed;
	MailBoxNum=	CAN_Transmit(CAN1, &CAN_Tx_MotorControlMessage);
	while(status!= CAN_TxStatus_Ok){
		status=CAN_TransmitStatus(CAN1,MailBoxNum);
	}

}
void Runnable_CAN_Tx_LightControlMessage(void){
	char MailBoxNum= CAN_TxStatus_NoMailBox;
	char status= CAN_TxStatus_Failed;
	MailBoxNum=	CAN_Transmit(CAN1, &CAN_Tx_LightControlMessage);
	while(status!= CAN_TxStatus_Ok){
		status=CAN_TransmitStatus(CAN1,MailBoxNum);
	}
}


// ----------------------------------------------------------------------------
