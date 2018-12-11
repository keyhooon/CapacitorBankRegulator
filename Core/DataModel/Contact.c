/*
 * Contact.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#include "Contact.h"

Contact_Typedef * CreateContact(char *name, char *callNumber) {
	int nameLen = strlen(name);
	int callNumberLen = strlen(callNumber);
	Contact_Typedef *result = DataAllocatorAlloc(hModelInMemoryAllocator,
			sizeof(Contact_Typedef) + nameLen + callNumberLen + 2);
	result->Name = ((char*) result + sizeof(Contact_Typedef));
	strcpy(result->Name, name);

	result->CallNumber = result->Name + nameLen + 1;
	strcpy(result->CallNumber, callNumber);
	return result;
}
void FreeContact(Contact_Typedef * contact) {
	DataAllocatorFree(contact);
}











