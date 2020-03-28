#include "CppUnitTest.h"
#include "Point2D.h"
#include "SmartPtr.h"

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

			Point2D point2DValue = *point2DSmartPtr;
			Assert::AreEqual(5.0f, point2DValue.GetX());

			Point2D * point2DPtr = point2DSmartPtr.operator->();
			Assert::AreEqual(5.0f, point2DPtr->GetX());

			Assert::IsTrue(point2DSmartPtr);
			point2DSmartPtr = nullptr;
			Assert::IsFalse(point2DSmartPtr);

			point2DSmartPtr = SmartPtr<Point2D>(new Point2D(6.0f, 6.0f));
			point2DSmartPtr = point2DZeroSmartPtr;

			point2DSmartPtr = nullptr;
			Assert::IsTrue(point2DSmartPtr == nullptr);

			SmartPtr<int> intSmartPtr = SmartPtr<int>(new int[2]{});
			int * pInt = intSmartPtr.operator->();
			pInt[0] = 0;
			pInt[1] = 5;
			Assert::AreEqual(5, intSmartPtr[1]);

			SmartPtr<int> intSmartPtrCopy = intSmartPtr;
			unsigned int expectedUseCount = 2;
			Assert::AreEqual(expectedUseCount, intSmartPtrCopy.UseCount());

			SmartPtr<int> intSmartPtrDiff = SmartPtr<int>(new int[2]{});
			int * pIntDiff = intSmartPtrDiff.operator->();
			pIntDiff[0] = 100;
			pIntDiff[1] = 500;

			intSmartPtr.Swap(intSmartPtrDiff);
			Assert::AreEqual(500, intSmartPtr[1]);
		}
	};
}