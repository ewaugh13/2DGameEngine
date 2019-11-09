#pragma once

#include <math.h>

class Point2D
{
public:
#pragma region Constructor and Destructor
	// standard constructor
	Point2D(float i_x, float i_y) :
		m_x(i_x),
		m_y(i_y)
	{
	}

	// copy constructor
	Point2D(const Point2D & i_rhs);

	// standard destructor
	~Point2D();
#pragma endregion

#pragma region Getters and Setters
	// Getters for private variables
	inline float GetX() const { return m_x; }
	inline float GetY() const { return m_y; }

	// Setters for private variables
	inline void SetX(float i_x) { m_x = i_x; }
	inline void SetY(float i_y) { m_y = i_y; }
#pragma endregion

#pragma region Incrementers and Decrementers
	void incrementXValue();
	void decrementXValue();
	void incrementYValue();
	void decrementYValue();
#pragma endregion

#pragma region Const Point2D
	// const point2D {0.0f, 0.0f, 0.0f}
	static const Point2D Zero;
#pragma endregion

#pragma region Class Operator Overloads
	// assignment operator
	Point2D& operator=(const Point2D & i_rhs);

#pragma region Arithmetic Operators
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
#pragma endregion

#pragma region Compound Assignment Operators
	// add point value to current point
	Point2D& operator+=(const Point2D & point);
	// subtract point value from current point
	Point2D& operator-=(const Point2D & point);
	// multiply point value and current point
	Point2D& operator*=(const Point2D & point);
	// multiply current value by a scalar
	Point2D& operator*=(float scalar);
	// divide current point by point
	Point2D& operator/=(const Point2D & point);
	// divide current point by scalar
	Point2D& operator/=(float scalar);
#pragma endregion

#pragma endregion

private:
	float m_x, m_y;
};

#include "Point2D-inl.h"
