/*
 * DIO_Prog.c
 *
 *  Created on: Dec 9, 2022
 *      Author: Mostafa Ashraf
 */

#include "DIO_Int.h"

/*SET PIN Direction*/
void MDIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	if(Copy_u8Direction == Pin_Input)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : CLR_BIT(DDRA,Copy_u8Pin); break;
			case(Port_B) : CLR_BIT(DDRB,Copy_u8Pin); break;
			case(Port_C) : CLR_BIT(DDRC,Copy_u8Pin); break;
			case(Port_D) : CLR_BIT(DDRD,Copy_u8Pin); break;
		}
	}
	else if(Copy_u8Direction == Pin_Output)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : SET_BIT(DDRA,Copy_u8Pin); break;
			case(Port_B) : SET_BIT(DDRB,Copy_u8Pin); break;
			case(Port_C) : SET_BIT(DDRC,Copy_u8Pin); break;
			case(Port_D) : SET_BIT(DDRD,Copy_u8Pin); break;
		}
	}
}

/*Internal Pull_Up Init*/
void MDIO_VidInternalPinBullUp(u8 Copy_u8Port, u8 Copy_u8Pin)						/*INTERNAL PIN PULL UP*/
{
	switch(Copy_u8Port)
	{
		case(Port_A) : SET_BIT(DDRA,Copy_u8Pin); break;
		case(Port_B) : SET_BIT(DDRB,Copy_u8Pin); break;
		case(Port_C) : SET_BIT(DDRC,Copy_u8Pin); break;
		case(Port_D) : SET_BIT(DDRD,Copy_u8Pin); break;
	}
	switch(Copy_u8Port) /*Enable Internal Pull_Up*/
	{
		case(Port_A) : SET_BIT(PORTA,Copy_u8Pin); break;
		case(Port_B) : SET_BIT(PORTB,Copy_u8Pin); break;
		case(Port_C) : SET_BIT(PORTC,Copy_u8Pin); break;
		case(Port_D) : SET_BIT(PORTD,Copy_u8Pin); break;
	}
}

/*SET PIN Value*/
void MDIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	if(Copy_u8Value == Pin_High)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : SET_BIT(PORTA,Copy_u8Pin); break;
			case(Port_B) : SET_BIT(PORTB,Copy_u8Pin); break;
			case(Port_C) : SET_BIT(PORTC,Copy_u8Pin); break;
			case(Port_D) : SET_BIT(PORTD,Copy_u8Pin); break;
		}
	}
	else if(Copy_u8Value == Pin_Low)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : CLR_BIT(PORTA,Copy_u8Pin); break;
			case(Port_B) : CLR_BIT(PORTB,Copy_u8Pin); break;
			case(Port_C) : CLR_BIT(PORTC,Copy_u8Pin); break;
			case(Port_D) : CLR_BIT(PORTD,Copy_u8Pin); break;
		}
	}
}

/*TOGGLE PIN Value*/
void MDIO_VidTogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : TOGGLE_BIT(PORTA,Copy_u8Pin); break;
		case(Port_B) : TOGGLE_BIT(PORTB,Copy_u8Pin); break;
		case(Port_C) : TOGGLE_BIT(PORTC,Copy_u8Pin); break;
		case(Port_D) : TOGGLE_BIT(PORTD,Copy_u8Pin); break;
	}
}

/*Get PIN Value*/
void MDIO_VidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8Pin_Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : *Copy_Pu8Pin_Value = GET_BIT(PINA,Copy_u8Pin); break;
		case(Port_B) : *Copy_Pu8Pin_Value = GET_BIT(PINB,Copy_u8Pin); break;
		case(Port_C) : *Copy_Pu8Pin_Value = GET_BIT(PINC,Copy_u8Pin); break;
		case(Port_D) : *Copy_Pu8Pin_Value = GET_BIT(PIND,Copy_u8Pin); break;
	}
}

