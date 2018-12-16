/*
 * CallLog.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "CallLog.h"

#define CALLLOG_COMPARATOR(x, y) SGLIB_NUMERIC_COMPARATOR(x->current_item.Time, y->current_item.Time)

#define DISPLAY_CALLLOG(display, callLog) \
	struct tm *info; \
	char buffer[40]; \
	 info = localtime( &(callLog.Time) ); \
	strftime(buffer,40,"%x - %I:%M%p", info); \
		sprintf(display, "%s\r\n %.20s",callLog.CallNumber, buffer);

#define DISPLAY_CALLLOG_DETAIL(display, callLog) \
	struct tm *info; \
	char buffer[40]; \
	 info = localtime( &(callLog.Time) ); \
	strftime(buffer,40,"%c", info); \
		sprintf(display, "%s\r\n %s",callLog.CallNumber, buffer);



DATA_ACCESS_LIST_FUNCTIONS(CallLog, CALLLOG_COMPARATOR, DISPLAY_CALLLOG,
		DISPLAY_CALLLOG_DETAIL)


static void AddCallLogEx(char * CallNumber, time_t Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming);


void SeedCallLog() {
	AddCallLogEx((const char*) "09124575442", 20000, 0, 1);
	AddCallLogEx((const char*) "09124463992", 30000, 1, 0);
	AddCallLogEx((const char*) "09127093902", 40000, 0, 0);
	AddCallLogEx((const char*) "09121015197", 25000, 0, 1);
	AddCallLogEx((const char*) "-", 35000, 1, 1);
	AddCallLogEx((const char*) "09354463261", 28000, 1, 0);
}

static void AddCallLogEx(char * CallNumber, time_t Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming) {
	CallLog_Typedef callLog = { 0, pvPortMalloc(strlen(CallNumber)), Time,
			IsSuccessfully, IsIncoming };
	strcpy(callLog.CallNumber, CallNumber);
	AddCallLog(&callLog);
}
