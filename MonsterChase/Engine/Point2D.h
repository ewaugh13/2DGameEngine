#pragma once
class Point2D
{
public:
	Point2D(int x, int y);
	~Point2D();

	// Getters for private variables
	int X() const { return m_x; }
	int Y() const { return m_y; }

	// Setters for private variables
	void X(int i_x) { m_x = i_x; }
	void Y(int i_y) { m_y = i_y; }

	// incrementers and decrementers for x and y
	void incrementXValue();
	void decrementXValue();
	void incrementYValue();
	void decrementYValue();

	// operator overloads

	// arithmetic operators
	// negate the x and y values of the current point
	Point2D operator-();
	// multiply scalar to current point and return new value
	Point2D operator*(int scalar);
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

private:
	int m_x, m_y;
};

// arithmetic operators
// add point to current point and return new value
Point2D operator+(Point2D &leftPoint, Point2D &rightPoint);
// subtract point to current point and return new value
Point2D operator-(Point2D &leftPoint, Point2D &rightPoint);
// multiply point to current point and return new value
Point2D operator*(Point2D &leftPoint, Point2D &rightPoint);
// divide current by point and return new value
Point2D operator/(Point2D &leftPoint, Point2D &rightPoint);

// comparision operators
// check if current and point have the same values
bool operator==(Point2D &leftPoint, Point2D &rightPoint);
// check if current and point have different values
bool operator!=(Point2D &leftPoint, Point2D &rightPoint);
// check if current is greater than point
bool operator>(Point2D &leftPoint, Point2D &rightPoint);
// check if current is less than point
bool operator<(Point2D &leftPoint, Point2D &rightPoint);
// check if current is greater than or equal to point
bool operator>=(Point2D &leftPoint, Point2D &rightPoint);
// check if current is less than or equal to point
bool operator<=(Point2D &leftPoint, Point2D &rightPoint);