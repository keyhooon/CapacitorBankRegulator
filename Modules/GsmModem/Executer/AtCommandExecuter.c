/*
 * AtCommandExecuter.c
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#include "AtCommandExecuter.h"
#include "cmsis_os.h"
#include "string.h"

void CommandExecuter_Task(void const * argument);
void GetCommandString(char* commandText,
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command);
void CommandExecuter_GetResponse_Async_Timeout(void *Arg);
void CommandExecuter_GetResponse_Async_End(
		CommandExecuter_TypeDef *commandExecuter);

CommandExecuter_TypeDef * CommandExecuter_Init(void (*Write)(char *, uint32_t),
		CommandTokenizer_TypeDef tokenizer, char * commandLineTermination) {
	CommandExecuter_TypeDef * commandExecuter = pvPortMalloc(
			sizeof(CommandExecuter_TypeDef));

	commandExecuter->commandLineTerminationChar = commandLineTermination;
	commandExecuter->Write = Write;
	commandExecuter->commandTokenizer = tokenizer;
	osMutexDef(CommandExecuter);
	osMessageQDef(CommandExecuter, 5, unsigned int);
	osSemaphoreDef(CommandExecuter);
	osThreadDef(CommandExecuter, CommandExecuter_Task, osPriorityAboveNormal, 0,
			256);

	commandExecuter->mutexId = osRecursiveMutexCreate(osMutex(CommandExecuter));
	commandExecuter->semaphoreId = osSemaphoreCreate(
			osSemaphore(CommandExecuter), 1);
	commandExecuter->messageId = osMessageCreate(osMessageQ(CommandExecuter),
			NULL);
	commandExecuter->threadId = osThreadCreate(osThread(CommandExecuter),
			commandExecuter);

	osSemaphoreWait(commandExecuter->semaphoreId, 0);
	return commandExecuter;
}
void CommandExecuter_DeInit(CommandExecuter_TypeDef *commandExecuter) {
	osMutexDelete(commandExecuter->mutexId);
	osSemaphoreDelete(commandExecuter->semaphoreId);
	vPortFree(commandExecuter);
}

void CommandExecuter_Task(void const * argument) {
	CommandExecuter_TypeDef * currentCommandExecuter = argument;
	Response_TypeDef response;
	currentCommandExecuter->LastResponse = &response;
	while (1) {
		osEvent event = osMessageGet(currentCommandExecuter->messageId,
		osWaitForever);

		if (event.status == osEventMessage) {
			response = ResponseParse(currentCommandExecuter->commandTokenizer,
					event.value.v);
			if (response.status)
			if (currentCommandExecuter->ResponseReceivedCallback != NULL)
				osSemaphoreRelease(currentCommandExecuter->semaphoreId);
			else
				CommandExecuter_GetResponse_Async_End(currentCommandExecuter);
		}
	}
}

void CommandExecuter_HandleReceivedResponse(
		CommandExecuter_TypeDef * commandExecuter, uint32_t Length) {
	osMessagePut(commandExecuter->messageId, Length, osWaitForever);
}

Response_TypeDef CommandExecuter_Execute(
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command) {
	char commandString[40];
	Response_TypeDef result;
	osRecursiveMutexWait(commandExecuter->mutexId, osWaitForever);
	GetCommandString(commandString, commandExecuter, command);
	commandExecuter->Write(commandString, strlen(commandString));
	int maxResponseTime = command.type.maximumResponseTime;
	if (maxResponseTime == 0)
		maxResponseTime = 1000;
	result = CommandExecuter_GetResponse(commandExecuter, maxResponseTime);
	osRecursiveMutexRelease(commandExecuter->mutexId);
	return result;
}

Response_TypeDef CommandExecuter_GetResponse(
		CommandExecuter_TypeDef *commandExecuter, int timeout) {
	osRecursiveMutexWait(commandExecuter->mutexId, osWaitForever);
	Response_TypeDef result;
	if (osSemaphoreWait(commandExecuter->semaphoreId, timeout) == osOK)
		result = *(commandExecuter->LastResponse);
	else {
		result.Tokens.Items = NULL;
		result.Tokens.IndexNeedToBeReleased = -1;
		result.Tokens.ResultIndex = -1;
		result.status = ResponseStatusError_Timeout;
		result.resultNumber = -1;
	}
	osRecursiveMutexRelease(commandExecuter->mutexId);
	return result;
}

void CommandExecuter_GetResponse_Async(CommandExecuter_TypeDef *commandExecuter,
		int timeout, void (*Callback)(Response_TypeDef response)) {
	Response_TypeDef result;
	osRecursiveMutexWait(commandExecuter->mutexId, osWaitForever);
	osTimerDef(CommandExecuter, CommandExecuter_GetResponse_Async_Timeout);
	commandExecuter->timerId = osTimerCreate(osTimer(CommandExecuter),
			osTimerOnce, commandExecuter);
	osTimerStart(commandExecuter->timerId, timeout);
	commandExecuter->ResponseReceivedCallback = Callback;
}
void CommandExecuter_GetResponse_Async_Cancel(
		CommandExecuter_TypeDef *commandExecuter) {
	if (commandExecuter->ResponseReceivedCallback != NULL)
		commandExecuter->ResponseReceivedCallback = NULL;
	osTimerDelete(commandExecuter->timerId);
	osRecursiveMutexRelease(commandExecuter->mutexId);
}
void CommandExecuter_GetResponse_Async_Timeout(void *Arg) {
	CommandExecuter_TypeDef *commandExecuter = Arg;
	CommandExecuter_GetResponse_Async_Cancel(commandExecuter);
}
void CommandExecuter_GetResponse_Async_End(
		CommandExecuter_TypeDef *commandExecuter) {
	commandExecuter->ResponseReceivedCallback(*commandExecuter->LastResponse);
	CommandExecuter_GetResponse_Async_Cancel(commandExecuter);
}

void GetCommandString(char* commandText,
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command) {
	switch (command.type.syntax) {
	case basic:
		if (command.parameters != NULL)
			if (command.properties.parameterType == string) {
				sprintf(commandText, "at%s%s%c", command.type.text,
						(char *) (command.parameters),
						commandExecuter->commandLineTerminationChar);
			} else if (command.properties.parameterType == integer) {
				sprintf(commandText, "at%s%d%c", command.type.text,
					*(int *) (command.parameters),
						commandExecuter->commandLineTerminationChar);
			}
		else
			sprintf(commandText, "at%s%c", command.type.text,
						commandExecuter->commandLineTerminationChar);
		break;
	case sParameter:
		sprintf(commandText, "ats%d=%d%c", *(int *) (command.parameters),
				*((int *) (command.parameters) + 1),
				commandExecuter->commandLineTerminationChar);
		break;
	case extended:
		switch (command.properties.action) {
		case Test:
			sprintf(commandText, "at+%s=?%c", command.type.text,
					commandExecuter->commandLineTerminationChar);
			break;
		case Read:
			sprintf(commandText, "at+%s?%c", command.type.text,
					commandExecuter->commandLineTerminationChar);
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
			commandText[index++] = commandExecuter->commandLineTerminationChar;
			commandText[index++] = 0;
			break;
		case Execute:
			sprintf(commandText, "at+%s%c", command.type.text,
					commandExecuter->commandLineTerminationChar);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
