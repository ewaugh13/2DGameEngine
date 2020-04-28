#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace Engine
{
	class Matrix4
	{

	public:

#pragma region Constructors and Operator Overloads

		Matrix4();

		Matrix4(float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44);

		Matrix4(const Matrix4 & i_Other);
		Matrix4 & operator=(const Matrix4 & i_Other);

		Matrix4 operator*(const Matrix4 & i_Other) const;
		Matrix4 operator*(const float i_Scalar) const;

#pragma endregion

#pragma region Transform Point

		Vector3 TransformPointRowVec(const Vector3 & i_Point) const;
		Vector3 TransformPointColVec(const Vector3 & i_Point) const;

		Vector3 TransformNormalRowVec(const Vector3 & i_Normal) const;
		Vector3 TransformNormalColVec(const Vector3 & i_Normal) const;

#pragma endregion

#pragma region Get Row and Col

		Vector4 GetRow(unsigned int i_Row) const;
		Vector4 GetCol(unsigned int i_Col) const;

#pragma endregion

#pragma region Matrix Creators

		static Matrix4 CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ);

#pragma endregion

#pragma region Rotation Row Vector

		// used for V = V * M

		static Matrix4 CreateXRotationRowVec(float i_RotationRadians);
		static Matrix4 CreateYRotationRowVec(float i_RotationRadians);
		static Matrix4 CreateZRotationRowVec(float i_RotationRadians);

		static Matrix4 CreateTranslationRowVec(float i_TransX, float i_TransY, float i_TransZ);
		static Matrix4 CreateTranslationRowVec(const Vector3 & i_Trans);

#pragma endregion

#pragma region Rotation Column Vector

		// used for V = M * V

		static Matrix4 CreateXRotationColVec(float i_RotationRadians);
		static Matrix4 CreateYRotationColVec(float i_RotationRadians);
		static Matrix4 CreateZRotationColVec(float i_RotationRadians);

		static Matrix4 CreateTranslationColVec(float i_TransX, float i_TransY, float i_TransZ);
		static Matrix4 CreateTranslationColVec(const Vector3 & i_Trans);

#pragma endregion

#pragma region Determinant, Inverse and Transpose

		// Get the determinant of this instance
		float Determinant() const;

		// Invert this instance
		void Invert();
		// Return a matrix that is the inverse of this instance but don't modify this instance
		Matrix4 GetInverse() const;

		// Return a matrix that is the inverse ASSUMING this matrix has axis rotation and translation only.
		Matrix4 GetInverseRotTransColVec() const;
		Matrix4 GetInverseRotTransRowVec() const;

		// Transpose this instance
		void Transpose();
		// return a matrix that is a transpose of this instance but don't modify this instance
		Matrix4 GetTranspose() const;

#pragma endregion

#pragma region Multiplication

		// Multiply Vector by Matrix (return v * M)
		Vector4 MultiplyLeft(const Vector4& i_Vector) const;
		// Multiply Vector by Matrix (return M * v)
		Vector4 MultiplyRight(const Vector4& i_Vector) const;

#pragma endregion

		static const Matrix4 IdentityMatrix;

	private:
		float
			// m_<row><colum>
			m_11, m_12, m_13, m_14,
			m_21, m_22, m_23, m_24,
			m_31, m_32, m_33, m_34,
			m_41, m_42, m_43, m_44;
	};

	// for external usage of multiplyig a matrix and a vector
	inline Vector4 operator*(const Matrix4 & i_Mat, const Vector4 & i_Vec);
	inline Vector4 operator*(const Vector4 & i_Vec, const Matrix4 & i_Mat);
}

#include "Matrix4-inl.h"

