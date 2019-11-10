#include "TeleportMonster.h"

TeleportMonster::TeleportMonster(const TeleportMonster & i_OtherTeleportMonster)
{
	this->m_TeleportPercent = i_OtherTeleportMonster.m_TeleportPercent;
}

void TeleportMonster::BeginUpdate(Actor & i_Monster)
{
	// TODO check if monster is close to player before teleport
	if (rand() % 100 <= this->m_TeleportPercent)
	{
		i_Monster.SetPosition(Point2D::GetRandomPosition(GRID_SIZE));
	}
}
