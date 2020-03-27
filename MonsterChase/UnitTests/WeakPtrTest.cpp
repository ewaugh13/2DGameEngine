#include "CppUnitTest.h"
#include "Point2D.h"
#include "SmartPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WeakPtrTest
{
	TEST_CLASS(Point2DUnitTest1)
	{
	public:

		TEST_METHOD(JoesTest)
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

			point2DZeroSmartPtr.~SmartPtr();
		}
	};
}