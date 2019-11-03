/*
 * it.c
 *
 *  Created on: 02-Nov-2019
 *      Author: blueh
 */
#include "stm32f4xx_hal.h"




void Systick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


//get the name of the uatr interrupt handler from the sratup code

