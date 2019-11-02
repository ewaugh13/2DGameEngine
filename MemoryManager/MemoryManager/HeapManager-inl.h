#pragma once

#include <stdio.h>
#include <assert.h>

inline size_t HeapManager::getLargestFreeBlock() const
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

inline size_t HeapManager::getTotalFreeMemory() const
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

inline bool HeapManager::Contains(void * i_ptr) const
{
	// see if ptr is somewhere inbetween start and end
	if (this->startOfMemoryPool <= i_ptr && this->endOfMemoryPool >= i_ptr)
	{
		return true;
	}

	return false;
}

inline bool HeapManager::IsAllocated(void * i_ptr) const
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

inline void HeapManager::ShowFreeBlocks() const
{
	BlockDescriptor * currentBlock = this->m_freeMemoryList;

	printf("The free memory");

	// iterate across all free memory and print out the address and size
	while (currentBlock != nullptr)
	{
		assert(currentBlock->m_sizeBlock > 0);
		printf("-->[%p,%zu%s", ALLOCATION_MEMORY_ADDRESS(currentBlock->m_pBlockBase), currentBlock->m_sizeBlock, "]");
		currentBlock = currentBlock->m_pNext;
	}
	printf("\n");
}

inline void HeapManager::ShowOutstandingAllocations() const
{
	BlockDescriptor * currentBlock = this->m_allocatedMemoryList;

	printf("The allocated memory");

	// iterate across all allocated memory and print out the address and size
	while (currentBlock != nullptr)
	{
		assert(currentBlock->m_sizeBlock > 0);
		printf("-->[%p,%zu%s", ALLOCATION_MEMORY_ADDRESS(currentBlock->m_pBlockBase), currentBlock->m_sizeBlock, "]");
		currentBlock = currentBlock->m_pNext;
	}
	printf("\n");
}

inline void HeapManager::addFreeMemoryDescriptor(BlockDescriptor * blockDescriptor)
{
	// clear current block descriptor and add back to free block descriptor list
	blockDescriptor->m_pBlockBase = nullptr;
	blockDescriptor->m_sizeBlock = 0;
	blockDescriptor->m_pPrevious = nullptr;
	blockDescriptor->m_pNext = nullptr;

	this->m_freeMemoryDescriptors = BlockDescriptorUtil::addNewTopElement(this->m_freeMemoryDescriptors, blockDescriptor);
}