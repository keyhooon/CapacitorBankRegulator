/*
 * Message.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_MESSAGE_H_
#define DATAMODEL_MESSAGE_H_

#include "main.h"
#include "string.h"
#include "time.h"
#include "../DataManager/List_Heap.h"



typedef struct {
	int32_t Id;
	char * Content;
	char * CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t Reserved1 :24;
} Message_Typedef;

DATA_ACCESS_LIST_PROTOTYPES(Message)

void SeedMessage();
#endif /* DATAMODEL_MESSAGE_H_ */
