/*
 * LED_Prog.c
 *
 *  Created on: Dec 11, 2022
 *      Author: Mostafa Ashraf
 */

#include "LED_Int.h"

u8 Global_u8CarState=GREEN;
u8 Global_u8ToggleFlag=False;
u8 Global_u8InterruptFlag=False;

/*LED Init*/
void HLED_VidInit(void)
{
	MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_High);
	MDIO_VidSetPinDirection(CAR_Port, CAR_RED, Pin_Output);
	MDIO_VidSetPinDirection(CAR_Port, CAR_GRN, Pin_Output);
	MDIO_VidSetPinDirection(CAR_Port, CAR_YEL, Pin_Output);
	MDIO_VidSetPinDirection(PT_Port, PT_RED, Pin_Output);
	MDIO_VidSetPinDirection(PT_Port, PT_GRN, Pin_Output);
	MDIO_VidSetPinDirection(PT_Port, PT_YEL, Pin_Output);
}

/* Toggle LED_Yellow */
void HPrivate_VidToggleLed(u32 Copy_u32Delay)
{
	u32 Local_u8Flag=False;
	MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_Low);
	MDIO_VidSetPinValue(PT_Port, PT_YEL, Pin_Low);
	for(Local_u8Flag=Copy_u32Delay/500;Local_u8Flag;Local_u8Flag--)
	{
		MTimer2_VidBusyWait_ms(500);
		if(Global_u8ToggleFlag)MDIO_VidTogglePinValue(PT_Port,PT_YEL);
		MDIO_VidTogglePinValue(CAR_Port,CAR_YEL);
		if(Global_u8InterruptFlag)
		{
			Global_u8CarState=GREEN;
			Global_u8InterruptFlag=False;
			break;
		}
	}
	MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_Low);
	MDIO_VidSetPinValue(PT_Port, PT_YEL, Pin_Low);
}
/* Pedestrian Mode */
void HLED_VidPedestrianMode()
{
	u8 Local_u8Flag=False;
	MTimer2_VidBusyWait_ms(1000);
	MDIO_VidGetPinValue(Port_D, Pin_2,&Local_u8Flag);
	if(Local_u8Flag)
	{
		if(Global_u8CarState==DEFAULT)
		{
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_High);
			MTimer2_VidBusyWait_ms(5000);
			MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_Low);
			Global_u8ToggleFlag=True;
			HPrivate_VidToggleLed(5000);
			Global_u8ToggleFlag=False;
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_High);
			Global_u8InterruptFlag=True;

		}
		else if(Global_u8CarState==YELLOW)
		{
			MDIO_VidSetPinValue(CAR_Port, CAR_GRN, Pin_Low);
			Global_u8ToggleFlag=True;
			HPrivate_VidToggleLed(5000);
			Global_u8ToggleFlag=False;
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_High);
			MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_High);
			MTimer2_VidBusyWait_ms(5000);
			MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_Low);
			Global_u8ToggleFlag=True;
			HPrivate_VidToggleLed(5000);
			Global_u8ToggleFlag=False;
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_High);
			Global_u8InterruptFlag=True;
		}
		else
		{
			Global_u8ToggleFlag=True;
			HPrivate_VidToggleLed(5000);
			Global_u8ToggleFlag=False;
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_High);
			MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_High);
			MTimer2_VidBusyWait_ms(5000);
			MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_Low);
			Global_u8ToggleFlag=True;
			HPrivate_VidToggleLed(5000);
			Global_u8ToggleFlag=False;
			MDIO_VidSetPinValue(PT_Port, PT_GRN, Pin_Low);
			MDIO_VidSetPinValue(PT_Port, PT_RED, Pin_High);
			Global_u8InterruptFlag=True;
		}
	}
}

/* Normal_Mode */
void HLED_VidNormalMode()
{
	switch(Global_u8CarState)
	{
		case GREEN:
		Global_u8CarState=YELLOW;
		MDIO_VidSetPinValue(CAR_Port, CAR_GRN, Pin_High);
		MTimer2_VidBusyWait_ms(5000);
		MDIO_VidSetPinValue(CAR_Port, CAR_GRN, Pin_Low);
		break;
		case YELLOW:
		Global_u8CarState=RED;
		MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_High);
		HPrivate_VidToggleLed(5000);
		MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_Low);
		break;
		case RED:
		Global_u8CarState=DEFAULT;
		MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_High);
		MTimer2_VidBusyWait_ms(5000);
		MDIO_VidSetPinValue(CAR_Port, CAR_RED, Pin_Low);
		break;
		default:
		Global_u8CarState=GREEN;
		MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_High);
		HPrivate_VidToggleLed(5000);
		MDIO_VidSetPinValue(CAR_Port, CAR_YEL, Pin_Low);
		break;
	}
}

