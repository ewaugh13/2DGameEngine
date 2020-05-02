#pragma once

#include "HeapManager.h"

#include <cstdint>

#pragma region Global Constants

// 8 bits in a byte
const uint8_t NUM_BITS_IN_BYTE = 8;

const uint64_t FULL_4_BYTES = 0xffffffff;
const uint64_t FULL_8_BYTES = 0xffffffffffffffff;

#pragma endregion

#pragma region Bit and Byte Helpers

// the byte that has the bit number
inline size_t GetByteIndex(size_t i_bitNumber, size_t i_numBitsInElement)
{
	return i_bitNumber / i_numBitsInElement;
}

// the bit position of the relevant byte
inline size_t GetBitPosition(size_t i_bitNumber, size_t i_numBitsInElement)
{
	return i_bitNumber % i_numBitsInElement;
}

// returns a byte with the only the bit position set to 1
inline size_t GetBitEvaluator(size_t i_bitNumber, size_t i_numBitsInElement)
{
	size_t bitPosition = GetBitPosition(i_bitNumber, i_numBitsInElement);

	return size_t(1) << bitPosition;
}

#pragma endregion

class BitArray
{
public:
	BitArray(size_t i_numBits, HeapManager::HeapManager * i_pAllocator, bool i_startClear = true);
	~BitArray();

	void SetAll(void);
	void ClearAll(void);

	bool AreAllSet(void) const;
	bool AreAllClear(void) const;

	inline bool IsBitSet(size_t i_bitNumber) const;
	inline bool IsBitClear(size_t i_bitNumber) const;

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstSetBit(size_t & o_bitNumber) const;
	bool GetFirstClearBit(size_t & o_bitNumber) const;

	bool operator[](size_t i_index) const;
#ifdef _WIN64
	uint64_t * GetBits() const { return m_pBits; }
#elif _WIN32
	uint32_t * GetBits() const { return m_pBits; }
#endif // _WIN64

private:
#ifdef _WIN64
	uint64_t * m_pBits;
#elif _WIN32
	uint32_t * m_pBits;
#endif // _WIN64
	HeapManager::HeapManager * m_allocatedUsed;
	const size_t m_numBits;
	const size_t m_numBytes;
	const size_t numElements;
	const size_t m_numBitsInElement;
};

#include "BitArray-inl.h"