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

//typedef struct Contact_List_Struct {
//	struct Contact_List_Struct *next;
//	struct Contact_List_Struct *previous;
//	Contact_Typedef value;
//} Contact_List_Typedef;
//int AddContact(Contact_Typedef *value);
//int RemoveContact(Contact_Typedef *value);
//int RemoveCurrentContact();
//int EditContact(Contact_Typedef *oldValue, Contact_Typedef *newValue);
//int GetContactCount();
//void GetContactDisplay(char *);
//char ** GetContactDisplayArray(void);
//void FreeContactDisplayArray(char ** stringArray);
//int SetSelectedContactItem(Contact_Typedef *value);
//Contact_Typedef * GetSelectedContactItem(void);
//void FreeContactItem(Contact_Typedef * value);
//int SetSelectedContactIndex(int value);
//int GetSelectedContactIndex();

void seedContact();
void AddContactEx(char * Name, char * CallNumber);

#endif /* DATACONTEXT_CONTACTLISTCONTEXT_H_ */
