/*
 * DataModel.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATAMODEL_DATAMODEL_H_
#define DATAMODEL_DATAMODEL_H_



typedef enum FieldType_Enum {
	integerField, stringField, longField, bitField
} FieldType_Typedef;

typedef struct {
	FieldType_Typedef type;
	char *display;
	int offsetInStruct :8;
	int lengthInStruct :4;
	int maxLength :16;
	int editable :1;
	int reserved :3;
} FieldAttribute_Typedef;

extern int hModelInMemoryAllocator;
void InitModelInMemoryAllocator();
int CalculateDataModelSizeWithoutExtra(FieldAttribute_Typedef ** fieldAttribute,
		int fieldCount);
#endif /* DATAMODEL_DATAMODEL_H_ */
