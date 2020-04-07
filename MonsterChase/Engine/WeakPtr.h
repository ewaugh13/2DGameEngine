#pragma once

#include "ReferenceCount.h"
#include "SmartPtr.h"

template<class T >
class WeakPtr
{
	template<class T>
	friend class SmartPtr;

public:
	// Empty constructor
	WeakPtr() :
		m_Ptr(nullptr), m_ReferenceCount(nullptr)
	{
	}

	// Constructor with SmartPtr
	WeakPtr(const SmartPtr<T> & i_SmartPtr) :
		m_Ptr(i_SmartPtr.m_Ptr), m_ReferenceCount(i_SmartPtr.m_ReferenceCount)
	{
		if (m_ReferenceCount != nullptr)
		{
			m_ReferenceCount->m_WeakPtrsCount++;
		}
	}

	// Copy constructor
	WeakPtr(const WeakPtr & i_Other) :
		m_Ptr(i_Other.m_Ptr), m_ReferenceCount(i_Other.m_ReferenceCount)
	{
		if (i_Other.m_ReferenceCount != nullptr)
		{
			m_ReferenceCount->m_WeakPtrsCount++;
		}
	}

	// Destructor
	~WeakPtr()
	{
		ReleaseWeakPtr();
	}

	// Assignment operator
	WeakPtr & operator=(const WeakPtr & i_Other)
	{
		if (this != &i_Other)
		{
			ReleaseWeakPtr();

			m_Ptr = i_Other.m_Ptr;
			m_ReferenceCount = i_Other.m_ReferenceCount;

			m_ReferenceCount->m_WeakPtrsCount++;
		}

		return *this;
	}

	// Assignment operator
	WeakPtr & operator=(const SmartPtr<T> & i_SmartPtr)
	{
		if (this != &i_SmartPtr)
		{
			ReleaseWeakPtr();

			m_Ptr = i_SmartPtr.m_Ptr;
			m_ReferenceCount = i_SmartPtr.m_ReferenceCount;

			m_ReferenceCount->m_WeakPtrsCount++;
		}

		return *this;
	}

	// Assignment operator to nullptr
	WeakPtr & operator=(std::nullptr_t i_Nullptr)
	{
		ReleaseWeakPtr();

		m_Ptr = nullptr;
		m_ReferenceCount = nullptr;

		return *this;
	}

	inline SmartPtr<T> AcquireSmartPtr()
	{
		return SmartPtr<T>(*this);
	}

	// If two weak ptrs are holding the same ptr
	template<class E>
	inline bool operator==(const WeakPtr<E> & i_Other) const
	{
		return m_Ptr == i_Other.m_Ptr;
	}

	// If the weak ptr is holding this value
	template<class E>
	inline bool operator==(const E * i_Other) const
	{
		return m_Ptr == i_Other;
	}

	// If two weak ptrs are holding a different ptr
	template<class E>
	inline bool operator!=(const WeakPtr<E> & i_Other) const
	{
		return m_Ptr != i_Other.m_Ptr;
	}

	// If the weak ptr is holding this value
	template<class E>
	inline bool operator!=(const E * i_Other) const
	{
		return m_Ptr != i_Other;
	}

	// If a weak ptr holds a nullptr and is null
	inline bool operator==(std::nullptr_t i_Nullptr) const
	{
		return m_Ptr == nullptr;
	}

	// If the weak ptr is valid
	inline operator bool() const
	{
		return m_Ptr != nullptr;
	}

	// Return num of weak ptrs reference count
	inline unsigned int UseCount()
	{
		return m_ReferenceCount->m_WeakPtrsCount;
	}

private:

	// Decrement weak ptr count and delete reference count if no more weak ptr references
	void ReleaseWeakPtr()
	{
		if (m_ReferenceCount != nullptr && --m_ReferenceCount->m_WeakPtrsCount == 0)
		{
			if (m_ReferenceCount->m_SmartPtrsCount == 0)
			{
				delete m_ReferenceCount;
				m_ReferenceCount = nullptr;

				m_Ptr = nullptr;
			}
		}
	}

	T * m_Ptr;
	ReferenceCount * m_ReferenceCount;
};

