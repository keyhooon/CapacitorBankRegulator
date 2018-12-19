/*
 * Message.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "Message.h"

const FieldAttribute_Typedef MessageFieldsAttribute[MESSAGE_FIELD_COUNT] = { //
		{ stringField, (const char*) "Content", 0, 4, 256, 1 }, // Content Field
				{ stringField, (const char*) "Number", 4, 4, 20, 1 }, // CallNumber Field
				{ longField, (const char*) "Time", 8, 8, 0, 0 }, // CallNumber Field
				{ bitField, (const char*) "Success", 20, 4, 0, 0 }, // CallNumber Field
				{ bitField, (const char*) "Incoming", 20, 0, 0, 0 }, // CallNumber Field
		};
Message_Typedef * CreateMessage(char *content, char *callNumber, time_t _time,
		uint32_t isSuccessfully, uint32_t isIncoming) {
	int ContentLen = strlen(content);
	int callNumberLen = strlen(callNumber);
	Message_Typedef *result = DataAllocator_Alloc(hModelInMemoryAllocator,
			sizeof(Message_Typedef) + ContentLen + callNumberLen + 2);
	result->Content = ((char*) result + sizeof(Message_Typedef));
	strcpy(result->Content, content);

	result->CallNumber = result->Content + ContentLen + 1;
	strcpy(result->CallNumber, callNumber);

	result->Time = _time;
	result->IsIncoming = isIncoming;
	result->IsSuccessfully = isSuccessfully;

	return result;
}
void FreeMessage(Message_Typedef * message) {
	DataAllocator_Free(hModelInMemoryAllocator, message);
}


