#pragma once

#include "Actor.h"
#include "Collideable.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace Collision
	{
		void AddCollidable(SmartPtr<Actor> & i_Actor, nlohmann::json & i_CollideableJSON);

		bool FoundCollisionLastTick();

		void Tick(float i_DeltaTime);

		void Init();
		void ShutDown();
	}
}

