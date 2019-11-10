#include "GamePlay.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "MonsterMovement.h"
#include "TeleportMonster.h"


GamePlay::GamePlay(int turnAmountGenerateMonsters)
{
	this->turnAmountGenerateMonsters = turnAmountGenerateMonsters;
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

			monsters[numMonsters - 1] = new Actor(monsterName, Point2D::GetRandomPosition(GRID_SIZE));
			monsters[numMonsters - 1]->AddComponent(new MonsterMovement(player));
			monsters[numMonsters - 1]->AddComponent(new TeleportMonster(TELEPORT_PERCENT));
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

		//this->monsterAIProcessor.monsterMovement(monsters, numMonsters, GRID_SIZE);

		player->BeginUpdate();
		player->Update();
		player->EndUpdate();

		for (size_t i = 0; i < numMonsters; i++)
		{
			monsters[i]->BeginUpdate();
			monsters[i]->Update();
			monsters[i]->EndUpdate();
		}

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