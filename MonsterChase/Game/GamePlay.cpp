#include "GamePlay.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>


GamePlay::GamePlay(int gridSize, int turnAmountGenerateMonsters)
{
	this->gridSize = gridSize;
	this->turnAmountGenerateMonsters = turnAmountGenerateMonsters;
}


GamePlay::~GamePlay()
{
}

// does the main gameplay loop
void GamePlay::gamePlayLoop(Engine * engine, Character * player, Character * &monsters, int& numMonsters)
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

			monsters = (Character *)engine->reinitalizeMemory(monsters, numMonsters * sizeof(Character));

			// create new monster
			monsters[numMonsters - 1].name = (char *)engine->initalizeMemory(2, sizeof(char));
			monsters[numMonsters - 1].name[0] = (char)(rand() % 255);
			monsters[numMonsters - 1].name[1] = '\0';

			this->setCharacterLocation(&monsters[numMonsters - 1]);
		}

		// print monster locations
		for (int i = 0; i < numMonsters; i++)
		{
			printf("Monster %s at [%02d,%02d]\n", monsters[i].name, monsters[i].position.x, monsters[i].position.y);
		}
		// print player location
		printf("Player %s at [%02d,%02d]\n", player->name, player->position.x, player->position.y);

		// print instructions for player
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;

		this->monsterAI(monsters, numMonsters);

		switch (_getch())
		{
			case 'A':
			case 'a':
				player->position.x--;
				if (player->position.x < -this->gridSize)
					player->position.x = -this->gridSize;
				break;
			case 'D':
			case 'd':
				player->position.x++;
				if (player->position.x > this->gridSize)
					player->position.x = this->gridSize;
				break;
			case 'W':
			case 'w':
				player->position.y++;
				if (player->position.y > this->gridSize)
					player->position.y = this->gridSize;
				break;
			case 'S':
			case 's':
				player->position.y--;
				if (player->position.y < -this->gridSize)
					player->position.y = -this->gridSize;
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
		for (int i = 0; i < numMonsters; i++)
		{
			if (player->position == monsters[i].position)
			{
				newNumMonsters--;
				if (newNumMonsters > 0)
				{
					Character * monstersTemp = (Character *)engine->initalizeMemory(newNumMonsters, sizeof(Character));

					// copy over the monsters that are in memory before and after the destroyed one
					if (i > 0)
					{
						engine->copyMemory((void*)monstersTemp, (void*)monsters, sizeof(Character) * (i));
					}
					engine->copyMemory(&monstersTemp[i], &monsters[i + 1], sizeof(Character) * (newNumMonsters - i));

					// free destroyed monster name and original monster data
					engine->freeMemory(monsters[i].name);
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
void GamePlay::setCharacterLocation(Character * character)
{
	int randXNegative = rand() % 2;
	int randYNegative = rand() % 2;

	int x = rand() % this->gridSize;
	int y = rand() % this->gridSize;
	if (randXNegative) { x *= -1; }
	if (randYNegative) { y *= -1; }

	character->position = Point2D(x, y);
}

// monster AI to move the monsters in a random direction
void GamePlay::monsterAI(Character * monsters, int& numMonsters)
{
	// move the monsters in a random direction 0 being up, 1 being right, 2 being down and 3 being left
	for (int i = 0; i < numMonsters; i++)
	{
		int direction = rand() % 4;
		switch (direction)
		{
			case 0: // up
				monsters[i].position.y++;
				break;
			case 1: // right
				monsters[i].position.x++;
				break;
			case 2: // down
				monsters[i].position.y--;
				break;
			case 3: // left
				monsters[i].position.x--;
				break;
			default:
				monsters[i].position.x++;
		}
		// check to see if the monster went out of bounds
		if (monsters[i].position.x > this->gridSize)
			monsters[i].position.x = this->gridSize;
		else if (monsters[i].position.x < -this->gridSize)
			monsters[i].position.x = -this->gridSize;
		else if (monsters[i].position.y > this->gridSize)
			monsters[i].position.y = this->gridSize;
		else if (monsters[i].position.y < -this->gridSize)
			monsters[i].position.y = -this->gridSize;
	}
}