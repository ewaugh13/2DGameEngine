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
void MonsterAI::monsterMovement(Character * monsters, const int& numMonsters, const int& gridSize)
{
	// move the monsters in a random direction 0 being up, 1 being right, 2 being down and 3 being left
	for (int i = 0; i < numMonsters; i++)
	{
		int direction = rand() % 4;
		switch (direction)
		{
			case 0: // up
				monsters[i].position.incrementYValue();
				break;
			case 1: // right
				monsters[i].position.incrementXValue();
				break;
			case 2: // down
				monsters[i].position.decrementYValue();
				break;
			case 3: // left
				monsters[i].position.decrementXValue();
				break;
			default:
				monsters[i].position.incrementXValue();
		}
		// check to see if the monster went out of bounds
		if (monsters[i].position.X() > gridSize)
			monsters[i].position.X(gridSize);
		else if (monsters[i].position.X() < -gridSize)
			monsters[i].position.X(-gridSize);
		else if (monsters[i].position.Y() > gridSize)
			monsters[i].position.Y(gridSize);
		else if (monsters[i].position.Y() < -gridSize)
			monsters[i].position.Y(-gridSize);
	}
}
