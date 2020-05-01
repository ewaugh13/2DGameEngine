#pragma once

#include "RigidBody.h"

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace Physics
	{
		void AddRigidBody(const SmartPtr<Actor> & i_Actor, nlohmann::json & i_RigidBodyJSON);

		void Tick(float i_DeltaTime);

		void Init();
		void ShutDown();
	}
}

