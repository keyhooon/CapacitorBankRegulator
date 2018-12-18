/*
 * ContactListContext.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATACONTEXT_CONTACTLISTCONTEXT_H_
#define DATACONTEXT_CONTACTLISTCONTEXT_H_

#include "MemoryDataContext.h"
#include "Contact.h"


DATA_CONTEXT_PROTOTYPES(Contact);

void seedContact();
void AddContactEx(char * Name, char * CallNumber);

#endif /* DATACONTEXT_CONTACTLISTCONTEXT_H_ */
