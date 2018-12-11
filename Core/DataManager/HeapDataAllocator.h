/*
 * DataManagerHeap.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATAMANAGER_HEAPDATAALLOCATOR_H_
#define DATAMANAGER_HEAPDATAALLOCATOR_H_




void *DataManagerHeapAlloc(struct DataAllocator_Struct * hDataAllocator,
		size_t xWantedSize);

void DataManagerHeapFree(struct DataAllocator_Struct * hDataAllocator, void *pv);

size_t DataManagerGetSize(struct DataAllocator_Struct * hDataAllocator,
		void *pv);

size_t DataManagerGetFreeHeapSize(struct DataAllocator_Struct * hDataAllocator);

size_t DataManagerGetMinimumEverFreeHeapSize(
		struct DataAllocator_Struct * hDataAllocator);

void DataManagerHeapInitialiseBlocks(void);


#endif /* DATAMANAGER_HEAPDATAALLOCATOR_H_ */
