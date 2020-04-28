#include "Matrix4.h"

#include <assert.h>

namespace Engine
{

#pragma region Constructors and Operator Overloads

	const Matrix4 Matrix4::IdentityMatrix =
		Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4::Matrix4()
	{
	}

	Matrix4::Matrix4(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44) :
		m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
		m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
		m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
		m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
	{
	}

	Matrix4::Matrix4(const Matrix4 & i_Other)
	{
		m_11 = i_Other.m_11; m_12 = i_Other.m_12; m_13 = i_Other.m_13; m_14 = i_Other.m_14;
		m_21 = i_Other.m_21; m_22 = i_Other.m_22; m_23 = i_Other.m_23; m_24 = i_Other.m_24;
		m_31 = i_Other.m_31; m_32 = i_Other.m_32; m_33 = i_Other.m_33; m_34 = i_Other.m_34;
		m_41 = i_Other.m_41; m_42 = i_Other.m_42; m_43 = i_Other.m_43; m_44 = i_Other.m_44;
	}

	Matrix4 & Matrix4::operator=(const Matrix4 & i_Other)
	{
		m_11 = i_Other.m_11; m_12 = i_Other.m_12; m_13 = i_Other.m_13; m_14 = i_Other.m_14;
		m_21 = i_Other.m_21; m_22 = i_Other.m_22; m_23 = i_Other.m_23; m_24 = i_Other.m_24;
		m_31 = i_Other.m_31; m_32 = i_Other.m_32; m_33 = i_Other.m_33; m_34 = i_Other.m_34;
		m_41 = i_Other.m_41; m_42 = i_Other.m_42; m_43 = i_Other.m_43; m_44 = i_Other.m_44;
		return *this;
	}

	Matrix4 Matrix4::operator*(const Matrix4 & i_Other) const
	{
		Matrix4 returnMatrix = Matrix4();

		// calculate first row
		returnMatrix.m_11 = m_11 * i_Other.m_11 + m_12 * i_Other.m_21 + m_13 * i_Other.m_31 + m_14 * i_Other.m_41;
		returnMatrix.m_12 = m_11 * i_Other.m_12 + m_12 * i_Other.m_22 + m_13 * i_Other.m_32 + m_14 * i_Other.m_42;
		returnMatrix.m_13 = m_11 * i_Other.m_13 + m_12 * i_Other.m_23 + m_13 * i_Other.m_33 + m_14 * i_Other.m_43;
		returnMatrix.m_14 = m_11 * i_Other.m_14 + m_12 * i_Other.m_24 + m_13 * i_Other.m_34 + m_14 * i_Other.m_44;

		// calculate second row
		returnMatrix.m_21 = m_21 * i_Other.m_11 + m_22 * i_Other.m_21 + m_23 * i_Other.m_31 + m_24 * i_Other.m_41;
		returnMatrix.m_22 = m_21 * i_Other.m_12 + m_22 * i_Other.m_22 + m_23 * i_Other.m_32 + m_24 * i_Other.m_42;
		returnMatrix.m_23 = m_21 * i_Other.m_13 + m_22 * i_Other.m_23 + m_23 * i_Other.m_33 + m_24 * i_Other.m_43;
		returnMatrix.m_24 = m_21 * i_Other.m_14 + m_22 * i_Other.m_24 + m_23 * i_Other.m_34 + m_24 * i_Other.m_44;

		// calculate third row
		returnMatrix.m_31 = m_31 * i_Other.m_11 + m_32 * i_Other.m_21 + m_33 * i_Other.m_31 + m_34 * i_Other.m_41;
		returnMatrix.m_32 = m_31 * i_Other.m_12 + m_32 * i_Other.m_22 + m_33 * i_Other.m_32 + m_34 * i_Other.m_42;
		returnMatrix.m_33 = m_31 * i_Other.m_13 + m_32 * i_Other.m_23 + m_33 * i_Other.m_33 + m_34 * i_Other.m_43;
		returnMatrix.m_34 = m_31 * i_Other.m_14 + m_32 * i_Other.m_24 + m_33 * i_Other.m_34 + m_34 * i_Other.m_44;

		// calculate fourth row
		returnMatrix.m_41 = m_41 * i_Other.m_11 + m_42 * i_Other.m_21 + m_43 * i_Other.m_31 + m_44 * i_Other.m_41;
		returnMatrix.m_42 = m_41 * i_Other.m_12 + m_42 * i_Other.m_22 + m_43 * i_Other.m_32 + m_44 * i_Other.m_42;
		returnMatrix.m_43 = m_41 * i_Other.m_13 + m_42 * i_Other.m_23 + m_43 * i_Other.m_33 + m_44 * i_Other.m_43;
		returnMatrix.m_44 = m_41 * i_Other.m_14 + m_42 * i_Other.m_24 + m_43 * i_Other.m_34 + m_44 * i_Other.m_44;

		return returnMatrix;
	}

