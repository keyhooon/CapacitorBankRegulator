/*
 * Message.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_MESSAGE_H_
#define DATAMODEL_MESSAGE_H_

#include "main.h"
#include "List_Heap.h"
#include "string.h"
#include "time.h"

#define MESSAGE_COMPARATOR(x, y) (x->current_item.Time- y->current_item.Time)

typedef struct {
	int32_t Id;
	char * Content;
	uint32_t CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t Reserved1 :24;
} Message_Typedef;

DATA_ACCESS_LIST_PROTOTYPES(Message)
#endif /* DATAMODEL_MESSAGE_H_ */
