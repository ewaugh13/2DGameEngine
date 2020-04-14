#pragma once

#include "RigidBody.h"

namespace Physics
{
	// TODO: add json info here
	SmartPtr<RigidBody> AddRigidBodyActor(const SmartPtr<Actor> & i_Actor, const Vector3 & i_MovementForces, const Vector3 & i_MaxVelocity, float i_Mass, float i_Kd);

	// Draw all sprites
	void Tick(float i_DeltaTime);

	// Clear all rigid bodies
	void ShutDown();
}

