#include "Allocators.h"
#include "Engine.h"
#include "GamePlay.h"
#include "GLib.h"
#include "GLibHelpers.h"
#include "MonsterMovement.h"
#include "PlayerMovement.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <malloc.h>
#include <Windows.h>

extern const int GRID_SIZE = 100;
extern bool PLAYING = true;
// number of turns that go by before we generate a new monster
const int TURN_AMOUNT_GENERATE_MONSTER = 9;

//int main()
//{
//	{
//		Engine * engine = new Engine();
//		GamePlay * gameplay = new GamePlay(TURN_AMOUNT_GENERATE_MONSTER);
//
//		// get the player name and set a location
//		std::cout << "What would you like to name the Player" << ": ";
//		char * playerName;
//		engine->getPlayerInput(playerName);
//
//		Actor * player = new Actor(playerName, Point2D::Zero);
//		engine->freeMemory(playerName);
//
//		// add player components
//		player->AddComponent(new PlayerMovement());
//
//		// get the number of monsters to create
//		std::cout << "How many monsters do you want to start with: ";
//		char * numMonstersInput;
//		engine->getPlayerInput(numMonstersInput);
//		unsigned int numMonsters = atoi(numMonstersInput);
//
//		Actor ** monsters = (Actor **)engine->initalizeMemory(numMonsters, sizeof(Actor *));
//
//		// get each monster name and set a location
//		for (unsigned int i = 0; i < numMonsters; i++)
//		{
//			std::cout << "What would you like to name Monster " << i << ": ";
//			char * monsterName;
//			engine->getPlayerInput(monsterName);
//
//			// create monster and add component for movement
//			monsters[i] = new Actor(monsterName, Point2D::GetRandomPosition(GRID_SIZE));
//			monsters[i]->AddComponent(new MonsterMovement(player));
//			engine->freeMemory(monsterName);
//		}
//
//		// while loop for game loop until user input to quit
//		gameplay->gamePlayLoop(engine, player, monsters, numMonsters);
//
//		// free everything we allocated
//		engine->freeMemory(numMonstersInput);
//		for (unsigned int i = 0; i < numMonsters; i++)
//		{
//			delete monsters[i];
//		}
//		engine->freeMemory(monsters);
//
//		delete player;
//		delete engine;
//		delete gameplay;
//	}
//	_CrtDumpMemoryLeaks();
//	return 0;
//}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

		GLib::Sprites::Sprite * pPlayerSprite = GLibHelper::CreateSprite("data\\Samus3.dds");

		bool bQuit = false;

		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (pPlayerSprite)
				{
					static float			moveDist = .01f;
					static float			moveDir = moveDist;

					static GLib::Point2D	Offset = { -180.0f, -100.0f };

					if (Offset.x < -220.0f)
						moveDir = moveDist;
					else if (Offset.x > -140.0f)
						moveDir = -moveDist;

					Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pPlayerSprite, Offset, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (pPlayerSprite)
			GLib::Sprites::Release(pPlayerSprite);

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}