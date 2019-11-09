#include "MonsterMovement.h"

void MonsterMovement::BeginUpdate(Actor & i_Monster)
{
	bool moveMonster = rand() % 2;

	if (moveMonster)
	{
		// if X pos aren't equal determine direction (x dir takes priority)
		if (this->m_TargetActor->GetPosition().GetX() != i_Monster.GetPosition().GetX())
		{
			(this->m_TargetActor->GetPosition().GetX() > i_Monster.GetPosition().GetX())
				? i_Monster.GetPosition().incrementXValue() : i_Monster.GetPosition().decrementXValue();
		}
		// if Y pos aren't equal determine direction
		else if (this->m_TargetActor->GetPosition().GetY() != i_Monster.GetPosition().GetY())
		{
			(this->m_TargetActor->GetPosition().GetY() > i_Monster.GetPosition().GetY())
				? i_Monster.GetPosition().incrementYValue() : i_Monster.GetPosition().decrementYValue();
		}

		if (i_Monster.GetPosition().GetX() > GRID_SIZE)
			i_Monster.GetPosition().SetX((float)GRID_SIZE);
		else if (i_Monster.GetPosition().GetX() < -GRID_SIZE)
			i_Monster.GetPosition().SetX((float)-GRID_SIZE);
		else if (i_Monster.GetPosition().GetY() > GRID_SIZE)
			i_Monster.GetPosition().SetY((float)GRID_SIZE);
		else if (i_Monster.GetPosition().GetY() < -GRID_SIZE)
			i_Monster.GetPosition().SetY((float)-GRID_SIZE);
	}
}
