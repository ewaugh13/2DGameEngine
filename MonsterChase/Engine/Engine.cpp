#include "Engine.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

Engine::Engine()
{
	//this->heapManager = new HeapManager();
}

Engine::~Engine()
{
}

// read player input 1 char at a time until enter a cariage return is read
void Engine::getPlayerInput(char * &input)
{
	input = (char *)this->initalizeMemory(1, sizeof(char));
	char charElement;
	size_t i = 0;
	while ((charElement = (char)_getche()) != '\r')
	{
		input[i] = charElement;
		// i + 2 to store new element and possible end delimiter
		input = (char *)this->reinitalizeMemory((void *)input, (i + 2) * sizeof(char));

		i++;
		input[i] = '\0';
	}
	std::cout << std::endl;
}

void * Engine::initalizeMemory(size_t amouunt, size_t sizeOfAllocation)
{
	return calloc(amouunt, sizeOfAllocation);
}

void * Engine::reinitalizeMemory(void * memoryAddress, size_t sizeOfAllocation)
{
	return realloc(memoryAddress, sizeOfAllocation);
}

void Engine::copyMemory(void * to, void * from, size_t sizeToCopy)
{
	memcpy(to, from, sizeToCopy);
}

void Engine::freeMemory(void * memoryAddress)
{
	free(memoryAddress);
}