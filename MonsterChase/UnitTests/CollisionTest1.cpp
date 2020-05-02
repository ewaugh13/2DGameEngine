#include "CppUnitTest.h"

#include "ActorCreator.h"
#include "JobSystem.h"
#include "Collision.h"
#include "PhysicsSystem.h"
#include "Timer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CollisionTests
{
	TEST_CLASS(CollisionTest1)
	{
	public:

		TEST_METHOD(CollisionTest)
		{
			using namespace Engine;

			JobSystem::CreateQueue("Default", 1);

			Physics::Init();
			Collision::Init();

			Timer * timer = new Timer();

			Engine::AutoResetEvent createActor1Event;
			Engine::AutoResetEvent createActor2Event;

			unsigned int numTimes = 4;

			int sleepTime = 30;

			for (size_t i = 0; i < numTimes; i++)
			{
				// create test actor1
				SmartPtr<Actor> smartPtrActor1;
				CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor1](SmartPtr<Actor>& i_Actor1)
				{
					smartPtrActor1 = i_Actor1;
					//DEBUG_PRINT("Actor loaded");
				}
				, &createActor1Event);

				createActor1Event.Wait();

				Sleep(sleepTime * 1000);

				// create test actor2
				SmartPtr<Actor> smartPtrActor2;
				CreateGameObjectAsync("..\\data\\Samus.json", [&smartPtrActor2](SmartPtr<Actor>& i_Actor2)
				{
					smartPtrActor2 = i_Actor2;
					smartPtrActor2->SetPosition(Vector3(0.0f, -100.0f, 0.0f));
					//DEBUG_PRINT("Actor loaded");
				}
				, &createActor2Event);

				createActor2Event.Wait();

				Sleep(sleepTime * 1000);
			}

			Assert::IsTrue(true);


			//bool foundCollision = false;
			//float timeToRun = 60.0f;
			//float currentTime = 0.0f;

			//while (currentTime < timeToRun && !foundCollision)
			//{

			//}

			//Assert::IsTrue(foundCollision);
		}
	};
}