/*PORT Control*/
void MDIO_VidSetWholePortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)	/*SET PORT Direction*/
{
	if(Copy_u8Direction == Pin_Input)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : DDRA &= 0x00; break;
			case(Port_B) : DDRB &= 0x00; break;
			case(Port_C) : DDRC &= 0x00; break;
			case(Port_D) : DDRD &= 0x00; break;
		}
	}
	else if(Copy_u8Direction == Pin_Output)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : DDRA |= 0xff; break;
			case(Port_B) : DDRB |= 0xff; break;
			case(Port_C) : DDRC |= 0xff; break;
			case(Port_D) : DDRD |= 0xff; break;
		}
	}
}

void MDIO_VidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : DDRA = Copy_u8Value; break;
		case(Port_B) : DDRB = Copy_u8Value; break;
		case(Port_C) : DDRC = Copy_u8Value; break;
		case(Port_D) : DDRD = Copy_u8Value; break;
	}
}

/*PORT PULL_UP Init*/
void MDIO_VidInternalPortBullUp(u8 Copy_u8Port)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : DDRA |= 0xff; break;
		case(Port_B) : DDRB |= 0xff; break;
		case(Port_C) : DDRC |= 0xff; break;
		case(Port_D) : DDRD |= 0xff; break;
	}
	switch(Copy_u8Port)
	{
		case(Port_A) : PORTA = 0xff; break;
		case(Port_B) : PORTB = 0xff; break;
		case(Port_C) : PORTC = 0xff; break;
		case(Port_D) : PORTD = 0xff; break;
	}
}

/*SET PORT Value*/
void MDIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : PORTA = Copy_u8Value; break;
		case(Port_B) : PORTB = Copy_u8Value; break;
		case(Port_C) : PORTC = Copy_u8Value; break;
		case(Port_D) : PORTD = Copy_u8Value; break;
	}
}

/*SET PORT Value*/
void MDIO_VidEditPortValue(u8 Copy_u8Port, u8 Copy_u8Pins, u8 Copy_u8Value)
{
	if(Copy_u8Pins == Pin_High)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : PORTA &= 0x0F; PORTA |= (Copy_u8Value&0xF0); break;
			case(Port_B) : PORTB &= 0x0F; PORTB |= (Copy_u8Value&0xF0); break;
			case(Port_C) : PORTC &= 0x0F; PORTC |= (Copy_u8Value&0xF0); break;
			case(Port_D) : PORTD &= 0x0F; PORTD |= (Copy_u8Value&0xF0); break;
		}
	}
	else if (Copy_u8Pins == Pin_Low)
	{
		switch(Copy_u8Port)
		{
			case(Port_A) : PORTA &= 0xF0; PORTA |= Copy_u8Value&0X0F; break;
			case(Port_B) : PORTB &= 0xF0; PORTB |= Copy_u8Value&0X0F; break;
			case(Port_C) : PORTC &= 0xF0; PORTC |= Copy_u8Value&0X0F; break;
			case(Port_D) : PORTD &= 0xF0; PORTD |= Copy_u8Value&0X0F; break;
		}
	}
}

/*Toggle PORT Value*/
void MDIO_VidTogglePortValue(u8 Copy_u8Port)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : PORTA ^= 0xff; break;
		case(Port_B) : PORTB ^= 0xff; break;
		case(Port_C) : PORTC ^= 0xff; break;
		case(Port_D) : PORTD ^= 0xff; break;
	}
}

/*Get PORT Value*/
void MDIO_VidGetPortValue(u8 Copy_u8Port, u8 *Copy_u8Port_Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A) : *Copy_u8Port_Value = PINA; break;
		case(Port_B) : *Copy_u8Port_Value = PINB; break;
		case(Port_C) : *Copy_u8Port_Value = PINC; break;
		case(Port_D) : *Copy_u8Port_Value = PIND; break;
	}
}
/*Global Interrupt Enable*/
void MDIO_VidGlobalInterruptEnable(void)
{
	SET_BIT(SREG,SREG_I);
}
