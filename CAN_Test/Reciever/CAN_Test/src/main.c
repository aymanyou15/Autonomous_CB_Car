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
#include <stm32f10x_can.h>
#include "Sched.h"
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

//	CanTxMsg CAN_TestMessage;
//	CanTxMsg CAN_TestMessageTwo;

CanRxMsg CAN_TestMessageR;
CanRxMsg CAN_TestMessageRD;


////
void Runnable_TX1(void);
void Runnable_TX2(void);


int main(int argc, char* argv[])

{
		Runnable_t RunnableTX1;
		Runnable_t RunnableTX2;

		GPIO_InitTypeDef GPIO_InitStruct_OUT_PIN;

		RunnableTX1.Callback=Runnable_TX1;
		RunnableTX1.CyclicTimeMs=20;
		RunnableTX2.Callback=Runnable_TX2;
		RunnableTX2.CyclicTimeMs=40;

		GPIO_InitStruct_OUT_PIN.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStruct_OUT_PIN.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_InitStruct_OUT_PIN.GPIO_Mode =  GPIO_Mode_Out_PP;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_Init(GPIOA, &GPIO_InitStruct_OUT_PIN);


	GPIO_InitTypeDef GPIO_InitStruct_CAN_RX;
	GPIO_InitTypeDef GPIO_InitStruct_CAN_TX;
	CAN_InitTypeDef CAN_InitStruct;
//------------------------------------------------------------------//

//-------------------------------0--------------------------------------//

		CAN_FilterInitTypeDef CAN_FilterStruct;
		CAN_FilterInitTypeDef CAN_FilterStructD;

	CAN_FilterStruct.CAN_FilterActivation = ENABLE;
	CAN_FilterStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterStruct.CAN_FilterIdHigh = 0X455<<5;
	CAN_FilterStruct.CAN_FilterIdLow = 0X0000;
	CAN_FilterStruct.CAN_FilterMaskIdHigh = 0X7ff<<5;
	CAN_FilterStruct.CAN_FilterMaskIdLow = 0X0000;
	CAN_FilterStruct.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterStruct.CAN_FilterNumber = 0; // 0 to 13??
	CAN_FilterStruct.CAN_FilterScale = CAN_FilterScale_32bit;

		CAN_FilterStructD.CAN_FilterActivation = ENABLE;
		CAN_FilterStructD.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
		CAN_FilterStructD.CAN_FilterIdHigh = 0X7AB<<5;
		CAN_FilterStructD.CAN_FilterIdLow = 0X0000;
		CAN_FilterStructD.CAN_FilterMaskIdHigh = 0X7ff<<5;
		CAN_FilterStructD.CAN_FilterMaskIdLow = 0X0000;
		CAN_FilterStructD.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterStructD.CAN_FilterNumber = 1; // 0 to 13??
		CAN_FilterStructD.CAN_FilterScale = CAN_FilterScale_32bit;
//----------------------------------------------------------------------//
	GPIO_InitStruct_CAN_RX.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct_CAN_RX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_CAN_RX.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_InitStruct_CAN_TX.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct_CAN_TX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_CAN_TX.GPIO_Mode = GPIO_Mode_AF_PP;
//----------------------------------------------------------------------//
//	CAN_TestMessage.StdId = 0x555;
//	CAN_TestMessage.ExtId = 0;
//	CAN_TestMessage.IDE = CAN_Id_Standard;
//	CAN_TestMessage.RTR = CAN_RTR_Data;
//	CAN_TestMessage.DLC = 4;
//	CAN_TestMessage.Data[0] = 0XAA;
//	CAN_TestMessage.Data[1] = 0X55;
//	CAN_TestMessage.Data[2] = 0XAA;
//	CAN_TestMessage.Data[3] = 0X55;

//	CAN_TestMessageTwo.StdId = 0X7AB;
//	CAN_TestMessageTwo.ExtId = 0;
//	CAN_TestMessageTwo.IDE = CAN_Id_Standard;
//	CAN_TestMessageTwo.RTR = CAN_RTR_Data;
//	CAN_TestMessageTwo.DLC = 2;
//	CAN_TestMessageTwo.Data[0] = 0XBA;
//	CAN_TestMessageTwo.Data[1] = 0XEE;

//--------------------------------------------------------------------------//
	CAN_TestMessageR.StdId = 0;
	CAN_TestMessageR.ExtId = 0;
	CAN_TestMessageR.IDE = 0;
	CAN_TestMessageR.RTR = 0;
	CAN_TestMessageR.DLC = 0;
	CAN_TestMessageR.Data[0] = 0X00;
	CAN_TestMessageR.Data[1] = 0X00;
	CAN_TestMessageR.Data[2] = 0X00;
	CAN_TestMessageR.Data[3] = 0X00;
	CAN_TestMessageR.Data[4] = 0X00;
	CAN_TestMessageR.FMI=0;

		CAN_TestMessageRD.StdId = 0;
		CAN_TestMessageRD.ExtId = 0;
		CAN_TestMessageRD.IDE = 0;
		CAN_TestMessageRD.RTR = 0;
		CAN_TestMessageRD.DLC = 0;
		CAN_TestMessageRD.Data[0] = 0X00;
		CAN_TestMessageRD.Data[1] = 0X00;
		CAN_TestMessageRD.Data[2] = 0X00;
		CAN_TestMessageRD.Data[3] = 0X00;
		CAN_TestMessageRD.Data[4] = 0X00;
		CAN_TestMessageRD.FMI=0;
//---------------------------------------------------------------------------//
//		CanTxMsg CAN_TestMessageR;
//		CAN_FilterInitTypeDef CAN_FilterStruct;



	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_Init(GPIOA, &GPIO_InitStruct_CAN_RX);

	GPIO_Init(GPIOA, &GPIO_InitStruct_CAN_TX);

	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, DISABLE);

	GPIO_PinRemapConfig(GPIO_Remap2_CAN1, DISABLE);

	CAN_StructInit(&CAN_InitStruct);

	CAN_Init(CAN1, &CAN_InitStruct);

	CAN_DBGFreeze(CAN1, DISABLE);

	CAN_FilterInit(&CAN_FilterStruct);
	CAN_FilterInit(&CAN_FilterStructD);

	Sched_vidInit();

	Sched_RegisterRunnable(&RunnableTX1, 0);
	Sched_RegisterRunnable(&RunnableTX2, 1);


