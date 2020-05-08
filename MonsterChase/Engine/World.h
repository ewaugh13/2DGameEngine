#pragma once

#include "Actor.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

namespace Engine
{
	namespace World
	{
		void AddActorToWorld(SmartPtr<Actor> & i_NewActor);
		void AddActorToWorld(SmartPtr<Actor> && i_NewActor);
		bool RemoveActorFromWorld(WeakPtr<Actor> & i_Actor);
		void Tick(float i_DeltaTime);
		void ShutDown();
	}
}

