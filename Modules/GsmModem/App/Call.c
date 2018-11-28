/*
 * Call.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include "App/Call.h"
#include "cmsis_os.h"


osThreadId CallThreadId;

void Call_Main(void * arg);

void Call_init() {
	osThreadDef(callTask, Call_Main, osPriorityNormal, 1, 256);
	CallThreadId = osThreadCreate(osThread(callTask), 0);
}
void Call_Main(void * arg) {

	while (1) {

	}
}
