/*
 * DataModel.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include "DataModel.h"

uint8_t buffer[100];

int hModelInMemoryAllocator;
void InitModelInMemoryAllocator() {
	hModelInMemoryAllocator = AddHeapDataAllocator(buffer);
}
