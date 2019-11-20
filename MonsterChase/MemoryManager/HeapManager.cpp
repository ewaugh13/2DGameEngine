#include "HeapManager.h"

#include <stdio.h>
#include <assert.h>

HeapManager::HeapManager(void * i_pStartMemory, size_t i_givenHeapMemorySize, unsigned int i_givenNumDescriptors)
{
	this->startOfMemoryPool = i_pStartMemory;
	// include the space for the block descriptors
	this->endOfMemoryPool = ADD_AMOUNT_TO_ADDRESS(i_pStartMemory, i_givenHeapMemorySize);

	size_t sizeOfBlockDescriptorsList = i_givenNumDescriptors * BLOCK_DESCRIPTOR_SIZE;

	this->m_freeMemoryList = (BlockDescriptor*)ADD_AMOUNT_TO_ADDRESS(i_pStartMemory, (i_givenHeapMemorySize - sizeOfBlockDescriptorsList));
	this->m_freeMemoryList->m_pBlockBase = i_pStartMemory;
	this->m_freeMemoryList->m_sizeBlock = i_givenHeapMemorySize - sizeOfBlockDescriptorsList;
	SET_BLOCK_DESCRIPTOR_REFERENCE(this->m_freeMemoryList);

	this->m_allocatedMemoryList = nullptr;

	this->m_freeMemoryDescriptors = NEXT_BLOCK_DESCRIPTOR(m_freeMemoryList);
	// if block base and size are 0 then its an empty one ready to be used
	this->m_freeMemoryDescriptors->m_pBlockBase = nullptr;
	this->m_freeMemoryDescriptors->m_sizeBlock = 0;

	// italize free memory descriptors
	BlockDescriptor * current = this->m_freeMemoryDescriptors;
	for (unsigned int i = 0; i < i_givenNumDescriptors; i++)
	{
		// sets up previous for all but first one
		if (i != 0)
		{
			current->m_pPrevious = PREVIOUS_BLOCK_DESCRIPTOR(current);
		}
		// sets up next link for all but last one
		if (i < i_givenNumDescriptors - 1)
		{
			current->m_pNext = NEXT_BLOCK_DESCRIPTOR(current);
			current = current->m_pNext;
		}
	}
}

HeapManager::~HeapManager()
{
	this->m_freeMemoryDescriptors = nullptr;
	this->m_freeMemoryList = nullptr;
	this->m_allocatedMemoryList = nullptr;

	this->startOfMemoryPool = nullptr;
	this->endOfMemoryPool = nullptr;
}

HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	static HeapManager manager = HeapManager(i_pHeapMemory, i_HeapMemorySize, i_numDescriptors);
	return &manager;
}

void HeapManager::destroy()
{
	this->~HeapManager();
}

void * HeapManager::_alloc(size_t i_bytes)
{
	return this->_alloc(i_bytes, DEFAULT_ALIGNMENT);
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	// if we have no free memory or empty block descriptors return nullptr
	if (this->m_freeMemoryList->m_pBlockBase == nullptr || this->m_freeMemoryDescriptors == nullptr)
	{
		return nullptr;
	}

	size_t actualBytesRequested = BYTE_ALIGN(i_bytes + BYTE_OVERHEAD, DEFAULT_ALIGNMENT);

	BlockDescriptor * currentBlock = this->m_freeMemoryList;

	// aligns where the memory would go considering we have a block descriptor pointer in front
	// it then figures out the amount we would need for this alignment and subtracts the block descriptor pointer
	size_t sizeForAligned = getSizeForAligned(currentBlock, i_alignment);

	while (currentBlock->m_sizeBlock < actualBytesRequested + sizeForAligned)
	{
		// there are no more available blocks to evaluate return
		if (currentBlock->m_pNext == nullptr)
		{
			return nullptr;
		}

		currentBlock = currentBlock->m_pNext;
		sizeForAligned = getSizeForAligned(currentBlock, i_alignment);
	}

	// get free descriptor for allocated block
	BlockDescriptor * allocatedBlock = this->m_freeMemoryDescriptors;

	// remove element from free memory descriptor list
	this->m_freeMemoryDescriptors = BlockDescriptorUtil::removeTopElement(this->m_freeMemoryDescriptors);

	// align the block base again and then subtract for the start of the block descriptor
	allocatedBlock->m_pBlockBase = ADD_AMOUNT_TO_ADDRESS(currentBlock->m_pBlockBase, sizeForAligned);
	allocatedBlock->m_sizeBlock = actualBytesRequested;

	// set the new head of allocated memory list to the allocated block
	this->m_allocatedMemoryList = BlockDescriptorUtil::addNewTopElement(this->m_allocatedMemoryList, allocatedBlock);


	// save the beginning start position of current for later if needed
	void * beginningOfCurrent = currentBlock->m_pBlockBase;

	// check to see if space after in current block remaining space could fit anything
	if (currentBlock->m_sizeBlock - actualBytesRequested - sizeForAligned >= MIN_SIZE_BLOCK)
	{
		currentBlock->m_sizeBlock -= (actualBytesRequested + sizeForAligned);
		currentBlock->m_pBlockBase = ADD_AMOUNT_TO_ADDRESS(currentBlock->m_pBlockBase, actualBytesRequested + sizeForAligned);
		SET_BLOCK_DESCRIPTOR_REFERENCE(currentBlock);
	}
	// remove current block from our free memory list and add descriptor back to free memory descriptor 
	else
	{
		BlockDescriptorUtil::removeNode(currentBlock, this->m_freeMemoryList);

		// clear current block descriptor and add back to free block descriptor list
		this->addFreeMemoryDescriptor(currentBlock);
	}

	// if space before newly allocated block (in the current free block) is large enough add it to free list
	if (sizeForAligned >= MIN_SIZE_BLOCK)
	{
		// get new block descriptor and then remove from free descriptors 
		BlockDescriptor * emptyBlockSpaceBefore = this->m_freeMemoryDescriptors;

		// remove element from free memory descriptor list
		this->m_freeMemoryDescriptors = BlockDescriptorUtil::removeTopElement(this->m_freeMemoryDescriptors);

		emptyBlockSpaceBefore->m_pBlockBase = beginningOfCurrent;
		emptyBlockSpaceBefore->m_sizeBlock = sizeForAligned;
		SET_BLOCK_DESCRIPTOR_REFERENCE(emptyBlockSpaceBefore);

		if (this->m_freeMemoryList != nullptr)
		{
			// set the new head of free memory list to the empty space
			this->m_freeMemoryList = BlockDescriptorUtil::addNewTopElement(this->m_freeMemoryList, emptyBlockSpaceBefore);
		}
		else
		{
			// initalize free memory list with this element
			this->m_freeMemoryList = emptyBlockSpaceBefore;
		}
	}

	// sets the first 4 bytes of the memory to store the pointer to the block descriptor
	SET_BLOCK_DESCRIPTOR_REFERENCE(allocatedBlock);
	allocatedBlock->m_allocated = 1;

	return ALLOCATION_MEMORY_ADDRESS(allocatedBlock->m_pBlockBase);
}

