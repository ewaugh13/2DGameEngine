#include "PadleMovement.h"

#include "ActorCreator.h"
#include "GLibHelpers.h"
#include "RigidBody.h"
#include "SmartPtr.h"

namespace GamePlay
{
	namespace PadleMovement
	{
		using namespace Engine;

		void AddPadleMovement(SmartPtr<Actor> & i_Actor, nlohmann::json & i_PadleMovementJSON)
		{
			using json = nlohmann::json;

			assert(i_PadleMovementJSON["padle_speed"].is_number_float());
			assert(i_PadleMovementJSON["up_key"].is_string());
			assert(i_PadleMovementJSON["down_key"].is_string());

			float padleSpeed = i_PadleMovementJSON["padle_speed"];

			// get the up key string and grab first char
			std::string upKeyString = i_PadleMovementJSON["up_key"];
			char upKeyChar = upKeyString.c_str()[0];

			// get the down key string and grab first char
			std::string downKeyString = i_PadleMovementJSON["down_key"];
			char downKeyChar = downKeyString.c_str()[0];

			if (i_Actor)
			{
				i_Actor->AddComponent("padlemovement", new PadleMovementComp(i_Actor, padleSpeed, upKeyChar, downKeyChar));
			}
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("padlemovement", std::bind(AddPadleMovement, _1, _2));
		}

		void ShutDown()
		{
			ActorCreator::DeregisterComponentCreator("padlemovement");
		}

		PadleMovementComp::PadleMovementComp(const PadleMovementComp & i_OtherPadleMovement)
		{
			m_Actor = i_OtherPadleMovement.m_Actor;
			m_PadleSpeed = i_OtherPadleMovement.m_PadleSpeed;
		}

		void PadleMovementComp::EndUpdate(float)
		{
			SmartPtr<Actor> actor = m_Actor.AcquireSmartPtr();
			if (actor)
			{
				Engine::Physics::RigidBody * PadleRigidBodyComp = dynamic_cast<Physics::RigidBody*>(actor->GetComponent("rigidbody"));
				if (PadleRigidBodyComp)
				{
					// moving down
					if (GLibHelper::KeyStates[m_DownKey] && !GLibHelper::KeyStates[m_UpKey])
						PadleRigidBodyComp->SetYForce(m_PadleSpeed * -1);
					// moving up
					else if (!GLibHelper::KeyStates[m_DownKey] && GLibHelper::KeyStates[m_UpKey])
						PadleRigidBodyComp->SetYForce(m_PadleSpeed);
				}
			}
		}
	}
}