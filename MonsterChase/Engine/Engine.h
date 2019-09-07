#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	void getPlayerInput(char * &input);
	void * initalizeMemory(int amouunt, int sizeOfAllocation);
	void * reinitalizeMemory(void * memoryAddress, int sizeOfAllocation);
	void copyMemory(void * to, void * from, int sizeToCopy);
	void freeMemory(void * memoryAddress);
};

