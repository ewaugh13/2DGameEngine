#include "Point2D.h"
#include <math.h>


Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
}


Point2D::~Point2D()
{
}


int Point2D::xValue()
{
	return this->x;
}

int Point2D::yValue()
{
	return this->y;
}

void Point2D::setXValue(int x)
{
	this->x = x;
}

void Point2D::setYValue(int y)
{
	this->y = y;
}

void Point2D::incrementXValue()
{
	this->x++;
}

void Point2D::decrementXValue()
{
	this->x--;
}

void Point2D::incrementYValue()
{
	this->y++;
}

void Point2D::decrementYValue()
{
	this->y--;
}


Point2D Point2D::operator+(const Point2D &point)
{
	Point2D newPoint = Point2D(0, 0);
	newPoint.x = this->x + point.x;
	newPoint.y = this->y + point.y;
	return newPoint;
}

Point2D Point2D::operator-(const Point2D &point)
{
	Point2D newPoint = Point2D(0, 0);
	newPoint.x = this->x - point.x;
	newPoint.y = this->y - point.y;
	return newPoint;
}

Point2D Point2D::operator-()
{
	Point2D newPoint = Point2D(-this->x, -this->y);
	return newPoint;
}

Point2D Point2D::operator*(const Point2D &point)
{
	Point2D newPoint = Point2D(0, 0);
	newPoint.x = this->x * point.x;
	newPoint.y = this->y * point.y;
	return newPoint;
}

Point2D Point2D::operator*(int scalar)
{
	Point2D newPoint = Point2D(this->x * scalar, this->y * scalar);
	return newPoint;
}

Point2D Point2D::operator/(const Point2D &point)
{
	Point2D newPoint = Point2D(0, 0);
	newPoint.x = this->x / point.x;
	newPoint.y = this->y / point.y;
	return newPoint;
}

Point2D Point2D::operator/(int scalar)
{
	Point2D newPoint = Point2D(this->x / scalar, this->y / scalar);
	return newPoint;
}

void Point2D::operator++()
{
	++this->x, ++this->y;
}

void Point2D::operator++(int)
{
	this->x++, this->y++;
}

void Point2D::operator--()
{
	--this->x, --this->y;
}

void Point2D::operator--(int)
{
	this->x--, this->y--;
}

bool Point2D::operator==(const Point2D & point)
{
	return this->x == point.x && this->y == point.y;
}

bool Point2D::operator!=(const Point2D & point)
{
	return this->x != point.x || this->y != point.y;
}

bool Point2D::operator>(const Point2D & point)
{
	double currentSize = sqrt(pow(this->x, 2) + pow(this->y, 2));
	double pointSize = sqrt(pow(point.x, 2) + pow(point.y, 2));
	return currentSize > pointSize;
}

bool Point2D::operator<(const Point2D & point)
{
	double currentSize = sqrt(pow(this->x, 2) + pow(this->y, 2));
	double pointSize = sqrt(pow(point.x, 2) + pow(point.y, 2));
	return currentSize < pointSize;
}

bool Point2D::operator>=(const Point2D & point)
{
	double currentSize = sqrt(pow(this->x, 2) + pow(this->y, 2));
	double pointSize = sqrt(pow(point.x, 2) + pow(point.y, 2));
	return currentSize >= pointSize;
}

bool Point2D::operator<=(const Point2D & point)
{
	double currentSize = sqrt(pow(this->x, 2) + pow(this->y, 2));
	double pointSize = sqrt(pow(point.x, 2) + pow(point.y, 2));
	return currentSize <= pointSize;
}

Point2D& Point2D::operator+=(const Point2D &point)
{
	this->x += point.x;
	this->y += point.y;
	return *this;
}

Point2D & Point2D::operator-=(const Point2D & point)
{
	this->x -= point.x;
	this->y -= point.y;
	return *this;
}

Point2D & Point2D::operator*=(const Point2D & point)
{
	this->x *= point.x;
	this->y *= point.y;
	return *this;
}

Point2D & Point2D::operator*=(int scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Point2D & Point2D::operator/=(const Point2D & point)
{
	this->x /= point.x;
	this->y /= point.y;
	return *this;
}

Point2D & Point2D::operator/=(int scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}
