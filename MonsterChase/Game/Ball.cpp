#include "Ball.h"

#include "ActorCreator.h"
#include "GLibHelpers.h"
#include "JobSystem.h"
#include "RigidBody.h"
#include "SmartPtr.h"

#include "GamePlay.h"

namespace GamePlay
{
	namespace Ball
	{
		using namespace Engine;

		void AddBall(SmartPtr<Actor> & i_Actor, nlohmann::json & i_BallJSON)
		{
			using json = nlohmann::json;

			assert(i_BallJSON["ball_x_speed"].is_number());
			assert(i_BallJSON["ball_y_speed"].is_number());
			assert(i_BallJSON["sleep_time_sec"].is_number());
			assert(i_BallJSON["left_border"].is_number());
			assert(i_BallJSON["right_border"].is_number());

			float ballXSpeed = i_BallJSON["ball_x_speed"];
			float ballYSpeed = i_BallJSON["ball_y_speed"];
			int sleepTimeSec = i_BallJSON["sleep_time_sec"];
			int leftBorder = i_BallJSON["left_border"];
			int rightBorder = i_BallJSON["right_border"];

			if (i_Actor)
				i_Actor->AddComponent("ball", new BallComp(i_Actor, ballXSpeed, ballYSpeed, sleepTimeSec, leftBorder, rightBorder));
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("ball", std::bind(AddBall, _1, _2));
		}

		void ShutDown()
		{
			ActorCreator::DeregisterComponentCreator("ball");
		}


		BallComp::BallComp(const BallComp & i_OtherBall)
		{
			m_Actor = i_OtherBall.m_Actor;
			m_LeftBorder = i_OtherBall.m_LeftBorder;
			m_RightBorder = i_OtherBall.m_RightBorder;
		}

		void BallComp::EndUpdate(float)
		{
			SmartPtr<Actor> actor = m_Actor.AcquireSmartPtr();
			if (actor)
			{
				Physics::RigidBody * ballRigidBodyComp = dynamic_cast<Physics::RigidBody*>(actor->GetComponent("rigidbody"));
				if (ballRigidBodyComp)
				{
					// check to see if we are out of bounds
					if (actor->GetPosition().GetX() < m_LeftBorder || actor->GetPosition().GetX() > m_RightBorder)
					{
						bool player1Scored = false;

						// add to player2 score
						if (actor->GetPosition().GetX() < m_LeftBorder)
							player1Scored = false;
						// add to player1 score
						else
							player1Scored = true;

						Vector3 zero = Vector3::Zero;
						actor->SetPosition(zero);
						ballRigidBodyComp->SetVelocity(zero);

						GamePlay::Pong::IncrementPlayerScore(player1Scored);

						// add job to set velocity of ball
						if (!Engine::JobSystem::ShutdownRequested())
						{
							Engine::JobSystem::RunJob("ActivateBall", [this, player1Scored]()
							{
								ActivateBall(m_SleepTimeSec, player1Scored);
							}, "Default");
						}
					}
				}
			}
		}

		void BallComp::ActivateBall(unsigned int i_IntervalMilliseconds, bool i_Player1Scored)
		{
			Sleep(i_IntervalMilliseconds * 1000);
			SmartPtr<Actor> actor = m_Actor.AcquireSmartPtr();
			if (actor)
			{
				Physics::RigidBody * ballRigidBodyComp = dynamic_cast<Physics::RigidBody*>(actor->GetComponent("rigidbody"));

				Vector3 newBallVelocity = Vector3::Zero;

				int yDirection = rand() % 2;
				if (i_Player1Scored)
				{
					if(yDirection == 0)
						newBallVelocity = Vector3(m_BallXSpeed * -1, m_BallYSpeed * -1, 0.0f);
					else
						newBallVelocity = Vector3(m_BallXSpeed * -1, m_BallYSpeed, 0.0f);
				}
				else
				{
					if (yDirection == 0)
						newBallVelocity = Vector3(m_BallXSpeed, m_BallYSpeed * -1, 0.0f);
					else
						newBallVelocity = Vector3(m_BallXSpeed, m_BallYSpeed, 0.0f);
				}

				ballRigidBodyComp->SetVelocity(newBallVelocity);
			}
		}
	}
}