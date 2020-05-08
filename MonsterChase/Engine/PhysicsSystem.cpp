#include "PhysicsSystem.h"

#include "ActorCreator.h"
#include "Destructors.h"
#include "FloatFunctionLibrary.h"
#include "LoadFile.h"
#include "ScopeLock.h"

#include <assert.h>

namespace Engine
{
	namespace Physics
	{
		void operator<<(Vector3 & vec, nlohmann::json & json_obj)
		{
			assert(json_obj.is_array() && json_obj.size() == 3);

			vec.SetX(json_obj[0]);
			vec.SetY(json_obj[1]);
			vec.SetZ(json_obj[2]);
		}

		bool bShutdown = false;

		std::vector<SmartPtr<RigidBody, RigidBodyDestructor>> AllRigidBodies;

		std::vector<SmartPtr<RigidBody, RigidBodyDestructor>> NewRigidBodies;
		Engine::Mutex NewRigidBodiesMutex;

		void AddRigidBody(const SmartPtr<Actor> & i_Actor, nlohmann::json & i_RigidBodyJSON)
		{
			if (!bShutdown)
			{
				using json = nlohmann::json;

				assert(i_RigidBodyJSON["mass"].is_number_float());
				assert(i_RigidBodyJSON["kd"].is_number_float());

				float mass = i_RigidBodyJSON["mass"];
				float kd = i_RigidBodyJSON["kd"];

				Vector3 movementForces = Vector3::Zero;
				movementForces << (i_RigidBodyJSON["movement_forces"]);

				Vector3 movementVelocity = Vector3::Zero;
				movementVelocity << (i_RigidBodyJSON["max_velocity"]);

				SmartPtr<RigidBody, RigidBodyDestructor> newRigidBodyActor(new RigidBody(i_Actor, movementForces, movementVelocity, mass, kd));

				{
					ScopeLock Lock(NewRigidBodiesMutex);
					NewRigidBodies.push_back(newRigidBodyActor);
				}
			}
		}

		void CheckForNewRigidBodies()
		{
			ScopeLock Lock(NewRigidBodiesMutex);
			for (std::vector<SmartPtr<RigidBody, RigidBodyDestructor>>::iterator iter = NewRigidBodies.begin(); iter != NewRigidBodies.end(); iter++)
			{
				SmartPtr<RigidBody, RigidBodyDestructor> rigidBody = *iter;

				SmartPtr<Actor> currentActor = rigidBody->GetActor().AcquireSmartPtr();
				if (currentActor)
				{
					currentActor->AddComponent("rigidbody", rigidBody.operator->());
				}

				AllRigidBodies.push_back(*iter);
			}

			NewRigidBodies.clear();
		}

		void Tick(float i_DeltaTime)
		{
			CheckForNewRigidBodies();
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("rigidbody", std::bind(AddRigidBody, _1, _2));
		}

		void ShutDown()
		{
			bShutdown = true;

			AllRigidBodies.clear();
			AllRigidBodies.shrink_to_fit();
			AllRigidBodies.~vector();

			ActorCreator::DeregisterComponentCreator("rigidbody");

			{
				ScopeLock Lock(NewRigidBodiesMutex);
				NewRigidBodies.clear();
				NewRigidBodies.shrink_to_fit();
				NewRigidBodies.~vector();
			}
		}
	}
}