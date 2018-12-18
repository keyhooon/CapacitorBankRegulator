/*
 * MessageListContext.h
 *
 *  Created on: Dec 18, 2018
 *      Author: HP
 */

#ifndef DATACONTEXT_MESSAGELISTCONTEXT_H_
#define DATACONTEXT_MESSAGELISTCONTEXT_H_

#include "MemoryDataContext.h"
#include "Message.h"

DATA_CONTEXT_PROTOTYPES(Message);

void SeedMessage();
void AddMessageEx(char * Content, char * CallNumber, time_t _Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming);

#endif /* DATACONTEXT_MESSAGELISTCONTEXT_H_ */
