#pragma once

#include "Actor.h"

extern const int GRID_SIZE;
extern bool PLAYING;

class PlayerMovement : public MyEngine::IActorComponent
{
public:
	void BeginUpdate(MyEngine::Actor & i_player);
};

