/*
 * MessageListSimContext.h
 *
 *  Created on: Jan 3, 2019
 *      Author: HP
 */

#ifndef DATACONTEXT_MESSAGELISTSIMCONTEXT_H_
#define DATACONTEXT_MESSAGELISTSIMCONTEXT_H_


#include "Message.h"
#include "DataContext.h"

int AddMessage(Message_Typedef *value);
int RemoveMessage(Message_Typedef *value);
int RemoveCurrentMessage();
int EditMessage(Message_Typedef *oldValue, Message_Typedef *newValue);
int GetMessageCount();
void GetMessageDisplay(char *);
char ** GetMessageDisplayArray(void);
void FreeMessageDisplayArray(char ** stringArray);
int SetSelectedMessageItem(Message_Typedef *value);
Message_Typedef * GetSelectedMessageItem(void);
void FreeMessageItem(Message_Typedef * value);
int SetSelectedMessageIndex(int value);
int GetSelectedMessageIndex();


#endif /* DATACONTEXT_MESSAGELISTSIMCONTEXT_H_ */
