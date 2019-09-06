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
void GamePlay::gamePlayLoop(Character * player, Character * &monsters, int& numMonsters)
{
	bool playing = true;
	int currentTurnCounter = 0;
	while (playing)
	{
		if (currentTurnCounter > this->turnAmountGenerateMonsters)
		{
			currentTurnCounter = 0;
			numMonsters++;

			//TODO move all of this
			monsters = (Character *)realloc(monsters, numMonsters * sizeof(Character));

			// create new monster
			monsters[numMonsters - 1].name = (char *)calloc(2, sizeof(char));
			monsters[numMonsters - 1].name[0] = (char)(rand() % 255);
			monsters[numMonsters - 1].name[1] = '\0';
			// TODO to this point

			this->setCharacterLocation(&monsters[numMonsters - 1]);
		}

		// print monster locations
		for (int i = 0; i < numMonsters; i++)
		{
			printf("Monster %s at [%02d,%02d]\n", monsters[i].name, monsters[i].x, monsters[i].y);
		}
		// print player location
		printf("Player %s at [%02d,%02d]\n", player->name, player->x, player->y);

		// print instructions for player
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;

		this->monsterAI(monsters, numMonsters);

		switch (_getch())
		{
			case 'A':
			case 'a':
				player->x--;
				if (player->x < -this->gridSize)
					player->x = -this->gridSize;
				break;
			case 'D':
			case 'd':
				player->x++;
				if (player->x > this->gridSize)
					player->x = this->gridSize;
				break;
			case 'W':
			case 'w':
				player->y++;
				if (player->y > this->gridSize)
					player->y = this->gridSize;
				break;
			case 'S':
			case 's':
				player->y--;
				if (player->y < -this->gridSize)
					player->y = -this->gridSize;
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
			if (player->x == monsters[i].x && player->y == monsters[i].y)
			{
				newNumMonsters--;
				if (newNumMonsters > 0)
				{
					// TODO remove all of this
					Character * monstersTemp = (Character *)calloc(newNumMonsters, sizeof(Character));

					// copy over the monsters that are in memory before and after the destroyed one
					if (i > 0)
					{
						memcpy((void*)monstersTemp, (void*)monsters, sizeof(Character) * (i));
					}
					memcpy(&monstersTemp[i], &monsters[i + 1], sizeof(Character) * (newNumMonsters - i));

					// free destroyed monster name and original monster data
					free(monsters[i].name);
					free(monsters);
					monsters = monstersTemp;
					// TODO to this point

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

	character->x = rand() % this->gridSize;
	character->y = rand() % this->gridSize;
	if (randXNegative) { character->x *= -1; }
	if (randYNegative) { character->y *= -1; }
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
				monsters[i].y++;
				break;
			case 1: // right
				monsters[i].x++;
				break;
			case 2: // down
				monsters[i].y--;
				break;
			case 3: // left
				monsters[i].x--;
				break;
			default:
				monsters[i].x++;
		}
		// check to see if the monster went out of bounds
		if (monsters[i].x > this->gridSize)
			monsters[i].x = this->gridSize;
		else if (monsters[i].x < -this->gridSize)
			monsters[i].x = -this->gridSize;
		else if (monsters[i].y > this->gridSize)
			monsters[i].y = this->gridSize;
		else if (monsters[i].y < -this->gridSize)
			monsters[i].y = -this->gridSize;
	}
}