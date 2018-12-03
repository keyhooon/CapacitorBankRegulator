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
	osThreadDef(callTask, Call_Main, osPriorityLow, 1, 256);
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
		event = osSignalWait(0xff, osWaitForever);
		if (event.value.signals & MESSAGE_CALL_RINGING)
			OnRing();
		else {
			OnCallStateChanged(call);
		}
	}

}

void ClccReceivedCallback(Response_TypeDef response) {
	char * temp;
	temp = response.Tokens.Items[0];
	osSignalSet(CallThreadId, 1 << (temp[11] - '0'));
}

void UnsolicitedResultCallback(Response_TypeDef response) {
	char * temp;
	if (response.Tokens.Count == 1) {
		if (response.resultNumber == 2)
			osSignalSet(CallThreadId, MESSAGE_CALL_RINGING);
	} else if (response.Tokens.Count > 1)
	{
		temp = response.Tokens.Items[response.Tokens.Count - 2];
		call.state =  1 << (temp[11] - '0');
		call.Name = " ";
		call.number = " ";
		osSignalSet(CallThreadId, call.state);
	}

}
__weak void OnRing(void){

}
__weak void OnCallStateChanged(CallInfo_Typedef callInfo){

}

