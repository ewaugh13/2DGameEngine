#pragma once

#include "Actor.h"
#include "Vector3.h"
#include "WeakPtr.h"

namespace Engine
{
	namespace Physics
	{
		class RigidBody : public IActorComponent
		{

		public:

			RigidBody(const SmartPtr<Actor> & i_Actor, const Vector3 & i_MovementForces, const Vector3 & i_MaxVelocity, float i_Mass, float i_Kd) :
				m_Actor(i_Actor), m_Forces(Vector3::Zero), m_MovementForces(i_MovementForces), m_Acceleration(Vector3::Zero),
				m_Velocity(Vector3::Zero), m_MaxVelocity(i_MaxVelocity), m_Mass(i_Mass), m_Kd(i_Kd)
			{
			}

			RigidBody(const RigidBody & i_OtherBody);

			void BeginUpdate(float i_DeltaTime);

			WeakPtr<Actor> GetActor() const { return m_Actor; }

			Vector3 GetVelocity() const { return m_Velocity; }
			void SetVelocity(Vector3 & i_Velocity) { m_Velocity = i_Velocity; }

			void SetMaxVelocity(Vector3 & i_NewMaxVelocity) { m_MaxVelocity = i_NewMaxVelocity; }

			Vector3 GetForces() const { return m_Forces; }

			void SetXForce(float i_NewXForce) { m_Forces.SetX(i_NewXForce); }
			void SetYForce(float i_NewYForce) { m_Forces.SetY(i_NewYForce); }

			void SetForces(Vector3 & i_NewForce) { m_Forces = i_NewForce; }

		private:

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
		};

		class RigidBodyDestructor : public ComponentDestructor
		{
		public:
			static void release(RigidBody * i_ptr)
			{
				SmartPtr<Actor> actor = i_ptr->GetActor().AcquireSmartPtr();
				if (actor)
					actor->RemoveComponent("rigidbody");

				delete i_ptr;
			}
		};
	}
}