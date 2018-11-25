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
	Response_TypeDef * LastResponse;
	osMutexId mutexId;
	osSemaphoreId semaphoreId;
	osMessageQId messageId;
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

CommandExecuter_TypeDef * CommandExecuter_Init(osMessageQId messageId,
		void (*Write)(char *, uint32_t), char * commandLineTermination);
void CommandExecuter_DeInit(CommandExecuter_TypeDef *commandExecuter);
Response_TypeDef CommandExecuter_Execute(
		CommandExecuter_TypeDef commandExecuter, Command_TypeDef command);

#endif /* GSMMODEM_EXECUTER_ATCOMMANDEXECUTER_H_ */
