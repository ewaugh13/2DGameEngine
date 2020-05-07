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

#include "Ball.h" 
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

			//bool setOnce = true;

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

					//if (setOnce)
					//{
					//	Physics::RigidBody * actorRigidBody = dynamic_cast<Physics::RigidBody*>(blockingActor->GetComponent("rigidbody"));
					//	actorRigidBody->SetVelocity(Vector3(-2.0f, 0.0f, 0.0f));

					//	setOnce = false;
					//}

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

	namespace Pong
	{

		unsigned int Player1Score = 0;
		unsigned int Player2Score = 0;

		void IncrementPlayerScore(bool i_Player1Scored)
		{
			if (i_Player1Scored)
				Player1Score++;
			else
				Player2Score++;
		}

		void PongGameLoop()
		{
			using namespace Engine;

			Engine::JobSystem::CreateQueue("Default", 2);

			// Engine Components
			Physics::Init();
			Collision::Init();
			Renderer::Init();

			// Gameplay Components
			Ball::Init();
			PadleMovement::Init();

			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

			{
				Timer * timer = new Timer();
				bool bQuit = false;

				SmartPtr<Actor> rightPadleActor = ActorCreator::CreateGameObject("..\\data\\RightPadle.json");
				World::AddActorToWorld(rightPadleActor);

				SmartPtr<Actor> leftPadleActor = ActorCreator::CreateGameObject("..\\data\\LeftPadle.json");
				World::AddActorToWorld(leftPadleActor);

				SmartPtr<Actor> ballActor = ActorCreator::CreateGameObject("..\\data\\Ball.json");
				World::AddActorToWorld(ballActor);

				SmartPtr<Actor> topWallActor = ActorCreator::CreateGameObject("..\\data\\TopWall.json");
				World::AddActorToWorld(topWallActor);

				SmartPtr<Actor> bottomWallActor = ActorCreator::CreateGameObject("..\\data\\BottomWall.json");
				World::AddActorToWorld(bottomWallActor);

				bool setOnce = true;

				do
				{
					// IMPORTANT: We need to let GLib do it's thing. 
					GLib::Service(bQuit);

					if (!bQuit)
					{
						if (GLibHelper::KeyStates['Q'] || Player1Score > 9 || Player2Score > 9)
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
							Ball::BallComp * ballComp = dynamic_cast<Ball::BallComp*>(ballActor->GetComponent("ball"));
							// add job to set velocity of ball
							if (!Engine::JobSystem::ShutdownRequested())
							{
								Engine::JobSystem::RunJob("ActivateBall", [ballComp]()
								{
									ballComp->ActivateBall(ballComp->GetSleepTimeSec(), rand() % 2);
								}, "Default");
							}

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
			Ball::ShutDown();
			PadleMovement::ShutDown();

			Engine::JobSystem::RequestShutdown();

			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}
	}
}
