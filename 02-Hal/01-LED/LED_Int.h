/*
 * LED_Int.h
 *
 *  Created on: Dec 11, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef LED_INT_H_
#define LED_INT_H_

#include "../../01-MCAL/01-DIO/DIO_Int.h"
#include "../../01-MCAL/03-TIMER/TIMER_Int.h"
#include "LED_Config.h"

void HLED_VidInit(void);
void HLED_VidNormalMode(void);
void HLED_VidPedestrianMode(void);
void HPrivate_VidToggleLed(u32 Copy_u32Delay);

#endif /* LED_INT_H_ */
