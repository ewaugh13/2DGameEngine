#include "Actor.h"
#include <stdlib.h>

Actor::~Actor()
{
	if (this->m_name)
	{
		free(this->m_name);
	}
}
