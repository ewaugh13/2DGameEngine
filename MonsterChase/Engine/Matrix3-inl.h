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

	inline Matrix3 Matrix3::GetTranspose() const
	{
		return Matrix3(
			m_11, m_21, m_31,
			m_12, m_22, m_32,
			m_13, m_23, m_33);
	}
}