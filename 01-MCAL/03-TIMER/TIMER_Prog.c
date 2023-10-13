/*
 * TIMER_Prog.c
 *
 *  Created on: Dec 10, 2022
 *      Author: Mostafa Ashraf
 */


#include  "TIMER_Int.h"

/*Timer 0*/
void MTimer0_VidBusyWait_ms(u32 Copy_u32Delay)
{
	f32 Local_f32Tick_Time=(1024.0/CPU_Freq)*1000;
	u32 Local_u32Total_Ticks=Copy_u32Delay/Local_f32Tick_Time;
	if (Local_u32Total_Ticks<=255)
	{
		MTimer0_VidInit(CTC,Local_u32Total_Ticks,Disable_CM,Disable_OF,Pre_Scalar_1024);
		while(!GET_BIT(TIFR,TIFR_OCF0));
		SET_BIT(TIFR,TIFR_OCF0);
	}
	else
	{
		Global_Timer0_u16Flag=(Local_u32Total_Ticks/255)+1;
		MTimer0_VidInit(Normal,255-((Local_u32Total_Ticks%255)*255),Disable_CM,Disable_OF,Pre_Scalar_1024);
		while(Global_Timer0_u16Flag)
		{
			if(GET_BIT(TIFR,TIFR_TOV0))
			{
				Global_Timer0_u16Flag--;
				SET_BIT(TIFR,TIFR_TOV0);
			}
		}
	}
}
void MTimer0_VidDelay_ms(u32 Copy_u32Delay,void (*Copy_VidDelay_Func)(void))
{
	f32 Local_f32Tic_Time=(1024.0/CPU_Freq)*1000;
	u32 Local_u32Total_Ticks=Copy_u32Delay/Local_f32Tic_Time;
	if (Local_u32Total_Ticks<=255)
	{
		MTimer0_VidInit(CTC,Local_u32Total_Ticks,Enable_CM,Disable_OF,Pre_Scalar_1024);
		MTimer0_VidCompareMatchInturrept(Copy_VidDelay_Func);
	}
	else
	{
		Global_Timer0_u16Flag=(Local_u32Total_Ticks/255)+1;
		MTimer0_VidInit(Normal,255-((Local_u32Total_Ticks%255)*255),Disable_CM,Enable_OF,Pre_Scalar_1024);
		MTimer0_VidOverflowInturrept(Copy_VidDelay_Func);
	}
}

void MTimer0_VidInit(u8 Copy_u8Mode,u8 Copy_u8OCR_Value,u8 Copy_u8Compare_Match_Interrupt,u8 Copy_u8Over_Flow_Interrupt,u8 Copy_u8Pre_Scalar)
{
	switch(Copy_u8Mode)
	{
		case(Normal) : CLR_BIT(TCCR0,TCCR0_WGM00);
					   CLR_BIT(TCCR0,TCCR0_WGM01);
					   OCR0 = Copy_u8OCR_Value; break;
					   
		case(CTC) : CLR_BIT(TCCR0,TCCR0_WGM00);
					SET_BIT(TCCR0,TCCR0_WGM01);
					OCR0 = Copy_u8OCR_Value; break;
					
		case(PWM_Phase_Correct) : SET_BIT(TCCR0,TCCR0_WGM00);
								  CLR_BIT(TCCR0,TCCR0_WGM01); break;
								  
		case(Fast_PWM) : SET_BIT(TCCR0,TCCR0_WGM00);
						 SET_BIT(TCCR0,TCCR0_WGM01); break;
						 
		default : CLR_BIT(TCCR0,TCCR0_WGM00);
				  CLR_BIT(TCCR0,TCCR0_WGM01);
	}
	switch(Copy_u8Compare_Match_Interrupt)
	{
		case(Enable_CM) : SET_BIT(TIMSK,TIMSK_OCIE0); break;
		
		case(Disable_CM) : CLR_BIT(TIMSK,TIMSK_OCIE0); break;
		
		default : SET_BIT(TIMSK,TIMSK_OCIE0);
	}
	switch(Copy_u8Over_Flow_Interrupt)
	{
		case(Enable_OF) : SET_BIT(TIMSK,TIMSK_TOIE0); break;
		
		case(Disable_OF) : CLR_BIT(TIMSK,TIMSK_TOIE0); break;
		
		default : SET_BIT(TIMSK,TIMSK_TOIE0);
	}

	if((Copy_u8Mode==PWM_Phase_Correct) || (Copy_u8Mode==Fast_PWM))
	{
		#if	PWM_Mode == COCSOB
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		#elif PWM_Mode == COBSOC
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		#else
		#warning (" Wrong Configuration !!")
		#endif
	}
	switch(Copy_u8Pre_Scalar)
	{
		case(Pre_Scalar_0) : SET_BIT(TCCR0 , TCCR0_CS00);
							 CLR_BIT(TCCR0 , TCCR0_CS01);
							 CLR_BIT(TCCR0 , TCCR0_CS02); break;
		
		case(Pre_Scalar_8) : CLR_BIT(TCCR0 , TCCR0_CS00);
							 SET_BIT(TCCR0 , TCCR0_CS01);
							 CLR_BIT(TCCR0 , TCCR0_CS02); break;
							 
		case(Pre_Scalar_64) : SET_BIT(TCCR0 , TCCR0_CS00);
							  SET_BIT(TCCR0 , TCCR0_CS01);
							  CLR_BIT(TCCR0 , TCCR0_CS02); break;
							  
		case(Pre_Scalar_256) : CLR_BIT(TCCR0 , TCCR0_CS00);
							   CLR_BIT(TCCR0 , TCCR0_CS01);
							   SET_BIT(TCCR0 , TCCR0_CS02); break;
							   
		case(Pre_Scalar_1024) : SET_BIT(TCCR0 , TCCR0_CS00);
								CLR_BIT(TCCR0 , TCCR0_CS01);
								SET_BIT(TCCR0 , TCCR0_CS02); break;
								
		default : CLR_BIT(TCCR0 , TCCR0_CS00);
				  CLR_BIT(TCCR0 , TCCR0_CS01);
				  CLR_BIT(TCCR0 , TCCR0_CS02);
	}
}

