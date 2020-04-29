#pragma once

#include <math.h>

namespace Engine
{
	class Vector3
	{
		friend class Vector4;
		friend class Matrix3;
		friend class Matrix4;

	public:
#pragma region Constructors

		// standard constructor
		Vector3() :
			m_x(0), m_y(0), m_z(0)
		{
		}

		// standard constructor
		Vector3(float i_x, float i_y, float i_z) :
			m_x(i_x), m_y(i_y), m_z(i_z)
		{
		}

		// copy constructor
		Vector3(const Vector3 & i_rhs) :
			m_x(i_rhs.m_x), m_y(i_rhs.m_y), m_z(i_rhs.m_z)
		{
		}

#pragma endregion

#pragma region Getters and Setters
		// Getters for private variables
		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }
		inline float GetZ() const { return m_z; }

		// Setters for private variables
		inline void SetX(float i_x) { m_x = i_x; }
		inline void SetY(float i_y) { m_y = i_y; }
		inline void SetZ(float i_z) { m_z = i_z; }
#pragma endregion

#pragma region Incrementers and Decrementers
		void incrementXValue();
		void decrementXValue();
		void incrementYValue();
		void decrementYValue();
		void incrementZValue();
		void decrementZValue();
#pragma endregion

#pragma region Utility Positions
		// const Vector3 {0.0f, 0.0f, 0.0f}
		static const Vector3 Zero;
#pragma endregion

#pragma region Class Operator Overloads
		// assignment operator
		Vector3& operator=(const Vector3 & i_OtherVector);

#pragma region Arithmetic Operators
		// negate the x and y values of the current point
		Vector3 operator-() const;
		// multiply scalar to current point and return new value
		Vector3 operator*(float scalar) const;
		// divide current by scalar and return new value
		Vector3 operator/(float scalar) const;
		// prefix adition to current
		void operator++();
		// postfix adition to current
		void operator++(int);
		// prefix subtraction to current
		void operator--();
		// postfix subtraction to current
		void operator--(int);
#pragma endregion

#pragma region Compound Assignment Operators
		// add point value to current point
		Vector3& operator+=(const Vector3 & point);
		// subtract point value from current point
		Vector3& operator-=(const Vector3 & point);
		// multiply point value and current point
		Vector3& operator*=(const Vector3 & point);
		// multiply current value by a scalar
		Vector3& operator*=(float scalar);
		// divide current point by point
		Vector3& operator/=(const Vector3 & point);
		// divide current point by scalar
		Vector3& operator/=(float scalar);
#pragma endregion

#pragma region Vector3 Math

		// gets the magnitude of this vector
		double Magnitude() const;
		// returns the vector normalized
		Vector3 Normalized() const;
		// does the dot product between 2 vectors
		float Dot(const Vector3 & i_OtherVector) const;
		// does the cross product between 2 vectors
		Vector3 Cross(const Vector3 & i_OtherVector) const;

#pragma endregion

#pragma endregion

	private:
		float m_x, m_y, m_z;
	};
}

#include "Vector3-inl.h"
