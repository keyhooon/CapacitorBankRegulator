/*
 * Gsm.c
 *
 *  Created on: Nov 5, 2018
 *      Author: HP
 */

#include <Parser/AtCommandParser.h>
#include "Gsm.h"
#include "cmsis_os.h"
#include "Board.h"

const char *ATCOMMAND_SEPERATOR = "\r\n";
const char *ATCOMMAND_FOOTER = "\r";


extern BufferStream_TypeDef *BOARD_COMx_BUFFER_STREAM[COMn];

Gsm_TypeDef GsmModem;

int Gsm_ExecuteCommand(CommandType_TypeDef type, CommandAction_TypeDef action,
		void * parameters) {
	int register r = DefaultRetriesCount;
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef response;
	while (r--) {
		response = CommandExecuter_Execute(*(GsmModem.commandExecuter),
				command);
		if (CHECK_RESPONSE(response)) {
			CommandTokenizer_FreeTokenList(response.Tokens);
			return 1;
		}
		CommandTokenizer_FreeTokenList(response.Tokens);
	}
	return 0;
}

int Gsm_ExecuteCommand_Ex(CommandType_TypeDef type,
		CommandAction_TypeDef action,
		void * parameters, char* response) {
	int register r = DefaultRetriesCount;
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef res;
	while (r--) {
		res = CommandExecuter_Execute(*(GsmModem.commandExecuter),
				command);
		if (CHECK_RESPONSE(res)) {
			strcpy(response, res.Tokens.Items[0]);
			CommandTokenizer_FreeTokenList(res.Tokens);
			return 1;
		}
		CommandTokenizer_FreeTokenList(res.Tokens);
	}
	*response = 0;
	return 0;
}
void Gsm_Init(osMessageQId GSMMessageQHandle)
{
	osMessageQDef(Gsm, 1, unsigned int);
	GSM_IO_Init();

	GsmModem.commandExecuter = CommandExecuter_Init(GSMMessageQHandle,
			GSM_IO_Write,
			COMMAND_LINE_TERMINATION_CAHR_DEFAULT);
	GsmModem.commandTokenizer = CommandTokenizer_Init(
			BOARD_COMx_BUFFER_STREAM[GSM_COM], ATCOMMAND_SEPERATOR,
			ATCOMMAND_FOOTER);

}

void GSM_Main(void const * argument)
{
	osMessageQId GSMMessageQHandle = *(osMessageQId*) argument;
	Gsm_Init(GSMMessageQHandle);
	Response_TypeDef response;
	GsmModem.commandExecuter->LastResponse = &response;
	while(1)
	{
		osEvent event = osMessageGet(GsmModem.commandExecuter->messageId,
				osWaitForever);

		if (event.status == osEventMessage)
		{
			response = ResponseParse(*GsmModem.commandTokenizer,
					event.value.v);

				osSemaphoreRelease(GsmModem.commandExecuter->semaphoreId);
		}
	}
}
extern osMessageQId GSMMessageQHandle;
void GSM_DataReceivedCallback(uint32_t Length) {
	osMessagePut(GSMMessageQHandle, Length, osWaitForever);
}
