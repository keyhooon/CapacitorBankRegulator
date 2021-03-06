/*
 * DataManagerAllocator.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATAMANAGER_DATAALLOCATOR_H_
#define DATAMANAGER_DATAALLOCATOR_H_

#include "FreeRTOS.h"
#include "task.h"

#define DATA_ALLOCATORS_LIST_SIZE		5

/* Define the linked list structure.  This is used to link free blocks in order
 of their memory address. */
typedef struct A_BLOCK_LINK {
	struct A_BLOCK_LINK *pxNextFreeBlock; /*<< The next free block in the list. */
	size_t xBlockSize; /*<< The size of the free block. */
} BlockLink_t;

typedef struct DataAllocator_Struct {

	uint8_t *ucHeap;

	/* Block sizes must not get too small. */
	uint8_t xMinimumBlockSize;

	/* Create a couple of list links to mark the start and end of the list. */
	BlockLink_t xStart, *pxEnd;

	/* Keeps track of the number of free bytes remaining, but says nothing about
	 fragmentation. */
	size_t xFreeBytesRemaining;
	size_t xMinimumEverFreeBytesRemaining;

	size_t xTotalHeapSize;

	/* Gets set to the top bit of an size_t type.  When this bit in the xBlockSize
	 member of an BlockLink_t structure is set then the block belongs to the
	 application.  When the bit is free the block is still part of the free heap
	 space. */
	size_t xBlockAllocatedBit;

	void *(*Alloc)(struct DataAllocator_Struct * hDataAllocator,
			size_t xWantedSize);

	void (*Free)(struct DataAllocator_Struct * hDataAllocator, void *pv);

	size_t (*GetSize)(struct DataAllocator_Struct * hDataAllocator, void *pv);

	size_t (*GetFreeSize)(struct DataAllocator_Struct * hDataAllocator);

	size_t (*GetMinimumEverFreeHeapSize)(
			struct DataAllocator_Struct * hDataAllocator);

} DataAllocator_Typedef;


int AddHeapDataAllocator(uint8_t * buffer, size_t xTotalSize);



void Remove_DataAllocator(int hDataAllocator);

void *DataAllocator_Alloc(int hDataAllocator, size_t xWantedSize);

void DataAllocator_Free(int hDataAllocator, void *pv);

size_t DataAllocator_GetSize(int hDataAllocator, void *pv);

size_t DataAllocator_GetFreeSize(int hDataAllocator);

size_t DataAllocator_GetMinimumEverFreeSize(int hDataAllocator);

#endif /* DATAMANAGER_DATAALLOCATOR_H_ */
