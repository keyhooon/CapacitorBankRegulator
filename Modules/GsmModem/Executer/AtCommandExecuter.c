/*
 * AtCommandExecuter.c
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#include "AtCommandExecuter.h"
#include "cmsis_os.h"
#include "string.h"

int strcpyl(char *dest, const char *src);
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
	commandExecuter->responseReceivedCallbacks = 0;
	osMutexDef(CommandExecuter);
	osMessageQDef(CommandExecuter, 5, unsigned int);
	osSemaphoreDef(CommandExecuter);
	osThreadDef(CommandExecuter, CommandExecuter_Task, osPriorityAboveNormal, 0,
			512);

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
	while (1) {
		osEvent event = osMessageGet(currentCommandExecuter->messageId,
		osWaitForever);

		if (event.status == osEventMessage) {
			response = ResponseParse(currentCommandExecuter->commandTokenizer,
					&event.value.v);
			while (response.Tokens.Items != NULL)
			{
				for (int i = 0; *(response.Tokens.Items + i) != NULL; i++) {
					char * responseToken = *(response.Tokens.Items + i);
					char * responseDelim = strchr(responseToken, ':');
					if (responseDelim == NULL)
						continue;
					int responseNameLen = responseDelim - responseToken;
					ResponseReceivedCallbackList_typedef *p;
					for (p = (currentCommandExecuter->responseReceivedCallbacks);
							p != NULL
									&& memcmp(p->ResponseName, responseToken,
											responseNameLen) != 0; p = p->next)
						;
					if (p != NULL && p->ResponseReceivedCallback)
						p->ResponseReceivedCallback(responseToken);
				}

				if (response.status == ResponseStatusOk) {
					if (responseResultList[response.resultNumber].type == final)
					{
						currentCommandExecuter->LastResponse = response;
						osSemaphoreRelease(currentCommandExecuter->semaphoreId);
					}
					else if (currentCommandExecuter->UnsolicitedResultCode) {
						currentCommandExecuter->UnsolicitedResultCode(response);
						CommandTokenizer_FreeTokenList(response.Tokens);
					}
				} else {
					CommandTokenizer_FreeTokenList(response.Tokens);
				}
				if (event.value.v == 0)
					response.Tokens.Items = NULL;
				else
					response = ResponseParse(
							currentCommandExecuter->commandTokenizer,
							&event.value.v);
			}
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
		result = (commandExecuter->LastResponse);
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
void GetCommandString(char* commandText,
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command) {
	int index = 0;
	commandText[index++] = 'A';
	commandText[index++] = 'T';
	switch (command.type.syntax) {
	case basic:
		index += strcpyl(&commandText[index], command.type.text);
		index += strcpyl(&commandText[index], command.parameters);
		break;
	case sParameter:
		commandText[index++] = 'S';
		char t[4];
		int tLen;
		itoa(*(int *) (command.parameters), t, 10);
		index += strcpyl(&commandText[index], t);
		commandText[index++] = '=';
		itoa(*((int *) (command.parameters) + 1), t, 10);
		index += strcpyl(&commandText[index], t);
		break;
	case extended:
		commandText[index++] = '+';
		index += strcpyl(&commandText[index], command.type.text);
		switch (command.action) {
		case Test:
			commandText[index++] = '=';
			commandText[index++] = '?';
			break;
		case Read:
			commandText[index++] = '?';
			break;
		case Execute:
			break;
		case Write:
			commandText[index++] = '=';
			index += strcpyl(&commandText[index], *(char**) command.parameters);
			command.parameters = ((char**) command.parameters) + 1;
			while (*(char**) command.parameters) {
				commandText[index++] = ',';
				index += strcpyl(&commandText[index],
						*(char**) command.parameters);
				command.parameters = ((char**) command.parameters) + 1;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	index += strcpyl(&commandText[index],
			commandExecuter->commandLineTerminationChar);
}

int strcpyl(char *dest, const char *src) {
	char *d = dest;
	const char *s = src;
	while (*s)
		*d++ = *s++;
	*d = 0;
	return s - src;
}
