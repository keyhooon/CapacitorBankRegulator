/*
 * ContactListContext.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */


#include "ContactListContext.h"
#include "string.h"
#include "Contact.h"

extern int hMemoryDataContextAllocator;

DATA_CONTEXT_FUNCTIONS(Contact, CONTACT, hMemoryDataContextAllocator);

static void AddContactEx(char * Name, char * LastName, char * CallNumber);

void SeedContact() {

	AddContactEx((const char*) "keyhan", (const char*) "babazadeh",
			(const char*) "09124575442");
	AddContactEx((const char*) "kian", (const char*) "babazadeh",
			(const char*) "09124463992");
	AddContactEx((const char*) "roozbeh", (const char*) "babazadeh",
			(const char*) "09127093902");
	AddContactEx((const char*) "mohammad", (const char*) "babazadeh",
			(const char*) "09121015197");
	AddContactEx((const char*) "kaveh", (const char*) "babazadeh",
			(const char*) "-");
	AddContactEx((const char*) "shima", (const char*) "shademan",
			(const char*) "09354463261");
}

static void AddContactEx(char * Name, char * CallNumber) {
	Contact_Typedef contact = { 0, pvPortMalloc(strlen(Name)), pvPortMalloc(
			strlen(CallNumber)), };
	strcpy(contact.Name, Name);
	strcpy(contact.CallNumber, CallNumber);
	AddContact(&contact);
}
