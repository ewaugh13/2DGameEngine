#include "MonsterAI.h"

#include <stdlib.h>
#include <stdio.h>


MonsterAI::MonsterAI()
{
}


MonsterAI::~MonsterAI()
{
}

// monster AI to move the monsters in a random direction
void MonsterAI::monsterMovement(Actor ** monsters, const int& numMonsters, const int& gridSize)
{
	// move the monsters in a random direction 0 being up, 1 being right, 2 being down and 3 being left
	for (int i = 0; i < numMonsters; i++)
	{
		int direction = rand() % 4;
		switch (direction)
		{
			case 0: // up
				monsters[i]->GetPosition().incrementYValue();
				break;
			case 1: // right
				monsters[i]->GetPosition().incrementXValue();
				break;
			case 2: // down
				monsters[i]->GetPosition().decrementYValue();
				break;
			case 3: // left
				monsters[i]->GetPosition().decrementXValue();
				break;
			default:
				monsters[i]->GetPosition().incrementXValue();
		}
		// check to see if the monster went out of bounds
		if (monsters[i]->GetPosition().GetX() > gridSize)
			monsters[i]->GetPosition().SetX((float)gridSize);
		else if (monsters[i]->GetPosition().GetX() < -gridSize)
			monsters[i]->GetPosition().SetX((float)-gridSize);
		else if (monsters[i]->GetPosition().GetY() > gridSize)
			monsters[i]->GetPosition().SetY((float)gridSize);
		else if (monsters[i]->GetPosition().GetY() < -gridSize)
			monsters[i]->GetPosition().SetY((float)-gridSize);
	}
}
