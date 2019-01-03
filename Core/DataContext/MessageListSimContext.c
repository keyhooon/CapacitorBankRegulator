/*
 * MessageListSimContext.c
 *
 *  Created on: Jan 3, 2019
 *      Author: HP
 */

#include "MessageListSimContext.h"

const ListApiHandlers_typedef MessageListApiHandlers = {
		AddMessage, //
		RemoveMessage, //
		RemoveCurrentMessage, //
		EditMessage, //
		GetMessageCount, //
		GetMessageDisplay, //
		GetMessageDisplayArray, //
		FreeMessageDisplayArray, //
		SetSelectedMessageItem, //
		GetSelectedMessageItem, //
		FreeMessageItem, //
		SetSelectedMessageIndex, //
		GetSelectedMessageIndex, //
		};

int AddMessage(Message_Typedef *value) {
	Message_List_Typedef * _dlp_ = FindMessageItem(value);
	if (_dlp_ == NULL) {
		size_t sz = DataAllocator_GetSize(MESSAGE_MODEL_DATA_ALLOCATOR, value);
		size_t header_sz = sizeof(Message_List_Typedef *) << 1;
		Message_List_Typedef * elem = DataAllocator_Alloc(hDataAllocator,
				sz + header_sz);
		CopyMessageItem(&(elem->value), value, sz);
		if (Message_List == NULL) {
			(Message_List) = (elem);
			(Message_List)->next = (Message_List)->previous = NULL;
		} else {
			(elem)->next = (Message_List);
			(elem)->previous = (Message_List)->previous;
			(Message_List)->previous = (elem);
			if ((elem)->previous != NULL)
				(elem)->previous->next = (elem);
		}
		Message_List = elem;
		return 0;
	} else
		return -1;
}
int RemoveMessage(Message_Typedef *value) {
	Message_List_Typedef * _dlp_ = FindMessageItem(value);
	if (_dlp_ != NULL) {
		if (_dlp_ == (Message_List)) {
			if ((_dlp_)->previous != NULL)
				Message_List = (_dlp_)->previous;
			else
				Message_List = (_dlp_)->next;
		}
		if ((_dlp_)->next != NULL)
			(_dlp_)->next->previous = (_dlp_)->previous;
		if ((_dlp_)->previous != NULL)
			(_dlp_)->previous->next = (_dlp_)->next;
		DataAllocator_Free(hDataAllocator, _dlp_);
		return 0;
	}
	return -1;
}
int RemoveCurrentMessage() {
	Message_List_Typedef * _dlp_ = Message_List;
	if (Message_List == NULL)
		return -1;
	if ((Message_List)->previous != NULL)
		Message_List = (Message_List)->previous;
	else
		Message_List = (Message_List)->next;
	if ((_dlp_)->next != NULL)
		(_dlp_)->next->previous = (_dlp_)->previous;
	if ((_dlp_)->previous != NULL)
		(_dlp_)->previous->next = (_dlp_)->next;
	DataAllocator_Free(hDataAllocator, _dlp_);
	return 0;
}
int EditMessage(Message_Typedef *oldValue, Message_Typedef *newValue) {
	if (RemoveMessage(oldValue))
		return -1;
	if (AddMessage(newValue)) {
		AddMessage(oldValue);
		return -1;
	}
	return 0;
}
int GetMessageCount() {
	int _r_ = 0;
	if ((Message_List) == NULL)
		return 0;
	else {
		for (Message_List_Typedef * _dlp_ = Message_List; _dlp_ != NULL; _dlp_ =
				_dlp_->previous)
			_r_++;
		for (Message_List_Typedef * _dlp_ = Message_List; _dlp_ != NULL; _dlp_ =
				_dlp_->next)
			_r_++;
		return _r_ - 1;
	}
}
void GetMessageDisplay(char * text) {
	MESSAGE_VIEW(text, Message_List->value);
}
char ** GetMessageDisplayArray() {
	char temp[100];
	int itemCount = GetMessageCount();
	char** stringArray = pvPortMalloc((itemCount + 1) * sizeof(char *));
	char ** result = stringArray;
	char * stringItem;
	Message_List_Typedef *_dlp_;
	for (_dlp_ = Message_List; _dlp_->previous != NULL; _dlp_ = _dlp_->previous)
		;
	for (; _dlp_ != NULL; _dlp_ = _dlp_->next) {
		MESSAGE_PREVIEW(temp, _dlp_->value);
		stringItem = pvPortMalloc(strlen(temp) + 1);
		strcpy(stringItem, temp);
		*(stringArray++) = stringItem;
	}
	*stringArray = NULL;
	return result;
}
void FreeMessageDisplayArray(char ** stringArray) {
	int i = 0;
	while (*(stringArray + i)) {
		vPortFree(*(stringArray + i++));
	}
	vPortFree(stringArray);
}
int SetSelectedMessageItem(Message_Typedef *value) {
	Message_List_Typedef * _dlp_ = FindMessageItem(value);
	if (_dlp_ != NULL) {
		Message_List = _dlp_;
		return 0;
	}
	return 1;
}
Message_Typedef * GetSelectedMessageItem(void) {
	Message_Typedef *_dlp_;
	if (Message_List != NULL) {
		size_t sz = DataAllocator_GetSize(hDataAllocator, Message_List);
		size_t header_sz = sizeof(Message_List_Typedef *) << 1;
		_dlp_ = DataAllocator_Alloc(MESSAGE_MODEL_DATA_ALLOCATOR,
				sz - header_sz);
		CopyMessageItem(_dlp_, ((char *) Message_List) + header_sz,
				sz - header_sz);
		return _dlp_;
	}
	return NULL;
}
void FreeMessageItem(Message_Typedef * value) {
	DataAllocator_Alloc(MESSAGE_MODEL_DATA_ALLOCATOR, value);
}
int SetSelectedMessageIndex(int value) {
	Message_List_Typedef *_dlp_;
	for (_dlp_ = Message_List; _dlp_->previous != NULL; _dlp_ = _dlp_->previous)
		;
	for (int i = 0; i < value && _dlp_ != NULL; i++, _dlp_ = _dlp_->next)
		;
	if (_dlp_ != NULL) {
		Message_List = _dlp_;
		return 0;
	}
	return -1;
}
int GetSelectedMessageIndex() {
	int i = -1;
	for (Message_List_Typedef *_dlp_ = Message_List; _dlp_ != NULL; _dlp_ =
			_dlp_->previous, i++)
		;
	return i;
}
