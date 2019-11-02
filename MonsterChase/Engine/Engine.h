#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	void getPlayerInput(char * &input);
	void * initalizeMemory(size_t amouunt, size_t sizeOfAllocation);
	void * reinitalizeMemory(void * memoryAddress, size_t sizeOfAllocation);
	void copyMemory(void * to, void * from, size_t sizeToCopy);
	void freeMemory(void * memoryAddress);
};

