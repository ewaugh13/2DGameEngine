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
//#include "PlayerMovement.h"

namespace GamePlay
{
	namespace Pong
	{

		unsigned int Player1Score = 0;
		unsigned int Player2Score = 0;

		bool bQuit = false;

		void IncrementPlayerScore(bool i_Player1Scored)
		{
			if (i_Player1Scored)
				Player1Score++;
			else
				Player2Score++;
		}

		bool GameActive()
		{
			return !bQuit;
		}

		void PongGameLoop()
		{
			using namespace Engine;

			JobSystem::CreateQueue("Default", 2);

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
				SmartPtr<Timer> timer = SmartPtr<Timer>(new Timer());

				World::AddActorToWorld(ActorCreator::CreateGameObject("..\\data\\RightPadle.json"));
				World::AddActorToWorld(ActorCreator::CreateGameObject("..\\data\\LeftPadle.json"));

				SmartPtr<Actor> ballActor = ActorCreator::CreateGameObject("..\\data\\Ball.json");
				World::AddActorToWorld(ballActor);

				World::AddActorToWorld(ActorCreator::CreateGameObject("..\\data\\TopWall.json"));
				World::AddActorToWorld(ActorCreator::CreateGameObject("..\\data\\BottomWall.json"));

				bool setOnce = true;

				do
				{
					// IMPORTANT: We need to let GLib do it's thing. 
					GLib::Service(bQuit);

					if (!bQuit)
					{
						if (GLibHelper::KeyStates['Q'])// || Player1Score > 9 || Player2Score > 9)
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

			//// Engine Components
			Physics::ShutDown();
			Collision::ShutDown();
			Renderer::ShutDown();

			// World shutdown
			World::ShutDown();

			// Gameplay Components
			Ball::ShutDown();
			PadleMovement::ShutDown();

			ActorCreator::ShutDown();

			JobSystem::RequestShutdown();
		}
	}
}
