/*
 * DataManagerHeap.c
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#include <HeapDataAllocator.h>


/* Block sizes must not get too small. */
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE		( ( size_t ) 8 )




extern DataAllocator_Typedef DataAllocatorsList[DATA_ALLOCATORS_LIST_SIZE];
/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
static void prvInsertBlockIntoFreeList(
		DataAllocator_Typedef * hDataAllocator,
		BlockLink_t *pxBlockToInsert);

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
static void prvHeapInit(DataAllocator_Typedef * hDataAllocator);

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 block must by correctly byte aligned. */
static const size_t xHeapStructSize = (sizeof(BlockLink_t)
		+ ((size_t) ( portBYTE_ALIGNMENT - 1)))
		& ~((size_t) portBYTE_ALIGNMENT_MASK);


/*-----------------------------------------------------------*/

int AddHeapDataAllocator(uint8_t * buffer, size_t xTotalSize) {
	int i;
	for (i = 0; i < DATA_ALLOCATORS_LIST_SIZE; i++)
		if (DataAllocatorsList[i].ucHeap == 0)
			break;
	if (i == DATA_ALLOCATORS_LIST_SIZE)
		return -1;
	DataAllocatorsList[i] =
			(DataAllocator_Typedef ) { .ucHeap = buffer,
							.xStart = 0U, .pxEnd = 0U, /* Create a couple of list links to mark the start and end of the list. */
							.xFreeBytesRemaining = 0U,
							.xMinimumEverFreeBytesRemaining = 0U, /* Keeps track of the number of free bytes remaining, but says nothing about fragmentation. */
							.xTotalHeapSize = xTotalSize,
							.xBlockAllocatedBit = 0, /* Gets set to the top bit of an size_t type.  When this bit in the xBlockSize
							 member of an BlockLink_t structure is set then the block belongs to the
							 application.  When the bit is free the block is still part of the free heap
							 space. */
							.Alloc = Heap_DA_Alloc, /* */
							.Free = Heap_DA_Free, /* */
							.GetSize = Heap_DA_GetSize, /* */
							.GetFreeSize = Heap_DA_GetFreeSize, /* */
							.GetMinimumEverFreeHeapSize =
									Heap_DA_GetMinimumEverFreeSize, };
	return i;
}
/*-----------------------------------------------------------*/

void *Heap_DA_Alloc(DataAllocator_Typedef * hDataAllocator,
		size_t xWantedSize) {
	BlockLink_t *pxBlock, *pxPreviousBlock, *pxNewBlockLink;
	void *pvReturn = NULL;

	vTaskSuspendAll();
	{
		/* If this is the first call to malloc then the heap will require
		 initialisation to setup the list of free blocks. */
		if (hDataAllocator->pxEnd == NULL) {
			prvHeapInit(hDataAllocator);
		}

		/* Check the requested block size is not so large that the top bit is
		 set.  The top bit of the block size member of the BlockLink_t structure
		 is used to determine who owns the block - the application or the
		 kernel, so it must be free. */
		if ((xWantedSize & hDataAllocator->xBlockAllocatedBit) == 0) {
			/* The wanted size is increased so it can contain a BlockLink_t
			 structure in addition to the requested amount of bytes. */
			if (xWantedSize > 0) {
				xWantedSize += xHeapStructSize;

				/* Ensure that blocks are always aligned to the required number
				 of bytes. */
				if ((xWantedSize & portBYTE_ALIGNMENT_MASK) != 0x00) {
					/* Byte alignment required. */
					xWantedSize += ( portBYTE_ALIGNMENT
							- (xWantedSize & portBYTE_ALIGNMENT_MASK));
					configASSERT(( xWantedSize & portBYTE_ALIGNMENT_MASK ) == 0);
				}
			}
			if ((xWantedSize > 0)
					&& (xWantedSize <= hDataAllocator->xFreeBytesRemaining)) {
				/* Traverse the list from the start	(lowest address) block until
				 one	of adequate size is found. */
				pxPreviousBlock = &hDataAllocator->xStart;
				pxBlock = hDataAllocator->xStart.pxNextFreeBlock;
				while ((pxBlock->xBlockSize < xWantedSize)
						&& (pxBlock->pxNextFreeBlock != NULL)) {
					pxPreviousBlock = pxBlock;
					pxBlock = pxBlock->pxNextFreeBlock;
				}

				/* If the end marker was reached then a block of adequate size
				 was	not found. */
				if (pxBlock != hDataAllocator->pxEnd) {
					/* Return the memory space pointed to - jumping over the
					 BlockLink_t structure at its start. */
					pvReturn =
							(void *) (((uint8_t *) pxPreviousBlock->pxNextFreeBlock)
									+ xHeapStructSize);

					/* This block is being returned for use so must be taken out
					 of the list of free blocks. */
					pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

					/* If the block is larger than required it can be split into
					 two. */
					if ((pxBlock->xBlockSize - xWantedSize)
							> heapMINIMUM_BLOCK_SIZE) {
						/* This block is to be split into two.  Create a new
						 block following the number of bytes requested. The void
						 cast is used to prevent byte alignment warnings from the
						 compiler. */
						pxNewBlockLink = (void *) (((uint8_t *) pxBlock)
								+ xWantedSize);
						configASSERT(
								( ( ( size_t ) pxNewBlockLink ) & portBYTE_ALIGNMENT_MASK ) == 0);

						/* Calculate the sizes of two blocks split from the
						 single block. */
						pxNewBlockLink->xBlockSize = pxBlock->xBlockSize
								- xWantedSize;
						pxBlock->xBlockSize = xWantedSize;

						/* Insert the new block into the list of free blocks. */
						prvInsertBlockIntoFreeList(hDataAllocator,
								pxNewBlockLink);
					}

					hDataAllocator->xFreeBytesRemaining -= pxBlock->xBlockSize;

					if (hDataAllocator->xFreeBytesRemaining
							< hDataAllocator->xMinimumEverFreeBytesRemaining) {
						hDataAllocator->xMinimumEverFreeBytesRemaining =
								hDataAllocator->xFreeBytesRemaining;
					}

					/* The block is being returned - it is allocated and owned
					 by the application and has no "next" block. */
					pxBlock->xBlockSize |= hDataAllocator->xBlockAllocatedBit;
					pxBlock->pxNextFreeBlock = NULL;
				}
			}
		}
		traceMALLOC( pvReturn, xWantedSize );
	}
	(void) xTaskResumeAll();

#if( configUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if (pvReturn == NULL) {
			extern void vApplicationMallocFailedHook(void);
			vApplicationMallocFailedHook();
		}
	}
