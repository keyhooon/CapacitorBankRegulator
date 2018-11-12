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
void Gsm_Init(osMessageQId GSMMessageQHandle)
{
	GSM_IO_Init();
	osMessageQDef(Gsm, 1, unsigned int);
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
extern osMessageQId GSMMessageQHandle;
void GSM_DataReceivedCallback(uint32_t Length) {
	osMessagePut(GSMMessageQHandle, Length, osWaitForever);
}
