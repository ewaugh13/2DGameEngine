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

		void SetCollisionLastTick(bool i_bFoundCollisionThisTick);
		bool FoundCollisionLastTick();

		void Tick(float i_DeltaTime);

		bool FindCollision(Collideable * i_CurrentCollideable, float i_DeltaTime, CollisionPair & o_FoundCollisionPair);
		void CacheCollisionCheckData();

		void Init();
		void ShutDown();
	}
}