void HeapManager::_free(void * i_ptr)
{
	if (i_ptr == nullptr)
	{
		return;
	}
	// gets the value of the block descriptor pointer to get the actual block descriptor value to use for freeing
	BlockDescriptor * newFreeBlock = (BlockDescriptor*)((BlockDescriptor*)DESCRIPTOR_POINTER_MEMORY_ADDRESS(i_ptr))->m_pBlockBase;

	// remove from allocated list
	BlockDescriptorUtil::removeNode(newFreeBlock, this->m_allocatedMemoryList);
	newFreeBlock->m_allocated = 0;

	// coalese the free blocks following the newly freed block
	this->coalese(newFreeBlock);

	// add to free list after coalesing
	this->m_freeMemoryList = BlockDescriptorUtil::addNewTopElement(this->m_freeMemoryList, newFreeBlock);
}

void HeapManager::collect()
{
	// iterate over all free to try and coallese
	BlockDescriptor * currentBlock = this->m_freeMemoryList;

	while (currentBlock != nullptr)
	{
		this->coalese(currentBlock);

		currentBlock = currentBlock->m_pNext;
	}
}

void HeapManager::coalese(BlockDescriptor * currentFreeBlock)
{
	void * nextBlockBase = ADD_AMOUNT_TO_ADDRESS(currentFreeBlock->m_pBlockBase, currentFreeBlock->m_sizeBlock);
	BlockDescriptor * nextBlock = (BlockDescriptor *)(((BlockDescriptor *)nextBlockBase)->m_pBlockBase);

	// if next block is free as well
	if (nextBlock != nullptr && nextBlock->m_allocated == 0 && nextBlock->m_sizeBlock > 0)
	{
		// attempt to coalese nextBlock before we do current
		coalese(nextBlock);

		// remove block we are coalesing from free list
		BlockDescriptorUtil::removeNode(nextBlock, this->m_freeMemoryList);

		// add the next blocks size to get the size of the new coalesed free block
		size_t difference = ABS(DIFFERENCE_BLOCK_BASES(currentFreeBlock->m_pBlockBase, nextBlock->m_pBlockBase));
		currentFreeBlock->m_sizeBlock = difference + nextBlock->m_sizeBlock;

		// clear current block descriptor and add back to free block descriptor list
		this->addFreeMemoryDescriptor(nextBlock);
	}
}

inline size_t getSizeForAligned(BlockDescriptor * block, size_t alignment)
{
	return BYTE_ALIGN((size_t)block->m_pBlockBase + sizeof(BlockDescriptor*), alignment) - (size_t)block->m_pBlockBase
		- sizeof(BlockDescriptor*);
}

inline BlockDescriptor * memListContains(BlockDescriptor * memoryList, void * searchBlockBase)
{
	BlockDescriptor * currentBlock = memoryList;

	// iterate across the memory list searching for the provided block
	while (currentBlock != nullptr)
	{
		if (currentBlock->m_pNext != nullptr)
		{
			assert(currentBlock->m_pNext->m_pPrevious == currentBlock);
		}
		ptrdiff_t difference = ABS(DIFFERENCE_BLOCK_BASES(currentBlock->m_pBlockBase, searchBlockBase));
		// if the difference is less than the min size block than these block 
		// are basically next to each other with some extra space inbetween
		if (difference < MIN_SIZE_BLOCK)
		{
			return currentBlock;
		}
		currentBlock = currentBlock->m_pNext;
	}

	return nullptr;
}