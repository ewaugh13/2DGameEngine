#pragma once

#include "HeapManager.h"

const size_t sizeHeap = 1024 * 1024;
const unsigned int numDescriptors = 2048;

namespace Engine
{
	HeapManager::HeapManager * initializeHeapManager();
	void * initalizeMemory(size_t amouunt, size_t sizeOfAllocation);
	void freeMemory(void * memoryAddress);
};

