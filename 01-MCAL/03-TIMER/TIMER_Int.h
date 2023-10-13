/*
 * TIMER_Int.h
 *
 *  Created on: Dec 10, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#include  "../../00-Lib/BIT_Math.h"
#include  "../../00-Lib/STD_Types.h"
#include  "TIMER_Config.h"
#include  "TIMER_Private.h"
/* Global Variables */
u32 Global_Timer0_u16Flag;
u32 Global_Timer2_u16Flag;

/**********************Timer 0**************************/
void MTimer0_VidInit(u8 Copy_u8Mode,u8 Copy_u8OCR_Value,u8 Copy_u8Compare_Match_Interrupt,u8 Copy_u8Over_Flow_Interrupt,u8 Copy_u8Pre_Scalar);
void MTimer0_VidBusyWait_ms(u32 Copy_u32Delay);
void MTimer0_VidDelay_ms(u32 Copy_u32Delay,void (*Copy_VidDelay_Func)(void));
void MTimer0_VidCompareMatchInturrept(void(*Copy_VidInturrept)(void));
void MTimer0_VidOverflowInturrept(void(*Copy_VidInturrept)(void));

/***********************Timer 2*************************/
void MTimer2_VidInit(u8 Copy_u8Mode,u8 Copy_u8OCR_Value,u8 Copy_u8Compare_Match_Interrupt,u8 Copy_u8Over_Flow_Interrupt,u8 Copy_u8Pre_Scalar);
void MTimer2_VidBusyWait_ms(u32 Copy_u32Delay);
void MTimer2_VidDelay_ms(u32 Copy_u32Delay,void (*Copy_VidDelay_Func)(void));
void MTimer2_VidCompareMatchInturrept(void(*Copy_VidInturrept)(void));
void MTimer2_VidOverflowInturrept(void(*Copy_VidInturrept)(void));

void MTimer_VidPWMDutyCycle(u8 Copy_u8Timer,u8 Copy_u8Duty_Cycle);

#endif /* TIMER_INT_H_ */
