/*
 * DataModel.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include "DataModel.h"

static char modelInMemoryBuffer[100];

int hModelInMemoryAllocator;
void InitModelInMemoryAllocator() {
	hModelInMemoryAllocator = AddHeapDataAllocator(modelInMemoryBuffer, 100);
}

int CalculateDataModelSizeWithoutExtra(FieldAttribute_Typedef * fieldAttribute,
		int fieldCount) {
	int result = 0;
	for (int i = 0; i < fieldCount; i++)
		result += fieldAttribute[i].lengthInStruct;
	return result;
}
int CalculateDataModelMaxSizeWithExtra(FieldAttribute_Typedef * fieldAttribute,
		int fieldCount) {
	int result = 0;
	for (int i = 0; i < fieldCount; i++)
		result += fieldAttribute[i].lengthInStruct;
	return result;
}

