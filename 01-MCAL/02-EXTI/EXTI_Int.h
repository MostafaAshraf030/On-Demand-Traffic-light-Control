/*
 * EXTI_Int.h
 *
 *  Created on: Dec 9, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_

#include  "../../00-Lib/BIT_Math.h"
#include  "../../00-Lib/STD_Types.h"
#include  "EXTI_Int.h"
#include  "EXTI_Private.h"

/*External Interrupt Enable */
void MExternal_Interrupt_VidInit(u8 Copy_u8Interrupt,u8 Copy_u8Mode);
void MExternal_Interrupt0(void(*Copy_VidInturrept)(void));
void MExternal_Interrupt1(void(*Copy_VidInturrept)(void));
void MExternal_Interrupt2(void(*Copy_VidInturrept)(void));

#endif /* EXTI_INT_H_ */
