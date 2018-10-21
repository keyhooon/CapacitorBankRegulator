/*
 * CallLog.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "CallLog.h"
#include "List_Heap.h"

#define CALLLOG_COMPARATOR(x, y) SGLIB_NUMERIC_COMPARATOR(x->current_item.Time, y->current_item.Time)

#define DISPLAY_CALLLOG(display, callLog) \
		sprintf(display, "%.11s, %.10s", callLog.CallNumber, callLog.Time);

DATA_ACCESS_LIST_FUNCTIONS(CallLog, CALLLOG_COMPARATOR, DISPLAY_CALLLOG)

