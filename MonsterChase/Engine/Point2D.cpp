#include "Point2D.h"

#include <stdlib.h>

#pragma region Constructor and Destructor
Point2D::Point2D(const Point2D & i_rhs)
{
	this->m_x = i_rhs.m_x;
	this->m_y = i_rhs.m_y;
}

Point2D::~Point2D()
{
}
#pragma endregion


const Point2D Point2D::Zero = Point2D(0.0f, 0.0f);

Point2D Point2D::GetRandomPosition(int gridSize)
{
	int randXNegative = rand() % 2;
	int randYNegative = rand() % 2;

	int x = rand() % gridSize;
	int y = rand() % gridSize;
	if (randXNegative) { x *= -1; }
	if (randYNegative) { y *= -1; }

	return Point2D((float)x, (float)y);
}