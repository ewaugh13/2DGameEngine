#pragma once

#include "Actor.h"

extern const int GRID_SIZE;

class MonsterMovement : public IActorComponent
{
public:
	MonsterMovement(Actor * i_TargetActor) : m_TargetActor(i_TargetActor)
	{
	}

	void BeginUpdate(Actor & i_Monster);
private:
	Actor * m_TargetActor;
};