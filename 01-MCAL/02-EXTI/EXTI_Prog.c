/*
 * EXTI_Prog.c
 *
 *  Created on: Dec 9, 2022
 *      Author: Mostafa Ashraf
 */

#include  "EXTI_Int.h"

/*Interrupt Init*/
void MExternal_Interrupt_VidInit(u8 Copy_u8Interrupt,u8 Copy_u8Mode)
{
	switch(Copy_u8Interrupt)
	{
		case(Interrupt_0):
		switch(Copy_u8Mode)
		{
			case(Low_Level) : CLR_BIT(MCUCR,MCUCR_ISC01);
							  CLR_BIT(MCUCR,MCUCR_ISC00);
							  SET_BIT(GICR,GICR_INT0); break;

			case(On_Change) : SET_BIT(MCUCR,MCUCR_ISC00);
							  CLR_BIT(MCUCR,MCUCR_ISC01);
							  SET_BIT(GICR,GICR_INT0); break;

			case(Falling_Edge) : CLR_BIT(MCUCR,MCUCR_ISC00);
								 SET_BIT(MCUCR,MCUCR_ISC01);
								 SET_BIT(GICR,GICR_INT0); break;

			case(Rising_Edge) : SET_BIT(MCUCR,MCUCR_ISC01);
								SET_BIT(MCUCR,MCUCR_ISC00);
								SET_BIT(GICR,GICR_INT0); break;

			case(Disable) : CLR_BIT(GICR,GICR_INT0); break;

			case(Enable) : SET_BIT(GICR,GICR_INT0); break;

			default : CLR_BIT(GICR,GICR_INT0); break;
		} break;
		case(Interrupt_1):
		switch(Copy_u8Mode)
		{
			case(Low_Level) : CLR_BIT(MCUCR,MCUCR_ISC11);
							  CLR_BIT(MCUCR,MCUCR_ISC10);
							  SET_BIT(GICR,GICR_INT1); break;

			case(On_Change)	: SET_BIT(MCUCR,MCUCR_ISC10);
							  CLR_BIT(MCUCR,MCUCR_ISC11);
							  SET_BIT(GICR,GICR_INT1); break;

			case(Falling_Edge) : CLR_BIT(MCUCR,MCUCR_ISC10);
								 SET_BIT(MCUCR,MCUCR_ISC11);
								 SET_BIT(GICR,GICR_INT1); break;

			case(Rising_Edge) : SET_BIT(MCUCR,MCUCR_ISC10);
								SET_BIT(MCUCR,MCUCR_ISC11);
								SET_BIT(GICR,GICR_INT1); break;

			case(Disable):CLR_BIT(GICR,GICR_INT1); break;

			case(Enable):SET_BIT(GICR,GICR_INT1); break;

			default:CLR_BIT(GICR,GICR_INT1); break;
		} break;
		case(Interrupt_2):
		switch(Copy_u8Mode)
		{
			case(Falling_Edge) : CLR_BIT(MCUCSR,MCUCSR_ISC2);
								 SET_BIT(GICR,GICR_INT2); break;

			case(Rising_Edge) : SET_BIT(MCUCSR,MCUCR_ISC00);
								SET_BIT(GICR,GICR_INT2); break;

			case(Disable) : CLR_BIT(GICR,GICR_INT2); break;

			case(Enable) : SET_BIT(GICR,GICR_INT2); break;

			default : CLR_BIT(GICR,GICR_INT2); break;
		} break;
		default:CLR_BIT(GICR,GICR_INT0);
				CLR_BIT(GICR,GICR_INT1);
				CLR_BIT(GICR,GICR_INT2); break;
	}
}

/*ISR Interrupt_0*/
static void (*External_Interrupt_0_Function)(void)=0;
void MExternal_Interrupt0(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		External_Interrupt_0_Function = Copy_VidInturrept;
	}
}
void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
	if(External_Interrupt_0_Function!=0)
	{
		MExternal_Interrupt_VidInit(Interrupt_0,Disable);
		External_Interrupt_0_Function();
		MExternal_Interrupt_VidInit(Interrupt_0,Enable);
	}
}
/*ISR Interrupt_1*/
static void (*External_Interrupt_1_Function)(void)=0;
void MExternal_Interrupt1(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		External_Interrupt_1_Function = Copy_VidInturrept;
	}
}
void __vector_2(void) __attribute__((signal,used));
void __vector_2(void)
{
	if(External_Interrupt_1_Function!=0)
	{
		MExternal_Interrupt_VidInit(Interrupt_1,Disable);
		External_Interrupt_1_Function();
		MExternal_Interrupt_VidInit(Interrupt_1,Enable);
	}
}
/*ISR Interrupt_2*/
static void (*External_Interrupt_2_Function)(void)=0;
void MExternal_Interrupt2(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		External_Interrupt_2_Function = Copy_VidInturrept;
	}
}
void __vector_3(void) __attribute__((signal,used));
void __vector_3(void)
{
	if(External_Interrupt_2_Function != 0)
	{
		MExternal_Interrupt_VidInit(Interrupt_2,Disable);
		External_Interrupt_2_Function();
		MExternal_Interrupt_VidInit(Interrupt_2,Enable);
	}
}
