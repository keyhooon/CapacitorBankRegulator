/*
 * DataModel.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_DATAMODEL_H_
#define DATAMODEL_DATAMODEL_H_



typedef enum FieldType_Enum {
	integerField, stringField,
} FieldType_Typedef;

typedef struct {
	FieldType_Typedef type;
	int offsetInStruct;
	int maxLength;
	char *display;
} FieldAttribute_Typedef;

extern int hModelInMemoryAllocator;
void InitModelInMemoryAllocator();
#endif /* DATAMODEL_DATAMODEL_H_ */
