#pragma once

#include "RigidBody.h"

namespace MyEngine
{
	namespace Physics
	{
		// TODO: add json info here
		SmartPtr<RigidBody> AddRigidBodyActor(const SmartPtr<Actor> & i_Actor, const char * i_ScriptFilename);

		// Draw all sprites
		void Tick(float i_DeltaTime);

		// Clear all rigid bodies
		void ShutDown();
	}
}

