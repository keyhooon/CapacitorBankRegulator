/*
 * ContactListContext.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */


#include "ContactListContext.h"

extern int hMemoryDataContextAllocator;

//DATA_CONTEXT_FUNCTIONS(Contact, CONTACT, hMemoryDataContextAllocator);

const ListApiHandlers_typedef ContactListApiHandlers = { AddContact,
		RemoveContact, RemoveCurrentContact, EditContact, GetContactCount,
		GetContactDisplay, GetContactDisplayArray, FreeContactDisplayArray,
		SetSelectedContactItem, GetSelectedContactItem, FreeContactItem,
		SetSelectedContactIndex, GetSelectedContactIndex, };
Contact_List_Typedef * Contact_List;
void Copy(char *to, char *from, size_t sz) {
	memcpy(to, from, sz);
	for (int i = 0; i < CONTACT_FIELD_COUNT; i++)
		if (ContactFieldsAttribute[i].type == stringField)
		{
			FieldAttribute_Typedef att = ContactFieldsAttribute[i];
			*(char **) (to + att.offsetInStruct) = to - from
					+ *(char **) (from + att.offsetInStruct);
		}
}
Contact_List_Typedef * FindContactItem(Contact_Typedef *value) {
	Contact_List_Typedef * _dlp_;
	for (_dlp_ = Contact_List;
			((_dlp_) != NULL)
					&& (CONTACT_COMPARATOR(_dlp_->value, (*value)) != 0);
			_dlp_ = _dlp_->previous)
		;
	if (_dlp_ == NULL)
		for (_dlp_ = Contact_List;
				((_dlp_) != NULL)
						&& (CONTACT_COMPARATOR(_dlp_->value, (*value)) != 0);
				_dlp_ = _dlp_->next)
			;
	return _dlp_;
}
int AddContact(Contact_Typedef *value) {
	Contact_List_Typedef * _dlp_ = FindContactItem(value);
	if (_dlp_ == NULL) {
		size_t sz = DataAllocator_GetSize(CONTACT_MODEL_DATA_ALLOCATOR, value);
		size_t header_sz = sizeof(Contact_List_Typedef *) << 1;
		Contact_List_Typedef * elem = DataAllocator_Alloc(
				hMemoryDataContextAllocator, sz + header_sz);
		Copy(&(elem->value), value, sz);
		if (Contact_List == NULL) {
			(Contact_List) = (elem);
			(Contact_List)->next = (Contact_List)->previous = NULL;
		} else {
			(elem)->next = (Contact_List);
			(elem)->previous = (Contact_List)->previous;
			(Contact_List)->previous = (elem);
			if ((elem)->previous != NULL)
				(elem)->previous->next = (elem);
		}
		return 0;
	} else
		return -1;
}
int RemoveContact(Contact_Typedef *value) {
	Contact_List_Typedef * _dlp_ = FindContactItem(value);
	if (_dlp_ != NULL) {
		if (_dlp_ == (Contact_List)) {
			if ((_dlp_)->previous != NULL)
				Contact_List = (_dlp_)->previous;
			else
				Contact_List = (_dlp_)->next;
		}
		if ((_dlp_)->next != NULL)
			(_dlp_)->next->previous = (_dlp_)->previous;
		if ((_dlp_)->previous != NULL)
			(_dlp_)->previous->next = (_dlp_)->next;
		DataAllocator_Free(hMemoryDataContextAllocator, _dlp_);
		return 0;
	}
	return -1;
}
int RemoveCurrentContact() {
	Contact_List_Typedef * _dlp_ = Contact_List;
	if (Contact_List == NULL)
		return -1;
	if ((Contact_List)->previous != NULL)
		Contact_List = (Contact_List)->previous;
	else
		Contact_List = (Contact_List)->next;
	if ((_dlp_)->next != NULL)
		(_dlp_)->next->previous = (_dlp_)->previous;
	if ((_dlp_)->previous != NULL)
		(_dlp_)->previous->next = (_dlp_)->next;
	DataAllocator_Free(hMemoryDataContextAllocator, _dlp_);
	return 0;
}
int EditContact(Contact_Typedef *oldValue, Contact_Typedef *newValue) {
	if (RemoveContact(oldValue)) {
		if (AddContact(newValue))
			return 0;
		else
			AddContact(oldValue);
	}
	return -1;
}
int GetContactCount() {
	int _r_ = 0;
	if ((Contact_List) == NULL)
		return 0;
	else {
		for (Contact_List_Typedef * _dlp_ = Contact_List; _dlp_ != NULL; _dlp_ =
				_dlp_->previous)
			_r_++;
		for (Contact_List_Typedef * _dlp_ = Contact_List; _dlp_ != NULL; _dlp_ =
				_dlp_->next)
			_r_++;
		return _r_ - 1;
	}
}
void GetContactDisplay(char * text) {
	CONTACT_VIEW(text, Contact_List->value);
}
char ** GetContactDisplayArray() {
	char temp[100];
	int itemCount = GetContactCount();
	char** stringArray = pvPortMalloc((itemCount + 1) * sizeof(char *));
	char ** result = stringArray;
	char * stringItem;
	Contact_List_Typedef *_dlp_;
	for (_dlp_ = Contact_List; _dlp_->previous != NULL; _dlp_ = _dlp_->previous)
		;
	for (; _dlp_ != NULL; _dlp_ = _dlp_->next) {
		CONTACT_PREVIEW(temp, _dlp_->value);
		stringItem = pvPortMalloc(strlen(temp) + 1);
		strcpy(stringItem, temp);
		*(stringArray++) = stringItem;
	}
	*stringArray = NULL;
	return result;
}
void FreeContactDisplayArray(char ** stringArray) {
	int i = 0;
	while (*(stringArray + i)) {
		vPortFree(*(stringArray + i++));
	}
	vPortFree(stringArray);
}
int SetSelectedContactItem(Contact_Typedef *value) {
	Contact_List_Typedef * _dlp_ = FindContactItem(value);
	if (_dlp_ != NULL) {
		Contact_List = _dlp_;
		return 0;
	}
	return 1;
}
Contact_Typedef * GetSelectedContactItem(void) {
	Contact_Typedef *_dlp_;
	if (Contact_List != NULL) {
		size_t sz = DataAllocator_GetSize(hMemoryDataContextAllocator,
				Contact_List);
		size_t header_sz = sizeof(Contact_List_Typedef *) << 1;
		_dlp_ = DataAllocator_Alloc(CONTACT_MODEL_DATA_ALLOCATOR,
				sz - header_sz);
		Copy(_dlp_, ((char *) Contact_List) + header_sz, sz - header_sz);
		return _dlp_;
	}
	return NULL;
}
void FreeContactItem(Contact_Typedef * value) {
	DataAllocator_Alloc(CONTACT_MODEL_DATA_ALLOCATOR, value);
}
int SetSelectedContactIndex(int value) {
	Contact_List_Typedef *_dlp_;
	for (_dlp_ = Contact_List; _dlp_->previous != NULL; _dlp_ = _dlp_->previous)
		;
	for (int i = 0; i < value && _dlp_ != NULL; i++, _dlp_ = _dlp_->next)
		;
	return (_dlp_ == NULL);
}
int GetSelectedContactIndex() {
	int i = -1;
	for (Contact_List_Typedef *_dlp_ = Contact_List; _dlp_ != NULL; _dlp_ =
			_dlp_->previous, i++)
		;
	return i;
}






void SeedContact() {
	AddContactEx((const char*) "keyhan babazadeh",
			(const char*) "09124575442");
	AddContactEx((const char*) "kian babazadeh",
			(const char*) "09124463992");
	AddContactEx((const char*) "roozbeh babazadeh",
			(const char*) "09127093902");
	AddContactEx((const char*) "mohammad babazadeh",
			(const char*) "09121015197");
	AddContactEx((const char*) "kaveh babazadeh",
			(const char*) "09121143144");
	AddContactEx((const char*) "shima shademan",
			(const char*) "09354463261");
}

void AddContactEx(char * Name, char * CallNumber) {
	Contact_Typedef *contact = CreateContact(Name, CallNumber);
	AddContact(contact);
	FreeContact(contact);
}
