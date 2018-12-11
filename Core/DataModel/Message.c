/*
 * Message.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */
#include "Message.h"
#include "string.h"
#include "time.h"
#include "../DataManager/List_Heap.h"

#define MESSAGE_COMPARATOR(x, y) (x->current_item.Time - y->current_item.Time)

#define DISPLAY_MESSAGE(display, message) \
		sprintf(display, "%.20s\r\n %.10s", message.Content, message.CallNumber);

#define DISPLAY_MESSAGE_DETAIL(display, message) \
		sprintf(display, "%s\r\n", message.Content);

DATA_ACCESS_LIST_FUNCTIONS(Message, MESSAGE_COMPARATOR, DISPLAY_MESSAGE,
		DISPLAY_MESSAGE_DETAIL)

static void AddMessageEx(char * Content, char * CallNumber, time_t Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming);

void SeedMessage() {

	AddMessageEx((const char*) "hi.", (const char*) "09124575442", 10000, 1, 1);
	AddMessageEx((const char*) "good bye.", (const char*) "09124463992", 15000,
			1, 0);
	AddMessageEx((const char*) "how are you? pls call me.",
			(const char*) "09127093902", 16000, 0, 0);
	AddMessageEx((const char*) "im not hear.", (const char*) "09121015197", 100,
			0, 0);
	AddMessageEx((const char*) "do you want exception?", (const char*) "-",
			18000, 0, 1);
	AddMessageEx((const char*) "where is my wife?", (const char*) "09354463261",
			19000,
			1, 0);
}

static void AddMessageEx(char * Content, char * CallNumber, time_t Time,
		uint32_t IsSuccessfully, uint32_t IsIncoming) {
	Message_Typedef message = { 0, Content, CallNumber, Time, IsSuccessfully,
			IsIncoming };
	message.Content = pvPortMalloc(strlen(Content));
	strcpy(message.Content, Content);
	message.CallNumber = pvPortMalloc(strlen(CallNumber));
	strcpy(message.CallNumber, CallNumber);
	message.Time = Time;
	message.IsSuccessfully = IsSuccessfully;
	message.IsIncoming = IsIncoming;
	AddMessage(&message);
}

