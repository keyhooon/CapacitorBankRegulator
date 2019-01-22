/*
 * AtCommandExecuter.c
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#include "AtCommandExecuter.h"
#include "cmsis_os.h"
#include "string.h"
const char Ctrl_Z = 26;

int strcpyl(char *dest, const char *src);
void CommandExecuter_Task(void const * argument);
void GetCommandString(char* commandText,
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command);

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
	unsigned int lengthToProcess = 0;
	while (1) {
		osEvent event = osMessageGet(currentCommandExecuter->messageId,
		osWaitForever);
		lengthToProcess += event.value.v;
		if (event.status == osEventMessage) {
			response = ResponseParse(currentCommandExecuter->commandTokenizer,
					&lengthToProcess);
			while (response.Tokens.Items != NULL)
			{
				// pass response.token.item string to function that registered to any of unsolicited code
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
					{
						char * arg = response.Tokens.Items[i + 1];
						p->ResponseReceivedCallback(responseToken, arg);
						// remove token from tokensList
						CommandTokenizer_RemoveTokenFromList(response.Tokens,
								i);
					}
				}
				if (response.status == ResponseStatusOk) {
					if (responseResultList[response.resultNumber].type == final)
					{
						// pass response to function that call at command
						currentCommandExecuter->LastResponse = response;
						osSemaphoreRelease(currentCommandExecuter->semaphoreId);
					}
					else if (currentCommandExecuter->UnsolicitedResultCode) {
						// pass response to function that responsible to Unsilicited Result
						currentCommandExecuter->UnsolicitedResultCode(response);
						CommandTokenizer_FreeTokenList(response.Tokens);
					}
				} else {
					// remove response if there isnt any result.
					CommandTokenizer_FreeTokenList(response.Tokens);
				}

				if (lengthToProcess == 0)
					response.Tokens.Items = NULL;
				else
					response = ResponseParse(
							currentCommandExecuter->commandTokenizer,
							&lengthToProcess);
			}
			if (CheckPattern(
					currentCommandExecuter->commandTokenizer.bufferStream,
					"> "))
			{
				lengthToProcess -= 2;
				response.status = ResponseStatusOk_WaitForData;
				currentCommandExecuter->LastResponse = response;
				osSemaphoreRelease(currentCommandExecuter->semaphoreId);
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

Response_TypeDef CommandExecuter_ExecuteWithData(
		CommandExecuter_TypeDef *commandExecuter, Command_TypeDef command,
		char * data) {
	char commandString[40];
	Response_TypeDef result;
	osRecursiveMutexWait(commandExecuter->mutexId, osWaitForever);
	GetCommandString(commandString, commandExecuter, command);
	commandExecuter->Write(commandString, strlen(commandString));
	// TODO: if write set with dma, we cant write imediately after one write, and Executing has error.
	if (CommandExecuter_GetResponse(commandExecuter, 1000).status
			== ResponseStatusOk_WaitForData)
	{
		commandExecuter->Write(data, strlen(data));
		commandExecuter->Write(&Ctrl_Z, 1);
	}
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
