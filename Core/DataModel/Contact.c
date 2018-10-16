/*
 * Contact.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#include "Contact.h"
#include "Sorted_List_Heap.h"


DATA_ACCESS_SORTED_LIST_FUNCTIONS(Contact, STRING_COMPARATOR)

void AddContactEx(char * Name, char * LastName, char * CallNumber) {
	Contact_Typedef contact = { 0, Name, LastName, CallNumber,
	};
	AddContact(&contact);
}
void seedContact() {

	AddContactEx((const char*) "keyhan", (const char*) "babazadeh",
			(const char*) "09124575442");
	AddContactEx((const char*) "kian", (const char*) "babazadeh",
			(const char*) "09124463992");
	AddContactEx((const char*) "roozbeh", (const char*) "babazadeh",
			(const char*) "09127093902");
	AddContactEx((const char*) "mohammad", (const char*) "babazadeh",
			(const char*) "09121015197");
	AddContactEx((const char*) "kaveh", (const char*) "babazadeh",
			(const char*) "09101143144");
	AddContactEx((const char*) "shima", (const char*) "shademan",
			(const char*) "09354463261");

}
char* displayContact() {

}
