#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <malloc.h>
#include <PlayerMovement.h>

#include "Engine.h"
#include "GamePlay.h"

extern const int GRID_SIZE = 100;
extern bool PLAYING = true;
// number of turns that go by before we generate a new monster
const int TURN_AMOUNT_GENERATE_MONSTER = 9;

int main()
{
	{
		Engine * engine = new Engine();
		GamePlay * gameplay = new GamePlay(TURN_AMOUNT_GENERATE_MONSTER);

		// get the number of monsters to create
		std::cout << "How many monsters do you want to start with: ";
		char * numMonstersInput;
		engine->getPlayerInput(numMonstersInput);
		unsigned int numMonsters = atoi(numMonstersInput);

		Actor ** monsters = (Actor **)engine->initalizeMemory(numMonsters, sizeof(Actor *));

		// get each monster name and set a location
		for (unsigned int i = 0; i < numMonsters; i++)
		{
			std::cout << "What would you like to name Monster " << i << ": ";
			char * monsterName;
			engine->getPlayerInput(monsterName);

			monsters[i] = new Actor(monsterName, gameplay->getActorLocation());
			engine->freeMemory(monsterName);
		}

		// get the player name and set a location
		std::cout << "What would you like to name the Player" << ": ";
		char * playerName;
		engine->getPlayerInput(playerName);

		Actor * player = new Actor(playerName, Point2D(0.0f, 0.0f));
		engine->freeMemory(playerName);

		// add player components
		player->AddComponent(new PlayerMovement());

		// while loop for game loop until user input to quit
		gameplay->gamePlayLoop(engine, player, monsters, numMonsters);

		// free everything we allocated
		engine->freeMemory(numMonstersInput);
		for (unsigned int i = 0; i < numMonsters; i++)
		{
			delete monsters[i];
		}
		engine->freeMemory(monsters);

		delete player;
		delete engine;
		delete gameplay;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

// call this from main if you want to test it
// commented out since it makes cpp check have a bunch of warnings

//void Point2D_UnitTest()
//{
//	Point2D P1(0.0f, 0.0f);
//	Point2D P2(0.0f, 0.0f);
//
//	Point2D P3 = P1 + P2;
//	P3 = P1 - P2;
//
//	Point2D P4 = P1 * 0.5f;
//
//	Point2D P5 = P1 / 2.0f;
//
//	Point2D P6 = -P4;
//
//	P6 *= 2.0f;
//	P5 /= 4.0f;
//
//	P2 += P1;
//	P3 -= P1;
//
//	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;
//
//	bool bArentEqual = P6 != P4;
//}