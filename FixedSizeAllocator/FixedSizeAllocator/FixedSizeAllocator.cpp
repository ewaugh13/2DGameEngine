#include "FixedSizeAllocator.h"
#include "HeapManager.h"

// global extern HeapManager that is initalized by MemorySystem
HeapManager * pHeapManager;

FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks) : 
	m_pAllocatorMemory(reinterpret_cast<uint8_t *>(pHeapManager->_alloc(i_blockSize * i_numBlocks))),
	m_blockSize(i_blockSize),
	m_numBlocks(i_numBlocks)
{
	// TODO set up BitArray
}

FixedSizeAllocator::~FixedSizeAllocator()
{
	size_t firstClear;

	if (m_pAvailableBits->GetFirstSetBit(firstClear))
	{
		// TODO log message
	}
}

void * FixedSizeAllocator::alloc()
{
	size_t firstAvailable;

	if (m_pAvailableBits->GetFirstClearBit(firstAvailable))
	{
		// set bit representing allocation
		m_pAvailableBits->SetBit(firstAvailable);

		// calculate address relevant to bit
		return m_pAllocatorMemory + (firstAvailable * m_blockSize);
	}

	return nullptr;
}

void FixedSizeAllocator::free(void * i_ptr)
{
	size_t blockIndex = (reinterpret_cast<uint8_t *>(i_ptr) - m_pAllocatorMemory) / m_blockSize;

	m_pAvailableBits->ClearBit(blockIndex);
}
