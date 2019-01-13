/*
 * App.c
 *
 *  Created on: Jan 12, 2019
 *      Author: HP
 */

#include "cmsis_os.h"
#include "DateService.h"
#include "MyApp.h"
#include "Api/3GPP_TS2707.h"

osThreadId AppTaskHandle;

void App_Main(void const * argument) {

//	if (DATE_SERVICE_ISVALID) {
		struct tm _tm;
		GSM_Clock(&_tm);
		DateService_Config(_tm);
//	} else {
//		/* Clear source Reset Flag */
//		__HAL_RCC_CLEAR_RESET_FLAGS();
//	}

	for (;;) {
		osDelay(100);
	}
}
void App_Init(void) {

	osThreadDef(AppTask, App_Main, osPriorityNormal, 0, 128);
	AppTaskHandle = osThreadCreate(osThread(AppTask), NULL);

}
