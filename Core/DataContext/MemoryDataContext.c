/*
 * DataContext.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include <MemoryDataContext.h>
#include "DataAllocator.h"


static uint8_t memoryDataContextBuffer[1000];
int hMemoryDataContextAllocator;

void InitMemoryDataContext() {
	hMemoryDataContextAllocator = AddHeapDataAllocator(memoryDataContextBuffer,
			1000);
}
