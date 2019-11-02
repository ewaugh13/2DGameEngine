#pragma once

#include <math.h>

class Point2D
{
public:
	Point2D(float x, float y);
	~Point2D();

	// Getters for private variables
	float X() const { return m_x; }
	float Y() const { return m_y; }

	// Setters for private variables
	void X(float i_x) { m_x = i_x; }
	void Y(float i_y) { m_y = i_y; }

	// incrementers and decrementers for x and y
	void incrementXValue();
	void decrementXValue();
	void incrementYValue();
	void decrementYValue();

	// operator overloads

	// arithmetic operators
	// negate the x and y values of the current point
	Point2D operator-() const;
	// multiply scalar to current point and return new value
	Point2D operator*(float scalar) const;
	// divide current by scalar and return new value
	Point2D operator/(float scalar) const;
	// prefix adition to current
	void operator++();
	// postfix adition to current
	void operator++(int);
	// prefix subtraction to current
	void operator--();
	// postfix subtraction to current
	void operator--(int);

	// compound assignment operators
	// add point value to current point
	Point2D& operator+=(const Point2D &point);
	// subtract point value from current point
	Point2D& operator-=(const Point2D &point);
	// multiply point value and current point
	Point2D& operator*=(const Point2D &point);
	// multiply current value by a scalar
	Point2D& operator*=(float scalar);
	// divide current point by point
	Point2D& operator/=(const Point2D &point);
	// divide current point by scalar
	Point2D& operator/=(float scalar);

private:
	float m_x, m_y;
};

// non class operator overloads

// arithmetic operators
Point2D operator+(const Point2D &leftPoint, const Point2D &rightPoint);
Point2D operator-(const Point2D &leftPoint, const Point2D &rightPoint);
Point2D operator*(const Point2D &leftPoint, const Point2D &rightPoint);
Point2D operator/(const Point2D &leftPoint, const Point2D &rightPoint);

// comparision operators
bool operator==(const Point2D &leftPoint, const Point2D &rightPoint);
bool operator!=(const Point2D &leftPoint, const Point2D &rightPoint);
bool operator>(const Point2D &leftPoint, const Point2D &rightPoint);
bool operator<(const Point2D &leftPoint, const Point2D &rightPoint);
bool operator>=(const Point2D &leftPoint, const Point2D &rightPoint);
bool operator<=(const Point2D &leftPoint, const Point2D &rightPoint);
