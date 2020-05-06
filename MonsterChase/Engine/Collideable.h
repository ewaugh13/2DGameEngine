#pragma once

#include "Actor.h"
#include "ConsolePrint.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include <functional>

namespace Engine
{
	namespace Collision
	{
		class Collideable;

		// Axis Aligned Bounding Box (Hit Box)
		typedef struct AABB
		{
			Vector3 m_Center;
			Vector3 m_Extents;
		} AABB;

		typedef struct CollisionCheckData
		{
			SmartPtr<Actor> m_Actor;
			Matrix4	m_ActorToWorld;
			Matrix3	m_OrientationInWorld;
			Vector3	m_BBCenterInWorld;
		} CollisionCheckData;

		typedef struct CollisionPair
		{
			Collideable * m_pCollideables[2];
			float m_CollisionTime;
			Vector3 m_CollisionNormal;
		} CollisionPair;

		typedef std::function<void(WeakPtr<Actor>&)> CollisionCallback_t;
		void PrintCollide(WeakPtr<Actor> & i_Actor);

		class Collideable : public IActorComponent
		{

		public:
			Collideable(const SmartPtr<Actor> & i_Actor, const AABB & i_BoundingBox, CollisionCheckData i_CachedCheckData) :
				m_Actor(i_Actor), m_BoundingBox(i_BoundingBox), m_CollisionCallback(PrintCollide), m_CachedCheckData(i_CachedCheckData)
			{
			}

			Collideable(const Collideable & i_OtherCollideable);

			void Update(float i_DeltaTime);

			WeakPtr<Actor> GetActor() const { return m_Actor; }

			CollisionCheckData GetCachedCheckData() const { return m_CachedCheckData; }

			void SetCachedCheckData(CollisionCheckData i_CachedCheckData) { m_CachedCheckData = i_CachedCheckData; }

			AABB GetBoundingBox() const { return m_BoundingBox; }

			void SetCollisionCallback(const CollisionCallback_t & i_Callback) { m_CollisionCallback = i_Callback; }

		private:
			WeakPtr<Actor> m_Actor;
			AABB m_BoundingBox;
			CollisionCallback_t	m_CollisionCallback;
			CollisionCheckData m_CachedCheckData;
		};

		class CollideableDestructor : public ComponentDestructor
		{
		public:
			static void release(Collideable * i_ptr) { delete i_ptr; }
		};
	}
}