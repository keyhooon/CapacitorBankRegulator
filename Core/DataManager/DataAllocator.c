/*
 * DataAllocator.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */


#include "DataAllocator.h"




DataAllocator_Typedef DataAllocatorsList[DATA_ALLOCATORS_LIST_SIZE];




void Remove_DataAllocator(int hDataAllocator) {
	DataAllocatorsList[hDataAllocator].ucHeap = 0;
}

void *DataAllocator_Alloc(int hDataAllocator, size_t xWantedSize) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->Alloc(handle, xWantedSize);
}

void DataAllocator_Free(int hDataAllocator, void *pv) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	handle->Free(handle, pv);
}

size_t DataAllocator_GetSize(int hDataAllocator, void *pv) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetSize(handle, pv);
}

size_t DataAllocator_GetFreeSize(int hDataAllocator) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetFreeSize(handle);
}

size_t DataAllocatorGetMinimumEverFreeHeapSize(int hDataAllocator) {
	DataAllocator_Typedef *handle = &DataAllocatorsList[hDataAllocator];
	return handle->GetMinimumEverFreeHeapSize(handle);
}
