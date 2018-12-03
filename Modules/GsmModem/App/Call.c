/*
 * Call.c
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#include "App/Call.h"
#include "cmsis_os.h"
#include "sglib.h"
#include "Gsm.h"
#include "Api/3GPP_TS27.h"
#include "Api/V25TER.h"

void ClccReceivedCallback(Response_TypeDef response);
void UnsolicitedResultCallback(Response_TypeDef response);

const char *callStateTextList[7] = {"Active","Held","Dialing","Alerting", "Incoming","Waiting","Disconnect"};

CommandExecuter_TypeDef *commandExecuter;
CallInfo_Typedef call;
osThreadId CallThreadId;

ResponseReceivedCallbackList_typedef ClccCallback = { "+CLCC",
		ClccReceivedCallback, 0 };

void Call_Main(void * arg);

void Call_init(CommandExecuter_TypeDef *GsmCommandExecuter) {
	osThreadDef(callTask, Call_Main, osPriorityNormal, 1, 256);
	CallThreadId = osThreadCreate(osThread(callTask), GsmCommandExecuter);
	commandExecuter = GsmCommandExecuter;
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
		char * ulNotifiedValue;
		xTaskNotifyWait(0x00, /* Don't clear any notification bits on entry. */
		0xffffffff, /* Reset the notification value to 0 on exit. */
		&ulNotifiedValue, /* Notified value pass out in ulNotifiedValue. */
		portMAX_DELAY); /* Block indefinitely. */
		event = osSignalWait(0xff, osWaitForever);
		if (ulNotifiedValue == NULL)
			OnRing();
		else {
			volatile CallInfo_Typedef call;
			char* ClccReceivedToken = ulNotifiedValue;
			call.state = (ClccReceivedToken[11] - '0');
			strtok(ClccReceivedToken, "\"");
			call.number = strtok(0, "\"");
			strtok(0, "\"");
			call.Name = strtok(0, "\"");
			OnCallStateChanged(call);
		}
	}

}

CallInfo_Typedef ClccReceivedHandler(char* ClccReceivedToken) {
	volatile CallInfo_Typedef c;
	c.state = (ClccReceivedToken[11] - '0');
	strtok(ClccReceivedToken, "\"");
	c.number = strtok(0, "\"");
	strtok(0, "\"");
	c.Name = strtok(0, "\"");
}

void ClccReceivedCallback(Response_TypeDef response) {
	xTaskNotify(CallThreadId, response.Tokens.Items[0],
			eSetValueWithoutOverwrite);
}

void UnsolicitedResultCallback(Response_TypeDef response) {
	char * temp;
	for (int i = 0; i < response.Tokens.Count - 1; i++)
		if (memcmp(response.Tokens.Items[i], "+CLCC", 5))
			xTaskNotify(CallThreadId, response.Tokens.Items[i],
					eSetValueWithoutOverwrite);
	if (response.resultNumber == 2)
		osSignalSet(CallThreadId, NULL);
}
__weak void OnRing(void){

}
__weak void OnCallStateChanged(CallInfo_Typedef callInfo){

}

