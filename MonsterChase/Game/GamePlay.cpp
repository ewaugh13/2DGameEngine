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

#include <cmath> 

// does the main gameplay loop
void GamePlay::GameLoop()
{
	using namespace Engine;

	Engine::JobSystem::CreateQueue("Default", 2);

	Physics::Init();
	Collision::Init();
	Renderer::Init();

	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

	{
		Timer * timer = new Timer();
		bool bQuit = false;

		Engine::AutoResetEvent createActor1Event;
		Engine::AutoResetEvent createActor2Event;

		// create test actor1
		SmartPtr<Actor> smartPtrActor1;
		ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor1](SmartPtr<Actor>& i_Actor1)
		{
			smartPtrActor1 = i_Actor1;
			//DEBUG_PRINT("Actor loaded");
		}
		, &createActor1Event);

		// create test actor2
		SmartPtr<Actor> smartPtrActor2;
		ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor2](SmartPtr<Actor>& i_Actor2)
		{
			smartPtrActor2 = i_Actor2;
			smartPtrActor2->SetPosition(Vector3(0.0f, -100.0f, 0.0f));
			//DEBUG_PRINT("Actor loaded");
		}
		, &createActor2Event);

		createActor1Event.Wait();
		createActor2Event.Wait();

		Engine::AutoResetEvent createActorEvent;

		SmartPtr<Actor> smartPtrActor;
		ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor](SmartPtr<Actor>& i_Actor)
		{
			smartPtrActor = i_Actor;
			//DEBUG_PRINT("Actor loaded");
		}
		, &createActorEvent);

		createActorEvent.Wait();

		float deltaTime = timer->DeltaTime();

		// TODO: maybe should be begin event instead of tick
		// first tick 
		Physics::Tick(deltaTime);
		Collision::Tick(deltaTime);
		Renderer::Tick(deltaTime);

		Physics::RigidBody * playerRigidBodyComp = dynamic_cast<Physics::RigidBody*>(smartPtrActor->GetComponent("rigidbody"));

		do
		{
			deltaTime = timer->DeltaTime();

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

				if (playerRigidBodyComp)
				{
					// TODO move to player input component
					// player input

					// moving left
					if (GLibHelper::KeyStates['A'] && !GLibHelper::KeyStates['D'])
						playerRigidBodyComp->SetForces(Vector3(-1, 0, 0));
					// moving right
					else if (!GLibHelper::KeyStates['A'] && GLibHelper::KeyStates['D'])
						playerRigidBodyComp->SetForces(Vector3(1, 0, 0));

					// moving down
					if (GLibHelper::KeyStates['S'] && !GLibHelper::KeyStates['W'])
						playerRigidBodyComp->SetForces(Vector3(0, -1, 0));
					// moving up
					else if (!GLibHelper::KeyStates['S'] && GLibHelper::KeyStates['W'])
						playerRigidBodyComp->SetForces(Vector3(0, 1, 0));
				}

				// TODO: put all actors in a world reference
				smartPtrActor->BeginUpdate(deltaTime);
				smartPtrActor->Update(deltaTime);
				smartPtrActor->EndUpdate(deltaTime);
			}
		} while (bQuit == false);
	}

	Physics::ShutDown();
	Collision::ShutDown();
	Renderer::ShutDown();

	Engine::JobSystem::RequestShutdown();

	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}