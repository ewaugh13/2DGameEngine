#pragma once

#include "Actor.h"
#include "Collideable.h"

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace Collision
	{
		void AddCollidable(SmartPtr<Actor> & i_Actor, nlohmann::json & i_CollideableJSON);

		void AddFoundCollision(CollisionPair & i_FoundCollision);
		void ProcessFoundCollisions(float i_DeltaTime);

		bool GetCachedCheckCalledThisTick();
		void SetCachedCheckCalledThisTick(bool i_bCachedCheckCalledThisTick);

		bool FoundCollisionLastTick();
		void SetCollisionLastTick(bool i_bFoundCollisionThisTick);

		void Tick(float i_DeltaTime);

		bool FindCollision(Collideable * i_CurrentCollideable, float i_DeltaTime, CollisionPair & o_FoundCollisionPair);
		void CacheCollisionCheckData();

		void Init();
		void ShutDown();
	}
}

