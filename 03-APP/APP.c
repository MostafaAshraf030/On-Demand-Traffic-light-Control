/*
 * main.c
 *
 *  Created on: Dec 12, 2022
 *      Author: Mostafa Ashraf
 */

#include "APP.h"

void APP_StartVid(void)
{
	HButton_VidInit();
	HLED_VidInit();
	MDIO_VidGlobalInterruptEnable();
	while(True)
	{
		HLED_VidNormalMode();
	}
}

