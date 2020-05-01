#include "Collision.h"

#include "ActorCreator.h"
#include "LoadFile.h"
#include "ScopeLock.h"

#include <assert.h>
#include <vector>

namespace Engine
{
	namespace Collision
	{
		// TODO: make more universal
		void operator<<(Vector3 & vec, nlohmann::json & json_obj)
		{
			assert(json_obj.is_array() && json_obj.size() == 2);

			vec.SetX(json_obj[0]);
			vec.SetY(json_obj[1]);
		}

		bool bShutdown = false;
		bool bFoundCollisionThisTick = false;

		std::vector<SmartPtr<Collideable, CollideableDestructor>> AllCollideables;

		std::vector<SmartPtr<Collideable, CollideableDestructor>> NewCollideables;
		Engine::Mutex NewCollideablesMutex;

		void AddCollidable(SmartPtr<Actor> & i_Actor, nlohmann::json & i_CollideableJSON)
		{
			if (!bShutdown)
			{
				using json = nlohmann::json;

				Vector3 center = Vector3::Zero;
				center << i_CollideableJSON["center"];

				Vector3 extents = Vector3::Zero;
				extents << i_CollideableJSON["extents"];

				AABB collisionBox = AABB({ center, extents });

				// TODO figure out setting callback
				SmartPtr<Collideable, CollideableDestructor> newCollideableActor(new Collideable(i_Actor, collisionBox, CollisionCheckData()));

				{
					ScopeLock Lock(NewCollideablesMutex);
					NewCollideables.push_back(newCollideableActor);
				}
			}
		}

		bool FoundCollisionLastTick()
		{
			return bFoundCollisionThisTick;
		}

		void CheckForNewCollideables()
		{
			ScopeLock Lock(NewCollideablesMutex);
			for (std::vector<SmartPtr<Collideable, CollideableDestructor>>::iterator iter = NewCollideables.begin(); iter != NewCollideables.end(); iter++)
			{
				SmartPtr<Collideable, CollideableDestructor> collideable = *iter;

				SmartPtr<Actor> currentActor = collideable->GetActor().AcquireSmartPtr();
				if (currentActor)
				{
					currentActor->AddComponent("collideable", collideable.operator->());
				}

				AllCollideables.push_back(*iter);
			}

			NewCollideables.clear();
		}

		void Tick(float i_DeltaTime)
		{
			// TODO figure out how to make collision this tick work with Update call
			bFoundCollisionThisTick = false;
			CheckForNewCollideables();
		}

		void Init()
		{
			using namespace std::placeholders;

			RegisterComponentCreator("collideable", std::bind(AddCollidable, _1, _2));
		}

		void ShutDown()
		{
			bShutdown = true;

			AllCollideables.clear();
			AllCollideables.shrink_to_fit();

			DeregisterComponentCreator("collideable");

			{
				ScopeLock Lock(NewCollideablesMutex);
				AllCollideables.clear();
				AllCollideables.shrink_to_fit();
			}
		}
	}
}