	Matrix4 Matrix4::operator*(const float i_Scalar) const
	{
		float n_11 = m_11 * i_Scalar;
		float n_12 = m_12 * i_Scalar;
		float n_13 = m_13 * i_Scalar;
		float n_14 = m_14 * i_Scalar;

		float n_21 = m_21 * i_Scalar;
		float n_22 = m_22 * i_Scalar;
		float n_23 = m_23 * i_Scalar;
		float n_24 = m_24 * i_Scalar;

		float n_31 = m_31 * i_Scalar;
		float n_32 = m_32 * i_Scalar;
		float n_33 = m_33 * i_Scalar;
		float n_34 = m_34 * i_Scalar;

		float n_41 = m_41 * i_Scalar;
		float n_42 = m_42 * i_Scalar;
		float n_43 = m_43 * i_Scalar;
		float n_44 = m_44 * i_Scalar;

		return Matrix4(
			n_11, n_12, n_13, n_14,
			n_21, n_22, n_23, n_24,
			n_31, n_32, n_33, n_34,
			n_41, n_42, n_43, n_44);
	}

#pragma endregion

#pragma region Get Row and Col

	Vector4 Matrix4::GetRow(unsigned int i_Row) const
	{
		switch (i_Row)
		{
		case 0:
			return Vector4(m_11, m_12, m_13, m_14);
		case 1:
			return Vector4(m_21, m_22, m_23, m_24);
		case 2:
			return Vector4(m_31, m_32, m_33, m_34);
		case 3:
			return Vector4(m_41, m_42, m_43, m_44);

		default:
			assert(false);
			return Vector4(NAN, NAN, NAN, NAN);
		}
	}

	Vector4 Matrix4::GetCol(unsigned int i_Col) const
	{
		switch (i_Col)
		{
		case 0:
			return Vector4(m_11, m_21, m_31, m_41);
		case 1:
			return Vector4(m_12, m_22, m_32, m_42);
		case 2:
			return Vector4(m_13, m_23, m_33, m_43);
		case 3:
			return Vector4(m_14, m_24, m_34, m_44);

		default:
			assert(false);
			return Vector4(NAN, NAN, NAN, NAN);
		}
	}

#pragma endregion

#pragma region Matrix Creators

	Matrix4 Matrix4::CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ)
	{
		return Matrix4(
			i_ScaleX, 0.0f, 0.0f, 0.0f,
			0.0f, i_ScaleY, 0.0f, 0.0f,
			0.0f, 0.0f, i_ScaleZ, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

#pragma endregion

#pragma region Rotation Row Vector

	Matrix4 Matrix4::CreateXRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosVal, sinVal, 0.0f,
			0.0f, -sinVal, cosVal, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateYRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			cosVal, 0.0f, -sinVal, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinVal, -0.0f, cosVal, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateZRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			cosVal, sinVal, 0.0f, 0.0f,
			-sinVal, cosVal, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateTranslationRowVec(float i_TransX, float i_TransY, float i_TransZ)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			i_TransX, i_TransY, i_TransZ, 1.0f);
	}

#pragma endregion

