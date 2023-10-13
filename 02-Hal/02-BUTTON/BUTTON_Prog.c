/*
 * BUTTON_Prog.c
 *
 *  Created on: Dec 11, 2022
 *      Author: Mostafa Ashraf
 */

#include "BUTTON_Int.h"

/*Button Init*/
void HButton_VidInit(void)
{
	MDIO_VidInternalPinBullUp(BUTTON_PORT, BUTTON_PIN);
	MExternal_Interrupt0(HLED_VidPedestrianMode);
	MExternal_Interrupt_VidInit(Interrupt_0,Falling_Edge);
}



