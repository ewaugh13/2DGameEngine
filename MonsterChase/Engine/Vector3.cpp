#include "Vector3.h"

#include <stdlib.h>

#pragma region Constructor and Destructor
Vector3::Vector3(const Vector3 & i_rhs)
{
	this->m_x = i_rhs.m_x;
	this->m_y = i_rhs.m_y;
	this->m_z = i_rhs.m_z;
}

Vector3::~Vector3()
{
}
#pragma endregion


const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);

Vector3 Vector3::GetRandomPosition(int gridSize)
{
	int randXNegative = rand() % 2;
	int randYNegative = rand() % 2;

	int x = rand() % gridSize;
	int y = rand() % gridSize;
	if (randXNegative) { x *= -1; }
	if (randYNegative) { y *= -1; }

	return Vector3(static_cast<float>(x), static_cast<float>(y), 0.0f);
}