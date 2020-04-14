#include "PhysicsSystem.h"

#include "Actor.h"
#include "FloatFunctionLibrary.h"

namespace Physics
{
	std::vector<SmartPtr<RigidBody>> ActorRigidBodies;

	SmartPtr<RigidBody> AddRigidBodyActor(const SmartPtr<Actor> & i_Actor, const Vector3 & i_MovementForces, const Vector3 & i_MaxVelocity, float i_Mass, float i_Kd)
	{
		SmartPtr<RigidBody> newRigidBodyActor(new RigidBody(i_Actor, i_MovementForces, i_MaxVelocity, i_Mass, i_Kd));
		ActorRigidBodies.push_back(newRigidBodyActor);

		return newRigidBodyActor;
	}

	void Tick(float i_DeltaTime)
	{
		for (std::vector<SmartPtr<RigidBody>>::iterator iter = ActorRigidBodies.begin(); iter != ActorRigidBodies.end(); iter++)
		{
			SmartPtr<RigidBody> currRigid = *iter;

			SmartPtr<Actor> currentActor = currRigid->m_Actor.AcquireSmartPtr();

			// if there is an actor and a sprite draw it
			if (currentActor)
			{
				currRigid->m_Acceleration = currRigid->m_Forces * currRigid->m_MovementForces / currRigid->m_Mass;

				Vector3 nextVelocity = currRigid->m_Velocity + (currRigid->m_Acceleration * i_DeltaTime);

				if (nextVelocity.GetX() > currRigid->m_MaxVelocity.GetX())
					nextVelocity.SetX(currRigid->m_MaxVelocity.GetX());
				if (nextVelocity.GetY() > currRigid->m_MaxVelocity.GetY())
					nextVelocity.SetY(currRigid->m_MaxVelocity.GetY());

				Vector3 averageVelocity = (nextVelocity + currRigid->m_Velocity) / 2.0f;
				currentActor->SetPosition(currentActor->GetPosition() + averageVelocity * i_DeltaTime);

				// set previous velocity for mid point
				currRigid->m_Velocity = nextVelocity;

				// apply drag left and right movement
				Vector3 dragForce = currRigid->m_Velocity * currRigid->m_Velocity * currRigid->m_Kd;
				if (!FloatFunctionLibrary::AlmostEqualZeroCertain(currRigid->m_Velocity.GetX(), 0.01f))
					currRigid->m_Forces.SetX(currRigid->m_Forces.GetX() + (currRigid->m_Velocity.GetX() > 0 ? -dragForce.GetX() : dragForce.GetX()));
				else
					currRigid->m_Forces.SetX(0);

				// TODO: change this to be gravity based
				if (!FloatFunctionLibrary::AlmostEqualZeroCertain(currRigid->m_Velocity.GetY(), 0.01f))
					currRigid->m_Forces.SetY(currRigid->m_Forces.GetY() + (currRigid->m_Velocity.GetY() > 0 ? -dragForce.GetY() : dragForce.GetY()));
				else
					currRigid->m_Forces.SetY(0);
			}
		}
	}

	void ShutDown()
	{
		ActorRigidBodies.clear();
		ActorRigidBodies.shrink_to_fit();
	}
}