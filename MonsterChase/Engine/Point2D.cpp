#include "Point2D.h"

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