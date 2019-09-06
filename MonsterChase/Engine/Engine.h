#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	void getPlayerInput(char * &input);
	void * initalizeMemory(int amouunt, int sizeOfAllocation);
	void freeMemory(void * memoryAddress);
	void * reinitalizeMemory(void * memoryAddress, int sizeOfAllocation);
};

