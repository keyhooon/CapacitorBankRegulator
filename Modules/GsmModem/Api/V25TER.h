/*
 * V25TER.h
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_API_V25TER_H_
#define GSMMODEM_API_V25TER_H_

#include "Gsm.h"

extern const CommandType_TypeDef REISSUES_THE_LAST_COMMAND_GIVEN;
extern const CommandType_TypeDef ANSWER_AN_INCOMING_CALL;
extern const CommandType_TypeDef MOBILE_ORGINATE_CALL_TO_DIAL_A_NUMBER;
extern const CommandType_TypeDef ORGINATE_CALL_TO_PHONE_NUMBER_IN_CURRENT_MEMORY;
extern const CommandType_TypeDef ORGINATE_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_CORRESPONDS;
extern const CommandType_TypeDef REDIAL_LAST_TELEPHONE_NUMBER_USED;
extern const CommandType_TypeDef SET_COMMAND_ECHO_MODE;
extern const CommandType_TypeDef DISCONNECT_EXISTING_CONNECTION;
extern const CommandType_TypeDef DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION;
extern const CommandType_TypeDef SET_MONITOR_SPEAKER_LOUDNESS;
extern const CommandType_TypeDef SET_MONITOR_SPEAKER_MODE;
extern const CommandType_TypeDef SWITCH_FROM_DATA_MODE_OR_PPP_ONLINE_MODE_TO_COMMAND_MODE;
extern const CommandType_TypeDef SWITCH_FROM_COMMAND_MODE_TO_DATA_MODE;
extern const CommandType_TypeDef SELECT_PULSE_DIALING;
extern const CommandType_TypeDef SET_RESULT_CODE_PRESENTATION_MODE;
extern const CommandType_TypeDef SET_NUMBER_OF_RINGS_BEFORE_AUTOMATICALY_ANSWERING_THE_CALL;
extern const CommandType_TypeDef SET_COMMAND_LINE_TERMINATION_CHARACTER;
extern const CommandType_TypeDef SET_RESPONSE_FORMATTINF_CHARACTER;
extern const CommandType_TypeDef SET_COMMAND_LINE_EDITING_CHARACTER;
extern const CommandType_TypeDef PAUSE_BEFORE_BLIND_DIALING;
extern const CommandType_TypeDef SET_NUMBER_OF_SECONDS_TO_WAIT_FOR_CONNECTION_COMPETION;
extern const CommandType_TypeDef SET_NUMBER_OF_SECONDS_TO_WAIT_FOR_COMMA_DIAL_MODIFIER_ENCOUNTERED;
extern const CommandType_TypeDef SET_DISCONNECT_DELAY_AFTER_INDICATING_THE_ABSENCE_OF_DATA_CARRIER;
extern const CommandType_TypeDef SELECT_TONE_DIALING;
extern const CommandType_TypeDef TA_RESPONSE_FORMAT;
extern const CommandType_TypeDef SET_CONNECT_RESULT_CODE_FORMAT_AND_MONITOR_CALL_PROGRESS;
extern const CommandType_TypeDef RESET_DEFAULT_CONFIGURATION;
extern const CommandType_TypeDef SET_DCD_FUNCTION_MODE;
extern const CommandType_TypeDef SET_DTR_FUNCTION_MODE;
extern const CommandType_TypeDef FACTORY_DEFIEND_CONFIGURATION;
extern const CommandType_TypeDef DISPLAY_CURRENT_CONFIGURATION;
extern const CommandType_TypeDef STORE_ACTIVE_PROFILE;
extern const CommandType_TypeDef REQUEST_COMPLETE_TA_CAPABILITIES_LIST;
extern const CommandType_TypeDef REQUEST_MANUFACTURER_IDENTIFICATION;
extern const CommandType_TypeDef REQUEST_TA_MODEL_IDENTIFICATION;
extern const CommandType_TypeDef REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE;
extern const CommandType_TypeDef REQUEST_GLOBAL_OBJECT_IDENTIFICATION;
extern const CommandType_TypeDef REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION;
extern const CommandType_TypeDef SET_TE_TA_CONTROL_CHARACTER_FRAMING;
extern const CommandType_TypeDef SET_TE_TA_LOCAL_DATA_FLOW_CONTROL;
extern const CommandType_TypeDef SET_TE_TA_FIXED_LOCAL_RATE;
extern const CommandType_TypeDef DISCONNECT_VOICE_CALL_ONLY;

#define GSM_ANSWER_AN_INCOMING_CALL() Gsm_ExecuteCommand(ANSWER_AN_INCOMING_CALL, 0, 0)

#define GSM_CALL_TO_DIAL_A_NUMBER(number) Gsm_ExecuteCommand(MOBILE_ORGINATE_CALL_TO_DIAL_A_NUMBER, string, &number)

#define GSM_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_NAME(name) Gsm_ExecuteCommand(ORGINATE_CALL_TO_PHONE_NUMBER_IN_MEMORY_WHICH_CORRESPONDS, string, &name)

#define GSM_CALL_TO_PHONE_NUMBER_IN_MEMORY(number) { \
	char num[10]; \
	itoa(number,num, 10); \
	Gsm_ExecuteCommand(ORGINATE_CALL_TO_PHONE_NUMBER_IN_CURRENT_MEMORY, integer, &num); \
}

#define GSM_REDIAL_LAST_TELEPHONE_NUMBER_USED() Gsm_ExecuteCommand(REDIAL_LAST_TELEPHONE_NUMBER_USED, Execute, 0)

#define GSM_DISCONNECT_EXISTING_CONNECTION() Gsm_ExecuteCommand(DISCONNECT_EXISTING_CONNECTION, Execute, 0)

#define GSM_SELECT_PULSE_DIALING() Gsm_ExecuteCommand(SELECT_PULSE_DIALING, 0, 0)

#define GSM_SELECT_TONE_DIALING() Gsm_ExecuteCommand(SELECT_TONE_DIALING, 0, 0)

#define GSM_DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(DISPLAY_PRODUCT_IDENTIFICATION_INFORMATION,Execute, 0, data)

#define GSM_REQUEST_MANUFACTURER_IDENTIFICATION(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(REQUEST_MANUFACTURER_IDENTIFICATION, Execute,0, data)

#define GSM_REQUEST_TA_MODEL_IDENTIFICATION(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(REQUEST_TA_MODEL_IDENTIFICATION, Execute, 0,data)

#define GSM_REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(	REQUEST_TA_REVISION_IDENTIFICATION_OF_SOFTWARE_RELEASE, Execute, 0,	data)

#define GSM_REQUEST_GLOBAL_OBJECT_IDENTIFICATION(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(REQUEST_GLOBAL_OBJECT_IDENTIFICATION, Execute,	0, data)

#define GSM_REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION(data) Gsm_ExecuteCommand_RetryUntillOk_Ex(REQUEST_TA_SERIAL_NUMBER_IDENTIFICATION,	Execute, 0, data)

#define GSM_SET_MONITOR_SPEAKER_LOUDNESS( value) { \
	int num = value; \
	Gsm_ExecuteCommand_RetryUntillOk(SET_MONITOR_SPEAKER_LOUDNESS, integer, &num); \
}
#define GSM_SET_MONITOR_SPEAKER_MODE( value) { \
	int num = value; \
	Gsm_ExecuteCommand_RetryUntillOk(SET_MONITOR_SPEAKER_MODE, integer, &num); \
}

#define GSM_SET_COMMAND_ECHO_MODE(echo) { \
	int num = echo; \
	Gsm_ExecuteCommand(SET_COMMAND_ECHO_MODE, integer, &num); \
}

#define GSM_SET_RESULT_CODE_PRESENTATION_MODE(value) { \
	int num = value; \
	Gsm_ExecuteCommand_RetryUntillOk(SET_RESULT_CODE_PRESENTATION_MODE, integer, &num); \
}

#define GSM_TA_RESPONSE_FORMAT( value) { \
	int num = value; \
	Gsm_ExecuteCommand(TA_RESPONSE_FORMAT, integer, &num); \
}

#endif /* GSMMODEM_API_V25TER_H_ */
