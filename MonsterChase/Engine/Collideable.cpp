#include "Collideable.h"

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
			// TODO logic for update
		}
	}
}
