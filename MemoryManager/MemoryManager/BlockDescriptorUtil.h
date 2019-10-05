#pragma once

typedef struct BlockDescriptor
{
	void * m_pBlockBase;
	size_t m_sizeBlock;
	BlockDescriptor * m_pPrevious;
	BlockDescriptor * m_pNext;
} BlockDescriptor;


namespace BlockDescriptorUtil
{
	// removes the head element and sets the second element to the new head
	inline BlockDescriptor * removeTopElement(BlockDescriptor * head)
	{
		BlockDescriptor * newHead = head->m_pNext;
		if (newHead == nullptr)
		{
			return nullptr;
		}
		head->m_pNext = nullptr;
		newHead->m_pPrevious = nullptr;

		return newHead;
	}

	// adds a new element as the head and previous head (if it exists) becomes the second element
	inline BlockDescriptor * addNewTopElement(BlockDescriptor * previousHead, BlockDescriptor * newHead)
	{
		if (previousHead != nullptr)
		{
			newHead->m_pNext = previousHead;
			previousHead->m_pPrevious = newHead;
		}

		return newHead;
	}

	// removes elements prev and next link and then links its prev and next to each other
	// if the node removed was the head it sets the head to the next element
	inline void removeNode(BlockDescriptor * node, BlockDescriptor *& freeMemoryList)
	{
		// set up links for its previous and next
		if (node->m_pPrevious != nullptr && node->m_pNext != nullptr)
		{
			node->m_pPrevious->m_pNext = node->m_pNext;
			node->m_pNext->m_pPrevious = node->m_pPrevious;
		}
		// its the head and we need to set up new head to return
		else if (node->m_pNext != nullptr)
		{	
			node->m_pNext->m_pPrevious = nullptr;
			freeMemoryList = node->m_pNext;
		}

		// clear current block descriptor and add back to free block descriptor list
		node->m_pBlockBase = nullptr;
		node->m_sizeBlock = 0;
		node->m_pPrevious = nullptr;
		node->m_pNext = nullptr;
	}
}