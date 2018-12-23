/*
 * Message.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "Message.h"

const FieldAttribute_Typedef MessageFieldsAttribute[MESSAGE_FIELD_COUNT] = { //
		{ stringField, 0, 4, 256, 1, (const char*) "Content" }, // Content Field
				{ stringField, 4, 4, 20, 1, (const char*) "Number" }, // CallNumber Field
				{ longField, 8, 8, 0, 0, (const char*) "Time" }, // CallNumber Field
				{ bitField, 20, 4, 0, 0, (const char*) "Success" }, // CallNumber Field
				{ bitField, 20, 0, 0, 0, (const char*) "Incoming" }, // CallNumber Field
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


