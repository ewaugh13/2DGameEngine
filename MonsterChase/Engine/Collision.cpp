#include "Collision.h"

#include "ActorCreator.h"
#include "LoadFile.h"
#include "RigidBody.h"
#include "ScopeLock.h"

#include <assert.h>
#include <vector>

namespace Engine
{
	namespace Collision
	{
		void operator<<(Vector3 & vec, nlohmann::json & json_obj)
		{
			assert(json_obj.is_array() && json_obj.size() == 2);

			vec.SetX(json_obj[0]);
			vec.SetY(json_obj[1]);
		}

		bool bShutdown = false;
		bool bFoundCollisionThisTick = false;
		bool bCachedCheckCalledThisTick = false;

		std::vector<SmartPtr<Collideable, CollideableDestructor>> AllCollideables;

		std::vector<SmartPtr<Collideable, CollideableDestructor>> NewCollideables;
		Engine::Mutex NewCollideablesMutex;

		std::vector<CollisionPair> FoundCollisions;

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

				CollisionCheckData checkData = CollisionCheckData();
				checkData.m_Actor = i_Actor;
				SmartPtr<Collideable, CollideableDestructor> newCollideableActor(new Collideable(i_Actor, collisionBox, checkData));

				{
					ScopeLock Lock(NewCollideablesMutex);
					NewCollideables.push_back(newCollideableActor);
				}
			}
		}

		void AddFoundCollision(CollisionPair & i_FoundCollision)
		{
			FoundCollisions.push_back(i_FoundCollision);
		}

		void ProcessFoundCollisions(float i_DeltaTime)
		{
			if (FoundCollisions.size() > 0 && i_DeltaTime > 0)
			{
				std::map<unsigned int, CollisionPair> earliestCollisions;
				float earliestCollisionTime = i_DeltaTime;
				for (unsigned int i = 0; i < FoundCollisions.size(); i++)
				{
					CollisionPair foundCollisionPair = FoundCollisions[i];
					if (foundCollisionPair.m_CollisionTime < earliestCollisionTime)
					{
						earliestCollisions.clear();
						earliestCollisionTime = foundCollisionPair.m_CollisionTime;
						earliestCollisions.insert({ i, foundCollisionPair });
					}
					else if (FloatFunctionLibrary::AlmostEqualRelativeAndAbs(earliestCollisionTime, foundCollisionPair.m_CollisionTime, 0.000000001f))
						earliestCollisions.insert({ i, foundCollisionPair });
				}

				int i = 0;
				// iterate through all earliest collisions at this time step
				for (std::map<unsigned int, CollisionPair>::iterator iter = earliestCollisions.begin(); iter != earliestCollisions.end(); iter++)
				{
					CollisionPair collisionPair = iter->second;
					// if we found a collison that needs the response resolved
					if (collisionPair.m_CollisionTime != i_DeltaTime && earliestCollisions.begin() != earliestCollisions.end())
					{
						FoundCollisions.erase(FoundCollisions.begin() + iter->first - i);
						i++;

						SmartPtr<Actor> actor = collisionPair.m_pCollideables[0]->GetActor().AcquireSmartPtr();

						// if the actors are valid get the rigid bodies and relfect their velocites by the normal
						if (actor)
						{
							// used to cancel out an existing forces on the rigid body
							Vector3 zero = Vector3::Zero;

							Physics::RigidBody * actorRigidBody = dynamic_cast<Physics::RigidBody*>(actor->GetComponent("rigidbody"));

							Vector3 actorVel = actorRigidBody->GetVelocity();
							Vector3 actorReflectVel = Vector3::Zero;

							// based on the normal direction find the reflected velocity
							float normalDirection = Vector3(1, 1, 0).Dot(collisionPair.m_CollisionNormal);
							if (normalDirection < 0)
							{
								actorReflectVel = actorVel -
									(collisionPair.m_CollisionNormal * actorVel.Dot(collisionPair.m_CollisionNormal)) * 2;
							}
							else
							{
								actorReflectVel = actorVel +
									(collisionPair.m_CollisionNormal * actorVel.Dot(collisionPair.m_CollisionNormal)) * 2;
							}
							actorRigidBody->SetVelocity(actorReflectVel);
							actorRigidBody->SetForces(zero);
						}
					}
				}
			
				std::vector<CollisionPair> remainingCollisions = FoundCollisions;
				FoundCollisions.shrink_to_fit();
				FoundCollisions.clear();

				if (remainingCollisions.size() > 0)
				{
					// tick all remaining collision pairs to the point in time when the earliest collision occured
					for (std::vector<CollisionPair>::iterator iter = remainingCollisions.begin(); iter != remainingCollisions.end(); iter++)
					{
						CollisionPair remainCollision = *iter;

						bool bFoundCollision = false;

						CollisionPair foundCollision;

						FindCollision(remainCollision.m_pCollideables[0], earliestCollisionTime, foundCollision);
					}

					// recompute the collision check data
					CacheCollisionCheckData();

					// do the remaining tick while actually tracking collisions now
					for (std::vector<CollisionPair>::iterator iter = remainingCollisions.begin(); iter != remainingCollisions.end(); iter++)
					{
						CollisionPair remainCollision = *iter;

						bool bFoundCollision = false;

						CollisionPair foundCollision;

						if (FindCollision(remainCollision.m_pCollideables[0], i_DeltaTime - earliestCollisionTime, foundCollision))
						{
							assert(foundCollision.m_pCollideables[0]);
							assert(foundCollision.m_pCollideables[1]);

							bFoundCollision = true;
						}

						if (bFoundCollision)
						{
							FoundCollisions.push_back(foundCollision);
						}
					}

					// process newly found collisions
					if (FoundCollisions.size() > 0)
					{
						ProcessFoundCollisions(i_DeltaTime - earliestCollisionTime);
					}
				}
			}
		}

		bool GetCachedCheckCalledThisTick()
		{
			return bCachedCheckCalledThisTick;
		}

		void SetCachedCheckCalledThisTick(bool i_bCachedCheckCalledThisTick)
		{
			bCachedCheckCalledThisTick = i_bCachedCheckCalledThisTick;
		}

		bool FoundCollisionLastTick()
		{
			return bFoundCollisionThisTick;
		}

		void SetCollisionLastTick(bool i_bFoundCollisionThisTick)
		{
			bFoundCollisionThisTick = i_bFoundCollisionThisTick;
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
			CheckForNewCollideables();

			FoundCollisions.clear();

			bFoundCollisionThisTick = false;
			bCachedCheckCalledThisTick = false;
		}

		bool CheckCollision2D(const Collideable & i_Collideable1, const Collideable & i_Collideable2, float i_DeltaTime, float & o_TimeCollision, Vector3 & o_CollisionNormal);
		bool DetectCrossTimes(float i_Center, float i_Extent, float i_Point, float i_TravelAlongAxis, float& o_TimeEntered, float & o_TimeExited);

		bool FindCollision(Collideable * i_CurrentCollideable, float i_DeltaTime, CollisionPair & o_FoundCollisionPair)
		{
			bool bFoundCollision = false;

			const size_t collideableCount = AllCollideables.size();

			if (collideableCount > 1)
			{
				for (size_t i = 0; i < collideableCount; i++)
				{
					if (i_CurrentCollideable != AllCollideables[i].operator->())
					{
						float timeCollision = 0.0f;
						Vector3 collisionNormal = Vector3::Zero;
						if (CheckCollision2D(*i_CurrentCollideable, *AllCollideables[i], i_DeltaTime, timeCollision, collisionNormal))
						{
							// if we find any earlier collisions we want to use that as the relevant one
							if (!bFoundCollision || (bFoundCollision && (timeCollision < o_FoundCollisionPair.m_CollisionTime)))
							{
								o_FoundCollisionPair.m_pCollideables[0] = i_CurrentCollideable;
								o_FoundCollisionPair.m_pCollideables[1] = AllCollideables[i].operator->();
								o_FoundCollisionPair.m_CollisionTime = timeCollision;
								o_FoundCollisionPair.m_CollisionNormal = collisionNormal;

								bFoundCollision = true;
							}
						}
					}
				}
			}

			return bFoundCollision;
		}

		void CacheCollisionCheckData()
		{
			bCachedCheckCalledThisTick = true;

			size_t collideableCount = AllCollideables.size();
			for (size_t i = 0; i < collideableCount;)
			{
				SmartPtr<Collideable, CollideableDestructor> currCollideable = AllCollideables[i];

				CollisionCheckData collisionData = currCollideable->GetCachedCheckData();

				if (collisionData.m_Actor)
				{
					collisionData.m_OrientationInWorld = Matrix3::CreateZRotationColVecFromDegrees(collisionData.m_Actor->GetZRotation());
					Matrix4 objectRot = Matrix4::CreateZRotationColVecFromDegrees(collisionData.m_Actor->GetZRotation());
					Matrix4 objectTrans = Matrix4::CreateTranslationColVec(collisionData.m_Actor->GetPosition());
					collisionData.m_ActorToWorld = objectTrans * objectRot;
					collisionData.m_BBCenterInWorld = collisionData.m_ActorToWorld.TransformPointColVec(currCollideable->GetBoundingBox().m_Center);

					currCollideable->SetCachedCheckData(collisionData);

					++i;
				}
				else
				{
					if (i < (collideableCount - 1))
						AllCollideables[i] = std::move(AllCollideables.back());

					AllCollideables.pop_back();
					--collideableCount;
				}
			}

			assert(collideableCount == AllCollideables.size());
		}

		bool CheckCollision2D(const Collideable & i_Collideable1, const Collideable & i_Collideable2, float i_DeltaTime, float & o_TimeCollision, Vector3 & o_CollisionNormal)
		{
			SmartPtr<Actor> actor1 = i_Collideable1.GetCachedCheckData().m_Actor;
			SmartPtr<Actor> actor2 = i_Collideable2.GetCachedCheckData().m_Actor;

			CollisionCheckData checkDataActor1 = i_Collideable1.GetCachedCheckData();
			CollisionCheckData checkDataActor2 = i_Collideable2.GetCachedCheckData();

			float timeEntered = 0.0f;
			float timeExited = 1.0f;

			// check both axes

			// check Actor2 against actor1's coordinate system

			// Actor2 vs Actor1 relative travel
			Vector3 actor2Travel = (actor2->GetVelocity() - actor1->GetVelocity()) * i_DeltaTime;

			// Actor1 X Axis
			{
				// M_WorldToA = M_AToWorld^-1 (Inverse)
				// M_AToB = M_WorldToB * M_AToWorld
				Matrix4 mActor2ToActor1 = checkDataActor1.m_ActorToWorld.GetInverse() * checkDataActor2.m_ActorToWorld;

				Vector4 actor2ExtentsXInActor1 = mActor2ToActor1 * Vector4(i_Collideable2.GetBoundingBox().m_Extents.GetX(), 0.0f, 0.0f, 0.0f);
				Vector4 actor2ExtentsYInActor1 = mActor2ToActor1 * Vector4(0.0f, i_Collideable2.GetBoundingBox().m_Extents.GetY(), 0.0f, 0.0f);

				float actor2ProjectionOntoActor1_x = fabs(actor2ExtentsXInActor1.GetX()) + fabs(actor2ExtentsYInActor1.GetX());

				Vector4 actor2CenterInActor1 = mActor2ToActor1 * Vector4(i_Collideable2.GetBoundingBox().m_Center, 1.0f);

				Vector3 actor1XAxisInWorld = checkDataActor1.m_OrientationInWorld.GetCol(0).Normalized();

				float actor2TravelAlongXAxis = actor2Travel.Dot(actor1XAxisInWorld);

				float axisEntered = 0.0f;
				float axisExited = 1.0f;

				float actor1ExpandedExtents_x = i_Collideable1.GetBoundingBox().m_Extents.GetX() + actor2ProjectionOntoActor1_x;
				float actor1Center_x = i_Collideable1.GetBoundingBox().m_Center.GetX();
				if (!DetectCrossTimes(actor1Center_x, actor1ExpandedExtents_x, actor2CenterInActor1.GetX(), actor2TravelAlongXAxis, axisEntered, axisExited))
					return false;

				Vector3 actor1Vel = actor1->GetVelocity();
				Vector3 actor2Vel = actor2->GetVelocity();

				if (axisEntered > timeEntered)
				{
					timeEntered = axisEntered;
					// if actor1 is to the left
					if (checkDataActor1.m_BBCenterInWorld.GetX() < checkDataActor2.m_BBCenterInWorld.GetX())
					{
						// heading right colliding into actor2 
						if (actor1->GetVelocity().GetX() > 0)
							o_CollisionNormal = actor1XAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
						// heading left colliding into actor2 
						else
							o_CollisionNormal = actor1XAxisInWorld;
					}
					// if actor1 is to the right
					else
					{
						// heading right colliding into actor2 
						if (actor1->GetVelocity().GetX() > 0)
							o_CollisionNormal = actor1XAxisInWorld;
						// heading left colliding into actor2 
						else
							o_CollisionNormal = actor1XAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
					}
				}
				if (axisExited < timeExited)
					timeExited = axisExited;
			}

			// Actor1 Y Axis
			{
				Matrix4 mActor2ToActor1 = checkDataActor1.m_ActorToWorld.GetInverse() * checkDataActor2.m_ActorToWorld;

				Vector4 actor2ExtentsXInActor1 = mActor2ToActor1 * Vector4(i_Collideable2.GetBoundingBox().m_Extents.GetX(), 0.0f, 0.0f, 0.0f);
				Vector4 actor2ExtentsYInActor1 = mActor2ToActor1 * Vector4(0.0f, i_Collideable2.GetBoundingBox().m_Extents.GetY(), 0.0f, 0.0f);

				float actor2ProjectionOntoActor1_y = fabs(actor2ExtentsXInActor1.GetY()) + fabs(actor2ExtentsYInActor1.GetY());

				Vector4 actor2CenterInActor1 = mActor2ToActor1 * Vector4(i_Collideable2.GetBoundingBox().m_Center, 1.0f);

				Vector3 actor1YAxisInWorld = checkDataActor1.m_OrientationInWorld.GetCol(1).Normalized();
				float actor2TravelAlongYAxis = actor2Travel.Dot(actor1YAxisInWorld);

				float axisEntered = 0.0f;
				float axisExited = 1.0f;

				float actor1ExpandedExtents_y = i_Collideable1.GetBoundingBox().m_Extents.GetY() + actor2ProjectionOntoActor1_y;
				float actor1Center_y = i_Collideable1.GetBoundingBox().m_Center.GetY();

				if (!DetectCrossTimes(actor1Center_y, actor1ExpandedExtents_y, actor2CenterInActor1.GetY(), actor2TravelAlongYAxis, axisEntered, axisExited))
					return false;

				if (axisEntered > timeEntered)
				{
					timeEntered = axisEntered;
					// if actor1 is to the left
					if (checkDataActor1.m_BBCenterInWorld.GetY() < checkDataActor2.m_BBCenterInWorld.GetY())
					{
						// heading right colliding into actor2 
						if (actor1->GetVelocity().GetY() > 0)
							o_CollisionNormal = actor1YAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
						// heading left colliding into actor2 
						else
							o_CollisionNormal = actor1YAxisInWorld;
					}
					// if actor1 is to the right
					else
					{
						// heading right colliding into actor2 
						if (actor1->GetVelocity().GetY() > 0)
							o_CollisionNormal = actor1YAxisInWorld;
						// heading left colliding into actor2 
						else
							o_CollisionNormal = actor1YAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
					}
				}
				if (axisExited < timeExited)
					timeExited = axisExited;
			}

			// check Actor1 against actor2's coordinate system

			// Actor1 vs Actor2 relative velocity
			Vector3 actor1Travel = (actor1->GetVelocity() - actor2->GetVelocity()) * i_DeltaTime;

			// Actor2 X Axis
			{
				Matrix4 mActor1ToActor2 = checkDataActor2.m_ActorToWorld.GetInverse() * checkDataActor1.m_ActorToWorld;

				Vector4 actor1ExtentsXInActor2 = mActor1ToActor2 * Vector4(i_Collideable1.GetBoundingBox().m_Extents.GetX(), 0.0f, 0.0f, 0.0f);
				Vector4 actor1ExtentsYInActor2 = mActor1ToActor2 * Vector4(0.0f, i_Collideable1.GetBoundingBox().m_Extents.GetY(), 0.0f, 0.0f);

				float actor1ProjectionOntoActor2_x = fabs(actor1ExtentsXInActor2.GetX()) + fabs(actor1ExtentsYInActor2.GetX());

				Vector4 actor1CenterInActor2 = mActor1ToActor2 * Vector4(i_Collideable1.GetBoundingBox().m_Center, 1.0f);

				Vector3 actor2XAxisInWorld = checkDataActor2.m_OrientationInWorld.GetCol(0).Normalized();
				float actor1TravelAlongXAxis = actor1Travel.Dot(actor2XAxisInWorld);

				float axisEntered = 0.0f;
				float axisExited = 1.0f;

				float actor2ExpandedExtents_x = i_Collideable2.GetBoundingBox().m_Extents.GetX() + actor1ProjectionOntoActor2_x;
				float actor2Center_x = i_Collideable2.GetBoundingBox().m_Center.GetX();

				if (!DetectCrossTimes(actor2Center_x, actor2ExpandedExtents_x, actor1CenterInActor2.GetX(), actor1TravelAlongXAxis, axisEntered, axisExited))
					return false;

				if (axisEntered > timeEntered)
				{
					timeEntered = axisEntered;
					// if actor2 is to the left
					if (checkDataActor2.m_BBCenterInWorld.GetX() < checkDataActor1.m_BBCenterInWorld.GetX())
					{
						// heading right colliding into actor1
						if (actor2->GetVelocity().GetX() > 0)
							o_CollisionNormal = actor2XAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
						// heading left colliding into actor1 
						else
							o_CollisionNormal = actor2XAxisInWorld;
					}
					// if actor2 is to the right
					else
					{
						// heading right colliding into actor1 
						if (actor2->GetVelocity().GetX() > 0)
							o_CollisionNormal = actor2XAxisInWorld;
						// heading left colliding into actor1 
						else
							o_CollisionNormal = actor2XAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
					}
				}
				if (axisExited < timeExited)
					timeExited = axisExited;
			}

			// Actor2 Y Axis
			{
				Matrix4 mActor1ToActor2 = checkDataActor2.m_ActorToWorld.GetInverse() * checkDataActor1.m_ActorToWorld;

				Vector4 actor1ExtentsXInActor2 = mActor1ToActor2 * Vector4(i_Collideable1.GetBoundingBox().m_Extents.GetX(), 0.0f, 0.0f, 0.0f);
				Vector4 actor1ExtentsYInActor2 = mActor1ToActor2 * Vector4(0.0f, i_Collideable1.GetBoundingBox().m_Extents.GetY(), 0.0f, 0.0f);

				float actor1ProjectionOntoActor2_y = fabs(actor1ExtentsXInActor2.GetY()) + fabs(actor1ExtentsYInActor2.GetY());

				Vector4 actor1CenterInActor2 = mActor1ToActor2 * Vector4(i_Collideable1.GetBoundingBox().m_Center, 1.0f);

				Vector3 actor2YAxisInWorld = checkDataActor2.m_OrientationInWorld.GetCol(1).Normalized();
				float actor1TravelAlongYAxis = actor1Travel.Dot(actor2YAxisInWorld);

				float axisEntered = 0.0f;
				float axisExited = 1.0f;

				float actor2ExpandedExtents_y = i_Collideable2.GetBoundingBox().m_Extents.GetY() + actor1ProjectionOntoActor2_y;
				float actor2Center_y = i_Collideable2.GetBoundingBox().m_Center.GetY();

				if (!DetectCrossTimes(actor2Center_y, actor2ExpandedExtents_y, actor1CenterInActor2.GetY(), actor1TravelAlongYAxis, axisEntered, axisExited))
					return false;

				if (axisEntered > timeEntered)
				{
					timeEntered = axisEntered;
					// if actor2 is to the left
					if (checkDataActor2.m_BBCenterInWorld.GetY() < checkDataActor1.m_BBCenterInWorld.GetY())
					{
						// heading right colliding into actor1 
						if (actor2->GetVelocity().GetY() > 0)
							o_CollisionNormal = actor2YAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
						// heading left colliding into actor1
						else
							o_CollisionNormal = actor2YAxisInWorld;
					}
					// if actor2 is to the right
					else
					{
						// heading right colliding into actor1 
						if (actor2->GetVelocity().GetY() > 0)
							o_CollisionNormal = actor2YAxisInWorld;
						// heading left colliding into actor1 
						else
							o_CollisionNormal = actor2YAxisInWorld * Matrix3::CreateZRotationColVecFromDegrees(180.0f);
					}
				}
				if (axisExited < timeExited)
					timeExited = axisExited;
			}

			if (timeEntered == 0.0f && timeExited != 1.0f)
				o_TimeCollision = (1.0f - timeExited) * i_DeltaTime;
			else if (timeExited == 1.0f && timeEntered != 0.0f)
				o_TimeCollision = timeEntered * i_DeltaTime;
			else
				o_TimeCollision = fabs(timeEntered - timeExited) * i_DeltaTime;
			return timeEntered < timeExited;
		}

		bool DetectCrossTimes(float i_Center, float i_Extent, float i_Point, float i_TravelAlongAxis, float & o_TimeEntered, float & o_TimeExited)
		{
			assert(i_Extent > 0.0f);

			float i_Start = i_Center - i_Extent;
			float i_End = i_Center + i_Extent;

			// if we aren't moving at all do standard calculation of point vs start and end
			if (FloatFunctionLibrary::AlmostEqualZeroCertain(i_TravelAlongAxis))
			{
				if ((i_Point < i_Start) || (i_Point > i_End))
					return false;
				else
				{
					o_TimeEntered = 0.0f;
					o_TimeExited = 1.0f;
					return true;
				}
			}

			// calculate when we will enter and when we will leave
			o_TimeEntered = (i_Start - i_Point) / i_TravelAlongAxis;
			o_TimeExited = (i_End - i_Point) / i_TravelAlongAxis;

			if (o_TimeEntered > o_TimeExited)
			{
				float temp = o_TimeEntered;
				o_TimeEntered = o_TimeExited;
				o_TimeExited = temp;
			}

			return !((o_TimeEntered >= 1.0f) || (o_TimeExited <= 0.0f));
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("collideable", std::bind(AddCollidable, _1, _2));
		}

		void ShutDown()
		{
			bShutdown = true;

			AllCollideables.clear();
			AllCollideables.shrink_to_fit();

			ActorCreator::DeregisterComponentCreator("collideable");

			{
				ScopeLock Lock(NewCollideablesMutex);
				AllCollideables.clear();
				AllCollideables.shrink_to_fit();
			}
		}
	}
}