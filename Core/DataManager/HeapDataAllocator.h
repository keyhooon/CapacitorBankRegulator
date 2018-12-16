/*
 * DataManagerHeap.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATAMANAGER_HEAPDATAALLOCATOR_H_
#define DATAMANAGER_HEAPDATAALLOCATOR_H_


#include <DataAllocator.h>

void *Heap_DA_Alloc(DataAllocator_Typedef * hDataAllocator,
		size_t xWantedSize);

void Heap_DA_Free(DataAllocator_Typedef * hDataAllocator, void *pv);

size_t Heap_DA_GetSize(DataAllocator_Typedef * hDataAllocator,
		void *pv);

size_t Heap_DA_GetFreeSize(DataAllocator_Typedef * hDataAllocator);

size_t Heap_DA_GetMinimumEverFreeSize(
		DataAllocator_Typedef * hDataAllocator);

void Heap_DA_InitialiseBlocks(void);


#endif /* DATAMANAGER_HEAPDATAALLOCATOR_H_ */
