#include "FixedSizeAllocator.h"
#include "HeapManager.h"

// global extern HeapManager that is initalized by MemorySystem
HeapManager::HeapManager * pHeapManager;

FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks) :
	m_pAllocatorMemory(reinterpret_cast<uint8_t *>(pHeapManager->_alloc(i_blockSize * i_numBlocks))),
	m_blockSize(i_blockSize),
	m_numBlocks(i_numBlocks)
{
	m_pAvailableBits = new BitArray(i_numBlocks, pHeapManager);
}

FixedSizeAllocator::~FixedSizeAllocator()
{
	size_t firstSet;

	if (m_pAvailableBits->GetFirstSetBit(firstSet))
	{
#if defined(_DEBUG)
		printf("There are still outstanding allocations\n");
#endif // _DEBUG
	}

	if (m_pAvailableBits)
		delete m_pAvailableBits;
}

void * FixedSizeAllocator::alloc()
{
	size_t firstAvailable;

	if (m_pAvailableBits->GetFirstClearBit(firstAvailable))
	{
#ifdef _DEBUG
		assert(m_pAvailableBits->IsBitClear(firstAvailable));
#endif //_DEBUG

		// set bit representing allocation
		m_pAvailableBits->SetBit(firstAvailable);

		// calculate address relevant to bit
		return m_pAllocatorMemory + (firstAvailable * m_blockSize);
	}

	return nullptr;
}

void FixedSizeAllocator::free(void * i_ptr)
{
	if (i_ptr == nullptr)
	{
		return;
	}
	// must be in range of this fixed sized allocators memory
	assert(InMemoryRange(i_ptr));

	uint8_t * ptrMemory = reinterpret_cast<uint8_t *>(i_ptr);
	size_t blockIndex = (ptrMemory - m_pAllocatorMemory) / m_blockSize;
#ifdef _DEBUG
	assert(m_pAvailableBits->IsBitSet(blockIndex));
#endif // _DEBUG

	m_pAvailableBits->ClearBit(blockIndex);
}

bool FixedSizeAllocator::InMemoryRange(void * i_ptr)
{
	uint8_t * ptrMemory = reinterpret_cast<uint8_t *>(i_ptr);
	return m_pAllocatorMemory <= ptrMemory && ptrMemory <= m_pAllocatorMemory + (m_blockSize * m_numBlocks);
}

void FixedSizeAllocator::ShowMemory()
{
	for (unsigned int i = 0; i < m_numBlocks; i++)
	{
		void * memAddress = m_pAllocatorMemory + (i * m_blockSize);
		printf("------|Block @:%p|Allocated:%s|------\n", memAddress, m_pAvailableBits->IsBitSet(i) ? "true " : "false");
	}
}