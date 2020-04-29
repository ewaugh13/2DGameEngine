#include "CppUnitTest.h"
#include "Vector3.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmartWeakPtrTest
{
	TEST_CLASS(SmartWeakPtrUnitTest1)
	{
	public:

		TEST_METHOD(SmartPtrTest)
		{
			using namespace Engine;

			SmartPtr<Vector3> Vector3SmartPtr = SmartPtr<Vector3>(new Vector3(5.0f, 5.0f, 0.0f));
			SmartPtr<Vector3> Vector3ZeroSmartPtr = SmartPtr<Vector3>(new Vector3(0.0f, 0.0f, 0.0f));

			// Test getting smartptr held value
			Vector3 Vector3Value = *Vector3SmartPtr;
			Assert::AreEqual(5.0f, Vector3Value.GetX());

			// Test getting smartptr held ptr
			Vector3 * Vector3Ptr = Vector3SmartPtr.operator->();
			Assert::AreEqual(5.0f, Vector3Ptr->GetX());

			// Test setting smart ptr equal to null and it not being valid
			Assert::IsTrue(Vector3SmartPtr);
			Vector3SmartPtr = nullptr;
			Assert::IsFalse(Vector3SmartPtr);

			// Test assignment eqaul operator
			Vector3SmartPtr = SmartPtr<Vector3>(new Vector3(6.0f, 6.0f, 0.0f));
			Vector3SmartPtr = Vector3ZeroSmartPtr;

			// Test smartptr being equal to null
			Vector3SmartPtr = nullptr;
			Assert::IsTrue(Vector3SmartPtr == nullptr);

			// Test indexing into smart ptr holding array
			SmartPtr<int> intSmartPtr = SmartPtr<int>(new int[2]{});
			int * pInt = intSmartPtr.operator->();
			pInt[0] = 0;
			pInt[1] = 5;
			Assert::AreEqual(5, intSmartPtr[1]);

			// Test copy constructor and use count
			SmartPtr<int> intSmartPtrCopy = intSmartPtr;
			unsigned int expectedUseCount = 2;
			Assert::AreEqual(expectedUseCount, intSmartPtrCopy.UseCount());

			SmartPtr<int> intSmartPtrDiff = SmartPtr<int>(new int[2]{});
			int * pIntDiff = intSmartPtrDiff.operator->();
			pIntDiff[0] = 100;
			pIntDiff[1] = 500;

			// Test swaping ptrs between 
			intSmartPtr.Swap(intSmartPtrDiff);
			Assert::AreEqual(500, intSmartPtr[1]);
		}

		TEST_METHOD(WeakPtrTest)
		{
			using namespace Engine;

			SmartPtr<Vector3> Vector3SmartPtr = SmartPtr<Vector3>(new Vector3(5.0f, 5.0f, 0.0f));

			// Create weakptr from smartptr
			WeakPtr<Vector3> Vector3WeakPtr = WeakPtr<Vector3>(Vector3SmartPtr);

			// Validate the weakptr ref count
			Assert::IsTrue(Vector3SmartPtr == Vector3WeakPtr);
			unsigned int weakPtrRefCount = 1;
			Assert::AreEqual(weakPtrRefCount, Vector3WeakPtr.UseCount());

			// Get smartptr from weakptr
			SmartPtr<Vector3> aquiredVector3 = Vector3WeakPtr.AcquireSmartPtr();

			// Access the held value from the aquired smartptr
			Vector3 Vector3Value = *aquiredVector3;
			Assert::AreEqual(5.0f, Vector3Value.GetX());

			// Access the held ptr from the aquired smartptr
			Vector3 * Vector3Ptr = aquiredVector3.operator->();
			Assert::AreEqual(5.0f, Vector3Ptr->GetX());

			// Create a weakptr from a null smartptr and assert it is null
			Vector3SmartPtr = nullptr;
			WeakPtr<Vector3> weakPtrFromNullSmart = WeakPtr<Vector3>(Vector3SmartPtr);
			Assert::IsTrue(weakPtrFromNullSmart == nullptr);

			// Create weakptr from aquired smartptr
			WeakPtr<Vector3> weakPtrFromAquired = WeakPtr<Vector3>(aquiredVector3);
			weakPtrRefCount = 2;
			Assert::AreEqual(weakPtrRefCount, weakPtrFromAquired.UseCount());
			Assert::IsTrue(weakPtrFromAquired);
		}
	};
}