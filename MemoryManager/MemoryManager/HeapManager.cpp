#include "HeapManager.h"

#include <assert.h>

HeapManager::HeapManager(void * i_pStartMemory, size_t i_givenHeapMemorySize, unsigned int i_givenNumDescriptors)
{
	size_t sizeOfBlockDescriptorsList = i_givenNumDescriptors * sizeof(BlockDescriptor);
	// TODO use helper
	this->m_freeMemoryDescriptors = (BlockDescriptor*)((char*)i_pStartMemory + (i_givenHeapMemorySize - sizeOfBlockDescriptorsList));
	this->m_freeMemoryDescriptors->m_pBlockBase = i_pStartMemory;
	this->m_freeMemoryDescriptors->m_sizeBlock = i_givenHeapMemorySize - sizeOfBlockDescriptorsList;
	
	BlockDescriptor * current = this->m_freeMemoryDescriptors;
	for (unsigned int i = 0; i < i_givenNumDescriptors; i++)
	{
		// if block base and size are 0 then its an empty one ready to be used
		current->m_pNext = current + (sizeof(BlockDescriptor));
		current = current->m_pNext;
	}

	// TODO
	this->m_freeMemoryList = this->m_freeMemoryDescriptors;

	this->m_allocatedMemoryList = nullptr;
}

HeapManager::~HeapManager()
{
	this->m_freeMemoryDescriptors = {};
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
	assert(this->m_freeMemoryList->m_pBlockBase != nullptr);

	size_t actualBytesRequested = BYTE_ALIGN(i_bytes + BYTE_OVERHEAD, i_alignment);

	BlockDescriptor * currentBlock = this->m_freeMemoryList;

	// aligns where the memory would go considering we have a block descriptor pointer in front
	// it then figures out the amount we would need for this alignment and subtracts the block descriptor pointer
	size_t sizeForAligned = BYTE_ALIGN((size_t)currentBlock->m_pBlockBase + sizeof(BlockDescriptor*), i_alignment) - (size_t)currentBlock->m_pBlockBase
		- sizeof(BlockDescriptor*);

	while (currentBlock->m_sizeBlock < actualBytesRequested + sizeForAligned)
	{
		// fail if there are no more available blocks
		assert(currentBlock->m_pNext != nullptr);

		currentBlock = currentBlock->m_pNext;
	}

	// get allocated block
	// TODO helper method to get next block and check if we have run out of blocks
	BlockDescriptor * allocatedBlock = this->m_freeMemoryDescriptors->m_pNext;

	this->m_freeMemoryDescriptors->m_pNext = this->m_freeMemoryDescriptors->m_pNext->m_pNext;

	// align the block base again and then subtract for the start of the block descriptor
	allocatedBlock->m_pBlockBase = (void*)(BYTE_ALIGN((size_t)currentBlock->m_pBlockBase + sizeof(BlockDescriptor), i_alignment) - sizeof(BlockDescriptor));
	allocatedBlock->m_sizeBlock = actualBytesRequested;

	// TODO helper to add element to beginning
	// set first element of allocated descriptions previous to most recent allocation
	// and set most recent allocation's next to the first element
	if (this->m_allocatedMemoryList != nullptr)
	{
		this->m_allocatedMemoryList->m_pPrevious = allocatedBlock;
		allocatedBlock->m_pNext = this->m_allocatedMemoryList;
	}

	// sets most recent allocated to beginning of linked list
	this->m_allocatedMemoryList = allocatedBlock;

	// save the begin start position for later if needed
	void * beginningOfCurrent = currentBlock->m_pBlockBase;

	// check to see if space after in current block remaining space could fit anything
	if (currentBlock->m_sizeBlock - actualBytesRequested - sizeForAligned >= MIN_SIZE_BLOCK)
	{
		currentBlock->m_sizeBlock -= (actualBytesRequested + sizeForAligned);
		currentBlock->m_pBlockBase = (char*)(currentBlock->m_pBlockBase) + actualBytesRequested + sizeForAligned;
	}
	// TODO add helper to remove link
	// remove current block from our free list
	else
	{
		if (currentBlock->m_pPrevious != nullptr)
		{
			currentBlock->m_pPrevious->m_pNext = currentBlock->m_pNext;
		}
		else if (currentBlock->m_pNext != nullptr)
		{
			currentBlock->m_pNext->m_pPrevious = currentBlock->m_pPrevious;
		}
	}

	// if space before newly allocated block (in the current free block) is large enough add it to free list
	size_t leftOverSpace = (size_t)allocatedBlock->m_pBlockBase - (size_t)beginningOfCurrent;
	if (leftOverSpace >= MIN_SIZE_BLOCK)
	{
		BlockDescriptor * emptyBlockSpaceBefore = this->m_freeMemoryDescriptors->m_pNext;

		this->m_freeMemoryDescriptors->m_pNext = this->m_freeMemoryDescriptors->m_pNext->m_pNext;

		emptyBlockSpaceBefore->m_pBlockBase = beginningOfCurrent;
		emptyBlockSpaceBefore->m_sizeBlock = leftOverSpace;

		// TODO helper to put element on front of linked list
		if (this->m_freeMemoryList->m_pBlockBase != nullptr)
		{
			//BlockDescriptor * previousFirstElement = new BlockDescriptor(m_pFreeDescriptors);

			//this->m_pFreeDescriptors = emptyBlockSpaceBefore;

			//this->m_pFreeDescriptors.m_pNext = previousFirstElement;
			//previousFirstElement->m_pPrevious = &this->m_pFreeDescriptors;


			BlockDescriptor * previousFirstElement = (BlockDescriptor*)(&m_freeMemoryList);

			this->m_freeMemoryList = emptyBlockSpaceBefore;

			this->m_freeMemoryList->m_pNext = previousFirstElement;
			previousFirstElement->m_pPrevious = this->m_freeMemoryList;
		}
		else
		{
			this->m_freeMemoryList = emptyBlockSpaceBefore;
		}
	}

	//TODO helper that takes in void* and increment and returns void*
	return (void*)((char*)allocatedBlock->m_pBlockBase + sizeof(BlockDescriptor));
}

void HeapManager::_free(void * i_ptr)
{
}

void HeapManager::collect()
{
}

size_t HeapManager::getLargestFreeBlock() const
{
	return size_t();
}

size_t HeapManager::getTotalFreeMemory() const
{
	return size_t();
}

bool HeapManager::Contains(void * i_ptr) const
{
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	return false;
}

void HeapManager::ShowFreeBlocks() const
{
}
