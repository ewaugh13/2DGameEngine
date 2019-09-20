#include "Point2D.h"
#include <math.h>


Point2D::Point2D(int i_x, int i_y)
{
	this->m_x = i_x;
	this->m_y = i_y;
}


Point2D::~Point2D()
{
}

void Point2D::incrementXValue()
{
	this->m_x++;
}

void Point2D::decrementXValue()
{
	this->m_x--;
}

void Point2D::incrementYValue()
{
	this->m_y++;
}

void Point2D::decrementYValue()
{
	this->m_y--;
}

// class operator overloads

Point2D Point2D::operator-()
{
	Point2D newPoint = Point2D(-this->m_x, -this->m_y);
	return newPoint;
}

Point2D Point2D::operator*(int scalar)
{
	Point2D newPoint = Point2D(this->m_x * scalar, this->m_y * scalar);
	return newPoint;
}

Point2D Point2D::operator/(int scalar)
{
	Point2D newPoint = Point2D(this->m_x / scalar, this->m_y / scalar);
	return newPoint;
}

void Point2D::operator++()
{
	++this->m_x, ++this->m_y;
}

void Point2D::operator++(int)
{
	this->m_x++, this->m_y++;
}

void Point2D::operator--()
{
	--this->m_x, --this->m_y;
}

void Point2D::operator--(int)
{
	this->m_x--, this->m_y--;
}

Point2D& Point2D::operator+=(const Point2D &point)
{
	this->m_x += point.m_x;
	this->m_y += point.m_y;
	return *this;
}

Point2D& Point2D::operator-=(const Point2D &point)
{
	this->m_x -= point.m_x;
	this->m_y -= point.m_y;
	return *this;
}

Point2D& Point2D::operator*=(const Point2D &point)
{
	this->m_x *= point.m_x;
	this->m_y *= point.m_y;
	return *this;
}

Point2D& Point2D::operator*=(int scalar)
{
	this->m_x *= scalar;
	this->m_y *= scalar;
	return *this;
}

Point2D& Point2D::operator/=(const Point2D &point)
{
	this->m_x /= point.m_x;
	this->m_y /= point.m_y;
	return *this;
}

Point2D& Point2D::operator/=(int scalar)
{
	this->m_x /= scalar;
	this->m_y /= scalar;
	return *this;
}


// non class operator overloads

Point2D operator+(Point2D &leftPoint, Point2D &rightPoint)
{
	return Point2D(leftPoint.X() + rightPoint.X(), leftPoint.Y() + rightPoint.Y());
}

Point2D operator-(Point2D &leftPoint, Point2D &rightPoint)
{
	return Point2D(leftPoint.X() - rightPoint.X(), leftPoint.Y() - rightPoint.Y());
}

Point2D operator*(Point2D &leftPoint, Point2D &rightPoint)
{
	return Point2D(leftPoint.X() * rightPoint.X(), leftPoint.Y() * rightPoint.Y());
}

Point2D operator/(Point2D &leftPoint, Point2D &rightPoint)
{
	return Point2D(leftPoint.X() / rightPoint.X(), leftPoint.Y() / rightPoint.Y());
}

bool operator==(Point2D &leftPoint, Point2D &rightPoint)
{
	return leftPoint.X() == rightPoint.X() && leftPoint.Y() == rightPoint.Y();
}

bool operator!=(Point2D &leftPoint, Point2D &rightPoint)
{
	return leftPoint.X() != rightPoint.X() || leftPoint.Y() != rightPoint.Y();
}

bool operator>(Point2D &leftPoint, Point2D &rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize > pointSize;
}

bool operator<(Point2D &leftPoint, Point2D &rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize < pointSize;
}

bool operator>=(Point2D &leftPoint, Point2D &rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize >= pointSize;
}

bool operator<=(Point2D &leftPoint, Point2D &rightPoint)
{
	double currentSize = sqrt(pow(leftPoint.X(), 2) + pow(leftPoint.Y(), 2));
	double pointSize = sqrt(pow(rightPoint.X(), 2) + pow(rightPoint.Y(), 2));
	return currentSize <= pointSize;
}