#endif

	configASSERT(
			( ( ( size_t ) pvReturn ) & ( size_t ) portBYTE_ALIGNMENT_MASK ) == 0);
	return pvReturn;
}
/*-----------------------------------------------------------*/

void Heap_DA_Free(DataAllocator_Typedef * hDataAllocator, void *pv) {
	uint8_t *puc = (uint8_t *) pv;
	BlockLink_t *pxLink;

	if (pv != NULL) {
		/* The memory being freed will have an BlockLink_t structure immediately
		 before it. */
		puc -= xHeapStructSize;

		/* This casting is to keep the compiler from issuing warnings. */
		pxLink = (void *) puc;

		/* Check the block is actually allocated. */
		configASSERT(
				(pxLink->xBlockSize & hDataAllocator->xBlockAllocatedBit) != 0);
		configASSERT(pxLink->pxNextFreeBlock == NULL);

		if ((pxLink->xBlockSize & hDataAllocator->xBlockAllocatedBit) != 0) {
			if (pxLink->pxNextFreeBlock == NULL) {
				/* The block is being returned to the heap - it is no longer
				 allocated. */
				pxLink->xBlockSize &= ~hDataAllocator->xBlockAllocatedBit;

				vTaskSuspendAll();
				{
					/* Add this block to the list of free blocks. */
					hDataAllocator->xFreeBytesRemaining += pxLink->xBlockSize;
					traceFREE( pv, pxLink->xBlockSize );
					prvInsertBlockIntoFreeList(hDataAllocator,
							((BlockLink_t *) pxLink));
				}
				(void) xTaskResumeAll();
			}
		}
	}
}
/*-----------------------------------------------------------*/
size_t Heap_DA_GetSize(DataAllocator_Typedef * hDataAllocator,
		void *pv) {
	uint8_t *puc = (uint8_t *) pv;
	BlockLink_t *pxLink;

	if (pv != NULL) {
		/* The memory being freed will have an BlockLink_t structure immediately
		 before it. */
		puc -= xHeapStructSize;

		/* This casting is to keep the compiler from issuing warnings. */
		pxLink = (void *) puc;

		/* Check the block is actually allocated. */
		configASSERT(
				(pxLink->xBlockSize & hDataAllocator->xBlockAllocatedBit) != 0);
		configASSERT(pxLink->pxNextFreeBlock == NULL);

		if ((pxLink->xBlockSize & hDataAllocator->xBlockAllocatedBit) != 0) {
			if (pxLink->pxNextFreeBlock == NULL) {
				return pxLink->xBlockSize & ~hDataAllocator->xBlockAllocatedBit;
			}
		}
	}
	return 0;
}
/*-----------------------------------------------------------*/

