/*
 * Call.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include "Gsm.h"
#include "Api/V25TER.h"
#include <Api/3GPP_TS2707.h>
#include <Handler/CallHandler.h>
#include "cmsis_os.h"

#include "DateService.h"
#include "CallLogListContext.h"


void ClccReceivedCallback(char* ClccReceivedToken, char * Arg);
void UnsolicitedResultCallback(Response_TypeDef response);
void ClccReceivedHandler(char* ClccReceivedToken);

const char *callStateTextList[7] = {"Active","Held","Dialing","Alerting", "Incoming","Waiting","Disconnect"};

//CommandExecuter_TypeDef *commandExecuter;

osThreadId CallThreadId;

ResponseReceivedCallbackList_typedef ClccCallback = { "+CLCC",
		ClccReceivedCallback, 0 };

void Call_Main(void * arg);

void Call_init(CommandExecuter_TypeDef *GsmCommandExecuter) {
	osThreadDef(callTask, Call_Main, osPriorityNormal, 1, 256);
	CallThreadId = osThreadCreate(osThread(callTask), GsmCommandExecuter);
}
void Call_Main(void * arg) {
	CallLog_Typedef *callLog;
	CommandExecuter_TypeDef *GsmCommandExecuter = arg;
	ClccCallback.next = GsmCommandExecuter->responseReceivedCallbacks;
	GsmCommandExecuter->responseReceivedCallbacks = &ClccCallback;
	GsmCommandExecuter->UnsolicitedResultCode = UnsolicitedResultCallback;
	GSM_TA_RESPONSE_FORMAT(0);
	GSM_SET_COMMAND_ECHO_MODE(0);
	GSM_List_Current_Calls_ME(1);

	while (1) {
		osEvent event;
		CallInfo_Typedef *callInfo;
		xTaskNotifyWait(0x00, /* Don't clear any notification bits on entry. */
		0xffffffff, /* Reset the notification value to 0 on exit. */
		&callInfo, /* Notified value pass out in ulNotifiedValue. */
		portMAX_DELAY); /* Block indefinitely. */
		if (callInfo == NULL)
			OnRing();
		else {
			struct tm _tm;
			switch (callInfo->state) {
			case Active:
				callLog->IsSuccessfully = 1;
				break;
			case Incoming:
				DateService_Get(&_tm);
				callLog = CreateCallLog(callInfo->number, mktime(&_tm), 0, 1);
				break;
			case Dialing:

				break;
			case Alerting:
				DateService_Get(&_tm);
				callLog = CreateCallLog(callInfo->number, mktime(&_tm), 0, 0);
				break;
			case Disconnect:
				AddCallLog(callLog);
				FreeCallLog(callLog);
				break;
			default:

				break;
			}
			OnCallStateChanged(callInfo);
		}
		vPortFree(callInfo);
	}

}

void ClccReceivedCallback(char* ClccReceivedToken, char * Arg) {
	CallInfo_Typedef *callInfo = pvPortMalloc(sizeof(CallInfo_Typedef));
	callInfo->state = (ClccReceivedToken[11] - '0');
	strtok(ClccReceivedToken, "\"");
	strcpy(callInfo->number, strtok(0, "\""));
	strtok(0, "\"");
	strcpy(callInfo->name, strtok(0, "\""));
	xTaskNotify(CallThreadId, callInfo, eSetValueWithoutOverwrite);
}

void UnsolicitedResultCallback(Response_TypeDef response) {
	if (response.resultNumber == 2)
		xTaskNotify(CallThreadId, NULL, eSetValueWithoutOverwrite);
}
__weak void OnRing(void){

}
__weak void OnCallStateChanged(CallInfo_Typedef * callInfo) {

}

