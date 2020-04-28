#pragma once

#include "Vector3.h"

#include <math.h>

namespace Engine
{
	class Vector4
	{
		friend class Vector3;
		friend class Matrix4;

	public:
#pragma region Constructor and Destructor

		// standard constructor
		Vector4() :
			m_x(0), m_y(0), m_z(0), m_w(0)
		{
		}

		// standard constructor
		Vector4(float i_x, float i_y, float i_z, float i_w) :
			m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
		{
		}

		Vector4(const Vector3 & i_Other, float i_W) :
			m_x(i_Other.m_x), m_y(i_Other.m_y), m_z(i_Other.m_z), m_w(i_W)
		{
		}

		// copy constructor
		Vector4(const Vector4 & i_Other) :
			m_x(i_Other.m_x), m_y(i_Other.m_y), m_z(i_Other.m_z), m_w(i_Other.m_w)
		{
		}

#pragma endregion

#pragma region Getters and Setters
		// Getters for private variables
		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }
		inline float GetZ() const { return m_z; }
		inline float GetW() const { return m_w; }

		// Setters for private variables
		inline void SetX(float i_x) { m_x = i_x; }
		inline void SetY(float i_y) { m_y = i_y; }
		inline void SetZ(float i_z) { m_z = i_z; }
		inline void SetW(float i_w) { m_w = i_w; }
#pragma endregion

#pragma region Incrementers and Decrementers
		void incrementXValue();
		void decrementXValue();
		void incrementYValue();
		void decrementYValue();
		void incrementZValue();
		void decrementZValue();
		void incrementWValue();
		void decrementWValue();
#pragma endregion

#pragma region Utility Positions

		// const Vector4 {0.0f, 0.0f, 0.0f, 0.0f}
		static const Vector4 Zero;

#pragma endregion

#pragma region Class Operator Overloads
		// assignment operator
		Vector4& operator=(const Vector4 & i_OtherVector);

#pragma region Arithmetic Operators
		// negate the x and y values of the current point
		Vector4 operator-() const;
		// multiply scalar to current point and return new value
		Vector4 operator*(float scalar) const;
		// divide current by scalar and return new value
		Vector4 operator/(float scalar) const;
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
		Vector4& operator+=(const Vector4 & point);
		// subtract point value from current point
		Vector4& operator-=(const Vector4 & point);
		// multiply point value and current point
		Vector4& operator*=(const Vector4 & point);
		// multiply current value by a scalar
		Vector4& operator*=(float scalar);
		// divide current point by point
		Vector4& operator/=(const Vector4 & point);
		// divide current point by scalar
		Vector4& operator/=(float scalar);
#pragma endregion

#pragma region Vector4 Math

		// gets the magnitude of this vector
		double Magnitude() const;
		// returns the vector normalized
		Vector4 Normalized() const;
		// does the dot product between 2 vectors
		float Dot(const Vector4 & i_OtherVector) const;

#pragma endregion

#pragma endregion

	private:
		float m_x, m_y, m_z, m_w;
	};
}

#include "Vector4-inl.h"