size_t Heap_DA_GetFreeSize(DataAllocator_Typedef * hDataAllocator) {
	return hDataAllocator->xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t Heap_DA_GetMinimumEverFreeSize(
		DataAllocator_Typedef * hDataAllocator) {
	return hDataAllocator->xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

void Heap_DA_InitialiseBlocks(void) {
	/* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

static void prvHeapInit(DataAllocator_Typedef * hDataAllocator) {
	BlockLink_t *pxFirstFreeBlock;
	uint8_t *pucAlignedHeap;
	size_t uxAddress;

	/* Ensure the heap starts on a correctly aligned boundary. */
	uxAddress = (size_t) hDataAllocator->ucHeap;

	if ((uxAddress & portBYTE_ALIGNMENT_MASK) != 0) {
		uxAddress += ( portBYTE_ALIGNMENT - 1);
		uxAddress &= ~((size_t) portBYTE_ALIGNMENT_MASK);
		hDataAllocator->xTotalHeapSize -= uxAddress
				- (size_t) hDataAllocator->ucHeap;
	}

	pucAlignedHeap = (uint8_t *) uxAddress;

	/* xStart is used to hold a pointer to the first item in the list of free
	 blocks.  The void cast is used to prevent compiler warnings. */
	hDataAllocator->xStart.pxNextFreeBlock = (void *) pucAlignedHeap;
	hDataAllocator->xStart.xBlockSize = (size_t) 0;

	/* pxEnd is used to mark the end of the list of free blocks and is inserted
	 at the end of the heap space. */
	uxAddress = ((size_t) pucAlignedHeap) + hDataAllocator->xTotalHeapSize;
	uxAddress -= xHeapStructSize;
	uxAddress &= ~((size_t) portBYTE_ALIGNMENT_MASK);
	hDataAllocator->pxEnd = (void *) uxAddress;
	hDataAllocator->pxEnd->xBlockSize = 0;
	hDataAllocator->pxEnd->pxNextFreeBlock = NULL;

	/* To start with there is a single free block that is sized to take up the
	 entire heap space, minus the space taken by pxEnd. */
	pxFirstFreeBlock = (void *) pucAlignedHeap;
	pxFirstFreeBlock->xBlockSize = uxAddress - (size_t) pxFirstFreeBlock;
	pxFirstFreeBlock->pxNextFreeBlock = hDataAllocator->pxEnd;

	/* Only one block exists - and it covers the entire usable heap space. */
	hDataAllocator->xMinimumEverFreeBytesRemaining =
			pxFirstFreeBlock->xBlockSize;
	hDataAllocator->xFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;

	/* Work out the position of the top bit in a size_t variable. */
	hDataAllocator->xBlockAllocatedBit = ((size_t) 1)
			<< ((sizeof(size_t) * heapBITS_PER_BYTE) - 1);
}
/*-----------------------------------------------------------*/

static void prvInsertBlockIntoFreeList(
		DataAllocator_Typedef * hDataAllocator,
		BlockLink_t *pxBlockToInsert) {
	BlockLink_t *pxIterator;
	uint8_t *puc;

	/* Iterate through the list until a block is found that has a higher address
	 than the block being inserted. */
	for (pxIterator = &hDataAllocator->xStart;
			pxIterator->pxNextFreeBlock < pxBlockToInsert;
			pxIterator = pxIterator->pxNextFreeBlock) {
		/* Nothing to do here, just iterate to the right position. */
	}

	/* Do the block being inserted, and the block it is being inserted after
	 make a contiguous block of memory? */
	puc = (uint8_t *) pxIterator;
	if ((puc + pxIterator->xBlockSize) == (uint8_t *) pxBlockToInsert) {
		pxIterator->xBlockSize += pxBlockToInsert->xBlockSize;
		pxBlockToInsert = pxIterator;
	}

	/* Do the block being inserted, and the block it is being inserted before
	 make a contiguous block of memory? */
	puc = (uint8_t *) pxBlockToInsert;
	if ((puc + pxBlockToInsert->xBlockSize)
			== (uint8_t *) pxIterator->pxNextFreeBlock) {
		if (pxIterator->pxNextFreeBlock != hDataAllocator->pxEnd) {
			/* Form one big block from the two blocks. */
			pxBlockToInsert->xBlockSize +=
					pxIterator->pxNextFreeBlock->xBlockSize;
			pxBlockToInsert->pxNextFreeBlock =
					pxIterator->pxNextFreeBlock->pxNextFreeBlock;
		} else {
			pxBlockToInsert->pxNextFreeBlock = hDataAllocator->pxEnd;
		}
	} else {
		pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
	}

	/* If the block being inserted plugged a gab, so was merged with the block
	 before and the block after, then it's pxNextFreeBlock pointer will have
	 already been set, and should not be set here as that would make it point
	 to itself. */
	if (pxIterator != pxBlockToInsert) {
		pxIterator->pxNextFreeBlock = pxBlockToInsert;
	}
}
