/*
 * Message.h
 *
 *  Created on: Dec 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_APP_MESSAGE_H_
#define GSMMODEM_APP_MESSAGE_H_

#define SIM_MESSAGE_STORAGE						(const char*)"SM"
#define PHONE_MESSAGE_STORAGE					(const char*)"ME"
#define SM_MESSAGE_STORAGE_PREFERRED			(const char*)"SM_P"
#define ME_MESSAGE_STORAGE_PREFERRED			(const char*)"ME_P"
#define SM_ME_MESSAGE_STORAGE					(const char*)"MT"


typedef struct {
	char messageStorageindex;
	char inStorageIndex;
} MessageInfo_Typedef;
#endif /* GSMMODEM_APP_MESSAGE_H_ */
