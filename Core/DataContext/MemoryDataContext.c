/*
 * DataContext.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include <MemoryDataContext.h>
#include "DataAllocator.h"


uint8_t buffer[1000];
int hMemoryDataContextAllocator;

void InitMemoryDataContext() {
	hMemoryDataContextAllocator = AddHeapDataAllocator(buffer);
}
