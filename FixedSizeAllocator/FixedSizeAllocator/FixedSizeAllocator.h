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

	bool InMemoryRange(void * i_ptr);

	void ShowMemory();

private:
	BitArray * m_pAvailableBits;
	uint8_t * m_pAllocatorMemory;
	const size_t m_blockSize;
	const size_t m_numBlocks;
};