/*
 * Message.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_MESSAGE_H_
#define DATAMODEL_MESSAGE_H_

#include "DataModel.h"
#include "string.h"
#include "time.h"

#define MESSAGE_COMPARATOR(message1, message2) 	(message1.Time > message2.Time ?-1 : (message1.Time == message2.Time? 0 : 1))

#define MESSAGE_PREVIEW(display, message) 		sprintf(display, "%.16s", message.Content)

#define MESSAGE_VIEW(display, message) 			sprintf(display, "%.20s\r\n%s",message.CallNumber, message.Content)

#define MESSAGE_MODEL_DATA_ALLOCATOR			hModelInMemoryAllocator

#define MESSAGE_FIELD_COUNT						6




typedef struct {
	char * Content;
	char * CallNumber;
	time_t Time;
	uint32_t IsSuccessfully :1;
	uint32_t IsIncoming :1;
	uint32_t IsRead :1;
	uint32_t Reserved1 :29;
} Message_Typedef;

extern const FieldAttribute_Typedef MessageFieldsAttribute[MESSAGE_FIELD_COUNT];

Message_Typedef * CreateMessage(char *content, char *callNumber, time_t _time,
		uint32_t isSuccessfully, uint32_t isIncoming);
void FreeMessage(Message_Typedef * message);
#endif /* DATAMODEL_MESSAGE_H_ */
