#include "GamePlay.h"
#include "Timer.h"

#include "GLib.h"
#include "GLibHelpers.h"

// does the main gameplay loop
void GamePlay::GameLoop()
{
	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

	GLib::Sprites::Sprite * pPlayerSprite = GLibHelper::CreateSprite("data\\SamusNeutral0.dds");
	float playerMoveDist = 5.0f;
	GLib::Point2D playerPosition = { -180.0f, -100.0f };

	Timer * timer = new Timer();

	bool bQuit = false;

	do
	{
		float dt = timer->DeltaTime();

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
				if (GLibHelper::KeyStates['A'])
					playerPosition.x -= playerMoveDist * dt;
				if (GLibHelper::KeyStates['W'])
					playerPosition.y += playerMoveDist * dt;
				if (GLibHelper::KeyStates['S'])
					playerPosition.y -= playerMoveDist * dt;
				if (GLibHelper::KeyStates['D'])
					playerPosition.x += playerMoveDist * dt;

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