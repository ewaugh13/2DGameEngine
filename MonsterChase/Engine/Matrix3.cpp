#include "Matrix3.h"

#include <assert.h>

namespace Engine
{
	const Matrix3 Matrix3::IdentityMatrix =
		Matrix3(1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f);

#pragma region Constructors and Operator Overloads

	Matrix3::Matrix3()
	{
	}

	Matrix3::Matrix3(
		float i_11, float i_12, float i_13,
		float i_21, float i_22, float i_23,
		float i_31, float i_32, float i_33) :
		m_11(i_11), m_12(i_12), m_13(i_13),
		m_21(i_21), m_22(i_22), m_23(i_23),
		m_31(i_31), m_32(i_32), m_33(i_33)
	{
	}

	Matrix3::Matrix3(const Matrix3 & i_Other)
	{
		m_11 = i_Other.m_11; m_12 = i_Other.m_12; m_13 = i_Other.m_13;
		m_21 = i_Other.m_21; m_22 = i_Other.m_22; m_23 = i_Other.m_23;
		m_31 = i_Other.m_31; m_32 = i_Other.m_32; m_33 = i_Other.m_33;
	}

	Matrix3 & Matrix3::operator=(const Matrix3 & i_Other)
	{
		m_11 = i_Other.m_11; m_12 = i_Other.m_12; m_13 = i_Other.m_13;
		m_21 = i_Other.m_21; m_22 = i_Other.m_22; m_23 = i_Other.m_23;
		m_31 = i_Other.m_31; m_32 = i_Other.m_32; m_33 = i_Other.m_33;
		return *this;
	}

	bool Matrix3::operator==(const Matrix3 & i_Other) const
	{
		return m_11 == i_Other.m_11 && m_12 == i_Other.m_12 && m_13 == i_Other.m_13
			&& m_21 == i_Other.m_21 && m_22 == i_Other.m_22 && m_23 == i_Other.m_23
			&& m_31 == i_Other.m_31 && m_32 == i_Other.m_32 && m_33 == i_Other.m_33;
	}

	Matrix3 Matrix3::operator*(const Matrix3 & i_Other) const
	{
		Matrix3 returnMatrix = Matrix3();

		// calculate first row
		returnMatrix.m_11 = m_11 * i_Other.m_11 + m_12 * i_Other.m_21 + m_13 * i_Other.m_31;
		returnMatrix.m_12 = m_11 * i_Other.m_12 + m_12 * i_Other.m_22 + m_13 * i_Other.m_32;
		returnMatrix.m_13 = m_11 * i_Other.m_13 + m_12 * i_Other.m_23 + m_13 * i_Other.m_33;

		// calculate second row
		returnMatrix.m_21 = m_21 * i_Other.m_11 + m_22 * i_Other.m_21 + m_23 * i_Other.m_31;
		returnMatrix.m_22 = m_21 * i_Other.m_12 + m_22 * i_Other.m_22 + m_23 * i_Other.m_32;
		returnMatrix.m_23 = m_21 * i_Other.m_13 + m_22 * i_Other.m_23 + m_23 * i_Other.m_33;

		// calculate third row
		returnMatrix.m_31 = m_31 * i_Other.m_11 + m_32 * i_Other.m_21 + m_33 * i_Other.m_31;
		returnMatrix.m_32 = m_31 * i_Other.m_12 + m_32 * i_Other.m_22 + m_33 * i_Other.m_32;
		returnMatrix.m_33 = m_31 * i_Other.m_13 + m_32 * i_Other.m_23 + m_33 * i_Other.m_33;

		return returnMatrix;
	}

	Matrix3 Matrix3::operator*(const float i_Scalar) const
	{
		float n_11 = m_11 * i_Scalar;
		float n_12 = m_12 * i_Scalar;
		float n_13 = m_13 * i_Scalar;

		float n_21 = m_21 * i_Scalar;
		float n_22 = m_22 * i_Scalar;
		float n_23 = m_23 * i_Scalar;

		float n_31 = m_31 * i_Scalar;
		float n_32 = m_32 * i_Scalar;
		float n_33 = m_33 * i_Scalar;

		return Matrix3(
			n_11, n_12, n_13,
			n_21, n_22, n_23,
			n_31, n_32, n_33);
	}

#pragma endregion

#pragma region Get Row and Col

