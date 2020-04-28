#include "Vector3.h"
#pragma once

namespace Engine
{

#pragma region Incrementers and Decrementers

	inline void Vector3::incrementXValue()
	{
		m_x++;
	}
	inline void Vector3::decrementXValue()
	{
		m_x--;
	}

	inline void Vector3::incrementYValue()
	{
		m_y++;
	}
	inline void Vector3::decrementYValue()
	{
		m_y--;
	}

	inline void Vector3::incrementZValue()
	{
		m_z++;
	}
	inline void Vector3::decrementZValue()
	{
		m_z--;
	}

#pragma endregion

#pragma region Class Operator Overloads

	inline Vector3& Vector3::operator=(const Vector3 & i_OtherVector)
	{
		m_x = i_OtherVector.m_x;
		m_y = i_OtherVector.m_y;
		m_z = i_OtherVector.m_z;
		return *this;
	}

#pragma region Arithmetic Operators

	inline Vector3 Vector3::operator-() const
	{
		Vector3 newvector = Vector3(-m_x, -m_y, -m_z);
		return newvector;
	}

	inline Vector3 Vector3::operator*(float scalar) const
	{
		Vector3 newvector = Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
		return newvector;
	}

	inline Vector3 Vector3::operator/(float scalar) const
	{
		Vector3 newvector = Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
		return newvector;
	}

	inline void Vector3::operator++()
	{
		++m_x, ++m_y, ++m_z;
	}

	inline void Vector3::operator++(int)
	{
		m_x++, m_y++, m_z++;
	}

	inline void Vector3::operator--()
	{
		--m_x, --m_y, --m_z;
	}

	inline void Vector3::operator--(int)
	{
		m_x--, m_y--, m_z--;
	}

#pragma endregion

#pragma region Compound Assignment Operators

	inline Vector3& Vector3::operator+=(const Vector3 & vector)
	{
		m_x += vector.m_x;
		m_y += vector.m_y;
		m_z += vector.m_z;
		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3 & vector)
	{
		m_x -= vector.m_x;
		m_y -= vector.m_y;
		m_z -= vector.m_z;
		return *this;
	}

	inline Vector3& Vector3::operator*=(const Vector3 & vector)
	{
		m_x *= vector.m_x;
		m_y *= vector.m_y;
		m_z *= vector.m_z;
		return *this;
	}

	inline Vector3& Vector3::operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	inline Vector3& Vector3::operator/=(const Vector3 & vector)
	{
		m_x /= vector.m_x;
		m_y /= vector.m_y;
		m_z /= vector.m_z;
		return *this;
	}

	inline Vector3& Vector3::operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		return *this;
	}

#pragma endregion

#pragma endregion

#pragma region Non Class Methods

#pragma region Vector3 Math

	inline double Vector3::Magnitude() const
	{
		return sqrt(pow(GetX(), 2) + pow(GetY(), 2)) + pow(GetZ(), 2);
	}

	inline Vector3 Vector3::Normalized() const
	{
		float length = static_cast<float>(Magnitude());
		if (FloatFunctionLibrary::AlmostEqualZeroCertain(length))
			return Zero;

		float invLength = 1.0f / length;
		return *this * invLength;
	}

	inline float Vector3::Dot(const Vector3 & i_OtherVector) const
	{
		return GetX() * i_OtherVector.GetX() + GetY() * i_OtherVector.GetY() + GetZ() * i_OtherVector.GetZ();
	}

	inline Vector3 Vector3::Cross(const Vector3 & i_OtherVector) const
	{
		return Vector3(GetY() * i_OtherVector.GetZ() - GetZ() * i_OtherVector.GetY(),
			GetZ() * i_OtherVector.GetX() - GetX() * i_OtherVector.GetZ(),
			GetX() * i_OtherVector.GetY() - GetY() * i_OtherVector.GetX());
	}

#pragma endregion

#pragma region Non-Class Operator Overloads

#pragma region Arithmetic Operators

	inline Vector3 operator+(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return Vector3(leftvector.GetX() + rightvector.GetX(), leftvector.GetY() + rightvector.GetY(), leftvector.GetZ() + rightvector.GetZ());
	}

	inline Vector3 operator-(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return Vector3(leftvector.GetX() - rightvector.GetX(), leftvector.GetY() - rightvector.GetY(), leftvector.GetZ() - rightvector.GetZ());
	}

	inline Vector3 operator*(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return Vector3(leftvector.GetX() * rightvector.GetX(), leftvector.GetY() * rightvector.GetY(), leftvector.GetZ() * rightvector.GetZ());
	}

	inline Vector3 operator/(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return Vector3(leftvector.GetX() / rightvector.GetX(), leftvector.GetY() / rightvector.GetY(), leftvector.GetZ() / rightvector.GetZ());
	}

#pragma endregion

#pragma region Comparision Operators

	inline bool operator==(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return leftvector.GetX() == rightvector.GetX() && leftvector.GetY() == rightvector.GetY() && leftvector.GetZ() == rightvector.GetZ();
	}

	inline bool operator!=(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		return leftvector.GetX() != rightvector.GetX() || leftvector.GetY() != rightvector.GetY() || leftvector.GetZ() != rightvector.GetZ();
	}

	inline bool operator>(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize > vectorSize;
	}

	inline bool operator<(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize < vectorSize;
	}

	inline bool operator>=(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize >= vectorSize;
	}

	inline bool operator<=(const Vector3 & leftvector, const Vector3 & rightvector)
	{
		double currentSize = leftvector.Magnitude();
		double vectorSize = rightvector.Magnitude();
		return currentSize <= vectorSize;
	}

#pragma endregion

#pragma endregion

#pragma endregion

}