#include "GamePlay.h"

#include "FloatFunctionLibrary.h"
#include "GLib.h"
#include "GLibHelpers.h"
#include "Renderable.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsSystem.h"
#include "Timer.h"

#include <cmath> 

// does the main gameplay loop
void GamePlay::GameLoop()
{
	using namespace MyEngine;

	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

	{
		Timer * timer = new Timer();
		bool bQuit = false;

		SmartPtr<Actor> smartPtrActor = Actor::CreateActor("data\\Samus.json");

		SmartPtr<Renderer::Renderable> playerSprite = Renderer::AddRenderable(smartPtrActor, "data\\Samus.json");
		SmartPtr<Physics::RigidBody> playerRigidBody = Physics::AddRigidBodyActor(smartPtrActor, "data\\Samus.json");

		do
		{
			float deltaTime = timer->DeltaTime();

			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				if (GLibHelper::KeyStates['Q'])
				{
					bQuit = true;

					continue;
				}

				if (playerRigidBody)
				{
					// player input
					// moving left
					if (GLibHelper::KeyStates['A'] && !GLibHelper::KeyStates['D'])
						playerRigidBody->SetHorizontalForce((-1));
					// moving right
					else if (!GLibHelper::KeyStates['A'] && GLibHelper::KeyStates['D'])
						playerRigidBody->SetHorizontalForce((1));

					// moving down
					if (GLibHelper::KeyStates['S'] && !GLibHelper::KeyStates['W'])
						playerRigidBody->SetVerticalForce((-1));
					// moving up
					else if (!GLibHelper::KeyStates['S'] && GLibHelper::KeyStates['W'])
						playerRigidBody->SetVerticalForce((1));

					Physics::Tick(deltaTime);
				}

				// if first sprite was loaded
				if (playerSprite)
				{
					Renderer::Draw(deltaTime);
				}
			}
		} while (bQuit == false);
	}

	Physics::ShutDown();
	Renderer::ShutDown();

	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}