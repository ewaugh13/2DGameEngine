#include "BitArray.h"

BitArray::BitArray(size_t i_numBits, HeapManager * i_pAllocator, bool i_startClear = true) :
	m_numBits(i_numBits), m_numBytes(i_numBits / 8)
{
	m_pBits = reinterpret_cast<uint64_t *>(i_pAllocator->_alloc(m_numBytes));

	if (!i_startClear)
	{
		for (unsigned int i = 0; i < m_numBytes; i++)
		{
			m_pBits[i] = 0xff;
		}
	}
}

BitArray::~BitArray()
{
}

void BitArray::ClearAll(void)
{
}

void BitArray::SetAll(void)
{
}

bool BitArray::AreAllClear(void) const
{
	return false;
}

bool BitArray::AreAllSet(void) const
{
	return false;
}

inline bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	return false;
}

inline bool BitArray::IsBitClear(size_t i_bitNumber) const
{
	return false;
}

void BitArray::SetBit(size_t i_bitNumber)
{
}

void BitArray::ClearBit(size_t i_bitNumber)
{
}

bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
{
	// TODO store last bit set and check next one first

	return false;
}

bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
{
	return false;
}

bool BitArray::operator[](size_t i_index) const
{
	//TODO
	return false;
}
