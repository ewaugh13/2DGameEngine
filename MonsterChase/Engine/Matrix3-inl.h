#pragma once

#include "Matrix3.h"

namespace Engine
{
	inline Vector3 operator*(const Matrix3 & i_Mat, const Vector3 & i_Vec)
	{
		return i_Mat.MultiplyRight(i_Vec);
	}

	inline Vector3 operator*(const Vector3 & i_Vec, const Matrix3 & i_Mat)
	{
		return i_Mat.MultiplyLeft(i_Vec);
	}

#pragma region Rotation Vectors

	inline Matrix3 Matrix3::CreateXRotationRowVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateXRotationRowVec(rotationRadians);
	}

	inline Matrix3 Matrix3::CreateYRotationRowVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateYRotationRowVec(rotationRadians);
	}

	inline Matrix3 Matrix3::CreateZRotationRowVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateZRotationRowVec(rotationRadians);
	}

	inline Matrix3 Matrix3::CreateXRotationColVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateXRotationColVec(rotationRadians);
	}

	inline Matrix3 Matrix3::CreateYRotationColVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateYRotationColVec(rotationRadians);
	}

	inline Matrix3 Matrix3::CreateZRotationColVecFromDegrees(float i_RotationDegrees)
	{
		const float Pi = 3.14159265358979323846f;
		float rotationRadians = (i_RotationDegrees * Pi) / 180.0f;

		return CreateZRotationColVec(rotationRadians);
	}

#pragma endregion

	inline Matrix3 Matrix3::GetTranspose() const
	{
		return Matrix3(
			m_11, m_21, m_31,
			m_12, m_22, m_32,
			m_13, m_23, m_33);
	}
}