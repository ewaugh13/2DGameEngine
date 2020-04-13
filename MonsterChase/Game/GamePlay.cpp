#include "GamePlay.h"

#include "FloatFunctionLibrary.h"
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
	Vector3 playerPosition = Vector3(-180.0f, -100.0f, 0.0f);

	// TODO: put these all in a struct for a rigid body
	float playerMass = 500.0f;

	Vector3 playerMoveForceAmount = Vector3(30.0f, 30.0f, 0.0f);

	float dragFactor = 0.0001f;

	Vector3 playerForces = Vector3::Zero;
	Vector3 playerAccel = Vector3::Zero;

	Vector3 playerVelocity = Vector3::Zero;
	Vector3 playerPrevVelocity = Vector3::Zero;
	Vector3 playerMaxVelocity = Vector3(5.0f, 5.0f, 0.0f);

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
				// moving left
				if (GLibHelper::KeyStates['A'] && !GLibHelper::KeyStates['D'])
					playerForces.SetX(-1);
				// moving right
				else if (!GLibHelper::KeyStates['A'] && GLibHelper::KeyStates['D'])
					playerForces.SetX(1);

				// moving down
				if (GLibHelper::KeyStates['S'] && !GLibHelper::KeyStates['W'])
					playerForces.SetY(-1);
				// moving up
				else if (!GLibHelper::KeyStates['S'] && GLibHelper::KeyStates['W'])
					playerForces.SetY(1);

				playerAccel = playerForces * playerMoveForceAmount / playerMass;
				playerVelocity = playerVelocity + (playerAccel * deltaTime);

				if (playerVelocity.GetX() > playerMaxVelocity.GetX())
					playerVelocity.SetX(playerMaxVelocity.GetX());
				if (playerVelocity.GetY() > playerMaxVelocity.GetY())
					playerVelocity.SetY(playerMaxVelocity.GetY());

				playerPosition += (playerPrevVelocity + playerVelocity) / 2.0f * deltaTime;

				// set previous velocity for mid point
				playerPrevVelocity = playerVelocity;

				// apply drag left and right movement
				Vector3 dragForce = playerVelocity * playerVelocity * dragFactor;
				if (!FloatFunctionLibrary::AlmostEqualZeroCertain(playerVelocity.GetX(), 0.01f))
				{
					if (playerVelocity.GetX() > 0)
					{
						playerForces.SetX(playerForces.GetX() - dragForce.GetX());
						if (playerVelocity.GetX() < 0)
						{
							playerForces.SetX(0);
						}
					}
					else
					{
						playerForces.SetX(playerForces.GetX() + dragForce.GetX());
						if (playerVelocity.GetX() > 0)
						{
							playerForces.SetX(0);
						}
					}
				}
				else
				{
					playerForces.SetX(0);
				}
				
				// TODO: change this to be gravity based
				if (!FloatFunctionLibrary::AlmostEqualZeroCertain(playerVelocity.GetY(), 0.001f))
				{
					if (playerVelocity.GetY() > 0)
					{
						playerForces.SetY(playerForces.GetY() - dragForce.GetY());
						if (playerVelocity.GetY() < 0)
						{
							playerForces.SetY(0);
						}
					}
					else
					{
						playerForces.SetY(playerForces.GetY() + dragForce.GetY());
						if (playerVelocity.GetY() > 0)
						{
							playerForces.SetY(0);
						}
					}
				}
				else
					playerForces.SetY(0);

				// Tell GLib to render this sprite at our calculated location
				GLib::Sprites::RenderSprite(*pPlayerSprite, { playerPosition.GetX(), playerPosition.GetY() }, 0.0f);
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