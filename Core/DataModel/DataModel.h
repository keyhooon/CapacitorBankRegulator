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
	int valueType :3;
	int offsetInStruct :8;
	int lengthInStruct :4;
	int maxLength :16;
	int editable :1;
	char *display;
} FieldAttribute_Typedef;

extern int hModelInMemoryAllocator;
void InitModelInMemoryAllocator();
int CalculateDataModelSizeWithoutExtra(FieldAttribute_Typedef * fieldAttribute,
		int fieldCount);
#endif /* DATAMODEL_DATAMODEL_H_ */
