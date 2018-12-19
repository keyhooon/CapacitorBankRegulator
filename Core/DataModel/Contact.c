/*
 * Contact.c
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#include "Contact.h"

const FieldAttribute_Typedef ContactFieldsAttribute[CONTACT_FIELD_COUNT] = { //
		{ stringField, (const char*) "Name", 0, 4, 20, 1 }, // Name Field
				{ stringField, (const char*) "Number", 4, 4, 20, 1 }, // CallNumber Field
		};

Contact_Typedef * CreateContact(char *name, char *callNumber) {
	int nameLen = strlen(name);
	int callNumberLen = strlen(callNumber);
	Contact_Typedef *result = DataAllocator_Alloc(hModelInMemoryAllocator,
			sizeof(Contact_Typedef) + nameLen + callNumberLen + 2);
	result->Name = ((char*) result + sizeof(Contact_Typedef));
	strcpy(result->Name, name);

	result->CallNumber = result->Name + nameLen + 1;
	strcpy(result->CallNumber, callNumber);
	return result;
}
void FreeContact(Contact_Typedef * contact) {
	DataAllocator_Free(hModelInMemoryAllocator, contact);
}











