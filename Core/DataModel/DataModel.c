/*
 * DataModel.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include "DataModel.h"

char buffer[100];

int hModelInMemoryAllocator;
void InitModelInMemoryAllocator() {
	hModelInMemoryAllocator = AddHeapDataAllocator(buffer);
}

int CalculateDataModelSizeWithoutExtra(FieldAttribute_Typedef ** fieldAttribute,
		int fieldCount) {
	int result = 0;
	for (int i = 0; i < fieldCount; i++)
		result += fieldAttribute[i]->lengthInStruct;
	return result;
}
