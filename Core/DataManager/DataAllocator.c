/*
 * DataAllocator.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */


#include "DataAllocator.h"


#define DATA_ALLOCATORS_LIST_SIZE		5

DataAllocator_Typedef DataAllocatorsList[DATA_ALLOCATORS_LIST_SIZE];



int AddHeapDataAllocator(uint8_t * buffer) {
	for (int i = 0; i < DATA_ALLOCATORS_LIST_SIZE; i++)
		if (DataAllocatorsList[i].ucHeap == 0) {
			DataAllocatorsList[i] = (DataAllocator_Typedef ) { .ucHeap = buffer,
							.xStart = 0U, .pxEnd = 0U, /* Create a couple of list links to mark the start and end of the list. */
							.xFreeBytesRemaining = 0U,
							.xMinimumEverFreeBytesRemaining = 0U, /* Keeps track of the number of free bytes remaining, but says nothing about fragmentation. */
							.xBlockAllocatedBit = 0, /* Gets set to the top bit of an size_t type.  When this bit in the xBlockSize
							 member of an BlockLink_t structure is set then the block belongs to the
							 application.  When the bit is free the block is still part of the free heap
							 space. */
							.DataAllocatorAlloc = DataManagerHeapAlloc, /* */
							.DataAllocatorFree = DataManagerHeapFree, /* */
							.GetSize = DataManagerGetSize, /* */
							.DataAllocatorGetFreeSize = DataManagerGetFreeHeapSize, /* */
							.DataAllocatorGetMinimumEverFreeHeapSize =
									DataManagerGetMinimumEverFreeHeapSize,
					};
		}
}

void RemoveDataAllocator(int hDataAllocator) {
	DataAllocatorsList[hDataAllocator].ucHeap = 0;
}

void *Alloc(int hDataAllocator, size_t xWantedSize) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->Alloc(handle, xWantedSize);
}

void Free(int hDataAllocator, void *pv) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	handle->Free(handle, pv);
}

size_t GetSize(int hDataAllocator, void *pv) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetSize(handle, pv);
}

size_t GetFreeSize(int hDataAllocator) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetFreeSize(handle);
}

size_t GetMinimumEverFreeHeapSize(int hDataAllocator) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetMinimumEverFreeHeapSize(handle);
}