#pragma region Rotation Column Vector

	Matrix4 Matrix4::CreateXRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosVal, -sinVal, 0.0f,
			0.0f, sinVal, cosVal, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateYRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			cosVal, 0.0f, sinVal, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sinVal, -0.0f, cosVal, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateZRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix4(
			cosVal, -sinVal, 0.0f, 0.0f,
			sinVal, cosVal, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::CreateTranslationColVec(float i_TransX, float i_TransY, float i_TransZ)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, i_TransX,
			0.0f, 1.0f, 0.0f, i_TransY,
			0.0f, 0.0f, 1.0f, i_TransZ,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

#pragma endregion

#pragma region Determinant, Inverse and Transpose

	float Matrix4::Determinant() const
	{
		/* see https://www.mathsisfun.com/algebra/matrix-determinant.html */

		float a = m_11; float b = m_12; float c = m_13; float d = m_14;
		float e = m_21; float f = m_22; float g = m_23; float h = m_24;
		float i = m_31; float j = m_32; float k = m_33; float l = m_34;
		float m = m_41; float n = m_42; float o = m_43; float p = m_44;

		float firstDetSect  = f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n);
		float secondDetSect = e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m);
		float thirdDetSect  = e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m);
		float fourthDetSect = e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m);

		return a * (firstDetSect) - b * (secondDetSect) + c * (thirdDetSect) - d * (fourthDetSect);
	}

	void Matrix4::Invert()
	{
		/* see https://ncalculators.com/matrix/inverse-matrix.htm */

		float determinant = Determinant();

		float a = m_11; float b = m_12; float c = m_13; float d = m_14;
		float e = m_21; float f = m_22; float g = m_23; float h = m_24;
		float i = m_31; float j = m_32; float k = m_33; float l = m_34;
		float m = m_41; float n = m_42; float o = m_43; float p = m_44;

		// get adjugate matrix
		m_11 = -(h * k * n) + (g * l * n) + (h * j * o) - (f * l * o) - (g * j * p) + (f * k * p);
		m_12 = (d * k * n) - (c * l * n) - (d * j * o) + (d * j * o) + (b * l * o) - (c * j * p);
		m_13 = -(d * g * n) + (c * h * n) + (d * f * o) - (b * h * o) - (c * f * p) + (b * g * p);
		m_14 = (d * g * j) - (c * h * j) - (d * f * k) + (b * h * k) + (c * f * l) - (b * g * l);

		m_21 = (h * k * m) - (g * l * m) - (h * i * o) + (e * l * o) + (g * i * p) - (e * k * p);
		m_22 = -(d * k * m) + (c * l * m) + (d * i * o) - (a * l * o) - (c * i * p) + (a * k * p);
		m_23 = (d * g * m) - (c * h * m) - (d * e * o) + (a * h * o) + (c * e * p) - (a * g * p);
		m_24 = -(d * g * i) + (c * h * i) + (d * e * k) - (a * h * k) - (c * e * l) + (a * g * l);

		m_31 = -(h * j * m) + (f * l * m) + (h * i * n) - (e * l * n) - (f * i * p) + (e * j * p);
		m_32 = (d * j * m) - (b * l * m) - (d * i * n) + (a * l * n) + (b * i * p) - (a * j * p);
		m_33 = -(d * f * m) + (b * h * m) + (d * e * n) - (a * h * n) - (b * e * p) + (a * f * p);
		m_34 = (d * f * i) - (b * h * i) - (d * e * j) + (a * h * j) + (b * e * l) - (a * f * l);

		m_41 = (g * j * m) - (f * k * m) - (g * i * n) + (e * k * n) + (f * i * o) - (e * j * o);
		m_42 = -(c * j * m) + (b * k * m) + (c * i * n) - (a * k * n) - (b * i * o) - (a * j * o);
		m_43 = (c * f * m) - (b * g * m) - (c * e * n) + (a * g * n) + (b * e * o) - (a * f * o);
		m_44 = -(c * f * i) + (b * g * i) + (c * e * j) - (a * g * j) - (b * e * k) + (a * f * k);

		*this = *this * (1 / determinant);
	}

	Matrix4 Matrix4::GetInverseRotTransColVec() const
	{
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_41));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_42));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_43));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_44));

		return Matrix4(
			m_11, m_21, m_31, -((m_11 * m_14) + (m_21 * m_24) + (m_31 * m_34)),
			m_12, m_22, m_32, -((m_12 * m_14) + (m_22 * m_24) + (m_32 * m_34)),
			m_13, m_23, m_33, -((m_13 * m_14) + (m_23 * m_24) + (m_33 * m_34)),
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::GetInverseRotTransRowVec() const
	{
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_41));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_42));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_43));
		assert(FloatFunctionLibrary::AlmostEqualZeroCertain(m_44));

		return Matrix4(
			m_11, m_21, m_31, 0.0f,
			m_12, m_22, m_32, 0.0f,
			m_13, m_23, m_33, 0.0f,
			-((m_11 * m_41) + (m_12 * m_42) + (m_13 * m_43)), -((m_21 * m_41) + (m_22 * m_42) + (m_23 * m_43)),
				-((m_31 * m_41) + (m_32 * m_42) + (m_33 * m_43)), 1.0f);
	}

	void Matrix4::Transpose()
	{
		float temp;

		// swap row 1 and column 1 except m_11
		temp = m_21; m_21 = m_12; m_12 = temp;
		temp = m_31; m_31 = m_13; m_13 = temp;
		temp = m_41; m_41 = m_14; m_14 = temp;

		temp = m_32; m_32 = m_23; m_23 = temp;
		temp = m_42; m_42 = m_24, m_24 = temp;

		temp = m_43; m_43 = m_34; m_34 = temp;
	}

#pragma endregion

#pragma region Multiplication

	Vector4 Matrix4::MultiplyLeft(const Vector4 & i_Vector) const
	{
		return Vector4(
			i_Vector.m_x * m_11 + i_Vector.m_y * m_21 + i_Vector.m_z * m_31 + i_Vector.m_w * m_41,
			i_Vector.m_x * m_12 + i_Vector.m_y * m_22 + i_Vector.m_z * m_32 + i_Vector.m_w * m_42,
			i_Vector.m_x * m_13 + i_Vector.m_y * m_23 + i_Vector.m_z * m_33 + i_Vector.m_w * m_43,
			i_Vector.m_x * m_14 + i_Vector.m_y * m_24 + i_Vector.m_z * m_34 + i_Vector.m_w * m_44);
	}

	Vector4 Matrix4::MultiplyRight(const Vector4 & i_Vector) const
	{
		return Vector4(
			i_Vector.m_x * m_11 + i_Vector.m_y * m_12 + i_Vector.m_z * m_13 + i_Vector.m_w * m_14,
			i_Vector.m_x * m_21 + i_Vector.m_y * m_22 + i_Vector.m_z * m_23 + i_Vector.m_w * m_24,
			i_Vector.m_x * m_31 + i_Vector.m_y * m_32 + i_Vector.m_z * m_33 + i_Vector.m_w * m_34,
			i_Vector.m_x * m_41 + i_Vector.m_y * m_42 + i_Vector.m_z * m_43 + i_Vector.m_w * m_44);
	}

#pragma endregion

}
