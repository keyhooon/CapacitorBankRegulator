/*
 * AtCommandExecuter.c
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#include "AtCommandExecuter.h"
#include "cmsis_os.h"
#include "string.h"

void GetCommandString(char* commandText,
		CommandExecuter_TypeDef commandExecuter, Command_TypeDef command);

CommandExecuter_TypeDef * CommandExecuter_Init(osMessageQId messageId,
		void (*Write)(char *, uint32_t), char * commandLineTermination) {
	CommandExecuter_TypeDef * commandExecuter = pvPortMalloc(
			sizeof(CommandExecuter_TypeDef));

	commandExecuter->commandLineTerminationChar =
			commandLineTermination;
	commandExecuter->Write = Write;
	osMutexDef_t mutex = { 0 };
	commandExecuter->mutexId = osMutexCreate(&mutex);
	commandExecuter->semaphoreId = osSemaphoreCreate(NULL, 1);
	commandExecuter->messageId = messageId;
	osSemaphoreWait(commandExecuter->semaphoreId, 0);
	return commandExecuter;
}
void CommandExecuter_DeInit(CommandExecuter_TypeDef *commandExecuter) {
	osMutexDelete(commandExecuter->mutexId);
	osSemaphoreDelete(commandExecuter->semaphoreId);
	vPortFree(commandExecuter);
}

Response_TypeDef CommandExecuter_Execute(
		CommandExecuter_TypeDef commandExecuter, Command_TypeDef command) {
	char commandString[40];
	Response_TypeDef result;
	osMutexWait(commandExecuter.mutexId, osWaitForever);
	GetCommandString(commandString, commandExecuter, command);
	commandExecuter.Write(commandString, strlen(commandString));
	int maxResponseTime = command.type.maximumResponseTime;
	if (maxResponseTime == 0)
		maxResponseTime = 1000;
	if (osSemaphoreWait(commandExecuter.semaphoreId, maxResponseTime) == osOK)
		result = *(commandExecuter.LastResponse);
	else
	{
		result.Tokens.Items = NULL;
		result.Tokens.IndexNeedToBeReleased = -1;
		result.Tokens.ResultIndex = -1;
		result.status = ResponseStatusError_Timeout;
		result.resultNumber = -1;
	}

	osMutexRelease(commandExecuter.mutexId);
	return result;
}
void GetCommandString(char* commandText,
		CommandExecuter_TypeDef commandExecuter, Command_TypeDef command) {
	switch (command.type.syntax) {
	case basic:
		if (command.parameters != NULL)
			sprintf(commandText, "at%s%d%c", command.type.text,
					*(int *) (command.parameters),
					*commandExecuter.commandLineTerminationChar);
		else
			sprintf(commandText, "at%s%c", command.type.text,
					*commandExecuter.commandLineTerminationChar);
		break;
	case sParameter:
		sprintf(commandText, "ats%d=%d%c", *(int *) (command.parameters),
				*((int *) (command.parameters) + 1),
				*commandExecuter.commandLineTerminationChar);
		break;
	case extended:
		switch (command.action) {
		case Test:
			sprintf(commandText, "at+%s=?%c", command.type.text,
					*commandExecuter.commandLineTerminationChar);
			break;
		case Read:
			sprintf(commandText, "at+%s?%c", command.type.text,
					*commandExecuter.commandLineTerminationChar);
			break;
		case Write:
			sprintf(commandText, "at+%s=", command.type.text);
			uint32_t index = strlen(commandText);
			while (*(char*) command.parameters) {
				uint32_t charIndex = 0;
				while (*(char*) command.parameters)
					*(commandText + index++) = *((*(char**) command.parameters)
							+ charIndex);
				commandText[index++] = ',';
				(command.parameters)++;
			}
			index--;
			commandText[index++] = *commandExecuter.commandLineTerminationChar;
			commandText[index++] = 0;
			break;
		case Execute:
			sprintf(commandText, "at+%s%c", command.type.text,
					*commandExecuter.commandLineTerminationChar);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
