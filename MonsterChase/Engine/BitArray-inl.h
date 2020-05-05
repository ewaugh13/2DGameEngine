#pragma once

inline bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	return m_pBits[byteIndex] & bitEvaluator;
}

inline bool BitArray::IsBitClear(size_t i_bitNumber) const
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	return !(m_pBits[byteIndex] & bitEvaluator);
}

inline void BitArray::SetBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	// using OR will set the bit we are concerned with
	m_pBits[byteIndex] = m_pBits[byteIndex] | bitEvaluator;
}

inline void BitArray::ClearBit(size_t i_bitNumber)
{
	size_t byteIndex = GetByteIndex(i_bitNumber, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_bitNumber, m_numBitsInElement);

	// using XOR with inverse of both will clear bit we are concerned with
	m_pBits[byteIndex] = ~m_pBits[byteIndex] ^ ~bitEvaluator;
}

inline bool BitArray::operator[](size_t i_index) const
{
	size_t byteIndex = GetByteIndex(i_index, m_numBitsInElement);
	size_t bitEvaluator = GetBitEvaluator(i_index, m_numBitsInElement);

	return m_pBits[byteIndex] & bitEvaluator;
}