#include "GamePlay.h"

#include "ActorCreator.h"
#include "GLib.h"
#include "GLibHelpers.h"
#include "JobSystem.h"
#include "Collision.h"
#include "Renderer.h"
#include "PhysicsSystem.h"
#include "Timer.h"
#include "World.h"

#include "PadleMovement.h"
#include "PlayerMovement.h"

namespace GamePlay
{
	void TestGameLoop()
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
			ActorCreator::CreateGameObjectAsync("..\\data\\LeftPadle.json", [&playerActor](SmartPtr<Actor>& i_Actor)
			{
				playerActor = i_Actor;
				//playerActor->SetZRotation(315.0f);
				DEBUG_PRINT("Player actor loaded");
			}
			, &createPlayerActorEvent);

			createPlayerActorEvent.Wait();
			World::AddActorToWorld(playerActor);

			SmartPtr<Actor> blockingActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\Ball.json", [&blockingActor](SmartPtr<Actor>& i_Actor)
			{
				blockingActor = i_Actor;
				DEBUG_PRINT("Blocking actor loaded");
			}
			, &createBlockingActorEvent);

			createBlockingActorEvent.Wait();
			World::AddActorToWorld(blockingActor);

			bool setOnce = true;

			do
			{
				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);

				if (!bQuit)
				{
					if (GLibHelper::KeyStates['Q'])
					{
						bQuit = true;

						continue;
					}

					float deltaTime = timer->DeltaTime();

					Physics::Tick(deltaTime);
					Collision::Tick(deltaTime);
					Renderer::Tick(deltaTime);

					if (setOnce)
					{
						Physics::RigidBody * actorRigidBody = dynamic_cast<Physics::RigidBody*>(blockingActor->GetComponent("rigidbody"));
						actorRigidBody->SetVelocity(Vector3(-2.0f, 0.0f, 0.0f));

						setOnce = false;
					}

					World::Tick(deltaTime);
				}
			} while (bQuit == false);
		}

		// Engine Components
		Physics::ShutDown();
		Collision::ShutDown();
		Renderer::ShutDown();

		// World shutdown
		World::ShutDown();

		// Gameplay Components
		PlayerMovement::ShutDown();

		Engine::JobSystem::RequestShutdown();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

	void Pong()
	{
		using namespace Engine;

		Engine::JobSystem::CreateQueue("Default", 2);

		// Engine Components
		Physics::Init();
		Collision::Init();
		Renderer::Init();

		// Gameplay Components
		PadleMovement::Init();

		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

		{
			Timer * timer = new Timer();
			bool bQuit = false;

			Engine::AutoResetEvent createLeftPadleEvent;
			Engine::AutoResetEvent createRightPadleEvent;
			Engine::AutoResetEvent createBallEvent;

			SmartPtr<Actor> rightPadleActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\RightPadle.json", [&rightPadleActor](SmartPtr<Actor>& i_Actor)
			{
				rightPadleActor = i_Actor;
				DEBUG_PRINT("Right padle loaded");
			}
			, &createRightPadleEvent);

			createRightPadleEvent.Wait();
			World::AddActorToWorld(rightPadleActor);

			SmartPtr<Actor> ballActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\Ball.json", [&ballActor](SmartPtr<Actor>& i_Actor)
			{
				ballActor = i_Actor;
				DEBUG_PRINT("Ball actor loaded");
			}
			, &createBallEvent);

			createBallEvent.Wait();
			World::AddActorToWorld(ballActor);

			SmartPtr<Actor> leftPadleActor;
			ActorCreator::CreateGameObjectAsync("..\\data\\LeftPadle.json", [&leftPadleActor](SmartPtr<Actor>& i_Actor)
			{
				leftPadleActor = i_Actor;
				DEBUG_PRINT("Left padle loaded");
			}
			, &createLeftPadleEvent);

			createLeftPadleEvent.Wait();
			World::AddActorToWorld(leftPadleActor);

			bool setOnce = true;

			do
			{
				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);

				if (!bQuit)
				{
					if (GLibHelper::KeyStates['Q'])
					{
						bQuit = true;

						continue;
					}

					float deltaTime = timer->DeltaTime();

					Physics::Tick(deltaTime);
					Collision::Tick(deltaTime);
					Renderer::Tick(deltaTime);

					if (setOnce)
					{
						Physics::RigidBody * actorRigidBody = dynamic_cast<Physics::RigidBody*>(ballActor->GetComponent("rigidbody"));
						actorRigidBody->SetVelocity(Vector3(-4.0f, -1.0f, 0.0f));

						setOnce = false;
					}

					World::Tick(deltaTime);
				}
			} while (bQuit == false);
		}

		// Engine Components
		Physics::ShutDown();
		Collision::ShutDown();
		Renderer::ShutDown();

		// World shutdown
		World::ShutDown();

		// Gameplay Components
		PadleMovement::ShutDown();

		Engine::JobSystem::RequestShutdown();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}
}
