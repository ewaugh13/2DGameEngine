#pragma once

namespace Engine
{
	inline Vector4 operator*(const Matrix4 & i_Mat, const Vector4 & i_Vec)
	{
		return i_Mat.MultiplyRight(i_Vec);
	}

	inline Vector4 operator*(const Vector4 & i_Vec, const Matrix4 & i_Mat)
	{
		return i_Mat.MultiplyLeft(i_Vec);
	}

#pragma region Transform Point

	inline Vector3 Matrix4::TransformPointRowVec(const Vector3 & i_Point) const
	{
		Vector4 point = MultiplyLeft(Vector4(i_Point, 1.0f));

		float invW = 1.0f / point.m_w;
		return Vector3(point.m_x * invW, point.m_y * invW, point.m_z * invW);
	}

	inline Vector3 Matrix4::TransformPointColVec(const Vector3 & i_Point) const
	{
		Vector4 point = MultiplyRight(Vector4(i_Point, 1.0f));

		float invW = 1.0f / point.m_w;
		return Vector3(point.m_x * invW, point.m_y * invW, point.m_z * invW);
	}

	inline Vector3 Matrix4::TransformNormalRowVec(const Vector3 & i_Normal) const
	{
		Vector4 point = MultiplyLeft(Vector4(i_Normal, 0.0f));
		return Vector3(point.m_x, point.m_y, point.m_z);
	}

	inline Vector3 Matrix4::TransformNormalColVec(const Vector3 & i_Normal) const
	{
		Vector4 point = MultiplyRight(Vector4(i_Normal, 0.0f));
		return Vector3(point.m_x, point.m_y, point.m_z);
	}

#pragma endregion

#pragma region Rotation Vector

	inline Matrix4 Matrix4::CreateTranslationRowVec(const Vector3 & i_Trans)
	{
		return CreateTranslationRowVec(i_Trans.m_x, i_Trans.m_y, i_Trans.m_z);
	}

	inline Matrix4 Matrix4::CreateTranslationColVec(const Vector3 & i_Trans)
	{
		return CreateTranslationColVec(i_Trans.m_x, i_Trans.m_y, i_Trans.m_z);
	}

#pragma endregion

#pragma region Inverse and Transpose

	inline Matrix4 Matrix4::GetInverse() const
	{
		Matrix4 invertedCopy = Matrix4(*this);
		invertedCopy.Invert();
		return invertedCopy;
	}

	inline Matrix4 Matrix4::GetTranspose() const
	{
		return Matrix4(
			m_11, m_21, m_31, m_41,
			m_12, m_22, m_32, m_42,
			m_13, m_23, m_33, m_43,
			m_14, m_24, m_34, m_44);
	}

#pragma endregion

}