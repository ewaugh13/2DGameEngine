#include "MemorySystem.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	pHeapManager = HeapManager::create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);

	// TOOD create your HeapManager and FixedSizeAllocators
	return true;
}

void Collect()
{
	pHeapManager->collect();
	// TODO coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	pHeapManager->destroy();
	// TOD Destroy your HeapManager and FixedSizeAllocators
}

