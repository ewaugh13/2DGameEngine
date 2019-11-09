#pragma once

#include "IActorComponent.h"

class MonsterMovement : public IActorComponent
{
public:
	void BeginUpdate(Actor & i_Actor)
	{
		i_Actor.GetPosition();
	}
};