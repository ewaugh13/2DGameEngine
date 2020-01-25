#include "GamePlay.h"
#include "GLib.h"
#include "GLibHelpers.h"
#include "Timer.h"

#include <cmath> 

// does the main gameplay loop
void GamePlay::GameLoop()
{
	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

	GLib::Sprites::Sprite * pPlayerSprite = GLibHelper::CreateSprite("data\\SamusNeutral0.dds");
	GLib::Point2D playerPosition = { -180.0f, -100.0f };
	GLib::Point2D playerPrevPosition = playerPosition;

	float playerMass = 300.0f;
	float playerMoveForceHorizontal = 10.0f;
	float playerMoveForceVertical = 5.0f;

	//float dragFactor = 0.3f;

	bool movingLeft = false;
	bool movingRight = false;

	Timer * timer = new Timer();

	bool bQuit = false;

	float playerAccelHoriz = 0.0f;

	do
	{
		float deltaTime = timer->DeltaTime();

		// IMPORTANT: We need to let GLib do it's thing. 
		GLib::Service(bQuit);

		if (!bQuit)
		{
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();

			if (GLibHelper::KeyStates['Q'])
			{
				bQuit = true;

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();

				continue;
			}

			// if first sprite was loaded
			if (pPlayerSprite)
			{
				//float playerAccelHoriz = 0.0f;
				float playerAccelVert = 0.0f;

				if (GLibHelper::KeyStates['A'] || GLibHelper::KeyStates['D'])
					playerAccelHoriz = playerMoveForceHorizontal / playerMass;
				
				//if (GLibHelper::KeyStates['W'] || GLibHelper::KeyStates['S'])
				//{
				//	verletMultiplyFactor = 2.0f;
				//	movingVert = true;
				//	playerAccelVert = playerMoveForceVertical / playerMass;
				//}

				movingLeft = GLibHelper::KeyStates['A'];

				if (GLibHelper::KeyStates['W'])
					playerAccelVert = playerMoveForceVertical / playerMass;
				if (GLibHelper::KeyStates['S'])
					playerAccelVert = -1 * (playerMoveForceVertical / playerMass);

				movingRight = GLibHelper::KeyStates['D'];

				if (GLibHelper::KeyStates['D'])
				{
					int x = 5;
					x++;
				}
				
				if (movingLeft && movingRight)
					movingLeft, movingRight = false;

				GLib::Point2D playerCurrentPosition = playerPosition;

				if (playerPrevPosition.x == playerPosition.x && playerAccelHoriz > 0.0f)
				{
					if (movingLeft)
						playerPrevPosition.x = playerPosition.x + (playerAccelHoriz * 4.0f * deltaTime);
					if (movingRight)
						playerPrevPosition.x = playerPosition.x - (playerAccelHoriz * 4.0f * deltaTime);
				}
				if (playerPrevPosition.y == playerPosition.y && playerAccelVert > 0.0f)
				{

				}

				// use verlet
				float newX = playerPosition.x;
				float newY = playerPosition.y;
				if (playerAccelHoriz > 0.0f && movingRight && !movingLeft)
					newX = playerPosition.x + std::abs(playerPosition.x - playerPrevPosition.x) + (playerAccelHoriz * deltaTime * deltaTime);
				else if(playerAccelHoriz > 0.0f && movingLeft && !movingRight)
					newX = playerPosition.x - (std::abs(playerPosition.x - playerPrevPosition.x) + (playerAccelHoriz * deltaTime * deltaTime));
				//if (movingVert)
				//	newY = (verletMultiplyFactor * playerPosition.y) - playerPrevPosition.y + (playerAccelVert * deltaTime);

				playerPosition.x = newX;
				playerPosition.y = newY;

				
				// set previous to past current
				if(movingLeft || movingRight)
					playerPrevPosition = playerCurrentPosition;

				if (playerAccelHoriz > 0.00001f)
				{
					playerAccelHoriz /= 1.5f;
				}
				else
				{
					playerAccelHoriz = 0.0f;
					movingLeft = false;
					movingRight = false;
				}

				//if (verletMultiplyFactor > 1.0f)
				//	//verletMultiplyFactor -= dragFactor;
				//// set back to 0 if needed
				//if (verletMultiplyFactor <= 1.0f)
				//{
				//	//verletMultiplyFactor = 0.0f;
				//	movingHoriz = false;
				//	movingVert = false;
				//}

				// Tell GLib to render this sprite at our calculated location
				GLib::Sprites::RenderSprite(*pPlayerSprite, playerPosition, 0.0f);
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