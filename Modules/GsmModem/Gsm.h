/*
 * Gsm.h
 *
 *  Created on: Nov 5, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_GSM_H_
#define GSMMODEM_GSM_H_

#include "Tokenizer/CommandTokenizer.h"
#include "Executer/AtCommandExecuter.h"
#include "cmsis_os.h"

#define CARRIAGE_RETURN_CODE 		"\r"	// Carriage return
#define LINE_FEED_CODE				"\n"	// Line feed

#define COMMAND_LINE_TERMINATION_CAHR_DEFAULT	CARRIAGE_RETURN_CODE
#define RESPONSE_FORMATTING_CHAR_DEFAULT		LINE_FEED_CODE
#define COMMAND_ECHO_DEFAULT					1
#define RESPONSE_FORMAT_DEFAULT					1

typedef struct Gsm_Struct {
	CommandExecuter_TypeDef * commandExecuter;
	CommandTokenizer_TypeDef * commandTokenizer;
} Gsm_TypeDef;


extern Gsm_TypeDef GsmModem;
#define DefaultRetriesCount		5

#define CHECK_RESPONSE(response) ((response).status == ResponseStatusOk && (response).resultNumber == RESULT_NUMBER_OK)


#define EXECUTE_COMMAND(type, action, parameters)  ({ \
	int register r = DefaultRetriesCount; \
	Command_TypeDef command = {typr, action, parameters}; \
	Response_TypeDef response ; \
	while (r--) { \
		response = CommandExecuter_Execute(*GsmModem.commandExecuter, command); \
		if (CHECK_RESPONSE(response)) \
		{ \
			CommandTokenizer_FreeTokenList(response->Tokens); \
			break; \
		} \
		CommandTokenizer_FreeTokenList(response->Tokens); \
	} \
	r; \
})

void GSM_Main(void const * argument);
#endif /* GSMMODEM_GSM_H_ */
