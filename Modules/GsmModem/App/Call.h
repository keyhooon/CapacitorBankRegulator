/*
 * Call.h
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_APP_CALL_H_
#define GSMMODEM_APP_CALL_H_

#include "Executer/AtCommandExecuter.h"




#define MESSAGE_CALL_ACTIVE					1<<0
#define MESSAGE_CALL_HELD					1<<1
#define MESSAGE_CALL_DIALING				1<<2
#define MESSAGE_CALL_ALERTING				1<<3
#define MESSAGE_CALL_INCOMING				1<<4
#define MESSAGE_CALL_WAITING				1<<5
#define MESSAGE_CALL_DISCONNECT				1<<6
#define MESSAGE_CALL_RINGING				1<<7


typedef enum {
	Active = 1 << 0,
	Held = 1 << 1,
	Dialing = 1 << 2,
	Alerting = 1 << 3,
	Incoming = 1 << 4,
	Waiting = 1 << 5,
	Disconnect = 1 << 6,
} CallState_Typedef;
typedef struct {
	CallState_Typedef state;
	char * number;
	char * Name;
} CallInfo_Typedef;


extern const char *callStateTextList[7];

void OnCallStateChanged(CallInfo_Typedef);
void OnRing(void);
void Call_init(CommandExecuter_TypeDef *GsmCommandExecuter);
#endif /* GSMMODEM_APP_CALL_H_ */
