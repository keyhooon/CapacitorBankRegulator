/*
 * CallLog.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "CallLog.h"

const FieldAttribute_Typedef CallLogFieldsAttribute[CALLLOG_FIELD_COUNT] = { //
		{ stringField, 0, 4, 20, 0, (const char*) "Number" }, // CallNumber Field
		{ longField, 4, 8, 0, 0, (const char*) "Date" }, // Date Field
		{ bitField, 12, 4, 0, 0, (const char*) "Successfulity" }, // IsSuccessfully Field
		{ bitField, 12, 0, 0, 0, (const char*) "In/Out" }, // IsIncoming Field

};


CallLog_Typedef * CreateCallLog(char *callNumber, time_t _time,
		uint32_t isSuccessfully, uint32_t isIncoming) {
	int callNumberLen = strlen(callNumber);
	CallLog_Typedef *result = DataAllocator_Alloc(hModelInMemoryAllocator,
			sizeof(CallLog_Typedef) + callNumberLen + 1);

	result->CallNumber = ((char*) result + sizeof(CallLog_Typedef));
	strcpy(result->CallNumber, callNumber);

	result->Time = _time;
	result->IsIncoming = isIncoming;
	result->IsSuccessfully = isSuccessfully;

	return result;
}
void FreeCallLog(CallLog_Typedef * callLog) {
	DataAllocator_Free(hModelInMemoryAllocator, callLog);
}
