#pragma once

#include "ReferenceCount.h"
#include "WeakPtr.h"

template<class T >
class SmartPtr
{
	template<class T>
	friend class WeakPtr;

public:
	// Empty constructor
	SmartPtr() :
		m_Ptr(nullptr), m_ReferenceCount(nullptr)
	{
	}

	// Constructor with ptr
	explicit SmartPtr(T * i_Ptr) :
		m_Ptr(i_Ptr), m_ReferenceCount(new ReferenceCount(1, 0))
	{
	}

	// Copy Constructor
	SmartPtr(const SmartPtr & i_Other) :
		m_Ptr(i_Other.m_Ptr), m_ReferenceCount(i_Other.m_ReferenceCount)
	{
		if (m_ReferenceCount != nullptr)
		{
			m_ReferenceCount->m_SmartPtrsCount++;
		}
	}

	// Copy Constructor for other type of SmartPtr
	template<class U>
	SmartPtr(const SmartPtr<U> & i_Other) :
		m_Ptr(i_Other.m_Ptr), m_ReferenceCount(i_Other.m_ReferenceCount)
	{
		if (m_ReferenceCount != nullptr)
		{
			m_ReferenceCount->m_SmartPtrsCount++;
		}
	}

	// Copy Constructor from WeakPtr
	SmartPtr(const WeakPtr<T> & i_WeakPtr) :
		m_Ptr((i_WeakPtr.m_ReferenceCount != nullptr && i_WeakPtr.m_ReferenceCount->m_SmartPtrsCount > 0) ? i_WeakPtr.m_Ptr : nullptr),
		m_ReferenceCount((i_WeakPtr.m_ReferenceCount != nullptr && i_WeakPtr.m_ReferenceCount->m_SmartPtrsCount > 0) ? i_WeakPtr.m_ReferenceCount : nullptr)
	{
		if (m_ReferenceCount != nullptr)
		{
			m_ReferenceCount->m_SmartPtrsCount++;
		}
	}

	// Move copy constructor
	SmartPtr(SmartPtr && i_Other) noexcept :
		m_Ptr(i_Other.m_Ptr), m_ReferenceCount(i_Other.m_ReferenceCount)
	{
		i_Other.m_Ptr = nullptr;
		i_Other.m_ReferenceCount = nullptr;
	}

	// Move copy constructor with WeakPtr
	SmartPtr(WeakPtr<T> && i_WeakPtr) noexcept :
		m_Ptr(i_WeakPtr.m_Ptr), m_ReferenceCount(i_WeakPtr.m_ReferenceCount)
	{
		i_WeakPtr.m_Ptr = nullptr;
		i_WeakPtr.m_ReferenceCount = nullptr;
	}

	// Destructor
	~SmartPtr()
	{
		ReleaseSmartPtr();
	}

	// Assignment operator
	SmartPtr & operator=(const SmartPtr & i_Other)
	{
		if (this != &i_Other)
		{
			ReleaseSmartPtr();

			m_Ptr = i_Other.m_Ptr;
			m_ReferenceCount = i_Other.m_ReferenceCount;

			m_ReferenceCount->m_SmartPtrsCount++;
		}

		return *this;
	}

	// Move Assignment operator
	SmartPtr& operator=(SmartPtr && i_Other)
	{
		if (m_Ptr != i_Other.m_Ptr)
		{
			ReleaseSmartPtr();

			m_Ptr = i_Other.m_Ptr;
			m_ReferenceCount = i_Other.m_ReferenceCount;

			i_Other.m_Ptr = nullptr;
			i_Other.m_ReferenceCount = nullptr;
		}

		return *this;
	}

	// Assignment operator to nullptr
	SmartPtr & operator=(std::nullptr_t i_Nullptr)
	{
		ReleaseSmartPtr();

		m_Ptr = nullptr;
		m_ReferenceCount = nullptr;

		return *this;
	}

	// If two smart ptrs are holding the same ptr
	template<class E>
	inline bool operator==(const SmartPtr<E> & i_Other) const
	{
		return m_Ptr == i_Other.m_Ptr;
	}

	// If a smart ptr and weak ptr hold the same ptr
	template<class E>
	inline bool operator==(const WeakPtr<E> & i_SmartPtr) const
	{
		return m_Ptr == i_SmartPtr.m_Ptr;
	}

	// If the smart ptr is holding this value
	template<class E>
	inline bool operator==(const E * i_Other) const
	{
		return m_Ptr == i_Other;
	}

	// If two smart ptrs are holding a different ptr
	template<class E>
	inline bool operator!=(const SmartPtr<E> & i_Other) const
	{
		return m_Ptr != i_Other.m_Ptr;
	}

	// If the smart ptr is holding this value
	template<class E>
	inline bool operator!=(const E * i_Other) const
	{
		return m_Ptr != i_Other;
	}

	// If a smart ptr holds a nullptr and is null
	inline bool operator==(std::nullptr_t i_Nullptr) const
	{
		return m_Ptr == nullptr;
	}

	// Return the ptr this smart ptr holds
	T * operator->()
	{
		return m_Ptr;
	}

	// Return the value this smart ptr holds
	T & operator*()
	{
		return (*m_Ptr);
	}

	// If the smart ptr is valid
	inline operator bool() const
	{
		return m_Ptr != nullptr;
	}

	// Index into smart ptr holding array ptr
	inline T operator[](int i_Index)
	{
		return m_Ptr[i_Index];
	}

	// Return num or smart ptrs reference count
	inline unsigned int UseCount()
	{
		return m_ReferenceCount->m_SmartPtrsCount;
	}

	// Swap two different smart ptrs ptrs they are holding
	inline void Swap(SmartPtr & i_Other)
	{
		T * temp = i_Other.m_Ptr;
		i_Other.m_Ptr = m_Ptr;
		m_Ptr = temp;
	}

private:

	// Decrement smart ptr count and delete object if no more references
	void ReleaseSmartPtr()
	{
		if (m_ReferenceCount != nullptr && --m_ReferenceCount->m_SmartPtrsCount == 0)
		{
			delete m_Ptr;
			m_Ptr = nullptr;

			if (m_ReferenceCount->m_WeakPtrsCount == 0)
			{
				delete m_ReferenceCount;
				m_ReferenceCount = nullptr;
			}
		}
	}

	T * m_Ptr;
	ReferenceCount * m_ReferenceCount;
};

