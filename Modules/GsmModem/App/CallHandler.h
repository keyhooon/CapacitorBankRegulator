/*
 * Call.h
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_APP_CALLHANDLER_H_
#define GSMMODEM_APP_CALLHANDLER_H_

#include "Executer/AtCommandExecuter.h"




#define MESSAGE_CALL_ACTIVE					0
#define MESSAGE_CALL_HELD					1
#define MESSAGE_CALL_DIALING				2
#define MESSAGE_CALL_ALERTING				3
#define MESSAGE_CALL_INCOMING				4
#define MESSAGE_CALL_WAITING				5
#define MESSAGE_CALL_DISCONNECT				6
#define MESSAGE_CALL_RINGING				7


typedef enum {
	Active = 0,
	Held = 1,
	Dialing = 2,
	Alerting = 3,
	Incoming = 4,
	Waiting = 5,
	Disconnect = 6,
} CallState_Typedef;
typedef struct {
	CallState_Typedef state;
	char number[20];
	char Name[16];
} CallInfo_Typedef;


extern const char *callStateTextList[7];

void OnCallStateChanged(CallInfo_Typedef *);
void OnRing(void);
void Call_init(CommandExecuter_TypeDef *GsmCommandExecuter);
#endif /* GSMMODEM_APP_CALLHANDLER_H_ */
