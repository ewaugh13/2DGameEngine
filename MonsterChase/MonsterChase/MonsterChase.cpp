#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <malloc.h>

#include "Engine.h"
#include "GamePlay.h"

const int GRID_SIZE = 100;
// number of turns that go by before we generate a new monster
const int TURN_AMOUNT_GENERATE_MONSTER = 9;

int main()
{
	{
		Engine * engine = new Engine();
		GamePlay * gameplay = new GamePlay(GRID_SIZE, TURN_AMOUNT_GENERATE_MONSTER);

		// get the number of monsters to create
		std::cout << "How many monsters do you want to start with: ";
		char * numMonstersInput;
		engine->getPlayerInput(numMonstersInput);
		int numMonsters = atoi(numMonstersInput);

		Character * monsters = (Character *)engine->initalizeMemory(numMonsters, sizeof(Character));
		Character * player = (Character *)engine->initalizeMemory(1, sizeof(Character));

		// get each monster name and set a location
		for (int i = 0; i < numMonsters; i++)
		{
			std::cout << "What would you like to name Monster " << i << ": ";
			engine->getPlayerInput(monsters[i].name);

			gameplay->setCharacterLocation(&monsters[i]);
		}

		// get the player name and set a location
		std::cout << "What would you like to name the Player" << ": ";
		char * playerName;
		engine->getPlayerInput(playerName);
		player->name = playerName;

		// while loop for game loop until user input to quit
		gameplay->gamePlayLoop(engine, player, monsters, numMonsters);

		// free everything we allocated
		engine->freeMemory(numMonstersInput);
		for (int i = 0; i < numMonsters; i++)
		{
			engine->freeMemory(monsters[i].name);
		}
		engine->freeMemory(monsters);
		engine->freeMemory(player);
		engine->freeMemory(playerName);

		delete engine;
		delete gameplay;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}