#include "GamePlay.h"

#include "ActorCreator.h"
#include "FloatFunctionLibrary.h"
#include "GLib.h"
#include "GLibHelpers.h"
#include "JobSystem.h"
#include "Collision.h"
#include "Renderer.h"
#include "PhysicsSystem.h"
#include "Timer.h"

#include "PlayerMovement.h"

#include <cmath> 

namespace GamePlay
{
	void GameLoop()
	{
		using namespace Engine;

		Engine::JobSystem::CreateQueue("Default", 2);

		// Engine Components
		Physics::Init();
		Collision::Init();
		Renderer::Init();

		// Gameplay Components
		PlayerMovement::Init();

		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

		{
			Timer * timer = new Timer();
			bool bQuit = false;

			Engine::AutoResetEvent createPlayerActorEvent;
			Engine::AutoResetEvent createBlockingActorEvent;

			SmartPtr<Actor> playerActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&playerActor](SmartPtr<Actor>& i_Actor)
			{
				playerActor = i_Actor;
				DEBUG_PRINT("Player actor loaded");
			}
			, &createPlayerActorEvent);

			createPlayerActorEvent.Wait();

			SmartPtr<Actor> blockingActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\Samus2.json", [&blockingActor](SmartPtr<Actor>& i_Actor)
			{
				blockingActor = i_Actor;
				DEBUG_PRINT("Blocking actor loaded");
			}
			, &createBlockingActorEvent);

			createBlockingActorEvent.Wait();

			do
			{
				float deltaTime = timer->DeltaTime();

				Physics::Tick(deltaTime);
				Collision::Tick(deltaTime);
				Renderer::Tick(deltaTime);

				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);

				if (!bQuit)
				{
					if (GLibHelper::KeyStates['Q'])
					{
						bQuit = true;

						continue;
					}

					// TODO: put all actors in a world reference
					playerActor->BeginUpdate(deltaTime);
					blockingActor->BeginUpdate(deltaTime);

					playerActor->Update(deltaTime);
					blockingActor->Update(deltaTime);

					// IMPORTANT: Tell GLib that we want to start rendering
					GLib::BeginRendering();
					// Tell GLib that we want to render some sprites
					GLib::Sprites::BeginRendering();

					playerActor->EndUpdate(deltaTime);
					blockingActor->EndUpdate(deltaTime);

					// Tell GLib we're done rendering sprites
					GLib::Sprites::EndRendering();
					// IMPORTANT: Tell GLib we're done rendering
					GLib::EndRendering();
				}
			} while (bQuit == false);
		}

		// Engine Components
		Physics::ShutDown();
		Collision::ShutDown();
		Renderer::ShutDown();

		// Gameplay Components
		PlayerMovement::Init();

		Engine::JobSystem::RequestShutdown();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}
}
