/*
 * DIO_Int.h
 *
 *  Created on: Dec 9, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

/*Include*/
#include "../../00-Lib/BIT_Math.h"
#include "../../00-Lib/STD_Types.h"
#include "DIO_Private.h"
/*Pin Control*/
void MDIO_VidInternalPinBullUp(u8 Copy_u8Port,u8 Copy_u8Pin);							
void MDIO_VidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Direction);		
void MDIO_VidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);				
void MDIO_VidTogglePinValue(u8 Copy_u8Port,u8 Copy_u8Pin);								
void MDIO_VidGetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 *Copy_Pu8Pin_Value);			
/*Port Control*/
void MDIO_VidInternalPortBullUp(u8 Copy_u8Port);										
void MDIO_VidSetWholePortDirection(u8 Copy_u8Port,u8 Copy_u8Direction);				
void MDIO_VidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8Direction);						
void MDIO_VidSetPortValue(u8 Copy_u8Port,u8 Copy_u8Value);								
void MDIO_VidTogglePortValue(u8 Copy_u8Port);											
void MDIO_VidGetPortValue(u8 Copy_u8Port,u8 *Copy_Pu8Port_Value);						
void MDIO_VidEditPortValue(u8 Copy_u8Port,u8 Copy_u8Pins,u8 Copy_u8Value);				
/*Global Interrupt*/
void MDIO_VidGlobalInterruptEnable(void);

#endif /* DIO_INT_H_ */
