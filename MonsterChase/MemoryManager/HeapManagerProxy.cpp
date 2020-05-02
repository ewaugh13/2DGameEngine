//
//#include "HeapManagerProxy.h"
//
//#include <assert.h>
//#include <stdio.h>
//
//#include "HeapManager.h"
//
//#define __TRACK_ALLOCATIONS
//
//namespace HeapManagerProxy
//{
//
//	HeapManager::HeapManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
//	{
//		return HeapManager::HeapManager::create(i_pMemory, i_sizeMemory, i_numDescriptors);
//	}
//
//	void Destroy(HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//		i_pManager->destroy();
//	}
//
//	void * alloc(HeapManager::HeapManager * i_pManager, size_t i_size)
//	{
//		assert(i_pManager);
//		return i_pManager->_alloc(i_size);
//	}
//
//	void * alloc(HeapManager::HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
//	{
//		assert(i_pManager);
//
//		return i_pManager->_alloc(i_size, i_alignment);
//	}
//
//	bool free(HeapManager::HeapManager * i_pManager, void * i_ptr)
//	{
//		assert(i_pManager);
//
//		i_pManager->_free(i_ptr);
//
//		return !i_pManager->IsAllocated(i_ptr);
//	}
//
//	void Collect(HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//		i_pManager->collect();
//	}
//
//
//	bool Contains(const HeapManager::HeapManager * i_pManager, void * i_ptr)
//	{
//		assert(i_pManager);
//
//		return i_pManager->Contains(i_ptr);
//	}
//
//	bool IsAllocated(const HeapManager::HeapManager * i_pManager, void * i_ptr)
//	{
//		assert(i_pManager);
//
//		return i_pManager->IsAllocated(i_ptr);
//	}
//
//	size_t GetLargestFreeBlock(const HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//		return i_pManager->getLargestFreeBlock();
//	}
//
//	size_t GetTotalFreeMemory(const HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//		return i_pManager->getTotalFreeMemory();
//	}
//
//	void ShowFreeBlocks(const HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//		i_pManager->ShowFreeBlocks();
//	}
//
//	void ShowOutstandingAllocations(const HeapManager::HeapManager * i_pManager)
//	{
//		assert(i_pManager);
//
//#ifdef __TRACK_ALLOCATIONS
//		i_pManager->ShowOutstandingAllocations();
//#else
//		printf("HeapManager compiled without __TRACK_ALLOCATIONS defined.\n");
//#endif
//
//	}
//
//} // namespace HeapManagerProxy