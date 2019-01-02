/*
 * Message.c
 *
 *  Created on: Dec 10, 2018
 *      Author: HP
 */

#include <Api/3GPP_TS2705.h>
#include "cmsis_os.h"
#include "sglib.h"
#include "Gsm.h"
#include "Api/V25TER.h"
#include "Message.h"

char* messageStorageType[5] = {
SIM_MESSAGE_STORAGE, PHONE_MESSAGE_STORAGE, SM_MESSAGE_STORAGE_PREFERRED,
		ME_MESSAGE_STORAGE_PREFERRED, SM_ME_MESSAGE_STORAGE };

void CmtiReceivedCallback(char* CmtiReceivedToken);
void OnMessageReceived();

osThreadId MessageThreadId;

ResponseReceivedCallbackList_typedef CmtiCallback = { "+CMTI",
		CmtiReceivedCallback, 0 };

void Message_Main(void * arg);

void Message_init(CommandExecuter_TypeDef *GsmCommandExecuter) {
	osThreadDef(messageTask, Message_Main, osPriorityNormal, 1, 128);
	MessageThreadId = osThreadCreate(osThread(messageTask), GsmCommandExecuter);
}
void Message_Main(void * arg) {
	CommandExecuter_TypeDef *GsmCommandExecuter = arg;
	CmtiCallback.next = GsmCommandExecuter->responseReceivedCallbacks;
	GsmCommandExecuter->responseReceivedCallbacks = &CmtiCallback;

	GSM_SELECT_SMS_MESSAGE_FORMAT(1);
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

void CmtiReceivedCallback(char* CmtiReceivedToken) {
	MessageInfo_Typedef messageInfo;
	strtok(CmtiReceivedToken, "\"");
	char* messageStorage = strtok(0, "\"");
	for (int i = 0; i < 5; i++)
		if (strcmp(messageStorageType[i], messageStorage) == 0) {
			messageInfo.messageStorageindex = i;
			break;
		}
	strtok(0, ",");
	messageInfo.messageStorageindex = atoi(strtok(0, " "));
	xTaskNotify(MessageThreadId, &messageInfo, eSetValueWithoutOverwrite);

}


__weak void OnMessageReceived() {

}

