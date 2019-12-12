#include "BitArray.h"

#include <intrin.h>

#pragma intrinsic(_BitScanForward)

BitArray::BitArray(size_t i_numBits, HeapManager * i_pAllocator, bool i_startClear = true) :
	m_allocatedUsed(i_pAllocator),
	m_numBits(i_numBits),
	m_numBytes(i_numBits / 8)
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
	// TODO veify
	m_allocatedUsed->_free(m_pBits);
}

// TODO put in inl.h file
void BitArray::SetAll(void)
{
	size_t numElements = m_numBytes / sizeof(m_pBits);
	for (unsigned int i = 0; i < numElements; i++)
	{
		m_pBits[i] = FULL_8_BYTES;
	}
}

// TODO put in inl.h file
void BitArray::ClearAll(void)
{
	size_t numElements = m_numBytes / sizeof(m_pBits);
	for (unsigned int i = 0; i < numElements; i++)
	{
		m_pBits[i] = 0x0;
	}
}

bool BitArray::AreAllSet(void) const
{
	size_t numElements = m_numBytes / sizeof(m_pBits);
	for (size_t i = 0; i < numElements; i++)
	{
		if (m_pBits[i] != FULL_8_BYTES)
			return false;
	}
	return true;
}

bool BitArray::AreAllClear(void) const
{
	size_t numElements = m_numBytes / sizeof(m_pBits);
	for (size_t i = 0; i < numElements; i++)
	{
		if (m_pBits[i] != 0x0)
			return false;
	}
	return true;
}

// TODO put in inl.h file
inline bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber);
	size_t bitPosition = GetBitPosition(i_bitNumber);

	uint8_t bitEvaluator = GetBitEvaluator(bitPosition);

	return m_pBits[byteIndex] & bitEvaluator;
}

// TODO put in inl.h file
inline bool BitArray::IsBitClear(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber);
	size_t bitPosition = GetBitPosition(i_bitNumber);

	uint8_t bitEvaluator = GetBitEvaluator(bitPosition);

	return !(m_pBits[byteIndex] & bitEvaluator);
}

// TODO put in inl.h file
void BitArray::SetBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber);
	size_t bitPosition = GetBitPosition(i_bitNumber);

	uint8_t bitEvaluator = GetBitEvaluator(bitPosition);

	// using OR will set the bit we are concerned with
	m_pBits[byteIndex] | bitEvaluator;
}

// TODO put in inl.h file
void BitArray::ClearBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber);
	size_t bitPosition = GetBitPosition(i_bitNumber);

	uint8_t bitEvaluator = GetBitEvaluator(bitPosition);

	// using XOR with inverse of both will clear bit we are concerned with
	m_pBits[byteIndex] = ~m_pBits[byteIndex] ^ ~bitEvaluator;
}

bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
{
	size_t index = 0;

	size_t numElements = m_numBytes / sizeof(m_pBits);

	// skip bytes where bits are clear
	while ((m_pBits[index] == 0x0) && (index < numElements))
		index++;

	if (index >= numElements)
		return false;

	// at the index there is a clear bit
	uint64_t setBits = m_pBits[index];
	/*
		size_t bit;

		size_t numBitsInElement = sizeof(m_pBits) * NUM_BITS_IN_BYTE;
		for (bit = 0; bit < numBitsInElement; bit++)
		{
			if (setBits & (1 << bit))
				break;
		}

		// set out bit number based pf the element and bit
		size_t o_bitNumber = index * numBitsInElement + bit;

		// whether bit was found in for loop
		return bit < numBitsInElement;
	*/
	return _BitScanForward(reinterpret_cast<unsigned long *>(o_bitNumber), setBits);
}

bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
{
	size_t index = 0;

	size_t numElements = m_numBytes / sizeof(m_pBits);

	// skip bytes where bits are set
	while ((m_pBits[index] == FULL_8_BYTES) && (index < numElements))
		index++;

	if (index >= numElements)
		return false;

	// at the index there is a clear bit
	uint64_t clearBits = m_pBits[index];

	/*
		size_t bit;

		size_t numBitsInElement = sizeof(m_pBits) * NUM_BITS_IN_BYTE;
		for (bit = 0; bit < numBitsInElement; bit++)
		{
			if (!(clearBits & (1 << bit)))
				break;
		}

		// set out bit number based pf the element and bit
		size_t o_bitNumber = index * numBitsInElement + bit;

		// whether bit was found in for loop
		return bit < numBitsInElement;
	*/

	// need to flip bits to actually get first clear bit
	return _BitScanForward(reinterpret_cast<unsigned long *>(o_bitNumber), ~clearBits);
}

// TODO put in inl.h file
bool BitArray::operator[](size_t i_index) const
{
	size_t byteIndex = GetByteIndex(i_index);
	size_t bitPosition = GetBitPosition(i_index);

	uint8_t bitEvaluator = GetBitEvaluator(bitPosition);

	return m_pBits[byteIndex] & bitEvaluator;
}
