#include "CppUnitTest.h"
#include "Point2D.h"
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
			SmartPtr<Point2D> point2DSmartPtr = SmartPtr<Point2D>(new Point2D(5.0f, 5.0f));
			SmartPtr<Point2D> point2DZeroSmartPtr = SmartPtr<Point2D>(new Point2D(0.0f, 0.0f));

			// Test getting smartptr held value
			Point2D point2DValue = *point2DSmartPtr;
			Assert::AreEqual(5.0f, point2DValue.GetX());

			// Test getting smartptr held ptr
			Point2D * point2DPtr = point2DSmartPtr.operator->();
			Assert::AreEqual(5.0f, point2DPtr->GetX());

			// Test setting smart ptr equal to null and it not being valid
			Assert::IsTrue(point2DSmartPtr);
			point2DSmartPtr = nullptr;
			Assert::IsFalse(point2DSmartPtr);

			// Test assignment eqaul operator
			point2DSmartPtr = SmartPtr<Point2D>(new Point2D(6.0f, 6.0f));
			point2DSmartPtr = point2DZeroSmartPtr;

			// Test smartptr being equal to null
			point2DSmartPtr = nullptr;
			Assert::IsTrue(point2DSmartPtr == nullptr);

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
			SmartPtr<Point2D> point2DSmartPtr = SmartPtr<Point2D>(new Point2D(5.0f, 5.0f));

			// Create weakptr from smartptr
			WeakPtr<Point2D> point2DWeakPtr = WeakPtr<Point2D>(point2DSmartPtr);

			// Validate the weakptr ref count
			Assert::IsTrue(point2DSmartPtr == point2DWeakPtr);
			unsigned int weakPtrRefCount = 1;
			Assert::AreEqual(weakPtrRefCount, point2DWeakPtr.UseCount());

			// Get smartptr from weakptr
			SmartPtr<Point2D> aquiredPoint2D = point2DWeakPtr.AcquireSmartPtr();

			// Access the held value from the aquired smartptr
			Point2D point2DValue = *aquiredPoint2D;
			Assert::AreEqual(5.0f, point2DValue.GetX());

			// Access the held ptr from the aquired smartptr
			Point2D * point2DPtr = aquiredPoint2D.operator->();
			Assert::AreEqual(5.0f, point2DPtr->GetX());

			// Create a weakptr from a null smartptr and assert it is null
			point2DSmartPtr = nullptr;
			WeakPtr<Point2D> weakPtrFromNullSmart = WeakPtr<Point2D>(point2DSmartPtr);
			Assert::IsTrue(weakPtrFromNullSmart == nullptr);

			// Create weakptr from aquired smartptr
			WeakPtr<Point2D> weakPtrFromAquired = WeakPtr<Point2D>(aquiredPoint2D);
			weakPtrRefCount = 2;
			Assert::AreEqual(weakPtrRefCount, weakPtrFromAquired.UseCount());
			Assert::IsTrue(weakPtrFromAquired);
		}
	};
}