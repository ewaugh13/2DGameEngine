#pragma once

#include "Actor.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

#include "../External/nlohmann/json.hpp"

namespace GamePlay
{
	namespace PlayerMovement
	{
		void AddPlayerMovement(SmartPtr<Engine::Actor> & i_Actor, nlohmann::json & i_PlayerMovementJSON);
		void Init();
		void ShutDown();

		class PlayerMovementComp : public Engine::IActorComponent
		{

		public:

			PlayerMovementComp(const SmartPtr<Engine::Actor> & i_Actor, const Engine::Vector3 & i_PlayerSpeed) :
				m_Actor(i_Actor), m_PlayerSpeed(i_PlayerSpeed)
			{
			}

			PlayerMovementComp(const PlayerMovementComp & i_OtherPlayerMovement);

			void EndUpdate(float i_DeltaTime);

			WeakPtr<Engine::Actor> GetActor() const { return m_Actor; }

		private:

			WeakPtr<Engine::Actor> m_Actor;
			Engine::Vector3 m_PlayerSpeed;
		};
	}
}

