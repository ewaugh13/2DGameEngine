#include "CppUnitTest.h"
#include "Vector3.h"
#include "Matrix4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathUnitTests
{
	TEST_CLASS(Vector3UnitTest)
	{
	public:

		TEST_METHOD(JoesTest)
		{
			using namespace Engine;

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
			using namespace Engine;

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

	TEST_CLASS(Matrix4UnitTest)
	{
	public:

		TEST_METHOD(MatrixTest)
		{
			using namespace Engine;

			Matrix4 identity = Matrix4::IdentityMatrix;
			Matrix4 identityTrans = identity.GetTranspose();
			Assert::IsTrue(identity == identityTrans);
			Assert::IsTrue(identity == identity.GetInverse());

			Matrix4 mat1 = Matrix4(
				2, 3, 4, 1,
				1, 2, 2, 1,
				2, 4, 3, 2,
				2, 1, 3, 2);

			// test scalar multiply
			Matrix4 mat2 = Matrix4(
				4, 6, 8, 2,
				2, 4, 4, 2,
				4, 8, 6, 4,
				4, 2, 6, 4);
			Assert::IsTrue(mat1 * 2 == mat2);

			// test matrix multiplication
			Matrix4 mat1X2 = Matrix4(
				34, 58, 58, 30,
				20, 32, 34, 18,
				36, 56, 62, 32,
				30, 44, 50, 26);
			Assert::IsTrue(mat1X2 == mat1 * mat2);

			// test transform point
			Vector3 point = Vector3(2.0f, 2.0f, 0.0f);
			Matrix4 transform = Matrix4::CreateTranslationRowVec(Vector3(1.0f, 2.0, 2.5f));
			Vector3 transformPoint = Vector3(3.0f, 4.0f, 2.5f);
			Assert::IsTrue(transformPoint == transform.TransformPointRowVec(point));

			// test rotation matricies
			Matrix4 ZRotation45 = Matrix4::CreateZRotationColVec(0.785398f);
			Matrix4 ZRotation45Expected = Matrix4(
											0.707106888f, -0.707106650f, 0.0f, 0.0f,
											0.707106650f,  0.707106888f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f);
			Assert::IsTrue(ZRotation45Expected == ZRotation45);

			// test determinant
			Assert::IsTrue(-3 == mat1.Determinant());
			Assert::IsTrue(-48 == mat2.Determinant());
			Assert::IsTrue(144 == mat1X2.Determinant());

			// test inverting
			Matrix4 mat1InvExpected = Matrix4(
											 1.0f, -5.0f,   1.66666675f,  0.333333343f,
											 0.0f,  0.0f,  0.333333343f, -0.333333343f,
											 0.0f,  2.0f,         -1.0f,          0.0f,
											-1.0f,  2.0f, -0.333333343f,  0.333333343f);
			Assert::IsTrue(mat1InvExpected == mat1.GetInverse());

			Matrix4 mat2InvExpected = Matrix4(
				 0.5f, -2.5f,  0.833333373f,  0.166666672f,
				 0.0f,  0.0f,  0.166666672f, -0.166666672f,
				 0.0f,  1.0f,         -0.5f,          0.0f,
				-0.5f,  1.0f, -0.166666672f,  0.166666672f);
			Assert::IsTrue(mat2InvExpected == mat2.GetInverse());

			Matrix4 mat1X2InvExpected = Matrix4(
				 0.333333343f, -0.5f, -0.888888896f,   1.05555558f,
				 0.166666672f,  0.0f, -0.111111112f, -0.055555556f,
				         0.0f, -1.0f,  0.833333313f, -0.333333343f,
				-0.666666687f,  2.5f, -0.388888896f, -0.444444448f);
			Assert::IsTrue(mat1X2InvExpected == mat1X2.GetInverse());

			// test transpose
			Matrix4 mat1TransposeExpected = Matrix4(
				2, 1, 2, 2,
				3, 2, 4, 1,
				4, 2, 3, 3,
				1, 1, 2, 2);
			Assert::IsTrue(mat1TransposeExpected == mat1.GetTranspose());
		}
	};
}