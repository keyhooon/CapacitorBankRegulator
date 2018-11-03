/*
 * Contact.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#include "Contact.h"
#include "List_Heap.h"
#include "string.h"

#define CONTACT_COMPARATOR(x, y) STRING_COMPARATOR(x->current_item.Name, y->current_item.Name)

#define DISPLAY_CONTACT(display, contact) \
		sprintf(display, "%.10s\r\n %.10s", contact.Name, contact.LastName);

#define DISPLAY_CONTACT_DETAIL(display, contact) \
		sprintf(display, "%.11s\r\n%.10s, %.10s",contact.CallNumber, contact.Name, contact.LastName);


DATA_ACCESS_LIST_FUNCTIONS(Contact, CONTACT_COMPARATOR, DISPLAY_CONTACT,
		DISPLAY_CONTACT_DETAIL)

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

static void AddContactEx(char * Name, char * LastName, char * CallNumber) {
	Contact_Typedef contact = { 0, pvPortMalloc(strlen(Name)), pvPortMalloc(
			strlen(LastName)), pvPortMalloc(strlen(CallNumber)), };
	strcpy(contact.Name, Name);
	strcpy(contact.LastName, LastName);
	strcpy(contact.CallNumber, CallNumber);
	AddContact(&contact);
}
