#include "CppUnitTest.h"

#include "ActorCreator.h"
#include "JobSystem.h"
#include "Collision.h"
#include "Collideable.h"
#include "PhysicsSystem.h"
#include "Timer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CollisionTests
{
	TEST_CLASS(CollisionTests)
	{
	public:

		TEST_METHOD(CollisionTest1)
		{
			using namespace Engine;

			JobSystem::CreateQueue("Default", 2);

			Physics::Init();
			Collision::Init();

			Timer * timer = new Timer();

			Engine::AutoResetEvent createActor1Event;
			Engine::AutoResetEvent createActor2Event;

			// create test actor1
			SmartPtr<Actor> smartPtrActor1;
			ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor1](SmartPtr<Actor>& i_Actor1)
			{
				smartPtrActor1 = i_Actor1;
				//DEBUG_PRINT("Actor loaded");
			}
			, &createActor1Event);

			// create test actor2
			SmartPtr<Actor> smartPtrActor2;
			ActorCreator::CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor2](SmartPtr<Actor>& i_Actor2)
			{
				smartPtrActor2 = i_Actor2;
				smartPtrActor2->SetPosition(Vector3(-140.0f, -100.0f, 0.0f));
				//DEBUG_PRINT("Actor loaded");
			}
			, &createActor2Event);

			createActor1Event.Wait();
			createActor2Event.Wait();

			float deltaTime = timer->DeltaTime();

			Physics::Tick(deltaTime);
			Collision::Tick(deltaTime);

			Physics::RigidBody * player1RigidBody = dynamic_cast<Physics::RigidBody*>(smartPtrActor1->GetComponent("rigidbody"));

			Collision::Collideable * player1Collideable = dynamic_cast<Collision::Collideable*>(smartPtrActor1->GetComponent("collideable"));
			Collision::Collideable * player2Collideable = dynamic_cast<Collision::Collideable*>(smartPtrActor2->GetComponent("collideable"));

			bool foundCollision = false;

			// detect collision between actor1 and actor2
			std::function<void(WeakPtr<Actor>&)> callbackActor1 = [&smartPtrActor2, &foundCollision](WeakPtr<Actor>& i_Actor1)
			{
				if (smartPtrActor2 == i_Actor1)
				{
					foundCollision = true;
				}
			};

			player1Collideable->SetCollisionCallback(callbackActor1);

			while (!foundCollision)
			{
				deltaTime = timer->DeltaTime();

				player1RigidBody->SetForces(Vector3(1.0f, 0.0f, 0.0f));

				Physics::Tick(deltaTime);
				Collision::Tick(deltaTime);

				smartPtrActor1->BeginUpdate(deltaTime);
				smartPtrActor2->BeginUpdate(deltaTime);

				smartPtrActor1->Update(deltaTime);
				smartPtrActor2->Update(deltaTime);

				smartPtrActor1->EndUpdate(deltaTime);
				smartPtrActor2->EndUpdate(deltaTime);
			}

			Assert::IsTrue(true);
		}
	};
}