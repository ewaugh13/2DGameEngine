#pragma once

#include "HeapManager.h"

#include <cstdint>

#pragma region Global Constants

const uint8_t NUM_BITS_IN_BYTE = 8;

const uint64_t FULL_8_BYTES = 0xffffffffffffffff;

#pragma endregion

#pragma region Bit and Byte Helpers

// the byte that has the bit number
inline size_t GetByteIndex(size_t i_bitNumber) { return i_bitNumber / NUM_BITS_IN_BYTE; }

// the bit position of the relevant byte
inline size_t GetBitPosition(size_t i_bitNumber) { return i_bitNumber % NUM_BITS_IN_BYTE; }

// returns a byte with the only the bit position set 1
inline uint8_t GetBitEvaluator(size_t i_bitPosition) { return 1 << i_bitPosition; }

#pragma endregion

class BitArray
{
public:
	BitArray(size_t i_numBits, HeapManager * i_pAllocator, bool i_startClear = true);
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

private:
	uint64_t * m_pBits;
	HeapManager * m_allocatedUsed;
	const size_t m_numBits;
	const size_t m_numBytes;
};

