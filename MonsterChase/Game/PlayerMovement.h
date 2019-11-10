#pragma once

#include "Actor.h"

extern const int GRID_SIZE;
extern bool PLAYING;

class PlayerMovement : public IActorComponent
{
public:
	void BeginUpdate(Actor & i_player);
};

