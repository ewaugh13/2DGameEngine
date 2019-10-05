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
	delete this;
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
		// fail if there are no more available blocks
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
	}
	// remove current block from our free memory list and add descriptor back to free memory descriptor 
	else
	{
		BlockDescriptorUtil::removeNode(currentBlock, this->m_freeMemoryList);

		this->m_freeMemoryDescriptors = BlockDescriptorUtil::addNewTopElement(this->m_freeMemoryDescriptors, currentBlock);
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
	BlockDescriptor * currentBlock = this->m_freeMemoryList;
	size_t largestFreeMemory = 0;

	// iterate across all free memory and find largest
	while (currentBlock != nullptr)
	{
		assert(currentBlock->m_sizeBlock > 0);
		if (currentBlock->m_sizeBlock > largestFreeMemory)
		{
			largestFreeMemory = currentBlock->m_sizeBlock;
		}
		currentBlock = currentBlock->m_pNext;
	}

	return largestFreeMemory;
}

size_t HeapManager::getTotalFreeMemory() const
{
	BlockDescriptor * currentBlock = this->m_freeMemoryList;
	size_t totalFreeMemory = 0;

	// iterate across all free memroy and add it up
	while (currentBlock != nullptr)
	{
		assert(currentBlock->m_sizeBlock > 0);
		totalFreeMemory += currentBlock->m_sizeBlock;
		currentBlock = currentBlock->m_pNext;
	}

	return totalFreeMemory;
}

bool HeapManager::Contains(void * i_ptr) const
{
	// see if ptr is somewhere inbetween start and end
	if (this->startOfMemoryPool <= i_ptr && this->endOfMemoryPool >= i_ptr)
	{
		return true;
	}

	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	BlockDescriptor * currentBlock = this->m_allocatedMemoryList;

	// iterate over allocated and search for ptr
	while (currentBlock != nullptr)
	{
		if (ALLOCATION_MEMORY_ADDRESS(currentBlock->m_pBlockBase) == i_ptr)
		{
			return true;
		}

		currentBlock = currentBlock->m_pNext;
	}

	return false;
}

void HeapManager::ShowFreeBlocks() const
{
}

// TODO do I need a show outstanding allocated blocks?

size_t getSizeForAligned(BlockDescriptor * block, size_t alignment)
{
	return BYTE_ALIGN((size_t)block->m_pBlockBase + sizeof(BlockDescriptor*), alignment) - (size_t)block->m_pBlockBase
		- sizeof(BlockDescriptor*);
}