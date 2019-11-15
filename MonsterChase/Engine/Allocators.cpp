#include "Allocators.h"

#pragma region Standard Allocators
void * operator new(size_t i_size)
{
	DEBUG_PRINT("Calling new (size_t) with (%Iu).\n", i_size);

	return pHeapManager->_alloc(i_size);
}

void operator delete(void * i_ptr)
{
	DEBUG_PRINT("Calling delete (void *) with (%p).\n", i_ptr);

	assert(i_ptr != nullptr);
	pHeapManager->_free(i_ptr);
}

void * operator new[](size_t i_size)
{
	DEBUG_PRINT("Calling new[] (size_t) with (%Iu).\n", i_size);
	
	return pHeapManager->_alloc(i_size);
}

void operator delete[](void * i_ptr)
{
	DEBUG_PRINT("Calling delete[] (void *) with (%p).\n", i_ptr);

	assert(i_ptr != nullptr);
	pHeapManager->_free(i_ptr);
}
#pragma endregion

#pragma region Tracked Allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Calling new (size_t) with (%Iu). (Called from (%s) on line (%u)\n", i_size, i_pFile, i_Line);

	return pHeapManager->_alloc(i_size);
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Calling delete (void *) with (%p). (Called from (%s) on line (%u)\n", i_ptr, i_pFile, i_Line);

	assert(i_ptr != nullptr);
	pHeapManager->_free(i_ptr);
}

void * operator new[](size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Calling new[] (size_t) with (%Iu). (Called from (%s) on line (%u)\n", i_size, i_pFile, i_Line);

	return pHeapManager->_alloc(i_size);
}

void operator delete[](void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Calling delete[] (void *) with (%p). (Called from (%s) on line (%u)\n", i_ptr, i_pFile, i_Line);

	assert(i_ptr != nullptr);
	pHeapManager->_free(i_ptr);
}
#pragma endregion