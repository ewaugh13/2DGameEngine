#include "BitArray.h"

#include <intrin.h>

#pragma intrinsic(_BitScanForward)

BitArray::BitArray(size_t i_numBits, HeapManager * i_pAllocator, bool i_startClear) :
	m_allocatedUsed(i_pAllocator),
	m_numBits(i_numBits),
	m_numBytes((i_numBits + 8 - 1) / 8),
	numElements(m_numBytes / sizeof(m_pBits)),
	m_numBitsInElement(sizeof(m_pBits) * NUM_BITS_IN_BYTE)
{
	m_pBits = reinterpret_cast<uint64_t *>(i_pAllocator->_alloc(m_numBytes));

	if (!i_startClear)
	{
		for (size_t i = 0; i <= numElements; i++)
		{
			m_pBits[i] = FULL_8_BYTES;
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
	for (size_t i = 0; i <= numElements; i++)
	{
		m_pBits[i] = FULL_8_BYTES;
	}
}

// TODO put in inl.h file
void BitArray::ClearAll(void)
{
	for (size_t i = 0; i <= numElements; i++)
	{
		m_pBits[i] = 0x0;
	}
}

bool BitArray::AreAllSet(void) const
{
	for (size_t i = 0; i <= numElements; i++)
	{
		// TODO maybe use 8 or 4 bytes
		if (m_pBits[i] != FULL_8_BYTES)
			return false;
	}
	return true;
}

bool BitArray::AreAllClear(void) const
{
	for (size_t i = 0; i <= numElements; i++)
	{
		if (m_pBits[i] != 0x0)
			return false;
	}
	return true;
}

// TODO put in inl.h file
inline bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	return m_pBits[byteIndex] & bitEvaluator;
}

// TODO put in inl.h file
inline bool BitArray::IsBitClear(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	return !(m_pBits[byteIndex] & bitEvaluator);
}

// TODO put in inl.h file
void BitArray::SetBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	// using OR will set the bit we are concerned with
	m_pBits[byteIndex] = m_pBits[byteIndex] | bitEvaluator;
}

// TODO put in inl.h file
void BitArray::ClearBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	// using XOR with inverse of both will clear bit we are concerned with
	m_pBits[byteIndex] = ~m_pBits[byteIndex] ^ ~bitEvaluator;
}

bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
{
	size_t index = 0;

	// skip bytes where bits are clear
	while ((m_pBits[index] == 0x0) && (index <= numElements))
		index++;

	if (index > numElements)
		return false;

	// at the index there is a clear bit
	uint64_t setBits = m_pBits[index];

	bool foundIndex = _BitScanForward64(reinterpret_cast<unsigned long *>(&o_bitNumber), static_cast<unsigned __int64>(setBits));

	// adds to relative bit number for element we just scanned
	// to get the correct bit of overall bit array
	o_bitNumber += index * m_numBitsInElement;

	return foundIndex;
}

bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
{
	size_t index = 0;

	// skip bytes where bits are set
	while ((m_pBits[index] == FULL_8_BYTES) && (index <= numElements))
		index++;

	if (index > numElements)
		return false;

	// at the index there is a clear bit
	uint64_t clearBits = m_pBits[index];

	// need to flip bits to actually get first clear bit
	bool foundIndex = _BitScanForward64(reinterpret_cast<unsigned long *>(&o_bitNumber), static_cast<unsigned __int64>(~clearBits));

	// adds to relative bit number for element we just scanned
	// to get the correct bit of overall bit array
	o_bitNumber += index * m_numBitsInElement;

	return foundIndex;
}

// TODO put in inl.h file
bool BitArray::operator[](size_t i_index) const
{
	size_t byteIndex = GetByteIndex(i_index, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_index, m_numBitsInElement);

	return m_pBits[byteIndex] & bitEvaluator;
}
