#include "FloatFunctionLibrary.h"

#pragma once

namespace Engine 
{

#pragma region Incrementers and Decrementers

	inline void Vector4::incrementXValue()
	{
		m_x++;
	}
	inline void Vector4::decrementXValue()
	{
		m_x--;
	}

	inline void Vector4::incrementYValue()
	{
		m_y++;
	}
	inline void Vector4::decrementYValue()
	{
		m_y--;
	}

	inline void Vector4::incrementZValue()
	{
		m_z++;
	}
	inline void Vector4::decrementZValue()
	{
		m_z--;
	}

	inline void Vector4::incrementWValue()
	{
		m_w++;
	}
	inline void Vector4::decrementWValue()
	{
		m_w--;
	}

#pragma endregion

#pragma region Class Operator Overloads

	inline Vector4& Vector4::operator=(const Vector4 & i_OtherVector)
	{
		m_x = i_OtherVector.m_x;
		m_y = i_OtherVector.m_y;
		m_z = i_OtherVector.m_z;
		m_w = i_OtherVector.m_w;
		return *this;
	}

#pragma region Arithmetic Operators

	inline Vector4 Vector4::operator-() const
	{
		return Vector4(-m_x, -m_y, -m_z, -m_w);
	}

	inline Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar);
	}

	inline Vector4 Vector4::operator/(float scalar) const
	{
		return Vector4(m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar);
	}

	inline void Vector4::operator++()
	{
		++m_x, ++m_y, ++m_z, ++m_w;
	}

	inline void Vector4::operator++(int)
	{
		m_x++, m_y++, m_z++, m_w++;
	}

	inline void Vector4::operator--()
	{
		--m_x, --m_y, --m_z, --m_w;
	}

	inline void Vector4::operator--(int)
	{
		m_x--, m_y--, m_z--, m_w--;
	}

#pragma endregion

#pragma region Compound Assignment Operators

	inline Vector4 & Vector4::operator+=(const Vector4 & vector)
	{
		m_x += vector.m_x;
		m_y += vector.m_y;
		m_z += vector.m_z;
		m_w += vector.m_w;
		return *this;
	}

	inline Vector4 & Vector4::operator-=(const Vector4 & vector)
	{
		m_x -= vector.m_x;
		m_y -= vector.m_y;
		m_z -= vector.m_z;
		m_w -= vector.m_w;
		return *this;
	}

	inline Vector4 & Vector4::operator*=(const Vector4 & vector)
	{
		m_x *= vector.m_x;
		m_y *= vector.m_y;
		m_z *= vector.m_z;
		m_w *= vector.m_w;
		return *this;
	}

	inline Vector4 & Vector4::operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		m_w *= scalar;
		return *this;
	}

	inline Vector4 & Vector4::operator/=(const Vector4 & vector)
	{
		m_x /= vector.m_x;
		m_y /= vector.m_y;
		m_z /= vector.m_z;
		m_w /= vector.m_w;
		return *this;
	}

	inline Vector4 & Vector4::operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		m_w /= scalar;
		return *this;
	}

#pragma endregion

#pragma endregion

#pragma region Non Class Methods

#pragma region Vector4 Math

	inline double Vector4::Magnitude() const
	{
		return sqrt(pow(GetX(), 2) + pow(GetY(), 2)) + pow(GetZ(), 2) + pow(GetW(), 2);
	}

	inline Vector4 Vector4::Normalized() const
	{
		float length = static_cast<float>(Magnitude());
		if (FloatFunctionLibrary::AlmostEqualZeroCertain(length))
			return Zero;

		float invLength = 1.0f / length;
		return *this * invLength;
	}

	inline float Vector4::Dot(const Vector4 & i_OtherVector) const
	{
		return GetX() * i_OtherVector.GetX() + GetY() * i_OtherVector.GetY() + GetZ() * i_OtherVector.GetZ() + GetW() * i_OtherVector.GetW();
	}

#pragma endregion

#pragma region Non-Class Operator Overloads

#pragma region Arithmetic Operators

	inline Vector4 operator+(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return Vector4(leftvector.GetX() + rightvector.GetX(), leftvector.GetY() + rightvector.GetY(),
			leftvector.GetZ() + rightvector.GetZ(), leftvector.GetW() + rightvector.GetW());
	}

	inline Vector4 operator-(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return Vector4(leftvector.GetX() - rightvector.GetX(), leftvector.GetY() - rightvector.GetY(),
			leftvector.GetZ() - rightvector.GetZ(), leftvector.GetW() - rightvector.GetW());
	}

	inline Vector4 operator*(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return Vector4(leftvector.GetX() * rightvector.GetX(), leftvector.GetY() * rightvector.GetY(),
			leftvector.GetZ() * rightvector.GetZ(), leftvector.GetW() * rightvector.GetW());
	}

	inline Vector4 operator/(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return Vector4(leftvector.GetX() / rightvector.GetX(), leftvector.GetY() / rightvector.GetY(),
			leftvector.GetZ() / rightvector.GetZ(), leftvector.GetW() / rightvector.GetW());
	}

#pragma endregion

#pragma region Comparision Operators

	inline bool operator==(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return leftvector.GetX() == rightvector.GetX() && leftvector.GetY() == rightvector.GetY()
			&& leftvector.GetZ() == rightvector.GetZ() && leftvector.GetW() == rightvector.GetW();
	}

	inline bool operator!=(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		return leftvector.GetX() != rightvector.GetX() || leftvector.GetY() != rightvector.GetY()
			|| leftvector.GetZ() != rightvector.GetZ() || leftvector.GetW() != rightvector.GetW();
	}

	inline bool operator>(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize > vectorSize;
	}

	inline bool operator<(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize < vectorSize;
	}

	inline bool operator>=(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize >= vectorSize;
	}

	inline bool operator<=(const Vector4 & leftvector, const Vector4 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize <= vectorSize;
	}

#pragma endregion

#pragma endregion

#pragma endregion

}