/**********************Timer 2**************************/
void MTimer2_VidDelay_ms(u32 Copy_u32Delay,void (*Copy_VidDelay_Func)(void))
{
	f32 Local_f32Tick_Time=(1024.0/CPU_Freq)*1000;
	u32 Local_u32Total_Ticks=Copy_u32Delay/Local_f32Tick_Time;
	if (Local_u32Total_Ticks<=255)
	{
		MTimer2_VidInit(CTC,Local_u32Total_Ticks,Enable_CM,Disable_OF,Pre_Scalar_1024);
		MTimer2_VidCompareMatchInturrept(Copy_VidDelay_Func);
	}
	else
	{
		Global_Timer2_u16Flag=(Local_u32Total_Ticks/255)+1;
		MTimer2_VidInit(Normal,255-((Local_u32Total_Ticks%255)*255),Disable_CM,Enable_OF,Pre_Scalar_1024);
		MTimer2_VidOverflowInturrept(Copy_VidDelay_Func);
	}
}
void MTimer2_VidBusyWait_ms(u32 Copy_u32Delay)
{
	f32 Local_f32Tic_Time=(1024.0/CPU_Freq)*1000;
	u32 Local_u32Total_Tics=Copy_u32Delay/Local_f32Tic_Time;
	if (Local_u32Total_Tics<=255)
	{
		MTimer2_VidInit(CTC,Local_u32Total_Tics,Disable_CM,Disable_OF,Pre_Scalar_1024);
		while(!GET_BIT(TIFR,TIFR_OCF2));
		SET_BIT(TIFR,TIFR_OCF2);
	}
	else
	{
		Global_Timer2_u16Flag=(Local_u32Total_Tics/255)+1;
		MTimer2_VidInit(Normal,255-((Local_u32Total_Tics%255)*255),Disable_CM,Disable_OF,Pre_Scalar_1024);
		while(Global_Timer2_u16Flag)
		{
			if(GET_BIT(TIFR,TIFR_TOV2))
			{
				Global_Timer2_u16Flag--;
				SET_BIT(TIFR,TIFR_TOV2);
			}
		}
	}

}

