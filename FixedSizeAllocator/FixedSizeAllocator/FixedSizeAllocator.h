#pragma once

#include "BitArray.h"

class FixedSizeAllocator
{
public:
	FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks);
	~FixedSizeAllocator();

	void * alloc();
	void free(void * i_ptr);

private:
	BitArray * m_pAvailableBits;
	uint8_t * m_pAllocatorMemory;
	const size_t m_blockSize;
	const size_t m_numBlocks;
};

