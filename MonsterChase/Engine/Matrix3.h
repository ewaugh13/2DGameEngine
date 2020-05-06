#pragma once

#include "Vector3.h"
#include "Matrix4.h"

namespace Engine
{
	class Matrix3
	{

	public:

#pragma region Constructors and Operator Overloads

		Matrix3();

		Matrix3(float i_11, float i_12, float i_13,
				float i_21, float i_22, float i_23,
				float i_31, float i_32, float i_33);

		Matrix3(const Matrix3 & i_Other);
		Matrix3 & operator=(const Matrix3 & i_Other);

		bool operator==(const Matrix3 & i_Other) const;

		Matrix3 operator*(const Matrix3 & i_Other) const;
		Matrix3 operator*(const float i_Scalar) const;

#pragma endregion
		
#pragma region Get Row and Col

		Vector3 GetRow(unsigned int i_Row) const;
		Vector3 GetCol(unsigned int i_Col) const;

#pragma endregion

		Matrix4 ToTransform() const;

#pragma region Matrix Creators

		static Matrix3 CreateScale(float i_ScaleX, float i_ScaleY, float i_ScaleZ);

#pragma endregion

#pragma region Rotation Row Vector

		// used for V = V * M

		static Matrix3 CreateXRotationRowVec(float i_RotationRadians);
		static Matrix3 CreateYRotationRowVec(float i_RotationRadians);
		static Matrix3 CreateZRotationRowVec(float i_RotationRadians);

		static Matrix3 CreateXRotationRowVecFromDegrees(float i_RotationDegrees);
		static Matrix3 CreateYRotationRowVecFromDegrees(float i_RotationDegrees);
		static Matrix3 CreateZRotationRowVecFromDegrees(float i_RotationDegrees);

#pragma endregion

#pragma region Rotation Column Vector

		// used for V = M * V

		static Matrix3 CreateXRotationColVec(float i_RotationRadians);
		static Matrix3 CreateYRotationColVec(float i_RotationRadians);
		static Matrix3 CreateZRotationColVec(float i_RotationRadians);

		static Matrix3 CreateXRotationColVecFromDegrees(float i_RotationDegrees);
		static Matrix3 CreateYRotationColVecFromDegrees(float i_RotationDegrees);
		static Matrix3 CreateZRotationColVecFromDegrees(float i_RotationDegrees);

#pragma endregion

#pragma region Transpose

		// Transpose this instance
		void Transpose();
		// return a matrix that is a transpose of this instance but don't modify this instance
		Matrix3 GetTranspose() const;

#pragma endregion

#pragma region Multiplication

		// Multiply Vector by Matrix (return v * M)
		Vector3 MultiplyLeft(const Vector3 & i_Vector) const;
		// Multiply Vector by Matrix (return M * v)
		Vector3 MultiplyRight(const Vector3 & i_Vector) const;

#pragma endregion

		static const Matrix3 IdentityMatrix;

	private:
		float
			// m_<row><colum>
			m_11, m_12, m_13,
			m_21, m_22, m_23,
			m_31, m_32, m_33;
	};

	// for external usage of multiplyig a matrix and a vector
	inline Vector3 operator*(const Matrix3 & i_Mat, const Vector3 & i_Vec);
	inline Vector3 operator*(const Vector3 & i_Vec, const Matrix3 & i_Mat);
}

#include "Matrix3-inl.h"