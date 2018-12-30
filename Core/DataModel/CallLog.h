/*
 * CallLog.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */


#ifndef DATAMODEL_CALLLOG_H_
#define DATAMODEL_CALLLOG_H_

#include "string.h"
#include "time.h"
#include "DataModel.h"

#define CALLLOG_COMPARATOR(calllog1, calllog2) 	(calllog1.Time > calllog2.Time ?-1 : (calllog1.Time == calllog2.Time? 0 : 1))

#define CALLLOG_PREVIEW(display, callLog) \
	struct tm *info; \
	char buffer[40]; \
	 info = localtime( &(callLog.Time) ); \
	strftime(buffer,40,"%x - %I:%M%p", info); \
		sprintf(display, "%s\r\n %.20s",callLog.CallNumber, buffer);

#define CALLLOG_VIEW(display, callLog) \
	struct tm *info; \
	char buffer[40]; \
	 info = localtime( &(callLog.Time) ); \
	strftime(buffer,40,"%c", info); \
		sprintf(display, "%s\r\n %s",callLog.CallNumber, buffer);

#define CALLLOG_MODEL_DATA_ALLOCATOR			hModelInMemoryAllocator

#define CALLLOG_FIELD_COUNT						4


typedef struct {
	char * CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t Reserved1 :24;
} CallLog_Typedef;

extern const FieldAttribute_Typedef CallLogFieldsAttribute[CALLLOG_FIELD_COUNT];

CallLog_Typedef * CreateCallLog(char *callNumber, time_t Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming);
void FreeCallLog(CallLog_Typedef * calllog);
#endif /* DATAMODEL_CALLLOG_H_ */