void MTimer2_VidInit (u8 Copy_u8Mode,u8 Copy_u8OCR_Value,u8 Copy_u8Compare_Match_Interrupt,u8 Copy_u8Over_Flow_Interrupt,u8 Copy_u8Pre_Scalar)
{
	switch(Copy_u8Mode)
	{
		case(Normal) : CLR_BIT(TCCR2,TCCR2_WGM21);
					   CLR_BIT(TCCR2,TCCR2_WGM20);
					   OCR2 = Copy_u8OCR_Value; break;
					   
		case(CTC) : CLR_BIT(TCCR2,TCCR2_WGM21);
					SET_BIT(TCCR2,TCCR2_WGM20);
					OCR2=Copy_u8OCR_Value; break;
					
		case(PWM_Phase_Correct) : SET_BIT(TCCR2,TCCR2_WGM21);
								  CLR_BIT(TCCR2,TCCR2_WGM20); break;
								  
		case(Fast_PWM) : SET_BIT(TCCR2,TCCR2_WGM21);
						 SET_BIT(TCCR2,TCCR2_WGM20); break;
						 
		default : CLR_BIT(TCCR2,TCCR2_WGM21);
				  CLR_BIT(TCCR2,TCCR2_WGM20);
	}
	switch(Copy_u8Compare_Match_Interrupt)
	{
		case(Enable_CM) : SET_BIT(TIMSK,TIMSK_OCIE2); break;
		
		case(Disable_CM) : CLR_BIT(TIMSK,TIMSK_OCIE2); break;
		
		default : CLR_BIT(TIMSK,TIMSK_OCIE2);
	}
	switch(Copy_u8Over_Flow_Interrupt)
	{
		case(Enable_OF) : SET_BIT(TIMSK,TIMSK_TOIE2); break;
		
		case(Disable_OF) : CLR_BIT(TIMSK,TIMSK_TOIE2); break;
		
		default : CLR_BIT(TIMSK,TIMSK_TOIE2);
	}
	if((Copy_u8Mode==PWM_Phase_Correct)||(Copy_u8Mode==Fast_PWM))
	{
		#if	PWM_Mode == COCSOB
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		#elif PWM_Mode == COBSOC
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		#else
		#warning (" Wrong Configuration !!")
		#endif
	}
	switch(Copy_u8Pre_Scalar)
	{
		case(Pre_Scalar_0) : CLR_BIT(TCCR2,TCCR2_CS22);
							 CLR_BIT(TCCR2,TCCR2_CS21);
							 SET_BIT(TCCR2,TCCR2_CS20); break;
							 
		case(Pre_Scalar_8) : CLR_BIT(TCCR2,TCCR2_CS22);
							 SET_BIT(TCCR2,TCCR2_CS21);
							 CLR_BIT(TCCR2,TCCR2_CS20);	break;
							 
		case(Pre_Scalar_32) : CLR_BIT(TCCR2,TCCR2_CS22);
							  SET_BIT(TCCR2,TCCR2_CS21);
							  SET_BIT(TCCR2,TCCR2_CS20); break;
							  
		case(Pre_Scalar_64) : SET_BIT(TCCR2,TCCR2_CS22);
							  CLR_BIT(TCCR2,TCCR2_CS21);
							  CLR_BIT(TCCR2,TCCR2_CS20); break;
							  
		case(Pre_Scalar_256) : SET_BIT(TCCR2,TCCR2_CS22);
							   SET_BIT(TCCR2,TCCR2_CS21);
							   CLR_BIT(TCCR2,TCCR2_CS20); break;
							   
		case(Pre_Scalar_1024) : SET_BIT(TCCR2,TCCR2_CS22);
								SET_BIT(TCCR2,TCCR2_CS21);
								SET_BIT(TCCR2,TCCR2_CS20); break;
								
		default : CLR_BIT(TCCR2,TCCR2_CS22);
				  CLR_BIT(TCCR2,TCCR2_CS21);
				  CLR_BIT(TCCR2,TCCR2_CS20);
	}
}

void MTimer_VidPWMDutyCycle(u8 Copy_u8Timer,u8 Copy_u8Duty_Cycle)
{
	u8 Local_u8Variable=((Copy_u8Duty_Cycle*255ul)/100ul);
	switch(Copy_u8Timer)
	{
		case(Timer_0):OCR0=Local_u8Variable;break;
		case(Timer_1):OCR1AL=Local_u8Variable;OCR1BL=Local_u8Variable;break;
		case(Timer_2):OCR2=Local_u8Variable;break;
	}
}

/******************* Timer0 Overflow_ISR ***********************/
static void (*Timer0_OverflowInturreptFunc)(void)=0;
void Timer_0_VidOverflow_Inturrept(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		Timer0_OverflowInturreptFunc = Copy_VidInturrept;
	}
}
void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	Global_Timer0_u16Flag--;
	if(Timer0_OverflowInturreptFunc!=0 && !Global_Timer0_u16Flag)
	{
		MTimer0_VidInit(Normal,0,Disable_CM,Disable_OF,0);
		Timer0_OverflowInturreptFunc();
	}
}

/***************************** CompareMatch_ISR **********************/
static void (*Timer0_CompareMatchInturreptFunc)(void)=0;
void Timer_0_VidCompare_Match_Inturrept(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		Timer0_CompareMatchInturreptFunc = Copy_VidInturrept;
	}
}
void __vector_10(void) __attribute__((signal,used));
void __vector_10(void)
{
	if(Timer0_CompareMatchInturreptFunc!=0)
	{
		MTimer0_VidInit(Normal,0,Disable_CM,Disable_OF,0);
		Timer0_CompareMatchInturreptFunc();
	}
}

/********************* Timer 2 Overflow_ISR *********************/
static void (*Timer2_OverflowInturreptFunc)(void)=0;
void Timer_2_VidOverflow_Inturrept(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		Timer2_OverflowInturreptFunc = Copy_VidInturrept;
	}
}
void __vector_5(void) __attribute__((signal,used));
void __vector_5(void)
{
	Global_Timer2_u16Flag--;
	if(Timer2_OverflowInturreptFunc!=0 && !Global_Timer2_u16Flag)
	{
		MTimer2_VidInit(Normal,0,Disable_CM,Disable_OF,0);
	}
}
/***************************** CompareMatch_ISR **********************/
static void (*Timer2_CompareMatchInturreptFunc)(void)=0;
void Timer_2_VidCompare_Match_Inturrept(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=0)
	{
		Timer2_CompareMatchInturreptFunc = Copy_VidInturrept;
	}
}
void __vector_4(void) __attribute__((signal,used));
void __vector_4(void)
{
	if(Timer2_CompareMatchInturreptFunc!=0)
	{
		Timer2_CompareMatchInturreptFunc();
		MTimer2_VidInit(Normal,0,Disable_CM,Disable_OF,0);
	}
}


