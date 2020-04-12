#pragma once

#include <math.h>

class Vector3
{
public:
#pragma region Constructor and Destructor
	// standard constructor
	Vector3(float i_x, float i_y, float i_z) :
		m_x(i_x), m_y(i_y), m_z(i_z)
	{
	}

	// copy constructor
	Vector3(const Vector3 & i_OtherVector);

	// standard destructor
	~Vector3();
#pragma endregion

#pragma region Getters and Setters
	// Getters for private variables
	inline float GetX() const { return m_x; }
	inline float GetY() const { return m_y; }
	inline float GetZ() const { return m_z; }

	// Setters for private variables
	inline void SetX(float i_x) { m_x = i_x; }
	inline void SetY(float i_y) { m_y = i_y; }
	inline void SetZ(float i_z) { m_z = i_z; }
#pragma endregion

#pragma region Incrementers and Decrementers
	void incrementXValue();
	void decrementXValue();
	void incrementYValue();
	void decrementYValue();
	void incrementZValue();
	void decrementZValue();
#pragma endregion

#pragma region Utility Positions
	// const Vector3 {0.0f, 0.0f, 0.0f}
	static const Vector3 Zero;

	// gets a random point based off grid size
	static Vector3 GetRandomPosition(int gridSize);
#pragma endregion

#pragma region Class Operator Overloads
	// assignment operator
	Vector3& operator=(const Vector3 & i_OtherVector);

#pragma region Arithmetic Operators
	// negate the x and y values of the current point
	Vector3 operator-() const;
	// multiply scalar to current point and return new value
	Vector3 operator*(float scalar) const;
	// divide current by scalar and return new value
	Vector3 operator/(float scalar) const;
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
	Vector3& operator+=(const Vector3 & point);
	// subtract point value from current point
	Vector3& operator-=(const Vector3 & point);
	// multiply point value and current point
	Vector3& operator*=(const Vector3 & point);
	// multiply current value by a scalar
	Vector3& operator*=(float scalar);
	// divide current point by point
	Vector3& operator/=(const Vector3 & point);
	// divide current point by scalar
	Vector3& operator/=(float scalar);
#pragma endregion

#pragma endregion

private:
	float m_x, m_y, m_z;
};

#include "Vector3-inl.h"
