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

	Timer * timer = new Timer();
	bool bQuit = false;

	GLib::Sprites::Sprite * pPlayerSprite = GLibHelper::CreateSprite("data\\SamusNeutral0.dds");
	GLib::Point2D playerPosition = { -180.0f, -100.0f };

	float playerMass = 500.0f;
	float playerMoveForceHoriz = 30.0f;
	float playerMoveForceVert = 30.0f;

	float dragFactor = 0.0001f;

	bool movingLeft = false, movingRight = false, movingDown = false, movingUp = false;

	float playerAccelHoriz = 0.0f, playerAccelVert = 0.0f;

	float playerVelocityHoriz = 0.0f, playerVelocityVert = 0.0f;
	float playerPrevVelocityHoriz = 0.0f, playerPrevVelocityVert = 0.0f;

	float playerMaxVelocityHoriz = 5.0f;
	float playerMaxVelocityVert = 5.0f;

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
				if (GLibHelper::KeyStates['A'] || GLibHelper::KeyStates['D'])
					playerAccelHoriz = playerMoveForceHoriz / playerMass;
				if (GLibHelper::KeyStates['W'] || GLibHelper::KeyStates['S'])
					playerAccelVert = playerMoveForceVert / playerMass;

				playerVelocityHoriz += (playerAccelHoriz * deltaTime);
				// if greater than max velocity set to max
				playerVelocityHoriz = playerVelocityHoriz > playerMaxVelocityHoriz ? playerMaxVelocityHoriz : playerVelocityHoriz;

				playerVelocityVert += (playerAccelVert * deltaTime);
				// if greater than max velocity set to max
				playerVelocityVert = playerVelocityVert > playerMaxVelocityVert ? playerMaxVelocityVert : playerVelocityVert;
				
				// set move left or right based on player input
				if(!movingLeft || movingRight)
					movingLeft = GLibHelper::KeyStates['A'];
				if(!movingRight || movingLeft)
					movingRight = GLibHelper::KeyStates['D'];
				// set move up or down based on player input
				if (!movingDown || movingUp)
					movingDown = GLibHelper::KeyStates['S'];
				if (!movingUp || movingDown)
					movingUp = GLibHelper::KeyStates['W'];
				
				// can't move left and right at the same time
				if (movingLeft && movingRight)
					movingLeft = false, movingRight = false;
				// can't move up and down at the same time
				if (movingDown && movingUp)
					movingLeft = false, movingRight = false;
				
				// use euler midpoint method move left or right
				if (playerAccelHoriz > 0.0f && movingRight && !movingLeft)
					playerPosition.x += ((playerPrevVelocityHoriz + playerVelocityHoriz) / 2.0f * deltaTime);
				else if (playerAccelHoriz > 0.0f && movingLeft && !movingRight)
					playerPosition.x -= ((playerPrevVelocityHoriz + playerVelocityHoriz) / 2.0f * deltaTime);
				// use euler midpoint method move down or up
				if (playerAccelVert > 0.0f && movingUp && !movingDown)
					playerPosition.y += ((playerPrevVelocityVert + playerVelocityVert) / 2.0f * deltaTime);
				else if (playerAccelVert > 0.0f && movingDown && !movingUp)
					playerPosition.y -= ((playerPrevVelocityVert + playerVelocityVert) / 2.0f * deltaTime);

				// set previous velocity for mid point
				playerPrevVelocityHoriz = playerVelocityHoriz;
				playerPrevVelocityVert = playerVelocityVert;

				// apply drag left and right movement
				if (playerVelocityHoriz > 0.0f)
					playerAccelHoriz -= dragFactor;
				else
				{
					playerAccelHoriz = 0.0f;
					movingLeft = false, movingRight = false;
				}

				// apply drag down and up movement
				if (playerVelocityVert > 0.0f)
					playerAccelVert -= dragFactor;
				else
				{
					playerAccelVert = 0.0f;
					movingDown = false, movingUp = false;
				}

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