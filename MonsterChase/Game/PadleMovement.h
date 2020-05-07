#pragma once

#include "Actor.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

#include "../External/nlohmann/json.hpp"

namespace GamePlay
{
	namespace PadleMovement
	{
		void AddPadleMovement(SmartPtr<Engine::Actor> & i_Actor, nlohmann::json & i_PadleMovementJSON);
		void Init();
		void ShutDown();

		class PadleMovementComp : public Engine::IActorComponent
		{

		public:

			PadleMovementComp(const SmartPtr<Engine::Actor> & i_Actor, float i_PadleSpeed, char i_UpKey, char i_Downkey) :
				m_Actor(i_Actor), m_PadleSpeed(i_PadleSpeed), m_UpKey(i_UpKey), m_DownKey(i_Downkey)
			{
			}

			PadleMovementComp(const PadleMovementComp & i_OtherPadleMovement);

			void EndUpdate(float i_DeltaTime);

			WeakPtr<Engine::Actor> GetActor() const { return m_Actor; }

		private:

			WeakPtr<Engine::Actor> m_Actor;
			float m_PadleSpeed;
			char m_UpKey;
			char m_DownKey;
		};
	}
}

