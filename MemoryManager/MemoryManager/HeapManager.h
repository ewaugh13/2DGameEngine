#pragma once

#include "BlockDescriptorUtil.h"

// this is a sample of what your HeapManager class interface should look like.

const unsigned int GUARD_BAND = 4;
// alignment must be a power of 2
const unsigned int DEFAULT_ALIGNMENT = 4;

// the overhead of having a description pointer and guard band
#define BYTE_OVERHEAD GUARD_BAND + sizeof(BlockDescriptor*)

// adds alignment - 1 to bytes requested and then and's 
// the that against alignment - 1 to get the rounded up value to alignment
// example bytes = 7 ALIGNMENT = 4 0111 + 0011 = 1011 & 1100 = 1000 (8)
#define BYTE_ALIGN(bytes, alignment) (bytes + (alignment - 1) & ~(alignment - 1))

// gets the pointer to the block descriptor of the current block
#define DESCRIPTOR_POINTER(p) ((char *)(p) - sizeof(BlockDescriptor*))

// the minumum size needed for a block
#define MIN_SIZE_BLOCK (BYTE_OVERHEAD + DEFAULT_ALIGNMENT)

// the block descriptor size
#define BLOCK_DESCRIPTOR_SIZE sizeof(BlockDescriptor)

// gets the previous BlockDescriptor from the block descriptor list
#define PREVIOUS_BLOCK_DESCRIPTOR(pbd) (BlockDescriptor*)((char*)pbd - BLOCK_DESCRIPTOR_SIZE)

// gets the next BlockDescriptor from the block descriptor list
#define NEXT_BLOCK_DESCRIPTOR(pbd) (BlockDescriptor*)((char*)pbd + BLOCK_DESCRIPTOR_SIZE)

// adds the amount to the addres to get new address
#define ADD_AMOUNT_TO_ADDRESS(addr, size) (void*)((char*)addr + size);

// the allocated memory space start address
#define ALLOCATION_MEMORY_ADDRESS(bb) (void*)((char*)bb + sizeof(BlockDescriptor*))

class HeapManager
{

public:
	HeapManager(void * i_pStartMemory, size_t i_givenHeapMemorySize, unsigned int i_givenNumDescriptors);
	~HeapManager();

	// creates static heap manager that uses the passed in memory location 
	// with a given size to allow reuqests to allocate and free memory
	static HeapManager* create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);

	// removes all set information and gives memory back
	void destroy();

	// allocates memory. named with a underscore to resolve name clash 
	void* _alloc(size_t i_bytes);
	// allocation with alignment. returns a block of memory with a given alignment
	void* _alloc(size_t i_bytes, unsigned int i_alignment);

	// frees an allocation
	void _free(void * i_ptr);

	// attempt to merge abutting blocks.
	void collect();

	// tells us the size of the largest free block
	size_t getLargestFreeBlock() const;
	// tells us how much total memory is available
	size_t getTotalFreeMemory() const;

	// tells us if a pointer is within this HeapManagers managed memory
	bool Contains(void * i_ptr) const;
	// tells us if this pointer is an outstanding allocation from this block
	bool IsAllocated(void * i_ptr) const;

	// a debugging helper function to show us all the free blocks.
	void ShowFreeBlocks() const;
	// a debugging helper function to show us all the outstanding blocks.
	void ShowOutstandingAllocations() const;

private:
	BlockDescriptor * m_freeMemoryDescriptors;

	BlockDescriptor * m_freeMemoryList;
	BlockDescriptor * m_allocatedMemoryList;

	void * startOfMemoryPool;
	void * endOfMemoryPool;
};

// gets the size needed to have the correct alignment before the start memory address
size_t getSizeForAligned(BlockDescriptor * block, size_t alignment);
