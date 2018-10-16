/*
 * CallLog.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#include "time.h"
#ifndef DATAMODEL_CALLLOG_H_
#define DATAMODEL_CALLLOG_H_

#include "main.h"
#include "List_Heap.h"
#include "string.h"

#define CALL_LOG_COMPARATOR(x, y) (x->current_item.Time- y->current_item.Time)

typedef struct {
	int32_t Id;
	uint32_t CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t Reserved1 :24;
} CallLog_Typedef;

DATA_ACCESS_LIST_PROTOTYPES(CallLog)
#endif /* DATAMODEL_CALLLOG_H_ */
