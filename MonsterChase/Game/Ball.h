#pragma once

#include "Actor.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

#include "../External/nlohmann/json.hpp"

namespace GamePlay
{
	namespace Ball
	{
		void AddBall(SmartPtr<Engine::Actor> & i_Actor, nlohmann::json & i_BallJSON);
		void Init();
		void ShutDown();

		class BallComp : public Engine::IActorComponent
		{

		public:

			BallComp(const SmartPtr<Engine::Actor> & i_Actor, float i_BallXSpeed, float i_BallYSpeed, int i_SleepTimeSec, int i_LeftBorder, int i_RightBorder) :
				m_Actor(i_Actor), m_BallXSpeed(i_BallXSpeed), m_BallYSpeed(i_BallYSpeed),
				m_SleepTimeSec(i_SleepTimeSec), m_LeftBorder(i_LeftBorder), m_RightBorder(i_RightBorder)
			{
			}

			BallComp(const BallComp & i_OtherBall);

			void ActivateBall(unsigned int i_IntervalMilliseconds, bool i_Player1Scored);

			void EndUpdate(float i_DeltaTime);

			WeakPtr<Engine::Actor> GetActor() const { return m_Actor; }

			int GetSleepTimeSec() const { return m_SleepTimeSec; }

		private:

			WeakPtr<Engine::Actor> m_Actor;
			float m_BallXSpeed;
			float m_BallYSpeed;
			int m_SleepTimeSec;
			int m_LeftBorder;
			int m_RightBorder;
		};
	}
}
