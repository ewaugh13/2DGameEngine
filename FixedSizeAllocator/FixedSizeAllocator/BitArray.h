#pragma once

#include "HeapManager.h"

#include <cstdint>

class BitArray
{
public:
	BitArray(size_t i_numBits, HeapManager * i_pAllocator, bool i_startClear = true);
	~BitArray();

	void ClearAll(void);
	void SetAll(void);

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	inline bool IsBitSet(size_t i_bitNumber) const;
	inline bool IsBitClear(size_t i_bitNumber) const;

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstClearBit(size_t & o_bitNumber) const;
	bool GetFirstSetBit(size_t & o_bitNumber) const;

	bool operator[](size_t i_index) const;

private:
	uint64_t * m_pBits;
	const size_t m_numBits;
	const size_t m_numBytes;
};

