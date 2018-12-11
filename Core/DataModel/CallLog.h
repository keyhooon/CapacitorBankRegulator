/*
 * CallLog.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */


#ifndef DATAMODEL_CALLLOG_H_
#define DATAMODEL_CALLLOG_H_

#include "main.h"
#include "string.h"
#include "time.h"
#include "../DataManager/List_Heap.h"

typedef struct {
	int32_t Id;
	uint32_t CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t Reserved1 :24;
} CallLog_Typedef;

DATA_ACCESS_LIST_PROTOTYPES(CallLog)

void seedCallLog();
#endif /* DATAMODEL_CALLLOG_H_ */
