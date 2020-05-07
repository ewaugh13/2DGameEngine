//#include "Engine.h"
//#include <iostream>
//#include <conio.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <malloc.h>
//#include <Windows.h>
//
//namespace Engine
//{
//	HeapManager::HeapManager * initializeHeapManager()
//	{
//		// Get SYSTEM_INFO, which includes the memory page size
//		SYSTEM_INFO SysInfo;
//		GetSystemInfo(&SysInfo);
//		// round our size to a multiple of memory page size
//		assert(SysInfo.dwPageSize > 0);
//
//		size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
//
//		// get memeory from virtual alloc
//		void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//
//		return HeapManager::HeapManager::create(pHeapMemory, sizeHeap, numDescriptors);
//	}
//
//	void * initalizeMemory(size_t amouunt, size_t sizeOfAllocation)
//	{
//		return calloc(amouunt, sizeOfAllocation);
//	}
//
//	void freeMemory(void * memoryAddress)
//	{
//		free(memoryAddress);
//	}
//}