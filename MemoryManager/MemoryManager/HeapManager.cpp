#include "HeapManager.h"

#include <assert.h>

HeapManager::HeapManager(void * i_pStartMemory, size_t i_givenHeapMemorySize, unsigned int i_givenNumDescriptors)
{
	// TODO
	this->m_pFreeDescriptors.m_pBlockBase = i_pStartMemory;
	this->m_pFreeDescriptors.m_sizeBlock = i_givenHeapMemorySize;
	this->m_pFreeDescriptors.m_pNext = nullptr;
	this->m_pFreeDescriptors.m_pPrevious = nullptr;

	this->m_pAllocatedDescriptors.m_pBlockBase = nullptr;
	this->m_pAllocatedDescriptors.m_sizeBlock = 0;
	this->m_pAllocatedDescriptors.m_pNext = nullptr;
	this->m_pAllocatedDescriptors.m_pPrevious = nullptr;
}

HeapManager::~HeapManager()
{
	// TODO possibly iterate over all elements and free
	// TODO then return memory back to virtual alloc/heap alloc
	this->m_pFreeDescriptors.m_pBlockBase = nullptr;
	this->m_pFreeDescriptors.m_sizeBlock = 0;
	this->m_pFreeDescriptors.m_pNext = nullptr;
	this->m_pFreeDescriptors.m_pPrevious = nullptr;

	this->m_pAllocatedDescriptors.m_pBlockBase = nullptr;
	this->m_pAllocatedDescriptors.m_sizeBlock = 0;
	this->m_pAllocatedDescriptors.m_pNext = nullptr;
	this->m_pAllocatedDescriptors.m_pPrevious = nullptr;
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
	assert(this->m_pFreeDescriptors.m_pBlockBase != nullptr);

	size_t actualBytesRequested = BYTE_ALIGN(i_bytes + BYTE_OVERHEAD, i_alignment);

	BlockDescriptor * currentBlock = &this->m_pFreeDescriptors;

	while (currentBlock->m_sizeBlock < actualBytesRequested)
	{
		// fail if there are no more available blocks
		assert(currentBlock->m_pNext != nullptr);

		currentBlock = currentBlock->m_pNext;
	}

	// set allocated block
	BlockDescriptor allocatedBlock = BlockDescriptor();
	allocatedBlock.m_pBlockBase = (void*)currentBlock->m_pBlockBase;
	allocatedBlock.m_sizeBlock = actualBytesRequested;

	// set first element of allocated descriptions previous to most recent allocation
	// and set most recent allocation's next to the first element
	if (this->m_pAllocatedDescriptors.m_pBlockBase != nullptr)
	{
		this->m_pAllocatedDescriptors.m_pPrevious = &allocatedBlock;
		allocatedBlock.m_pNext = &this->m_pAllocatedDescriptors;
	}

	// sets most recent allocated to beginning of linked list
	this->m_pAllocatedDescriptors = allocatedBlock;

	// check to see if current blocks remaining space could fit anything
	if (currentBlock->m_sizeBlock - actualBytesRequested > BYTE_OVERHEAD)
	{
		currentBlock->m_sizeBlock -= actualBytesRequested;
		currentBlock->m_pBlockBase = (void*)((size_t)currentBlock->m_pBlockBase + actualBytesRequested);
	}
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

	return (void*)((size_t)allocatedBlock.m_pBlockBase + sizeof(BlockDescriptor));
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
