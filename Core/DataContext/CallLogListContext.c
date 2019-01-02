/*
 * CallLogListContext.c
 *
 *  Created on: Dec 30, 2018
 *      Author: HP
 */




#include "CallLogListContext.h"

extern int hMemoryDataContextAllocator;

DATA_CONTEXT_FUNCTIONS(CallLog, CALLLOG, hMemoryDataContextAllocator);

void SeedCallLog() {
	AddCallLogEx((const char*) "09124575442", 1545090000, 1, 0);
	AddCallLogEx((const char*) "09124463992", 1545000000, 1, 1);
	AddCallLogEx((const char*) "09127093902", 1545000001, 0, 1);
	AddCallLogEx((const char*) "09121015197", 1545000002, 1, 1);
	AddCallLogEx((const char*) "09121143144", 1545000003, 0, 1);
	AddCallLogEx((const char*) "09354463261", 1545091200, 0, 1);
}

void AddCallLogEx(char * CallNumber, time_t _Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming) {
	CallLog_Typedef *callLog = CreateCallLog(CallNumber, _Time,
			IsSuccessfully, IsIncoming);
	AddCallLog(callLog);
	FreeCallLog(callLog);
}
