#include "CppUnitTest.h"
#include "Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector3UnitTests
{
	TEST_CLASS(Vector3UnitTest1)
	{
	public:

		TEST_METHOD(JoesTest)
		{
			Vector3 P1(0.0f, 0.0f, 0.0f);
			Vector3 P2(0.0f, 0.0f, 0.0f);

			Vector3 P3 = P1 + P2;
			P3 = P1 - P2;

			Vector3 P4 = P1 * 0.5f;

			Vector3 P5 = P1 / 2.0f;

			Vector3 P6 = -P4;

			P6 *= 2.0f;
			P5 /= 4.0f;

			P2 += P1;
			P3 -= P1;

			Vector3 P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

			bool bArentEqual = P6 != P4;
			Assert::IsFalse(bArentEqual);
		}

		TEST_METHOD(ConstTest)
		{
			const Vector3 ConstP1 = Vector3(1.0f, 1.0f, 0.0f);
			const Vector3 ConstP2 = ConstP1 * 4;
			const Vector3 ConstP3 = ConstP2 / 4;
			const Vector3 ConstP4 = -ConstP3;
			const Vector3 ConstP5 = ConstP4;

			Vector3 P6 = Vector3(1.0f, 1.0f, 0.0f);
			P6 += ConstP1;
			P6 -= ConstP2;
			P6 *= ConstP3;
			P6 /= ConstP4;

			Vector3 P7 = ConstP1 + ConstP2;
			Vector3 P8 = ConstP3 * ConstP2;
			Vector3 P9 = ConstP5 - ConstP4;
			Vector3 P10 = ConstP2 / ConstP4;

			Vector3 P11 = Vector3(ConstP5);

			Assert::IsTrue(P11 == ConstP5);
			Assert::IsTrue(ConstP2 > ConstP4);
			Assert::IsTrue(ConstP4 >= ConstP5);
			Assert::IsTrue(P10 != P9);
			Assert::IsTrue(P10 != P9);
		}

	};
}