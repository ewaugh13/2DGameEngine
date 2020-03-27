#pragma once

#include "BitArray.h"

class FixedSizeAllocator;

typedef struct FSAMap
{
	FixedSizeAllocator * fsa;
	size_t sizeBlock;
} FSAMap;

typedef struct FSAInitData
{
	size_t sizeBlock;
	size_t numBlocks;
} FSAInitData;

class FixedSizeAllocator
{
public:
	FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks);
	~FixedSizeAllocator();

	void * alloc();
	void free(void * i_ptr);

	// if ptr is in the memory range for this fsa
	bool InMemoryRange(void * i_ptr);

	// prints out memory for fsa showing which
	// blocks are free or allocated
	void ShowMemory();

private:
	BitArray * m_pAvailableBits;
	uint8_t * m_pAllocatorMemory;
	const size_t m_blockSize;
	const size_t m_numBlocks;
};