#include "World.h"

#include "Collision.h"
#include "ScopeLock.h"

#include "GLib.h"

#include <DirectXColors.h>
#include <vector>

namespace Engine
{
	namespace World
	{
		std::vector<SmartPtr<Actor>> WorldActors;
		Mutex WorldActorsLock;

		void AddActorToWorld(SmartPtr<Actor> & i_NewActor)
		{
			ScopeLock Lock(WorldActorsLock);
			WorldActors.push_back(i_NewActor);
		}

		void AddActorToWorld(SmartPtr<Actor>&& i_NewActor)
		{
			ScopeLock Lock(WorldActorsLock);
			WorldActors.push_back(i_NewActor);
		}

		bool RemoveActorFromWorld(WeakPtr<Actor> & i_Actor)
		{
			SmartPtr<Actor> actor = i_Actor.AcquireSmartPtr();

			ScopeLock Lock(WorldActorsLock);

			// iterate through all actors and if found remove it from vector
			for (auto& iter : WorldActors)
			{
				if (iter == i_Actor)
				{
					if (iter != WorldActors.back())
						std::swap(iter, WorldActors.back());

					WorldActors.pop_back();
					return true;
				}
			}

			return false;
		}

		void Tick(float i_DeltaTime)
		{
			for (auto& iter : WorldActors)
			{
				iter->BeginUpdate(i_DeltaTime);
			}

			for (auto& iter : WorldActors)
			{
				iter->Update(i_DeltaTime);
			}

			Collision::ProcessFoundCollisions(i_DeltaTime);

			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			memcpy(&clearColor, DirectX::Colors::Black, sizeof(float[4]));
			GLib::BeginRendering(clearColor);
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();

			for (auto& iter : WorldActors)
			{
				iter->EndUpdate(i_DeltaTime);
			}

			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}

		void ShutDown()
		{
			WorldActors.clear();
			WorldActors.shrink_to_fit();
			WorldActors.~vector();
		}
	}
}