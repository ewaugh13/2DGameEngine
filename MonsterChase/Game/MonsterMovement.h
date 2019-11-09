#pragma once

#include "Actor.h"

class MonsterMovement : public IActorComponent
{
public:
	void BeginUpdate(Actor & i_Actor)
	{
		i_Actor.GetPosition();
	}
};