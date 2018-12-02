/*
 * LedStatus.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include "Board.h"
#include "LedStatus.h"


void LedStatus_Init() {
	for(int i = 0; i < LEDn; i++)
		BSP_LED_Init(i);

}
