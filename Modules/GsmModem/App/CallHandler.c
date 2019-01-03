/*
 * Call.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include <Api/3GPP_TS2707.h>
#include <App/CallHandler.h>
#include "cmsis_os.h"
#include "sglib.h"
#include "Gsm.h"
#include "Api/V25TER.h"

void ClccReceivedCallback(char* ClccReceivedToken);
void UnsolicitedResultCallback(Response_TypeDef response);
void ClccReceivedHandler(char* ClccReceivedToken);

const char *callStateTextList[7] = {"Active","Held","Dialing","Alerting", "Incoming","Waiting","Disconnect"};

//CommandExecuter_TypeDef *commandExecuter;

osThreadId CallThreadId;
CallInfo_Typedef call;
ResponseReceivedCallbackList_typedef ClccCallback = { "+CLCC",
		ClccReceivedCallback, 0 };

void Call_Main(void * arg);

void Call_init(CommandExecuter_TypeDef *GsmCommandExecuter) {
	osThreadDef(callTask, Call_Main, osPriorityNormal, 1, 256);
	CallThreadId = osThreadCreate(osThread(callTask), GsmCommandExecuter);
}
void Call_Main(void * arg) {
	CommandExecuter_TypeDef *GsmCommandExecuter = arg;
	ClccCallback.next = GsmCommandExecuter->responseReceivedCallbacks;
	GsmCommandExecuter->responseReceivedCallbacks = &ClccCallback;
	GsmCommandExecuter->UnsolicitedResultCode = UnsolicitedResultCallback;
	GSM_TA_RESPONSE_FORMAT(0);
	GSM_SET_COMMAND_ECHO_MODE(0);
	GSM_List_Current_Calls_ME(1);

	while (1) {
		osEvent event;
		CallInfo_Typedef *call;
		xTaskNotifyWait(0x00, /* Don't clear any notification bits on entry. */
		0xffffffff, /* Reset the notification value to 0 on exit. */
		&call, /* Notified value pass out in ulNotifiedValue. */
		portMAX_DELAY); /* Block indefinitely. */
		if (call == NULL)
			OnRing();
		else {
			OnCallStateChanged(call);
		}
	}

}

void ClccReceivedCallback(char* ClccReceivedToken) {
	call.state = (ClccReceivedToken[11] - '0');
	strtok(ClccReceivedToken, "\"");
	strcpy(call.number, strtok(0, "\""));
	strtok(0, "\"");
	strcpy(call.Name, strtok(0, "\""));
	xTaskNotify(CallThreadId, &call, eSetValueWithoutOverwrite);

}

void UnsolicitedResultCallback(Response_TypeDef response) {
	if (response.resultNumber == 2)
		xTaskNotify(CallThreadId, NULL, eSetValueWithoutOverwrite);
}
__weak void OnRing(void){

}
__weak void OnCallStateChanged(CallInfo_Typedef * callInfo) {

}