//
	Sched_vidStart();


	while (1)
	{


//			char MailBoxNum= CAN_TxStatus_NoMailBox;
//			char status= CAN_TxStatus_Failed;
//			while((MailBoxNum == CAN_TxStatus_NoMailBox) || (status==CAN_TxStatus_Failed)	){
//				MailBoxNum=
//						CAN_Transmit(CAN1, &CAN_TestMessage);
//				if(MailBoxNum<=2){
//				status=CAN_TransmitStatus(CAN1,MailBoxNum);
//			}
//		}
//		for(int i=0;i<32000;i++);.
//		CAN_Transmit(CAN1, &CAN_TestMessage);
//		CAN_Transmit(CAN1, &CAN_TestMessageTwo);

	}
//
///************************** Common CAN initialization **********************/
//
//	GPIO_InitTypeDef GPIO_InitStruct_CAN_RX;
//	GPIO_InitTypeDef GPIO_InitStruct_CAN_TX;
//	CAN_InitTypeDef  CAN_InitStruct;
//
//	GPIO_InitStruct_CAN_RX.GPIO_Pin = GPIO_Pin_11;
//	GPIO_InitStruct_CAN_RX.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct_CAN_RX.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//
//	GPIO_InitStruct_CAN_TX.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStruct_CAN_TX.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_InitStruct_CAN_TX.GPIO_Mode = GPIO_Mode_AF_PP;
//
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//
//	GPIO_Init(GPIOA, &GPIO_InitStruct_CAN_RX);
//
//	GPIO_Init(GPIOA, &GPIO_InitStruct_CAN_TX);
//
//	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, DISABLE);
//
//	GPIO_PinRemapConfig(GPIO_Remap2_CAN1, DISABLE);
//
//	CAN_StructInit(&CAN_InitStruct); // freq:72MHZ  1st_Segment:15  2nd segment:2  prescale:4
//
//	CAN_Init(CAN1, &CAN_InitStruct);
//
//	CAN_DBGFreeze(CAN1, DISABLE);
//
//
//
///****************************** Master ECU *********************************/
//	CanRxMsg CAN_Rx_EncoderMessage;
//	CanRxMsg CAN_Rx_UltrasonicMessage;
//	CanRxMsg CAN_Rx_LightControlMessage;
//	CanRxMsg CAN_Rx_LightInitMessage;
//
//	CAN_FilterInitTypeDef CAN_FilterEncoderMessage;
//	CAN_FilterInitTypeDef CAN_FilterUltrasonicMessage;
//	CAN_FilterInitTypeDef CAN_FilterLightControlMessage;
//	CAN_FilterInitTypeDef CAN_FilterLightInitMessage;
//
//	CAN_FilterLightInitMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterLightInitMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterLightInitMessage.CAN_FilterIdHigh = 0x07F<<5;
//	CAN_FilterLightInitMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterLightInitMessage.CAN_FilterMaskIdHigh = 0x07F<<5;
//	CAN_FilterLightInitMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterLightInitMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterLightInitMessage.CAN_FilterNumber = 0; // 0 to 13??
//	CAN_FilterLightInitMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_LightInitMessage.StdId=0;
//	CAN_Rx_LightInitMessage.ExtId=0;
//	CAN_Rx_LightInitMessage.RTR=0;
//	CAN_Rx_LightInitMessage.IDE=0;
//	CAN_Rx_LightInitMessage.DLC=0;
//	CAN_Rx_LightInitMessage.Data[0]=0;
//	CAN_Rx_LightInitMessage.Data[1]=0;
//	CAN_Rx_LightInitMessage.Data[2]=0;
//	CAN_Rx_LightInitMessage.Data[3]=0;
//	CAN_Rx_LightInitMessage.Data[4]=0;
//	CAN_Rx_LightInitMessage.Data[5]=0;
//	CAN_Rx_LightInitMessage.Data[6]=0;
//	CAN_Rx_LightInitMessage.Data[7]=0;
//	CAN_Rx_LightInitMessage.FMI=0;
//
//	CAN_FilterEncoderMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterEncoderMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterEncoderMessage.CAN_FilterIdHigh = 0X3FF<<5;
//	CAN_FilterEncoderMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterEncoderMessage.CAN_FilterMaskIdHigh = 0X3FF<<5;
//	CAN_FilterEncoderMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterEncoderMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterEncoderMessage.CAN_FilterNumber = 1; // 0 to 13??
//	CAN_FilterEncoderMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_EncoderMessage.StdId=0;
//	CAN_Rx_EncoderMessage.ExtId=0;
//	CAN_Rx_EncoderMessage.RTR=0;
//	CAN_Rx_EncoderMessage.IDE=0;
//	CAN_Rx_EncoderMessage.DLC=0;
//	CAN_Rx_EncoderMessage.Data[0]=0;
//	CAN_Rx_EncoderMessage.Data[1]=0;
//	CAN_Rx_EncoderMessage.Data[2]=0;
//	CAN_Rx_EncoderMessage.Data[3]=0;
//	CAN_Rx_EncoderMessage.Data[4]=0;
//	CAN_Rx_EncoderMessage.Data[5]=0;
//	CAN_Rx_EncoderMessage.Data[6]=0;
//	CAN_Rx_EncoderMessage.Data[7]=0;
//	CAN_Rx_EncoderMessage.FMI=0;
//
//	CAN_FilterUltrasonicMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterUltrasonicMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterUltrasonicMessage.CAN_FilterIdHigh = 0X1FF<<5;
//	CAN_FilterUltrasonicMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterUltrasonicMessage.CAN_FilterMaskIdHigh = 0X1FF<<5;
//	CAN_FilterUltrasonicMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterUltrasonicMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterUltrasonicMessage.CAN_FilterNumber = 2; // 0 to 13??
//	CAN_FilterUltrasonicMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_UltrasonicMessage.StdId=0;
//	CAN_Rx_UltrasonicMessage.ExtId=0;
//	CAN_Rx_UltrasonicMessage.RTR=0;
//	CAN_Rx_UltrasonicMessage.IDE=0;
//	CAN_Rx_UltrasonicMessage.DLC=0;
//	CAN_Rx_UltrasonicMessage.Data[0]=0;
//	CAN_Rx_UltrasonicMessage.Data[1]=0;
//	CAN_Rx_UltrasonicMessage.Data[2]=0;
//	CAN_Rx_UltrasonicMessage.Data[3]=0;
//	CAN_Rx_UltrasonicMessage.Data[4]=0;
//	CAN_Rx_UltrasonicMessage.Data[5]=0;
//	CAN_Rx_UltrasonicMessage.Data[6]=0;
//	CAN_Rx_UltrasonicMessage.Data[7]=0;
//	CAN_Rx_UltrasonicMessage.FMI=0;
//
//	CAN_FilterLightControlMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterLightControlMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterLightControlMessage.CAN_FilterIdHigh = 0X7FF<<5;
//	CAN_FilterLightControlMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterLightControlMessage.CAN_FilterMaskIdHigh = 0X7FF<<5;
//	CAN_FilterLightControlMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterLightControlMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterLightControlMessage.CAN_FilterNumber = 3; // 0 to 13??
//	CAN_FilterLightControlMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_LightControlMessage.StdId=0;
//	CAN_Rx_LightControlMessage.ExtId=0;
//	CAN_Rx_LightControlMessage.RTR=0;
//	CAN_Rx_LightControlMessage.IDE=0;
//	CAN_Rx_LightControlMessage.DLC=0;
//	CAN_Rx_LightControlMessage.Data[0]=0;
//	CAN_Rx_LightControlMessage.Data[1]=0;
//	CAN_Rx_LightControlMessage.Data[2]=0;
//	CAN_Rx_LightControlMessage.Data[3]=0;
//	CAN_Rx_LightControlMessage.Data[4]=0;
//	CAN_Rx_LightControlMessage.Data[5]=0;
//	CAN_Rx_LightControlMessage.Data[6]=0;
//	CAN_Rx_LightControlMessage.Data[7]=0;
//	CAN_Rx_LightControlMessage.FMI=0;
//
//	CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_LightInitMessage);
//	CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_UltrasonicMessage);
//	CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_EncoderMessage);
//	CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_LightControlMessage);
//
///****************************** Motor ECU *********************************/
//	CanRxMsg CAN_Rx_MotorControlMessage;
//	CanRxMsg CAN_Rx_MotorInitMessage;
//
//	CAN_FilterInitTypeDef CAN_FilterMotorInitMessage;
//	CAN_FilterInitTypeDef CAN_FilterMotorControlMessage;
//
//	CAN_FilterMotorInitMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterMotorInitMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterMotorInitMessage.CAN_FilterIdHigh = 0x07F<<5;
//	CAN_FilterMotorInitMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterMotorInitMessage.CAN_FilterMaskIdHigh = 0x07F<<5;
//	CAN_FilterMotorInitMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterMotorInitMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterMotorInitMessage.CAN_FilterNumber = 0; // 0 to 13??
//	CAN_FilterMotorInitMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_MotorInitMessage.StdId=0;
//	CAN_Rx_MotorInitMessage.ExtId=0;
//	CAN_Rx_MotorInitMessage.RTR=0;
//	CAN_Rx_MotorInitMessage.IDE=0;
//	CAN_Rx_MotorInitMessage.DLC=0;
//	CAN_Rx_MotorInitMessage.Data[0]=0;
//	CAN_Rx_MotorInitMessage.Data[1]=0;
//	CAN_Rx_MotorInitMessage.Data[2]=0;
//	CAN_Rx_MotorInitMessage.Data[3]=0;
//	CAN_Rx_MotorInitMessage.Data[4]=0;
//	CAN_Rx_MotorInitMessage.Data[5]=0;
//	CAN_Rx_MotorInitMessage.Data[6]=0;
//	CAN_Rx_MotorInitMessage.Data[7]=0;
//	CAN_Rx_MotorInitMessage.FMI=0;
//
//	CAN_FilterMotorControlMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterMotorControlMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterMotorControlMessage.CAN_FilterIdHigh = 0x0FF<<5;
//	CAN_FilterMotorControlMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterMotorControlMessage.CAN_FilterMaskIdHigh = 0x0FF<<5;
//	CAN_FilterMotorControlMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterMotorControlMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterMotorControlMessage.CAN_FilterNumber = 1; // 0 to 13??
//	CAN_FilterMotorControlMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_MotorControlMessage.StdId=0;
//	CAN_Rx_MotorControlMessage.ExtId=0;
//	CAN_Rx_MotorControlMessage.RTR=0;
//	CAN_Rx_MotorControlMessage.IDE=0;
//	CAN_Rx_MotorControlMessage.DLC=0;
//	CAN_Rx_MotorControlMessage.Data[0]=0;
//	CAN_Rx_MotorControlMessage.Data[1]=0;
//	CAN_Rx_MotorControlMessage.Data[2]=0;
//	CAN_Rx_MotorControlMessage.Data[3]=0;
//	CAN_Rx_MotorControlMessage.Data[4]=0;
//	CAN_Rx_MotorControlMessage.Data[5]=0;
//	CAN_Rx_MotorControlMessage.Data[6]=0;
//	CAN_Rx_MotorControlMessage.Data[7]=0;
//	CAN_Rx_MotorControlMessage.FMI=0;
////seeb dool ll scheduler
//	CAN_Receive(CAN1, CAN_FIFO0, &CAN_Rx_MotorInitMessage);
//	CAN_Receive(CAN1, CAN_FIFO1, &CAN_Rx_MotorControlMessage);
///****************************** Sensor ECU *********************************/
//	typedef char u8;
//	CanTxMsg CAN_Tx_InitMessage;
//	CanTxMsg CAN_Tx_UltrasonicMessage;
//	CanTxMsg CAN_Tx_EncoderMessage;
//	CanTxMsg CAN_Tx_MotorControlMessage;
//	CanTxMsg CAN_Tx_LightControlMessage;
//	u8 UltrasonicReadings[6]={0};
//	u8 EncoderReading = 0;
//	u8 FrontLight=0;
//	u8 BackLight=0;
//	u8 MotorSignal=0;
//
//	CanRxMsg CAN_Rx_InitMessage;
//
//	CAN_FilterInitTypeDef CAN_FilterInitMessage;
//
//	CAN_FilterInitMessage.CAN_FilterActivation = ENABLE;
//	CAN_FilterInitMessage.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
//	CAN_FilterInitMessage.CAN_FilterIdHigh = 0x07F<<5;
//	CAN_FilterInitMessage.CAN_FilterIdLow = 0X0000;
//	CAN_FilterInitMessage.CAN_FilterMaskIdHigh = 0x07F<<5;
//	CAN_FilterInitMessage.CAN_FilterMaskIdLow = 0X0000;
//	CAN_FilterInitMessage.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterInitMessage.CAN_FilterNumber = 0; // 0 to 13??
//	CAN_FilterInitMessage.CAN_FilterScale = CAN_FilterScale_32bit;
//
//	CAN_Rx_InitMessage.StdId=0;
//	CAN_Rx_InitMessage.ExtId=0;
//	CAN_Rx_InitMessage.RTR=0;
//	CAN_Rx_InitMessage.IDE=0;
//	CAN_Rx_InitMessage.DLC=0;
//	CAN_Rx_InitMessage.Data[0]=0;
//	CAN_Rx_InitMessage.Data[1]=0;
//	CAN_Rx_InitMessage.Data[2]=0;
//	CAN_Rx_InitMessage.Data[3]=0;
//	CAN_Rx_InitMessage.Data[4]=0;
//	CAN_Rx_InitMessage.Data[5]=0;
//	CAN_Rx_InitMessage.Data[6]=0;
//	CAN_Rx_InitMessage.Data[7]=0;
//	CAN_Rx_InitMessage.FMI=0;
//
//	CAN_Tx_InitMessage.StdId = 0x07F;
//	CAN_Tx_InitMessage.ExtId = 0;
//	CAN_Tx_InitMessage.IDE = CAN_Id_Standard;
//	CAN_Tx_InitMessage.RTR = CAN_RTR_Data;
//	CAN_Tx_InitMessage.DLC = 1;
//	CAN_Tx_InitMessage.Data[0] = 0x00;
//	CAN_Tx_InitMessage.Data[1] = 0x00;
//	CAN_Tx_InitMessage.Data[2] = 0x00;
//	CAN_Tx_InitMessage.Data[3] = 0x00;
//	CAN_Tx_InitMessage.Data[4] = 0x00;
//	CAN_Tx_InitMessage.Data[5] = 0x00;
//	CAN_Tx_InitMessage.Data[6] = 0x00;
//	CAN_Tx_InitMessage.Data[7] = 0x00;
//
//	CAN_Tx_UltrasonicMessage.StdId = 0X1FF;
//	CAN_Tx_UltrasonicMessage.ExtId = 0;
//	CAN_Tx_UltrasonicMessage.IDE = CAN_Id_Standard;
//	CAN_Tx_UltrasonicMessage.RTR = CAN_RTR_Data;
//	CAN_Tx_UltrasonicMessage.DLC = 6;
//	CAN_Tx_UltrasonicMessage.Data[0] = UltrasonicReadings[0];
//	CAN_Tx_UltrasonicMessage.Data[1] = UltrasonicReadings[1];
//	CAN_Tx_UltrasonicMessage.Data[2] = UltrasonicReadings[2];
//	CAN_Tx_UltrasonicMessage.Data[3] = UltrasonicReadings[3];
//	CAN_Tx_UltrasonicMessage.Data[4] = UltrasonicReadings[4];
//	CAN_Tx_UltrasonicMessage.Data[5] = UltrasonicReadings[5];
//
//	CAN_Tx_EncoderMessage.StdId = 0X3FF;
//	CAN_Tx_EncoderMessage.ExtId = 0;
//	CAN_Tx_EncoderMessage.IDE = CAN_Id_Standard;
//	CAN_Tx_EncoderMessage.RTR = CAN_RTR_Data;
//	CAN_Tx_EncoderMessage.DLC = 1;
//	CAN_Tx_EncoderMessage.Data[0] =  EncoderReading;
//
//	CAN_Tx_LightControlMessage.StdId = 0X7FF;
//	CAN_Tx_LightControlMessage.ExtId = 0;
//	CAN_Tx_LightControlMessage.IDE = CAN_Id_Standard;
//	CAN_Tx_LightControlMessage.RTR = CAN_RTR_Data;
//	CAN_Tx_LightControlMessage.DLC = 2;
//	CAN_Tx_LightControlMessage.Data[0] =  FrontLight;
//	CAN_Tx_LightControlMessage.Data[1] =  BackLight;
//
//	CAN_Tx_MotorControlMessage.StdId = 0x0FF;
//	CAN_Tx_MotorControlMessage.ExtId = 0;
//	CAN_Tx_MotorControlMessage.IDE = CAN_Id_Standard;
//	CAN_Tx_MotorControlMessage.RTR = CAN_RTR_Data;
//	CAN_Tx_MotorControlMessage.DLC = 1;
//	CAN_Tx_MotorControlMessage.Data[0] = MotorSignal;
//
//
//	CAN_Transmit(CAN1, &CAN_Tx_InitMessage);
//	CAN_Transmit(CAN1, &CAN_Tx_UltrasonicMessage);
//	CAN_Transmit(CAN1, &CAN_Tx_EncoderMessage);
//	CAN_Transmit(CAN1, &CAN_Tx_MotorControlMessage);
//	CAN_Transmit(CAN1, &CAN_Tx_LightControlMessage);


