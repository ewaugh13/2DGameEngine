#pragma once
class Point2D
{
public:
	int x, y;

	Point2D(int x, int y);
	~Point2D();

	// operator overloads

	// arithmetic operators
	// add point to current point and return new value
	Point2D operator+(const Point2D &point);
	// subtract point to current point and return new value
	Point2D operator-(const Point2D &point);
	// negate the x and y values of the current point
	Point2D operator-();
	// multiply point to current point and return new value
	Point2D operator*(const Point2D &point);
	// multiply scalar to current point and return new value
	Point2D operator*(int scalar);
	// divide current by point and return new value
	Point2D operator/(const Point2D &point);
	// divide current by scalar and return new value
	Point2D operator/(int scalar);
	// prefix adition to current
	void operator++();
	// postfix adition to current
	void operator++(int);
	// prefix subtraction to current
	void operator--();
	// postfix subtraction to current
	void operator--(int);

	// comparision operators
	// check if current and point have the same values
	bool operator==(const Point2D &point);
	// check if current and point have different values
	bool operator!=(const Point2D &point);
	// check if current is greater than point
	bool operator>(const Point2D &point);
	// check if current is less than point
	bool operator<(const Point2D &point);
	// check if current is greater than or equal to point
	bool operator>=(const Point2D &point);
	// check if current is less than or equal to point
	bool operator<=(const Point2D &point);

	// compound assignment operators
	// add point value to current point
	Point2D& operator+=(const Point2D &point);
	// subtract point value from current point
	Point2D& operator-=(const Point2D &point);
	// multiply point value and current point
	Point2D& operator*=(const Point2D &point);
	// multiply current value by a scalar
	Point2D& operator*=(int scalar);
	// divide current point by point
	Point2D& operator/=(const Point2D &point);
	// divide current point by scalar
	Point2D& operator/=(int scalar);
};

