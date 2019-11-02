#include "Point2D.h"
#pragma once

#pragma region Constructor and Destructor
inline Point2D::Point2D(const Point2D & i_rhs)
{
	this->m_x = i_rhs.m_x;
	this->m_y = i_rhs.m_y;
}

inline Point2D::~Point2D()
{
}
#pragma endregion

#pragma region Incrementers and Decrementers
inline void Point2D::incrementXValue()
{
	this->m_x++;
}

inline void Point2D::decrementXValue()
{
	this->m_x--;
}

inline void Point2D::incrementYValue()
{
	this->m_y++;
}

inline void Point2D::decrementYValue()
{
	this->m_y--;
}
#pragma endregion

#pragma region Class Operator Overloads
inline Point2D& Point2D::operator=(const Point2D & i_rhs)
{
	this->m_x = i_rhs.m_x;
	this->m_y = i_rhs.m_y;
	return *this;
}

#pragma region Arithmetic Operators
inline Point2D& Point2D::operator-() const
{
	Point2D newPoint = Point2D(-this->m_x, -this->m_y);
	return newPoint;
}

inline Point2D& Point2D::operator*(float scalar) const
{
	Point2D newPoint = Point2D(this->m_x * scalar, this->m_y * scalar);
	return newPoint;
}

inline Point2D& Point2D::operator/(float scalar) const
{
	Point2D newPoint = Point2D(this->m_x / scalar, this->m_y / scalar);
	return newPoint;
}

inline void Point2D::operator++()
{
	++this->m_x, ++this->m_y;
}

inline void Point2D::operator++(int)
{
	this->m_x++, this->m_y++;
}

inline void Point2D::operator--()
{
	--this->m_x, --this->m_y;
}

inline void Point2D::operator--(int)
{
	this->m_x--, this->m_y--;
}
#pragma endregion

#pragma region Compound Assignment Operators
inline Point2D& Point2D::operator+=(const Point2D & point)
{
	this->m_x += point.m_x;
	this->m_y += point.m_y;
	return *this;
}

inline Point2D& Point2D::operator-=(const Point2D & point)
{
	this->m_x -= point.m_x;
	this->m_y -= point.m_y;
	return *this;
}

inline Point2D& Point2D::operator*=(const Point2D & point)
{
	this->m_x *= point.m_x;
	this->m_y *= point.m_y;
	return *this;
}

inline Point2D& Point2D::operator*=(float scalar)
{
	this->m_x *= scalar;
	this->m_y *= scalar;
	return *this;
}

inline Point2D& Point2D::operator/=(const Point2D & point)
{
	this->m_x /= point.m_x;
	this->m_y /= point.m_y;
	return *this;
}

inline Point2D& Point2D::operator/=(float scalar)
{
	this->m_x /= scalar;
	this->m_y /= scalar;
	return *this;
}
#pragma endregion

#pragma endregion

#pragma region Non Class Methods

#pragma region Point2D Math
inline float dot(const Point2D & i_lhs, const Point2D & i_rhs)
{
	return i_lhs.X() * i_rhs.X() + i_lhs.Y() * i_rhs.Y();
}

inline float cross(const Point2D & i_lhs, const Point2D & i_rhs)
{
	return i_lhs.X() * i_rhs.Y() - i_lhs.Y() * i_rhs.X();
}
#pragma endregion

#pragma region Non-Class Operator Overloads

#pragma region Arithmetic Operators
inline Point2D operator+(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return Point2D(leftPoint.X() + rightPoint.X(), leftPoint.Y() + rightPoint.Y());
}

inline Point2D operator-(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return Point2D(leftPoint.X() - rightPoint.X(), leftPoint.Y() - rightPoint.Y());
}

inline Point2D operator*(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return Point2D(leftPoint.X() * rightPoint.X(), leftPoint.Y() * rightPoint.Y());
}

inline Point2D operator/(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return Point2D(leftPoint.X() / rightPoint.X(), leftPoint.Y() / rightPoint.Y());
}
#pragma endregion

#pragma region Comparision Operators
inline bool operator==(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return leftPoint.X() == rightPoint.X() && leftPoint.Y() == rightPoint.Y();
}

inline bool operator!=(const Point2D & leftPoint, const Point2D & rightPoint)
{
	return leftPoint.X() != rightPoint.X() || leftPoint.Y() != rightPoint.Y();
}

inline bool operator>(const Point2D & leftPoint, const Point2D & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize > pointSize;
}

inline bool operator<(const Point2D & leftPoint, const Point2D & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize < pointSize;
}

inline bool operator>=(const Point2D & leftPoint, const Point2D & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize >= pointSize;
}

inline bool operator<=(const Point2D & leftPoint, const Point2D & rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize <= pointSize;
}
#pragma endregion

#pragma endregion

#pragma endregion