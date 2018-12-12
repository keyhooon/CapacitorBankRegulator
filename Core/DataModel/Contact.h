/*
 * Contact.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_CONTACT_H_
#define DATAMODEL_CONTACT_H_
#include "DataModel.h"
#include "string.h"

#define CONTACT_COMPARATOR(contact1, contact2) 	strcmp(contact1.Name, contact2.Name);

#define CONTACT_PREVIEW(display, contact) 		sprintf(display, "%.16s", contact.Name);

#define CONTACT_VIEW(display, contact) 			sprintf(display, "%.20s\r\n%.16s",contact.CallNumber, contact.Name);

#define CONTACT_MODEL_DATA_ALLOCATOR			hModelInMemoryAllocator

typedef struct {
	char * Name;
	char * CallNumber;
} Contact_Typedef;

Contact_Typedef * CreateContact(char *name, char *callNumber);
void FreeContact(Contact_Typedef * contact);

#endif /* DATAMODEL_CONTACT_H_ */
