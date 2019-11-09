#include "GamePlay.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>


GamePlay::GamePlay(int turnAmountGenerateMonsters)
{
	this->turnAmountGenerateMonsters = turnAmountGenerateMonsters;
	this->monsterAIProcessor = MonsterAI();
}


GamePlay::~GamePlay()
{
}

// does the main gameplay loop
void GamePlay::gamePlayLoop(Engine * engine, Actor * player, Actor ** &monsters, unsigned int &numMonsters)
{
	int currentTurnCounter = 0;
	while (PLAYING)
	{
		// create new monster if we reach turn amount
		if (currentTurnCounter > this->turnAmountGenerateMonsters)
		{
			currentTurnCounter = 0;
			numMonsters++;

			monsters = (Actor **)engine->reinitalizeMemory(monsters, numMonsters * sizeof(Actor *));

			// create new monster
			char * monsterName = (char *)engine->initalizeMemory(2, sizeof(char));
			monsterName[0] = (char)(rand() % 255);
			monsterName[1] = '\0';

			monsters[numMonsters - 1] = new Actor(monsterName, getActorLocation());
			engine->freeMemory(monsterName);
		}

		// print monster locations
		for (unsigned int i = 0; i < numMonsters; i++)
		{
			printf("Monster %s at [%02d,%02d]\n", monsters[i]->GetName(), static_cast<int>(monsters[i]->GetPosition().GetX()), static_cast<int>(monsters[i]->GetPosition().GetY()));
		}
		// print player location
		printf("Player %s at [%02d,%02d]\n", player->GetName(), static_cast<int>(player->GetPosition().GetX()), static_cast<int>(player->GetPosition().GetY()));

		// print instructions for player
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;

		this->monsterAIProcessor.monsterMovement(monsters, numMonsters, GRID_SIZE);

		player->BeginUpdate();
		player->Update();
		player->EndUpdate();

		/*switch (_getch())
		{
			case 'A':
			case 'a':
				player->GetPosition().decrementXValue();
				if (player->GetPosition().GetX() < -GRID_SIZE)
					player->GetPosition().SetX((float)-GRID_SIZE);
				break;
			case 'D':
			case 'd':
				player->GetPosition().incrementXValue();
				if (player->GetPosition().GetX() > GRID_SIZE)
					player->GetPosition().SetX((float)GRID_SIZE);
				break;
			case 'W':
			case 'w':
				player->GetPosition().incrementYValue();
				if (player->GetPosition().GetY() > GRID_SIZE)
					player->GetPosition().SetY((float)GRID_SIZE);
				break;
			case 'S':
			case 's':
				player->GetPosition().decrementYValue();
				if (player->GetPosition().GetY() < -GRID_SIZE)
					player->GetPosition().SetY((float)-GRID_SIZE);
				break;
			case 'Q':
			case 'q':
				PLAYING = false;
				break;
			default:
				continue;
		}*/

		// destroy monster if its on the same space as a player
		int newNumMonsters = numMonsters;
		for (size_t i = 0; i < numMonsters; i++)
		{
			if (player->GetPosition() == monsters[i]->GetPosition())
			{
				newNumMonsters--;
				if (numMonsters > 0)
				{
					Actor ** monstersTemp = (Actor **)engine->initalizeMemory(newNumMonsters, sizeof(Actor *));

					// copy over the monsters that are in memory before and after the destroyed one
					if (i > 0)
					{
						engine->copyMemory(monstersTemp, monsters, sizeof(Actor *) * (i));
					}
					engine->copyMemory(&monstersTemp[i],
						&monsters[i + 1],
						sizeof(Actor *) * (static_cast<size_t>(newNumMonsters) - i));

					// free destroyed monster name and original monster data
					delete monsters[i];
					engine->freeMemory(monsters);
					monsters = monstersTemp;

					numMonsters = newNumMonsters;
					i--;
				}
			}
		}
		currentTurnCounter++;
	}
}

// sets a character's x and y location from a range of -gridSize to gridSize
Point2D GamePlay::getActorLocation()
{
	int randXNegative = rand() % 2;
	int randYNegative = rand() % 2;

	int x = rand() % GRID_SIZE;
	int y = rand() % GRID_SIZE;
	if (randXNegative) { x *= -1; }
	if (randYNegative) { y *= -1; }

	return Point2D((float)x, (float)y);
}