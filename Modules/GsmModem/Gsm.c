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
CommandExecuter_TypeDef *GsmCommandExecuter;

void Gsm_GetResponse_Async_End(Response_TypeDef response);
void (*Callback_GetResponse)(Response_TypeDef response);

void Gsm_GetResponse_Async(int timeout,
		void (*Callback)(Response_TypeDef response)) {
	Callback_GetResponse = Callback;
	CommandExecuter_GetResponse_Async(GsmCommandExecuter, timeout,
			Gsm_GetResponse_Async_End);
}
void Gsm_GetResponse_Async_Cancel() {
	CommandExecuter_GetResponse_Async_Cancel(GsmCommandExecuter);
}
void Gsm_GetResponse_Async_End(Response_TypeDef response) {
	Callback_GetResponse(response);
	CommandTokenizer_FreeTokenList(response.Tokens);
}
int Gsm_ExecuteCommand(CommandType_TypeDef type, CommandAction_TypeDef action,
		void * parameters) {
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef response;
	response = CommandExecuter_Execute(GsmCommandExecuter, command);
	CommandTokenizer_FreeTokenList(response.Tokens);
	return response.resultNumber;
}
int Gsm_ExecuteCommand_WithData(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char * data) {
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef response;
	response = CommandExecuter_ExecuteWithData(GsmCommandExecuter, command,
			data);
	CommandTokenizer_FreeTokenList(response.Tokens);
	return response.resultNumber;
}
int Gsm_ExecuteCommand_Ex(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char* response) {
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef res;
	res = CommandExecuter_Execute(GsmCommandExecuter, command);
	if (CHECK_RESPONSE(res))
		strcpy(response, res.Tokens.Items[0]);
	else
		*response = 0;
	CommandTokenizer_FreeTokenList(res.Tokens);
	return res.resultNumber;
}
int Gsm_ExecuteCommand_Ex2(CommandType_TypeDef type,
		CommandAction_TypeDef action, void * parameters, char* response,
		char* response2) {
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef res;
	res = CommandExecuter_Execute(GsmCommandExecuter, command);
	if (CHECK_RESPONSE(res))
	{
		if (response != NULL)
			strcpy(response, res.Tokens.Items[0]);
		if (response2 != NULL)
			strcpy(response2, res.Tokens.Items[1]);
	}
	else
	{
		*response = 0;
		*response2 = 0;
	}
	CommandTokenizer_FreeTokenList(res.Tokens);
	return res.resultNumber;
}


int Gsm_ExecuteCommand_RetryUntillOk(CommandType_TypeDef type, CommandAction_TypeDef action,
		void * parameters) {
	int register r = DefaultRetriesCount;
	Response_TypeDef response;
	while (r--) {
		Command_TypeDef command = { type, action, parameters };
		response = CommandExecuter_Execute(GsmCommandExecuter, command);
		CommandTokenizer_FreeTokenList(response.Tokens);
		if (CHECK_RESPONSE(response)) {
			break;
		}
		CommandTokenizer_FreeTokenList(response.Tokens);
	}
	return response.resultNumber;
}

int Gsm_ExecuteCommand_RetryUntillOk_Ex(CommandType_TypeDef type,
		CommandAction_TypeDef action,
		void * parameters, char* response) {
	int register r = DefaultRetriesCount;
	Command_TypeDef command = { type, action, parameters };
	Response_TypeDef res;
	while (r--) {
		res = CommandExecuter_Execute(GsmCommandExecuter, command);
		if (CHECK_RESPONSE(res)) {
			strcpy(response, res.Tokens.Items[0]);
			CommandTokenizer_FreeTokenList(res.Tokens);
			return res.resultNumber;
		}
		CommandTokenizer_FreeTokenList(res.Tokens);
	}
	*response = 0;
	return res.resultNumber;
}

void Gsm_Init()
{
	GSM_IO_Init();
	CommandTokenizer_TypeDef tokenizer = { BOARD_COMx_BUFFER_STREAM[GSM_COM],
			ATCOMMAND_SEPERATOR, ATCOMMAND_FOOTER };
	GsmCommandExecuter = CommandExecuter_Init(GSM_IO_Write, tokenizer,
			COMMAND_LINE_TERMINATION_CAHR_DEFAULT);
	Call_init(GsmCommandExecuter);
	Message_init(GsmCommandExecuter);

}

void GSM_DataReceivedCallback(uint32_t Length) {
	if (GsmCommandExecuter != NULL)
	CommandExecuter_HandleReceivedResponse(GsmCommandExecuter, Length);
}
