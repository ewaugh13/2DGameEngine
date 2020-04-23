#pragma once

#include "Actor.h"
#include "Vector3.h"
#include "WeakPtr.h"

namespace Engine
{
	namespace Physics
	{
		typedef struct RigidBody
		{
			WeakPtr<Actor> m_Actor;
			Vector3 m_Forces;
			// the force applied when moving
			Vector3 m_MovementForces;
			Vector3 m_Acceleration;
			Vector3 m_Velocity;
			// the max velocity of the actor
			Vector3 m_MaxVelocity;
			float m_Mass;
			float m_Kd;

			RigidBody(const SmartPtr<Actor> & i_Actor, const Vector3 & i_MovementForces, const Vector3 & i_MaxVelocity, float i_Mass, float i_Kd) :
				m_Actor(i_Actor), m_Forces(Vector3::Zero), m_MovementForces(i_MovementForces), m_Acceleration(Vector3::Zero),
				m_Velocity(Vector3::Zero), m_MaxVelocity(i_MaxVelocity), m_Mass(i_Mass), m_Kd(i_Kd)
			{
			}

		public:

			void SetForces(Vector3 & i_NewForce) { m_Forces = i_NewForce; }
			void SetForces(Vector3 && i_NewForce) { m_Forces = i_NewForce; }

		} RigidBody;
	}
}