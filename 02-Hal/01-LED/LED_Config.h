/*
 * LED_Config.h
 *
 *  Created on: Dec 11, 2022
 *      Author: Mostafa Ashraf
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

/* CAR Pin Connection */
#define CAR_Port Port_A
#define CAR_RED	Pin_2
#define CAR_GRN	Pin_0
#define CAR_YEL	Pin_1
/* Pedestrian Pin Connection */
#define PT_Port	Port_B
#define PT_RED	Pin_2
#define PT_GRN	Pin_0
#define PT_YEL	Pin_1
/* Type_Def */
typedef enum {GREEN,YELLOW,RED,DEFAULT}Traffic;

#endif /* LED_CONFIG_H_ */
