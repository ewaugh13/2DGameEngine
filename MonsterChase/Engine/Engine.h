#pragma once

#include "HeapManager.h"

const size_t sizeHeap = 1024 * 1024;
const unsigned int numDescriptors = 2048;

class Engine
{
public:
	Engine();
	~Engine();

	void getPlayerInput(char * &input);
	static HeapManager * initializeHeapManager();
	void * initalizeMemory(size_t amouunt, size_t sizeOfAllocation);
	void * reinitalizeMemory(void * memoryAddress, size_t sizeOfAllocation);
	void copyMemory(void * to, void * from, size_t sizeToCopy);
	void freeMemory(void * memoryAddress);
};

