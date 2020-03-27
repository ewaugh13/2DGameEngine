#pragma once

#include "ReferenceCount.h"

template<class T >
class SmartPtr
{
public:
	explicit SmartPtr(T * i_Ptr) :
		m_Ptr(i_Ptr), m_ReferenceCount(new ReferenceCount(1, 0))
	{
	}

	SmartPtr(SmartPtr & i_Other) :
		m_Ptr(i_Other.m_Ptr), m_ReferenceCount(i_Other.m_ReferenceCount)
	{
		(*m_ReferenceCount->m_SmartPtrsCount)++;
	}

	SmartPtr & operator=(SmartPtr & i_Other)
	{
		if (this != &i_Other)
		{
			Release();

			m_Ptr = i_Other.m_Ptr;
			m_ReferenceCount = i_Other.m_ReferenceCount;

			m_ReferenceCount->m_SmartPtrsCount++;
		}

		return *this;
	}

	SmartPtr & operator=(std::nullptr_t i_Nullptr)
	{
		Release();

		m_Ptr = nullptr;
		m_ReferenceCount = nullptr;

		return *this;
	}

	/*inline*/ bool operator==(std::nullptr_t i_Nullptr) const
	{
		return pPtr != nullptr;
	}

	~SmartPtr()
	{
		Release();
	}

	T * operator->()
	{
		return m_Ptr;
	}

	T & operator*()
	{
		return (*m_Ptr);
	}

	/*inline*/ operator bool() const
	{
		return m_Ptr != nullptr;
	}

private:

	void Release()
	{
		if (m_ReferenceCount != nullptr && --m_ReferenceCount->m_SmartPtrsCount == 0)
		{
			delete m_Ptr;
			delete m_ReferenceCount;
		}
	}

	T * m_Ptr;
	ReferenceCount * m_ReferenceCount;
};

