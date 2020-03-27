#pragma once

struct ReferenceCount
{
	unsigned int m_SmartPtrsCount;
	unsigned int m_WeakPtrsCount;

	ReferenceCount(int i_SmartPtrsCount, unsigned int i_WeakPtrsCount) :
		m_SmartPtrsCount(i_SmartPtrsCount), m_WeakPtrsCount(i_WeakPtrsCount)
	{
	}
};