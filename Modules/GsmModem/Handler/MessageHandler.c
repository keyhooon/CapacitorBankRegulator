/*
 * Message.c
 *
 *  Created on: Dec 10, 2018
 *      Author: HP
 */

#include <Api/3GPP_TS2705.h>
#include <Handler/MessageHandler.h>
#include "Message.h"
#include "cmsis_os.h"
#include "sglib.h"
#include "Gsm.h"
#include "Api/V25TER.h"
#include "time.h"

char* messageStorageType[5] = {
SIM_MESSAGE_STORAGE, PHONE_MESSAGE_STORAGE, SM_MESSAGE_STORAGE_PREFERRED,
		ME_MESSAGE_STORAGE_PREFERRED, SM_ME_MESSAGE_STORAGE };

void CmtReceivedCallback(char* CmtReceivedToken);
void OnMessageReceived();

osThreadId MessageThreadId;

ResponseReceivedCallbackList_typedef CmtCallback = { "+CMT",
		CmtReceivedCallback, 0 };

void Message_Main(void * arg);

void Message_init(CommandExecuter_TypeDef *GsmCommandExecuter) {
	osThreadDef(messageTask, Message_Main, osPriorityNormal, 1, 128);
	MessageThreadId = osThreadCreate(osThread(messageTask), GsmCommandExecuter);
}
void Message_Main(void * arg) {
	CommandExecuter_TypeDef *GsmCommandExecuter = arg;
	CmtCallback.next = GsmCommandExecuter->responseReceivedCallbacks;
	GsmCommandExecuter->responseReceivedCallbacks = &CmtCallback;

	GSM_SELECT_SMS_MESSAGE_FORMAT(1);
	GSM_NEW_SMS_MESSAGE_INDICATION(2);

	while (1) {
		osEvent event;
		MessageInfo_Typedef messageInfo;
		xTaskNotifyWait(0x00, /* Don't clear any notification bits on entry. */
		0xffffffff, /* Reset the notification value to 0 on exit. */
		&messageInfo, /* Notified value pass out in ulNotifiedValue. */
		portMAX_DELAY); /* Block indefinitely. */
		OnMessageReceived();

	}

}

void CmtReceivedCallback(char* CmtReceivedToken) {
	Message_Typedef message;
	struct tm tm;
	time_t t;
	strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken);
	char* callNumber = strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken);
	strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken);
	char* name = strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken);
	strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken);
	strptime(strtok_r(CmtReceivedToken, "\"", &CmtReceivedToken),
			"%y/%m/%d,%H:%M:%S", &tm);
	t = mktime(&tm);
	AddMessageEx(CmtReceivedToken, callNumber, t, 1, 1);
}


__weak void OnMessageReceived() {

}

