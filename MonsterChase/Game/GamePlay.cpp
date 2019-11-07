#include "GamePlay.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>


GamePlay::GamePlay(int gridSize, int turnAmountGenerateMonsters)
{
	this->gridSize = gridSize;
	this->turnAmountGenerateMonsters = turnAmountGenerateMonsters;
	this->monsterAIProcessor = MonsterAI();
}


GamePlay::~GamePlay()
{
}

// does the main gameplay loop
void GamePlay::gamePlayLoop(Engine * engine, Actor * player, Actor ** &monsters, unsigned int &numMonsters)
{
	bool playing = true;
	int currentTurnCounter = 0;
	while (playing)
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
			printf("Monster %s at [%02d,%02d]\n", monsters[i]->Name(), static_cast<int>(monsters[i]->Position().X()), static_cast<int>(monsters[i]->Position().Y()));
		}
		// print player location
		printf("Player %s at [%02d,%02d]\n", player->Name(), static_cast<int>(player->Position().X()), static_cast<int>(player->Position().Y()));

		// print instructions for player
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;

		this->monsterAIProcessor.monsterMovement(monsters, numMonsters, this->gridSize);

		switch (_getch())
		{
			case 'A':
			case 'a':
				player->Position().decrementXValue();
				if (player->Position().X() < -this->gridSize)
					player->Position().X((float)-this->gridSize);
				break;
			case 'D':
			case 'd':
				player->Position().incrementXValue();
				if (player->Position().X() > this->gridSize)
					player->Position().X((float)this->gridSize);
				break;
			case 'W':
			case 'w':
				player->Position().incrementYValue();
				if (player->Position().Y() > this->gridSize)
					player->Position().Y((float)this->gridSize);
				break;
			case 'S':
			case 's':
				player->Position().decrementYValue();
				if (player->Position().Y() < -this->gridSize)
					player->Position().Y((float)-this->gridSize);
				break;
			case 'Q':
			case 'q':
				playing = false;
				break;
			default:
				continue;
		}

		// destroy monster if its on the same space as a player
		int newNumMonsters = numMonsters;
		for (size_t i = 0; i < numMonsters; i++)
		{
			if (player->Position() == monsters[i]->Position())
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

	int x = rand() % this->gridSize;
	int y = rand() % this->gridSize;
	if (randXNegative) { x *= -1; }
	if (randYNegative) { y *= -1; }

	return Point2D((float)x, (float)y);
}