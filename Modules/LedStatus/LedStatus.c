/*
 * LedStatus.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include "Board.h"
#include "LedStatus.h"
#include "cmsis_os.h"

void StatusShowCallback(void const * argument);

osTimerId StatusTimerHandle;

uint32_t ledTim[4];
uint32_t ledTimStart[4] = { 1, 2, 3, 4 };

void LedStatus_Init() {
	ledTimStart[AliveLed] = 5;

	for(int i = 0; i < LEDn; i++)
		BSP_LED_Init(i);
	osTimerDef(StatusTimer, StatusShowCallback);
	StatusTimerHandle = osTimerCreate(osTimer(StatusTimer), osTimerPeriodic,
	NULL);

	osTimerStart(StatusTimerHandle, 100);
}

void StatusShowCallback(void const * argument) {
	/* USER CODE BEGIN StatusShowCallback */
	if (ledTim[AliveLed]-- == 0) {
		ledTim[AliveLed] = ledTimStart[AliveLed];
		BSP_LED_Toggle(AliveLed);
	}
	/* USER CODE END StatusShowCallback */
}
