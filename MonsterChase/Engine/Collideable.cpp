#include "Collideable.h"

#include "Collision.h"

#include <assert.h>

namespace Engine
{
	namespace Collision
	{
		void PrintCollide(WeakPtr<Actor>& i_Actor)
		{
			SmartPtr<Actor> actor = i_Actor.AcquireSmartPtr();
			if (actor)
			{
				DEBUG_PRINT("hit actor");
			}
		}

		Collideable::Collideable(const Collideable & i_OtherCollideable)
		{
			m_Actor = i_OtherCollideable.m_Actor;
			m_BoundingBox = i_OtherCollideable.m_BoundingBox;
			m_CollisionCallback = i_OtherCollideable.m_CollisionCallback;
			m_CachedCheckData = i_OtherCollideable.m_CachedCheckData;
		}

		void Collideable::Update(float i_DeltaTime)
		{
			bool bFoundCollision = false;

			if (!Collision::GetCachedCheckCalledThisTick())
				Collision::CacheCollisionCheckData();

			CollisionPair foundCollision;

			if (FindCollision(this, i_DeltaTime, foundCollision))
			{
				foundCollision.m_pCollideables;
				assert(foundCollision.m_pCollideables[0]);
				assert(foundCollision.m_pCollideables[1]);

				if (foundCollision.m_pCollideables[0]->m_CollisionCallback)
					foundCollision.m_pCollideables[0]->m_CollisionCallback(foundCollision.m_pCollideables[1]->m_Actor);

				if (foundCollision.m_pCollideables[1]->m_CollisionCallback)
					foundCollision.m_pCollideables[1]->m_CollisionCallback(foundCollision.m_pCollideables[0]->m_Actor);

				bFoundCollision = true;
			}

			if(bFoundCollision)
				Collision::SetCollisionLastTick(bFoundCollision);
		}
	}
}
