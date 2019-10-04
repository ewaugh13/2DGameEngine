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
}