//	void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
//	uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
//	void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);
//	void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
//	void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
//	uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);
//	uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode);
//	uint8_t CAN_Sleep(CAN_TypeDef* CANx);
//	uint8_t CAN_WakeUp(CAN_TypeDef* CANx);
}
void Runnable_TX1(void){
////	GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_SET);
//	char MailBoxNum= CAN_TxStatus_NoMailBox;
//	char status= CAN_TxStatus_Failed;
//	while((MailBoxNum == CAN_TxStatus_NoMailBox) || (status!=CAN_TxStatus_Ok)	){
//		MailBoxNum= CAN_Transmit(CAN1, &CAN_TestMessage);
//		if(MailBoxNum<=2){
//		status=CAN_TransmitStatus(CAN1,MailBoxNum);
//	}
//}

	while(!( CAN_MessagePending(CAN1, CAN_FIFO0)));

	CAN_Receive(CAN1, CAN_FIFO0, &CAN_TestMessageR);
	CAN_FIFORelease(CAN1, CAN_FIFO0);
	if(CAN_TestMessageR.StdId==0x455){
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_SET);
	}
}
void Runnable_TX2(void){
////	GPIO_WriteBit(GPIOA, GPIO_Pin_12,Bit_RESET);
//	CAN_Transmit(CAN1, &CAN_TestMessageTwo);

	while(!( CAN_MessagePending(CAN1, CAN_FIFO0)));
	CAN_Receive(CAN1, CAN_FIFO0, &CAN_TestMessageRD);
	CAN_FIFORelease(CAN1, CAN_FIFO0);
	if(CAN_TestMessageRD.StdId==0x7AB){
			GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_RESET);
		}
}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
