#pragma once

#include "Actor.h"

extern const int GRID_SIZE;

class TeleportMonster : public IActorComponent
{
public:
	TeleportMonster(int i_TeleportPercent) : m_TeleportPercent(i_TeleportPercent)
	{
	}

	TeleportMonster(const TeleportMonster & i_OtherTeleportMonster);

	void BeginUpdate(Actor & i_Monster);
private:
	int m_TeleportPercent;
};

