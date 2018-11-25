/*
 * Contact.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_CONTACT_H_
#define DATAMODEL_CONTACT_H_
#include "main.h"
#include "List_Heap.h"
#include "string.h"



typedef struct {
	int32_t Id;
	char * Name;
	char * LastName;
	char * CallNumber;
} Contact_Typedef;

DATA_ACCESS_LIST_PROTOTYPES(Contact)

void seedContact();
#endif /* DATAMODEL_CONTACT_H_ */
