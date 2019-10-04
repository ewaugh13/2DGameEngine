#include "HeapManager.h"

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

	this->m_allocatedMemoryList = nullptr;

	this->m_freeMemoryDescriptors = NEXT_BLOCK_DESCRIPTOR(m_freeMemoryList);
	// if block base and size are 0 then its an empty one ready to be used
	this->m_freeMemoryDescriptors->m_pBlockBase = nullptr;
	this->m_freeMemoryDescriptors->m_sizeBlock = 0;

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
	// TODO maybe?
	this->m_freeMemoryDescriptors = nullptr;
	this->m_freeMemoryList = nullptr;
	this->m_allocatedMemoryList = nullptr;
}

HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	static HeapManager manager = HeapManager(i_pHeapMemory, i_HeapMemorySize, i_numDescriptors);
	return &manager;
}

void HeapManager::destroy()
{
	delete this;
}

void * HeapManager::_alloc(size_t i_bytes)
{
	return this->_alloc(i_bytes, DEFAULT_ALIGNMENT);
}

void * HeapManager::_alloc(size_t i_bytes, unsigned int i_alignment)
{
	// we need to have a pool of memory to use to allocate
	if (this->m_freeMemoryList->m_pBlockBase == nullptr)
	{
		return nullptr;
	}

	size_t actualBytesRequested = BYTE_ALIGN(i_bytes + BYTE_OVERHEAD, i_alignment);

	BlockDescriptor * currentBlock = this->m_freeMemoryList;

	// aligns where the memory would go considering we have a block descriptor pointer in front
	// it then figures out the amount we would need for this alignment and subtracts the block descriptor pointer
	size_t sizeForAligned = BYTE_ALIGN((size_t)currentBlock->m_pBlockBase + sizeof(BlockDescriptor*), i_alignment) - (size_t)currentBlock->m_pBlockBase
		- sizeof(BlockDescriptor*);

	while (currentBlock->m_sizeBlock < actualBytesRequested + sizeForAligned)
	{
		// fail if there are no more available blocks
		if (currentBlock->m_pNext == nullptr)
		{
			return nullptr;
		}

		//TODO helper to call for size for aligned
		currentBlock = currentBlock->m_pNext;
		sizeForAligned = BYTE_ALIGN((size_t)currentBlock->m_pBlockBase + sizeof(BlockDescriptor*), i_alignment) - (size_t)currentBlock->m_pBlockBase
			- sizeof(BlockDescriptor*);
	}

	// get free descriptor for allocated block
	if (this->m_freeMemoryDescriptors == nullptr)
	{
		return nullptr;
	}
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
	}
	// TODO add helper to remove link
	// remove current block from our free memory list
	else
	{
		if (currentBlock->m_pPrevious != nullptr)
		{
			currentBlock->m_pPrevious->m_pNext = currentBlock->m_pNext;
		}
		if (currentBlock->m_pNext != nullptr)
		{
			currentBlock->m_pNext->m_pPrevious = currentBlock->m_pPrevious;
		}

		// clear current block descriptor and add back to free block descriptor list
		currentBlock->m_pBlockBase = nullptr;
		currentBlock->m_sizeBlock = 0;
		currentBlock->m_pPrevious = nullptr;
		currentBlock->m_pNext = nullptr;

		this->m_freeMemoryDescriptors = BlockDescriptorUtil::addNewTopElement(this->m_freeMemoryDescriptors, currentBlock);
	}

	// if space before newly allocated block (in the current free block) is large enough add it to free list
	size_t leftOverSpace = (size_t)allocatedBlock->m_pBlockBase - (size_t)beginningOfCurrent;
	if (leftOverSpace >= MIN_SIZE_BLOCK)
	{
		// get new block descriptor and then remove from free descriptors 
		BlockDescriptor * emptyBlockSpaceBefore = this->m_freeMemoryDescriptors;

		// remove element from free memory descriptor list
		this->m_freeMemoryDescriptors = BlockDescriptorUtil::removeTopElement(this->m_freeMemoryDescriptors);

		emptyBlockSpaceBefore->m_pBlockBase = beginningOfCurrent;
		emptyBlockSpaceBefore->m_sizeBlock = leftOverSpace;

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

	// returns the memory space for the allocation
	return ALLOCATION_MEMORY_ADDRESS(allocatedBlock->m_pBlockBase);
}

void HeapManager::_free(void * i_ptr)
{
}

void HeapManager::collect()
{
}

size_t HeapManager::getLargestFreeBlock() const
{
	// iterate across all free memory and find largest
	return size_t();
}

size_t HeapManager::getTotalFreeMemory() const
{
	// iterate across all free memroy and add it up
	return size_t();
}

bool HeapManager::Contains(void * i_ptr) const
{
	// see if ptr is somewhere inbetween start and end
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	// iterate over allocated and search for ptr
	// base + pointer size to get address
	return false;
}

void HeapManager::ShowFreeBlocks() const
{
}

// TODO do I need a show outstanding free blocks?