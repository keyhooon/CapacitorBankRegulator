/*
 * CallLogListContext.h
 *
 *  Created on: Dec 30, 2018
 *      Author: HP
 */

#ifndef DATACONTEXT_CALLLOGLISTCONTEXT_H_
#define DATACONTEXT_CALLLOGLISTCONTEXT_H_


#include "MemoryDataContext.h"
#include "CallLog.h"

DATA_CONTEXT_PROTOTYPES(CallLog);

void SeedCallLog();
void AddCallLogEx(char * CallNumber, time_t Time, uint32_t IsSuccessfully,
		uint32_t IsIncoming);

#endif /* DATACONTEXT_CALLLOGLISTCONTEXT_H_ */
