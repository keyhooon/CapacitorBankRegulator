/*
 * Gsm.c
 *
 *  Created on: Nov 5, 2018
 *      Author: HP
 */

#include <Parser/AtCommandParser.h>
#include "Gsm.h"
#include "cmsis_os.h"

const char *ATCOMMAND_SEPERATOR = "\r\n";
const char *ATCOMMAND_FOOTER = "\r";




Gsm_TypeDef GsmModem;
void Gsm_Init(BufferStream_TypeDef *inputBuffer,
		void (*Write)(char *, uint32_t))
{
	osMessageQDef(Gsm, 1, unsigned int);
	GsmModem.commandExecuter = CommandExecuter_Init(
			osMessageCreate(osMessageQ(Gsm), NULL), Write,
			COMMAND_LINE_TERMINATION_CAHR_DEFAULT);
	GsmModem.commandTokenizer = CommandTokenizer_Init(inputBuffer,
			ATCOMMAND_SEPERATOR, ATCOMMAND_FOOTER);
	GSM_IO_Init();
}

void GSM_Main(void const * argument)
{
	const GsmModem_initParam_typeDef *param = argument;
	Gsm_Init(param->inputBuffer, param->Write);
	Response_TypeDef response;
	while(1)
	{
		osEvent event = osMessageGet(GsmModem.commandExecuter->messageId,
				osWaitForever);

		if (event.status == osEventMessage)
		{
			response = ResponseParse(*GsmModem.commandTokenizer,
					event.value.v);
			if (osSemaphoreGetCount(GsmModem.commandExecuter->semaphoreId))
			{
				GsmModem.commandExecuter->LastResponse = response;
				osSemaphoreRelease(GsmModem.commandExecuter->semaphoreId);
			}
		}
	}
}

void GSM_DataReceivedCallback(uint32_t Length) {
	osMessagePut(GsmModem.commandExecuter->messageId, Length, osWaitForever);
}
