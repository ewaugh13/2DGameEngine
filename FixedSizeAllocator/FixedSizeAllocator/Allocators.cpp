#include "global.h"

#include <inttypes.h>
#include <malloc.h>

#include <stdio.h>
#include <map>

// initalizing global extern for fsa sizes
FSAInitData FSASizes[numFSAs] = { {16, 100}, {32, 200}, {96, 400} };

// ititilizing global extern for the fsa map
// that is initalized by the memory system
FSAMap FSAMapData[numFSAs] = {};

// if num is in range of a to b
inline bool InRange(size_t a, size_t b, size_t num)
{
	return num - a <= b - a;
}

// allocates using fixed size allocator is possible
// if not appropriate fixed sized allocator use default
void * _alloc(size_t i_size)
{
	FixedSizeAllocator * fsa = nullptr;
	size_t sizeBlock = 0;
	// search for fsa to use if applicable
	for (unsigned int i = 0; i < numFSAs; i++)
	{
		size_t lowRange, highRange;
		if (i == 0)
			lowRange = 0;
		else
			lowRange = FSASizes[i - 1].sizeBlock + 1;
		highRange = FSASizes[i].sizeBlock;

		if (InRange(lowRange, highRange, i_size))
		{
			sizeBlock = FSAMapData[i].sizeBlock;
			fsa = FSAMapData[i].fsa;
			break;
		}
	}

	void * allocatedAddress = nullptr;
	if (fsa)
		allocatedAddress = fsa->alloc();
	if (allocatedAddress)
	{
#if defined(_DEBUG)
		printf("using fixed allocator with block size: %zu\n", sizeBlock);
#endif //_DEBUG
		return allocatedAddress;
	}

#if defined(_DEBUG)
	printf("using default heap manager\n");
#endif //_DEBUG
	return pHeapManager->_alloc(i_size);
}

// frees using fixed size allocator is possible
// if not appropriate fixed sized allocator use default
void _free(void * i_ptr)
{
	FixedSizeAllocator * fsa = nullptr;
	size_t sizeBlock = 0;
	// search for fsa to use if applicable
	for (unsigned int i = 0; i < numFSAs; i++)
	{
		size_t lowRange, highRange;
		if (i == 0)
			lowRange = 0;
		else
			lowRange = FSASizes[i - 1].sizeBlock + 1;
		highRange = FSASizes[i].sizeBlock;

		if (FSAMapData[i].fsa && FSAMapData[i].fsa->InMemoryRange(i_ptr))
		{
			sizeBlock = FSAMapData[i].sizeBlock;
			fsa = FSAMapData[i].fsa;
			break;
		}
	}
	if (fsa)
	{
#if defined(_DEBUG)
		printf("using fixed allocator with block size: %zu\n", sizeBlock);
#endif //_DEBUG
		fsa->free(i_ptr);
	}
	else
	{
#if defined(_DEBUG)
		printf("using default heap manager\n");
#endif //_DEBUG
		pHeapManager->_free(i_ptr);
	}
}

void * __cdecl malloc(size_t i_size)
{
#if defined(_DEBUG)
	printf("malloc %zu\n", i_size);
#endif //_DEBUG

	return _alloc(i_size);
}

void __cdecl free(void * i_ptr)
{
#if defined(_DEBUG)
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
#endif //_DEBUG

	_free(i_ptr);
}

void * operator new(size_t i_size)
{
#if defined(_DEBUG)
	printf("new %zu\n", i_size);
#endif //_DEBUG
	
	return _alloc(i_size);
}

void operator delete(void * i_ptr)
{
#if defined(_DEBUG)
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
#endif //_DEBUG
	
	_free(i_ptr);
}

void * operator new[](size_t i_size)
{
#if defined(_DEBUG)
	printf("new [] %zu\n", i_size);
#endif //_DEBUG
	
	return _alloc(i_size);
}

void operator delete [](void * i_ptr)
{
#if defined(_DEBUG)
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
#endif //_DEBUG
	
	_free(i_ptr);
}