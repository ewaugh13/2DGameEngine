#include "MemorySystem.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	pHeapManager = HeapManager::create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	assert(pHeapManager);

	for (unsigned int i = 0; i < numFSAs; i++)
	{
		FSAMapData[i].sizeBlock = FSASizes[i].sizeBlock;
		if (FSASizes[i].numBlocks)
		{
			FSAMapData[i].fsa = new FixedSizeAllocator(FSASizes[i].sizeBlock, FSASizes[i].numBlocks);
		}
	}

	return true;
}

void Collect()
{
	pHeapManager->collect();
}

void DestroyMemorySystem()
{
	// do larger ones first since they used
	// smaller ones for their own allocation
	for (int i = numFSAs - 1; i >= 0; i--)
	{
		if (FSAMapData[i].fsa)
			delete (FSAMapData[i].fsa);
	}

	pHeapManager->destroy();
}