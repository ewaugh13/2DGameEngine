#pragma once

#include "Actor.h"

extern const int GRID_SIZE;
extern bool PLAYING;

class PlayerMovement : public IActorComponent
{
public:
	PlayerMovement()
	{
	}

	void BeginUpdate(Actor & i_Actor);
};

