//#ifndef __HEAP_MANAGER_PROXY_H
//#define __HEAP_MANAGER_PROXY_H
//
//#include <stdint.h>
//
//class HeapManager;
//
//namespace HeapManagerProxy
//{
//
//	HeapManager::HeapManager *	CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
//	void			Destroy(HeapManager::HeapManager * i_pManager);
//
//	void *			alloc(HeapManager::HeapManager * i_pManager, size_t i_size);
//	void *			alloc(HeapManager::HeapManager * i_pManager, size_t i_size, unsigned int i_alignment);
//	bool			free(HeapManager::HeapManager * i_pManager, void * i_ptr);
//
//	void			Collect(HeapManager::HeapManager * i_pManager);
//
//	bool			Contains(const HeapManager::HeapManager * i_pManager, void * i_ptr);
//	bool			IsAllocated(const HeapManager::HeapManager * i_pManager, void * i_ptr);
//
//	size_t			GetLargestFreeBlock(const HeapManager::HeapManager * i_pManager);
//	size_t			GetTotalFreeMemory(const HeapManager::HeapManager * i_pManager);
//
//	void			ShowFreeBlocks(const HeapManager::HeapManager * i_pManager);
//	void			ShowOutstandingAllocations(const HeapManager::HeapManager * i_pManager);
//
//} // namespace HeapManagerProxy
//
//#endif // __HEAP_MANAGER_PROXY_H