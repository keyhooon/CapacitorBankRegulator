/*
 * ContactListContext.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */


#include "ContactListContext.h"

extern int hMemoryDataContextAllocator;

DATA_CONTEXT_FUNCTIONS(Contact, CONTACT, hMemoryDataContextAllocator);



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
