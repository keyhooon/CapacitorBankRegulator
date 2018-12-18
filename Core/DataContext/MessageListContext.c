/*
 * MessageListContext.c
 *
 *  Created on: Dec 18, 2018
 *      Author: HP
 */


#include "MessageListContext.h"

extern int hMemoryDataContextAllocator;

DATA_CONTEXT_FUNCTIONS(Message, MESSAGE, hMemoryDataContextAllocator);



void SeedMessage() {
	AddMessageEx((const char*) "Hi", (const char*) "09124575442", 1545090000, 1,
			0);
	AddMessageEx((const char*) "I am @ the work", (const char*) "09124463992",
			1545000000, 1, 1);
	AddMessageEx((const char*) "Come On!!!!", (const char*) "09127093902",
			1545000001, 0, 1);
	AddMessageEx((const char*) "Work on progress", (const char*) "09121015197",
			1545000002, 1, 1);
	AddMessageEx((const char*) "Wood & Metal", (const char*) "09121143144",
			1545000003, 0, 1);
	AddMessageEx((const char*) "Sry!!!", (const char*) "09354463261",
			1545091200, 0, 1);
}

void AddMessageEx(char * Content, char * CallNumber, time_t _Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming) {
	Message_Typedef *message = CreateMessage(Content, CallNumber, _Time,
			IsSuccessfully, IsIncoming);
	AddMessage(message);
	FreeMessage(message);
}
