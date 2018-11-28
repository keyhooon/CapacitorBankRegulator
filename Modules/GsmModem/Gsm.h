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

#define DefaultRetriesCount		5

#define CHECK_RESPONSE(response) ((response).status == ResponseStatusOk && (response).resultNumber == RESULT_NUMBER_OK)


void Gsm_GetResponse_Async(int timeout,
		void (*Callback)(Response_TypeDef response));
void Gsm_GetResponse_Async_Cancel();

int Gsm_ExecuteCommand(CommandType_TypeDef type, CommandAction_TypeDef action,
		void * parameters);
int Gsm_ExecuteCommand_Ex(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char* response);
int Gsm_ExecuteCommand_Ex2(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char* response,
		char* response2);
int Gsm_ExecuteCommand_RetryUntillOk(CommandType_TypeDef type, CommandAction_TypeDef action,
		void * parameters);
int Gsm_ExecuteCommand_RetryUntillOk_Ex(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char* response);
int Gsm_GetResponseReult(int timeout);
void Gsm_Init();




#endif /* GSMMODEM_GSM_H_ */
