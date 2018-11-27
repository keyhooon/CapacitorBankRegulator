/*
 * AtCommandExecuter.h
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_EXECUTER_ATCOMMANDEXECUTER_H_
#define GSMMODEM_EXECUTER_ATCOMMANDEXECUTER_H_

#include "cmsis_os.h"
#include "Parser/AtCommandParser.h"

typedef struct AtCommandExecuter_Struct {
	char * commandLineTerminationChar;			// s3
	void (*Write)(char *, uint32_t);
	void (*ResponseReceavedCallback)(Response_TypeDef);
	Response_TypeDef * LastResponse;
	CommandTokenizer_TypeDef commandTokenizer;
	osMutexId mutexId;
	osSemaphoreId semaphoreId;
	osMessageQId messageId;
	osThreadId threadId;
	osTimerId timerId;
} CommandExecuter_TypeDef;

typedef enum {
	basic, sParameter, extended,
} CommandSyntax_TypeDef;

typedef enum {
	Test, Read, Write, Execute
} CommandAction_TypeDef;

typedef enum {
	string, integer
} CommandParameterType_TypeDef;

typedef struct {
	const char * text;
	uint32_t maximumResponseTime;
	CommandSyntax_TypeDef syntax;
} CommandType_TypeDef;

typedef struct {
	CommandType_TypeDef type;
	union {
		CommandAction_TypeDef action;
		CommandParameterType_TypeDef parameterType;
	} properties;
	void * parameters;
} Command_TypeDef;

CommandExecuter_TypeDef * CommandExecuter_Init(void (*Write)(char *, uint32_t),
		CommandTokenizer_TypeDef tokenizer, char * commandLineTermination);
void CommandExecuter_DeInit(CommandExecuter_TypeDef *commandExecuter);
void CommandExecuter_HandleReceivedResponse(
		CommandExecuter_TypeDef *commandExecuter, uint32_t Length);
Response_TypeDef CommandExecuter_Execute(
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command);
Response_TypeDef CommandExecuter_GetResponse(
		CommandExecuter_TypeDef *commandExecuter, int timeout);
void CommandExecuter_GetResponse_Async(CommandExecuter_TypeDef *commandExecuter,
		int timeout, void (*Callback)(Response_TypeDef response));
void CommandExecuter_GetResponse_Async_Cancel(
		CommandExecuter_TypeDef *commandExecuter);
#endif /* GSMMODEM_EXECUTER_ATCOMMANDEXECUTER_H_ */
