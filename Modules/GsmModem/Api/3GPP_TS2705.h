/*
 * 3GPP_TS2705.h
 *
 *  Created on: Dec 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_API_3GPP_TS2705_H_
#define GSMMODEM_API_3GPP_TS2705_H_

#include "Gsm.h"
#include "stdlib.h"
#include "string.h"

extern const CommandType_TypeDef DELETE_SMS_MESSAGE;
extern const CommandType_TypeDef SELECT_SMS_MESSAGE_FORMAT;
extern const CommandType_TypeDef LIST_SMS_MESSAGE_FROM_PREFERRED_STORE;
extern const CommandType_TypeDef READ_SMS_MESSAGE;
extern const CommandType_TypeDef SEND_SMS_MESSAGE;
extern const CommandType_TypeDef WRITE_SMS_TO_MEMORY;
extern const CommandType_TypeDef SEND_SMS_MESSAGE_FROM_STORAGE;
extern const CommandType_TypeDef NEW_SMS_MESSAGE_INDICATION;
extern const CommandType_TypeDef PREFERRED_SMS_MESSAGE_STORAGE;
extern const CommandType_TypeDef RESTORE_SMS_SETTINGS;
extern const CommandType_TypeDef SAVE_SMS_SETTINGS;
extern const CommandType_TypeDef SMS_SERVICE_CENTER_ADDRESS;
extern const CommandType_TypeDef SELECT_CELL_BROADCAST_SMS_MESSAGE;
extern const CommandType_TypeDef SHOW_SMS_TEXT_MODE_PARAMETERS;
extern const CommandType_TypeDef SET_SMS_TEXT_MODE_PARAMETERS;
extern const CommandType_TypeDef SELECT_MESSAGE_SERVICE;


#define GSM_DELETE_SMS_MESSAGE()
#define GSM_SELECT_SMS_MESSAGE_FORMAT(value)	{ \
		char num[2] = {value + '0',0}; \
		Gsm_ExecuteCommand(SELECT_SMS_MESSAGE_FORMAT, Write, num); \
}
#define GSM_LIST_SMS_MESSAGE_FROM_PREFERRED_STORE()
#define GSM_READ_SMS_MESSAGE()
#define GSM_SEND_SMS_MESSAGE()
#define GSM_WRITE_SMS_TO_MEMORY()
#define GSM_SEND_SMS_MESSAGE_FROM_STORAGE()
#define GSM_NEW_SMS_MESSAGE_INDICATION(value)	{ \
		char num[3] = {'2', value + '0',0}; \
		Gsm_ExecuteCommand(NEW_SMS_MESSAGE_INDICATION, Write, num); \
}
#define GSM_PREFERRED_SMS_MESSAGE_STORAGE()
#define GSM_RESTORE_SMS_SETTINGS()
#define GSM_SAVE_SMS_SETTINGS()
#define GSM_SMS_SERVICE_CENTER_ADDRESS()
#define GSM_SELECT_CELL_BROADCAST_SMS_MESSAGE()
#define GSM_SHOW_SMS_TEXT_MODE_PARAMETERS()
#define GSM_SET_SMS_TEXT_MODE_PARAMETERS()
#define GSM_SELECT_MESSAGE_SERVICE()

#endif /* GSMMODEM_API_3GPP_TS2705_H_ */
