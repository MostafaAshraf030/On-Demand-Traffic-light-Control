/*
 * EXTI_Private.h
 *
 *  Created on: Dec 9, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

enum
{
	Interrupt_0,
	Interrupt_1,
	Interrupt_2
}	External_Interrupt;

enum
{
	Low_Level,
	On_Change,
	Falling_Edge,
	Rising_Edge,
	Enable,
	Disable
}	Interrupt_Mode;

/*REG*/
#define   GIFR    *((volatile u8*)0x5A)
#define   GICR    *((volatile u8*)0x5B)
#define   MCUCR   *((volatile u8*)0x55)
#define   MCUCSR  *((volatile u8*)0x54)

/*MCUCR bits*/
#define   MCUCR_ISC00      0
#define   MCUCR_ISC01      1
#define   MCUCR_ISC10      2
#define   MCUCR_ISC11      3

/*MCUCSR bits*/
#define   MCUCSR_ISC2      6

/*GICR bits*/
#define   GICR_INT0		6
#define   GICR_INT1		7
#define   GICR_INT2		5

/*GIFR bits*/
#define   GIFR_INT0		6
#define   GIFR_INT1		7
#define   GIFR_INT2		5

#endif /* EXTI_PRIVATE_H_ */
