#pragma once

#include "Actor.h"

extern const int GRID_SIZE;

class MonsterMovement : public MyEngine::IActorComponent
{
public:
	MonsterMovement(MyEngine::Actor * i_TargetActor) : m_TargetActor(i_TargetActor)
	{
	}

	MonsterMovement(const MonsterMovement & i_OtherMonsterMovement);

	void BeginUpdate(MyEngine::Actor & i_Monster);
private:
	MyEngine::Actor * m_TargetActor;
};