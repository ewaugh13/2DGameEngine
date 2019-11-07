#pragma once

#include "Point2D.h"
#include <string.h>

class Actor
{
public:
	Actor(const char * i_name, const Point2D& i_initalPosition) :
		m_name(i_name ? _strdup(i_name) : nullptr), m_position(i_initalPosition)
	{
	}
	~Actor();

#pragma region Getters and Setters
	char * Name() const { return m_name; }
	void Name(const char * i_name) { m_name = const_cast<char *>(i_name); }

	Point2D& Position() { return m_position; }
	void Position(const Point2D& i_position) { m_position = i_position; }
#pragma endregion


private:
	char * m_name;
	Point2D m_position;
};

