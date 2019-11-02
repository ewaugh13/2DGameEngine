#include "CppUnitTest.h"
#include "Point2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Point2DUnitTests
{
	TEST_CLASS(Point2DUnitTest1)
	{
	public:

		TEST_METHOD(JoesTest)
		{
			Point2D P1(0.0f, 0.0f);
			Point2D P2(0.0f, 0.0f);

			Point2D P3 = P1 + P2;
			P3 = P1 - P2;

			Point2D P4 = P1 * 0.5f;

			Point2D P5 = P1 / 2.0f;

			Point2D P6 = -P4;

			P6 *= 2.0f;
			P5 /= 4.0f;

			P2 += P1;
			P3 -= P1;

			Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

			bool bArentEqual = P6 != P4;
			Assert::IsFalse(bArentEqual);
		}

		TEST_METHOD(ConstTest)
		{
			const Point2D ConstP1 = Point2D(1.0f, 1.0f);
			const Point2D ConstP2 = ConstP1 * 4;
			const Point2D ConstP3 = ConstP2 / 4;
			const Point2D ConstP4 = -ConstP3;
			const Point2D ConstP5 = ConstP4;

			Point2D P6 = Point2D(1.0f, 1.0f);
			P6 += ConstP1;
			P6 -= ConstP2;
			P6 *= ConstP3;
			P6 /= ConstP4;

			Point2D P7 = ConstP1 + ConstP2;
			Point2D P8 = ConstP3 * ConstP2;
			Point2D P9 = ConstP5 - ConstP4;
			Point2D P10 = ConstP2 / ConstP4;

			Point2D P11 = Point2D(ConstP5);

			Assert::IsTrue(P11 == ConstP5);
			Assert::IsTrue(ConstP2 > ConstP4);
			Assert::IsTrue(ConstP4 >= ConstP5);
			Assert::IsTrue(P10 != P9);
			Assert::IsTrue(P10 != P9);
		}

	};
}