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
				monsters[i]->Position().incrementYValue();
				break;
			case 1: // right
				monsters[i]->Position().incrementXValue();
				break;
			case 2: // down
				monsters[i]->Position().decrementYValue();
				break;
			case 3: // left
				monsters[i]->Position().decrementXValue();
				break;
			default:
				monsters[i]->Position().incrementXValue();
		}
		// check to see if the monster went out of bounds
		if (monsters[i]->Position().X() > gridSize)
			monsters[i]->Position().X((float)gridSize);
		else if (monsters[i]->Position().X() < -gridSize)
			monsters[i]->Position().X((float)-gridSize);
		else if (monsters[i]->Position().Y() > gridSize)
			monsters[i]->Position().Y((float)gridSize);
		else if (monsters[i]->Position().Y() < -gridSize)
			monsters[i]->Position().Y((float)-gridSize);
	}
}
