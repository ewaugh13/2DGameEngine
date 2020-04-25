#include "RigidBody.h"

#include "FloatFunctionLibrary.h"

namespace Engine
{
	namespace Physics
	{
		RigidBody::RigidBody(const RigidBody & i_OtherBody)
		{
			m_Actor = i_OtherBody.m_Actor;
			m_Forces = i_OtherBody.m_Forces;
			m_MovementForces = i_OtherBody.m_MovementForces;
			m_Acceleration = i_OtherBody.m_Acceleration;
			m_Velocity = i_OtherBody.m_Velocity;
			m_MaxVelocity = i_OtherBody.m_MaxVelocity;
			m_Mass = i_OtherBody.m_Mass;
			m_Kd = i_OtherBody.m_Kd;
		}

		void RigidBody::BeginUpdate(float i_DeltaTime)
		{
			SmartPtr<Actor> currentActor = m_Actor.AcquireSmartPtr();

			// if there is an actor and a sprite draw it
			if (currentActor)
			{
				m_Acceleration = m_Forces * m_MovementForces / m_Mass;

				Vector3 nextVelocity = m_Velocity + (m_Acceleration * i_DeltaTime);

				if (nextVelocity.GetX() > 0)
				{
					if (nextVelocity.GetX() > m_MaxVelocity.GetX())
						nextVelocity.SetX(m_MaxVelocity.GetX());
				}
				else
				{
					if (nextVelocity.GetX() < -m_MaxVelocity.GetX())
						nextVelocity.SetX(-m_MaxVelocity.GetX());
				}
				if (nextVelocity.GetY() > 0)
				{
					if (nextVelocity.GetY() > m_MaxVelocity.GetY())
						nextVelocity.SetY(m_MaxVelocity.GetY());
				}
				else
				{
					if (nextVelocity.GetY() < -m_MaxVelocity.GetY())
						nextVelocity.SetY(-m_MaxVelocity.GetY());
				}

				Vector3 averageVelocity = (nextVelocity + m_Velocity) / 2.0f;
				currentActor->SetPosition(currentActor->GetPosition() + averageVelocity * i_DeltaTime);

				// apply drag left and right movement
				Vector3 dragForce = m_Velocity * m_Velocity * m_Kd;
				if((m_Velocity.GetX() < 0 && nextVelocity.GetX() > 0) || (m_Velocity.GetX() > 0 && nextVelocity.GetX() < 0))
					m_Forces.SetX(0);
				else
					m_Forces.SetX(m_Forces.GetX() + (m_Velocity.GetX() > 0 ? -dragForce.GetX() : dragForce.GetX()));

				// TODO: change this to be gravity based
				if ((m_Velocity.GetY() < 0 && nextVelocity.GetY() > 0) || (m_Velocity.GetY() > 0 && nextVelocity.GetY() < 0))
					m_Forces.SetY(0);
				else
					m_Forces.SetY(m_Forces.GetY() + (m_Velocity.GetY() > 0 ? -dragForce.GetY() : dragForce.GetY()));

				// set previous velocity for mid point
				m_Velocity = nextVelocity;
			}
		}
	}
}
