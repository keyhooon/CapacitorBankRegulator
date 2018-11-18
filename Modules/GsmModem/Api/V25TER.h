/*
 * V25TER.h
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_API_V25TER_H_
#define GSMMODEM_API_V25TER_H_

#include "Gsm.h"
#include "string.h"
#include "stdlib.h"

const CommandType_TypeDef REISSUES_THE_LAST_COMMAND_GIVEN = { "A/", 0, basic };
const CommandType_TypeDef ANSWER_AN_INCOMING_CALL = { "A", 20000, basic };
const CommandType_TypeDef MOBILE_ORGINATE_CALL_TO_DIAL_A_NUMBER = { "D", 20000,
		basic };
const CommandType_TypeDef ORGINATE_CALL_TO_PHONE_NUMBER_IN_CURRENT_MEMORY = {
		"D", 0, basic };
const CommandType_TypeDef ORGINATE_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_CORRESPONDS =
		{ "D", 0, basic };
const CommandType_TypeDef REDIAL_LAST_TELEPHONE_NUMBER_USED = { "DL", 0, basic };
const CommandType_TypeDef SET_COMMAND_ECHO_MODE = { "E", 0, basic };
const CommandType_TypeDef DISCONNECT_EXISTING_CONNECTION = { "H", 20000, basic };
const CommandType_TypeDef DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION = { "I", 0,
		basic };
const CommandType_TypeDef SET_MONITOR_SPEAKER_LOUDNESS = { "L", 0, basic };
const CommandType_TypeDef SET_MONITOR_SPEAKER_MODE = { "M", 0, basic };
const CommandType_TypeDef SWITCH_FROM_DATA_MODE_OR_PPP_ONLINE_MODE_TO_COMMAND_MODE =
		{ "+++", 0, basic };
const CommandType_TypeDef SWITCH_FROM_COMMAND_MODE_TO_DATA_MODE = { "O", 0,
		basic };
const CommandType_TypeDef SELECT_PULSE_DIALING = { "P", 0, basic };
const CommandType_TypeDef SET_RESULT_CODE_PRESENTATION_MODE = { "Q", 0, basic };
const CommandType_TypeDef SET_NUMBER_OF_RINGS_BEFORE_AUTOMATICALY_ANSWERING_THE_CALL =
		{ 0, 0, sParameter };
const CommandType_TypeDef SET_COMMAND_LINE_TERMINATION_CHARACTER = { 0, 0,
		sParameter };
const CommandType_TypeDef SET_RESPONSE_FORMATTINF_CHARACTER =
		{ 0, 0, sParameter };
const CommandType_TypeDef SET_COMMAND_LINE_EDITING_CHARACTER = { 0, 0,
		sParameter };
const CommandType_TypeDef PAUSE_BEFORE_BLIND_DIALING = { 0, 0, sParameter };
const CommandType_TypeDef SET_NUMBER_OF_SECONDS_TO_WAIT_FOR_CONNECTION_COMPETION =
		{ 0, 0, sParameter };
const CommandType_TypeDef SET_NUMBER_OF_SECONDS_TO_WAIT_FOR_COMMA_DIAL_MODIFIER_ENCOUNTERED =
		{ 0, 0, sParameter };
const CommandType_TypeDef SET_DISCONNECT_DELAY_AFTER_INDICATING_THE_ABSENCE_OF_DATA_CARRIER =
		{ 0, 0, sParameter };
const CommandType_TypeDef SELECT_TONE_DIALING = { "T", 0, basic };
const CommandType_TypeDef TA_RESPONSE_FORMAT = { "V", 0, basic };
const CommandType_TypeDef SET_CONNECT_RESULT_CODE_FORMAT_AND_MONITOR_CALL_PROGRESS =
		{ "X", 0, basic };
const CommandType_TypeDef RESET_DEFAULT_CONFIGURATION = { "Z", 0, basic };
const CommandType_TypeDef SET_DCD_FUNCTION_MODE = { "&C", 0, basic };
const CommandType_TypeDef SET_DTR_FUNCTION_MODE = { "&D", 0, basic };
const CommandType_TypeDef FACTORY_DEFIEND_CONFIGURATION = { "&F", 0, basic };
const CommandType_TypeDef DISPLAY_CURRENT_CONFIGURATION = { "&V", 0, basic };
const CommandType_TypeDef STORE_ACTIVE_PROFILE = { "&W", 0, basic };
const CommandType_TypeDef REQUEST_COMPLETE_TA_CAPABILITIES_LIST = { "GCAP", 0,
		basic };
const CommandType_TypeDef REQUEST_MANUFACTURER_IDENTIFICATION = { "GMI", 0,
		extended };
const CommandType_TypeDef REQUEST_TA_MODEL_IDENTIFICATION =
		{ "GMM", 0, extended };
const CommandType_TypeDef REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE =
		{ "GMR", 0, extended };
const CommandType_TypeDef REQUEST_GLOBAL_OBJECT_IDENTIFICATION = { "GOI", 0,
		extended };
const CommandType_TypeDef REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION = { "GSN", 0,
		extended };
const CommandType_TypeDef SET_TE_TA_CONTROL_CHARACTER_FRAMING = { "ICF", 0,
		extended };
const CommandType_TypeDef SET_TE_TA_LOCAL_DATA_FLOW_CONTROL = { "IFC", 0,
		extended };
const CommandType_TypeDef SET_TE_TA_FIXED_LOCAL_RATE = { "IPR", 0, extended };
const CommandType_TypeDef DISCONNECT_VOICE_CALL_ONLY = { "HVOIC", 0, extended };

#define GSM_ANSWER_AN_INCOMING_CALL() Gsm_ExecuteCommand(ANSWER_AN_INCOMING_CALL, 0, 0)

#define GSM_CALL_TO_DIAL_A_NUMBER(number) Gsm_ExecuteCommand(MOBILE_ORGINATE_CALL_TO_DIAL_A_NUMBER, 0, &number)

#define GSM_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_NAME(name) Gsm_ExecuteCommand(ORGINATE_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_CORRESPONDS, 0, &name)

#define GSM_CALL_TO_PHONE_NUMBER_IN_MEMORY(number) { \
	char num[10]; \
	itoa(number,num, 10); \
	Gsm_ExecuteCommand(ORGINATE_CALL_TO_PHONE_NUMBER_IN_CURRENT_MEMORY, 0, &num); \
}

#define GSM_REDIAL_LAST_TELEPHONE_NUMBER_USED() Gsm_ExecuteCommand(REDIAL_LAST_TELEPHONE_NUMBER_USED, Execute, 0)

#define GSM_DISCONNECT_EXISTING_CONNECTION() Gsm_ExecuteCommand(DISCONNECT_EXISTING_CONNECTION, Execute, 0)

#define GSM_SELECT_PULSE_DIALING() Gsm_ExecuteCommand(SELECT_PULSE_DIALING, 0, 0)

#define GSM_SELECT_TONE_DIALING() Gsm_ExecuteCommand(SELECT_TONE_DIALING, 0, 0)

#define GSM_DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION(data) Gsm_ExecuteCommand_Ex(DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION,Execute, 0, data)

#define GSM_REQUEST_MANUFACTURER_IDENTIFICATION(data) Gsm_ExecuteCommand_Ex(REQUEST_MANUFACTURER_IDENTIFICATION, Execute,0, data)

#define GSM_REQUEST_TA_MODEL_IDENTIFICATION(data) Gsm_ExecuteCommand_Ex(REQUEST_TA_MODEL_IDENTIFICATION, Execute, 0,data)

#define GSM_REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE(data) Gsm_ExecuteCommand_Ex(	REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE, Execute, 0,	data)

#define GSM_REQUEST_GLOBAL_OBJECT_IDENTIFICATION(data) Gsm_ExecuteCommand_Ex(REQUEST_GLOBAL_OBJECT_IDENTIFICATION, Execute,	0, data)

#define GSM_REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION(data) Gsm_ExecuteCommand_Ex(REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION,	Execute, 0, data)

#define GSM_SET_MONITOR_SPEAKER_LOUDNESS( value) { \
	int num = value; \
	Gsm_ExecuteCommand(SET_MONITOR_SPEAKER_LOUDNESS, 0, &num); \
}
#define GSM_SET_MONITOR_SPEAKER_MODE( value) { \
	int num = value; \
	Gsm_ExecuteCommand(SET_MONITOR_SPEAKER_MODE, 0,	&num); \
}

#define GSM_SET_COMMAND_ECHO_MODE(echo) { \
	int num = echo; \
	Gsm_ExecuteCommand(SET_COMMAND_ECHO_MODE, Execute, &num); \
}

#define GSM_SET_RESULT_CODE_PRESENTATION_MODE(value) { \
	int num = value; \
	Gsm_ExecuteCommand(SET_RESULT_CODE_PRESENTATION_MODE, 0, &num); \
}

#define GSM_TA_RESPONSE_FORMAT( value) { \
	int num = value; \
	Gsm_ExecuteCommand(TA_RESPONSE_FORMAT, 0, &num); \
}

#endif /* GSMMODEM_API_V25TER_H_ */
