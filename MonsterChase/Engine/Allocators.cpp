#include "Allocators.h"
#include "ConsolePrint.h"
#include "MemoryManagerGlobals.h"

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
		//printf("using fixed allocator with block size: %zu\n", sizeBlock);
#endif //_DEBUG
		return allocatedAddress;
	}

#if defined(_DEBUG)
	//printf("using default heap manager\n");
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
		//printf("using fixed allocator with block size: %zu\n", sizeBlock);
#endif //_DEBUG
		fsa->free(i_ptr);
	}
	else
	{
#if defined(_DEBUG)
		//printf("using default heap manager\n");
#endif //_DEBUG
		pHeapManager->_free(i_ptr);
	}
}

#pragma region Standard Allocators
void * __cdecl malloc(size_t i_size)
{
	//DEBUG_PRINT("Calling new (size_t) with (%Iu).\n", i_size);

	return _alloc(i_size);
}

void __cdecl free(void * i_ptr)
{
	//DEBUG_PRINT("Calling delete (void *) with (%p).\n", i_ptr);

	assert(i_ptr != nullptr);
	_free(i_ptr);
}

void * operator new(size_t i_size)
{
	//DEBUG_PRINT("Calling new (size_t) with (%Iu).\n", i_size);

	return _alloc(i_size);
}

void operator delete(void * i_ptr)
{
	//DEBUG_PRINT("Calling delete (void *) with (%p).\n", i_ptr);

	assert(i_ptr != nullptr);
	_free(i_ptr);
}

void * operator new[](size_t i_size)
{
	//DEBUG_PRINT("Calling new[] (size_t) with (%Iu).\n", i_size);
	
	return _alloc(i_size);
}

void operator delete[](void * i_ptr)
{
	//DEBUG_PRINT("Calling delete[] (void *) with (%p).\n", i_ptr);

	assert(i_ptr != nullptr);
	_free(i_ptr);
}
#pragma endregion

#pragma region Tracked Allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling new (size_t) with (%Iu). (Called from (%s) on line (%u)\n", i_size, i_pFile, i_Line);

	return _alloc(i_size);
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling delete (void *) with (%p). (Called from (%s) on line (%u)\n", i_ptr, i_pFile, i_Line);

	assert(i_ptr != nullptr);
	_free(i_ptr);
}

void * operator new[](size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling new[] (size_t) with (%Iu). (Called from (%s) on line (%u)\n", i_size, i_pFile, i_Line);

	return _alloc(i_size);
}

void operator delete[](void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling delete[] (void *) with (%p). (Called from (%s) on line (%u)\n", i_ptr, i_pFile, i_Line);

	assert(i_ptr != nullptr);
	_free(i_ptr);
}
#pragma endregion