	Vector3 Matrix3::GetRow(unsigned int i_Row) const
	{
		switch (i_Row)
		{
		case 0:
			return Vector3(m_11, m_12, m_13);
		case 1:
			return Vector3(m_21, m_22, m_23);
		case 2:
			return Vector3(m_31, m_32, m_33);

		default:
			assert(false);
			return Vector3(NAN, NAN, NAN);
		}
	}

	Vector3 Matrix3::GetCol(unsigned int i_Col) const
	{
		switch (i_Col)
		{
		case 0:
			return Vector3(m_11, m_21, m_31);
		case 1:
			return Vector3(m_12, m_22, m_32);
		case 2:
			return Vector3(m_13, m_23, m_33);

		default:
			assert(false);
			return Vector3(NAN, NAN, NAN);
		}
	}

#pragma endregion


	Matrix4 Matrix3::ToTransform() const
	{
		return Matrix4(
			m_11, m_12, m_13, 0.0f,
			m_21, m_22, m_23, 0.0f,
			m_31, m_32, m_33, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

#pragma region Matrix Creators

	Matrix3 Matrix3::CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ)
	{
		return Matrix3(
			i_ScaleX, 0.0f, 0.0f,
			0.0f, i_ScaleY, 0.0f,
			0.0f, 0.0f, i_ScaleZ);
	}

#pragma endregion

#pragma region Rotation Row Vector

	Matrix3 Matrix3::CreateXRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			1.0f, 0.0f, 0.0f,
			0.0f, cosVal, sinVal,
			0.0f, -sinVal, cosVal);
	}

	Matrix3 Matrix3::CreateYRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			cosVal, 0.0f, -sinVal,
			0.0f, 1.0f, 0.0f,
			sinVal, -0.0f, cosVal);
	}

	Matrix3 Matrix3::CreateZRotationRowVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			cosVal, sinVal, 0.0f,
			-sinVal, cosVal, 0.0f,
			0.0f, 0.0f, 1.0f);
	}

#pragma endregion

#pragma region Rotation Column Vector

	Matrix3 Matrix3::CreateXRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			1.0f, 0.0f, 0.0f,
			0.0f, cosVal, -sinVal,
			0.0f, sinVal, cosVal);
	}

	Matrix3 Matrix3::CreateYRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			cosVal, 0.0f, sinVal,
			0.0f, 1.0f, 0.0f,
			-sinVal, -0.0f, cosVal);
	}

	Matrix3 Matrix3::CreateZRotationColVec(float i_RotationRadians)
	{
		float sinVal = sinf(i_RotationRadians);
		float cosVal = cosf(i_RotationRadians);

		return Matrix3(
			cosVal, -sinVal, 0.0f,
			sinVal, cosVal, 0.0f,
			0.0f, 0.0f, 1.0f);
	}

#pragma endregion

	void Matrix3::Transpose()
	{
		float temp;

		// swap row 1 and column 1 except m_11
		temp = m_21; m_21 = m_12; m_12 = temp;
		temp = m_31; m_31 = m_13; m_13 = temp;

		temp = m_32; m_32 = m_23; m_23 = temp;
	}

#pragma region Multiplication

	Vector3 Matrix3::MultiplyLeft(const Vector3 & i_Vector) const
	{
		return Vector3(
			i_Vector.m_x * m_11 + i_Vector.m_y * m_21 + i_Vector.m_z * m_31,
			i_Vector.m_x * m_12 + i_Vector.m_y * m_22 + i_Vector.m_z * m_32,
			i_Vector.m_x * m_13 + i_Vector.m_y * m_23 + i_Vector.m_z * m_33);
	}

	Vector3 Matrix3::MultiplyRight(const Vector3 & i_Vector) const
	{
		return Vector3(
			i_Vector.m_x * m_11 + i_Vector.m_y * m_12 + i_Vector.m_z * m_13,
			i_Vector.m_x * m_21 + i_Vector.m_y * m_22 + i_Vector.m_z * m_23,
			i_Vector.m_x * m_31 + i_Vector.m_y * m_32 + i_Vector.m_z * m_33);
	}

#pragma endregion

}
