#include "PlayerMovement.h"

#include "ActorCreator.h"
#include "GLibHelpers.h"
#include "RigidBody.h"
#include "SmartPtr.h"

namespace GamePlay
{
	namespace PlayerMovement
	{
		using namespace Engine;

		// TODO: make more universal
		void operator<<(Vector3 & vec, nlohmann::json & json_obj)
		{
			assert(json_obj.is_array() && json_obj.size() == 3);

			vec.SetX(json_obj[0]);
			vec.SetY(json_obj[1]);
			vec.SetZ(json_obj[2]);
		}

		void AddPlayerMovement(SmartPtr<Actor> & i_Actor, nlohmann::json & i_PlayerMovementJSON)
		{
			using json = nlohmann::json;

			Vector3 playerSpeed = Vector3::Zero;
			playerSpeed << (i_PlayerMovementJSON["player_speed"]);

			if (i_Actor)
			{
				i_Actor->AddComponent("playermovement", new PlayerMovementComp(i_Actor, playerSpeed));
			}
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("playermovement", std::bind(AddPlayerMovement, _1, _2));
		}

		void ShutDown()
		{
			ActorCreator::DeregisterComponentCreator("playermovement");
		}

		PlayerMovementComp::PlayerMovementComp(const PlayerMovementComp & i_OtherPlayerMovement)
		{
			m_Actor = i_OtherPlayerMovement.m_Actor;
			m_PlayerSpeed = i_OtherPlayerMovement.m_PlayerSpeed;
		}

		void PlayerMovementComp::EndUpdate(float)
		{
			SmartPtr<Actor> actor = m_Actor.AcquireSmartPtr();
			if (actor)
			{
				Engine::Physics::RigidBody * playerRigidBodyComp = dynamic_cast<Physics::RigidBody*>(actor->GetComponent("rigidbody"));
				if (playerRigidBodyComp)
				{
					// moving left
					if (GLibHelper::KeyStates['A'] && !GLibHelper::KeyStates['D'])
						playerRigidBodyComp->SetXForce(m_PlayerSpeed.GetX() * -1);
					// moving right
					else if (!GLibHelper::KeyStates['A'] && GLibHelper::KeyStates['D'])
						playerRigidBodyComp->SetXForce(m_PlayerSpeed.GetX());

					// moving down
					if (GLibHelper::KeyStates['S'] && !GLibHelper::KeyStates['W'])
						playerRigidBodyComp->SetYForce(m_PlayerSpeed.GetY() * -1);
					// moving up
					else if (!GLibHelper::KeyStates['S'] && GLibHelper::KeyStates['W'])
						playerRigidBodyComp->SetYForce(m_PlayerSpeed.GetY());
				}
			}
		}
	}
}