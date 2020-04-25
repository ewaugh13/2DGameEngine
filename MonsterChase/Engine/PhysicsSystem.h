#pragma once

#include "RigidBody.h"

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace Physics
	{
		void AddRigidBodyActor(const SmartPtr<Actor> & i_Actor, nlohmann::json & i_RigidBodyJSON);

		void Tick(float i_DeltaTime);

		void CheckForNewRigidBodies();

		void Init();
		void ShutDown();
	}
}

