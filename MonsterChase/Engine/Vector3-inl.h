#include "Vector3.h"
#pragma once

#pragma region Incrementers and Decrementers
inline void Vector3::incrementXValue()
{
	this->m_x++;
}

inline void Vector3::decrementXValue()
{
	this->m_x--;
}

inline void Vector3::incrementYValue()
{
	this->m_y++;
}

inline void Vector3::decrementYValue()
{
	this->m_y--;
}
inline void Vector3::incrementZValue()
{
	this->m_z++;
}
inline void Vector3::decrementZValue()
{
	this->m_z--;
}
#pragma endregion

#pragma region Class Operator Overloads
inline Vector3& Vector3::operator=(const Vector3 & i_OtherVector)
{
	this->m_x = i_OtherVector.m_x;
	this->m_y = i_OtherVector.m_y;
	this->m_z = i_OtherVector.m_z;
	return *this;
}

#pragma region Arithmetic Operators
inline Vector3 Vector3::operator-() const
{
	Vector3 newPoint = Vector3(-this->m_x, -this->m_y, -this->m_z);
	return newPoint;
}

inline Vector3 Vector3::operator*(float scalar) const
{
	Vector3 newPoint = Vector3(this->m_x * scalar, this->m_y * scalar, this->m_z * scalar);
	return newPoint;
}

inline Vector3 Vector3::operator/(float scalar) const
{
	Vector3 newPoint = Vector3(this->m_x / scalar, this->m_y / scalar, this->m_z / scalar);
	return newPoint;
}

inline void Vector3::operator++()
{
	++this->m_x, ++this->m_y, ++this->m_z;
}

inline void Vector3::operator++(int)
{
	this->m_x++, this->m_y++, this->m_z++;
}

inline void Vector3::operator--()
{
	--this->m_x, --this->m_y, --this->m_z;;
}

inline void Vector3::operator--(int)
{
	this->m_x--, this->m_y--, this->m_z--;
}
#pragma endregion

#pragma region Compound Assignment Operators
inline Vector3& Vector3::operator+=(const Vector3 & point)
{
	this->m_x += point.m_x;
	this->m_y += point.m_y;
	this->m_z += point.m_z;
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3 & point)
{
	this->m_x -= point.m_x;
	this->m_y -= point.m_y;
	this->m_z -= point.m_z;
	return *this;
}

inline Vector3& Vector3::operator*=(const Vector3 & point)
{
	this->m_x *= point.m_x;
	this->m_y *= point.m_y;
	this->m_z *= point.m_z;
	return *this;
}

inline Vector3& Vector3::operator*=(float scalar)
{
	this->m_x *= scalar;
	this->m_y *= scalar;
	this->m_z *= scalar;
	return *this;
}

inline Vector3& Vector3::operator/=(const Vector3 & point)
{
	this->m_x /= point.m_x;
	this->m_y /= point.m_y;
	this->m_z /= point.m_z;
	return *this;
}

inline Vector3& Vector3::operator/=(float scalar)
{
	this->m_x /= scalar;
	this->m_y /= scalar;
	this->m_z /= scalar;
	return *this;
}
#pragma endregion

#pragma endregion

#pragma region Non Class Methods

#pragma region Vector3 Math
inline float dot(const Vector3 & i_lhs, const Vector3 & i_rhs)
{
	return i_lhs.GetX() * i_rhs.GetX() + i_lhs.GetY() * i_rhs.GetY() + i_lhs.GetZ() * i_rhs.GetZ();
}

inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs)
{
	return Vector3(i_lhs.GetY() * i_rhs.GetZ() - i_lhs.GetZ() * i_rhs.GetY(),
		i_lhs.GetZ() * i_rhs.GetX() - i_lhs.GetX() * i_rhs.GetZ(),
		i_lhs.GetX() * i_rhs.GetY() - i_lhs.GetY() * i_rhs.GetX());

}
#pragma endregion

#pragma region Non-Class Operator Overloads

#pragma region Arithmetic Operators
inline Vector3 operator+(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return Vector3(leftPoint.GetX() + rightPoint.GetX(), leftPoint.GetY() + rightPoint.GetY(), leftPoint.GetZ() + rightPoint.GetZ());
}

inline Vector3 operator-(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return Vector3(leftPoint.GetX() - rightPoint.GetX(), leftPoint.GetY() - rightPoint.GetY(), leftPoint.GetZ() - rightPoint.GetZ());
}

inline Vector3 operator*(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return Vector3(leftPoint.GetX() * rightPoint.GetX(), leftPoint.GetY() * rightPoint.GetY(), leftPoint.GetZ() * rightPoint.GetZ());
}

inline Vector3 operator/(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return Vector3(leftPoint.GetX() / rightPoint.GetX(), leftPoint.GetY() / rightPoint.GetY(), leftPoint.GetZ() / rightPoint.GetZ());
}
#pragma endregion

#pragma region Comparision Operators
inline bool operator==(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return leftPoint.GetX() == rightPoint.GetX() && leftPoint.GetY() == rightPoint.GetY() && leftPoint.GetZ() == rightPoint.GetZ();
}

inline bool operator!=(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	return leftPoint.GetX() != rightPoint.GetX() || leftPoint.GetY() != rightPoint.GetY() || leftPoint.GetZ() != rightPoint.GetZ();
}

inline bool operator>(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.GetX(), 2) + pow(leftPoint.GetY(), 2) + pow(leftPoint.GetZ(), 2));
	double pointSize = sqrt(pow(rightPoint.GetX(), 2) + pow(rightPoint.GetY(), 2) + pow(rightPoint.GetZ(), 2));
	return currentSize > pointSize;
}

inline bool operator<(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.GetX(), 2) + pow(leftPoint.GetY(), 2) + pow(leftPoint.GetZ(), 2));
	double pointSize = sqrt(pow(rightPoint.GetX(), 2) + pow(rightPoint.GetY(), 2) + pow(rightPoint.GetZ(), 2));
	return currentSize < pointSize;
}

inline bool operator>=(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.GetX(), 2) + pow(leftPoint.GetY(), 2) + pow(leftPoint.GetZ(), 2));
	double pointSize = sqrt(pow(rightPoint.GetX(), 2) + pow(rightPoint.GetY(), 2) + pow(rightPoint.GetZ(), 2));
	return currentSize >= pointSize;
}

inline bool operator<=(const Vector3 & leftPoint, const Vector3 & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.GetX(), 2) + pow(leftPoint.GetY(), 2) + pow(leftPoint.GetZ(), 2));
	double pointSize = sqrt(pow(rightPoint.GetX(), 2) + pow(rightPoint.GetY(), 2) + pow(rightPoint.GetZ(), 2));
	return currentSize <= pointSize;
}
#pragma endregion

#pragma endregion

#pragma endregion