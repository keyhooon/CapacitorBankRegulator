/*
 * 3GPP_TS2705.c
 *
 *  Created on: Dec 10, 2018
 *      Author: HP
 */

#include "3GPP_TS2705.h"

const CommandType_TypeDef DELETE_SMS_MESSAGE =   //
		{ "CMGD", 5000, extended };
const CommandType_TypeDef SELECT_SMS_MESSAGE_FORMAT = //
		{ "CMGF", 0, extended };
const CommandType_TypeDef LIST_SMS_MESSAGE_FROM_PREFERRED_STORE =  //
		{ "CMGL", 20000, extended };
const CommandType_TypeDef READ_SMS_MESSAGE = //
		{ "CMGR", 5000, extended };
const CommandType_TypeDef SEND_SMS_MESSAGE = //
		{ "CMGS", 60000, extended };
const CommandType_TypeDef WRITE_SMS_TO_MEMORY = //
		{ "CMGW", 5000, extended };
const CommandType_TypeDef SEND_SMS_MESSAGE_FROM_STORAGE = //
		{ "CMSS", 60000, extended };
const CommandType_TypeDef NEW_SMS_MESSAGE_INDICATION = //
		{ "CNMI", 0, extended };
const CommandType_TypeDef PREFERRED_SMS_MESSAGE_STORAGE = //
		{ "CPMS", 0, extended };
const CommandType_TypeDef RESTORE_SMS_SETTINGS = //
		{ "CRES", 5000, extended };
const CommandType_TypeDef SAVE_SMS_SETTINGS = //
		{ "CSAS", 5000, extended };
const CommandType_TypeDef SMS_SERVICE_CENTER_ADDRESS = //
		{ "CSCA", 5000, extended };
const CommandType_TypeDef SELECT_CELL_BROADCAST_SMS_MESSAGE = //
		{ "CSCB", 0, extended };
const CommandType_TypeDef SHOW_SMS_TEXT_MODE_PARAMETERS = //
		{ "CSDH", 0, extended };
const CommandType_TypeDef SET_SMS_TEXT_MODE_PARAMETERS = //
		{ "CSMP", 0, extended };
const CommandType_TypeDef SELECT_MESSAGE_SERVICE = //
		{ "CSMS", 0, extended };


