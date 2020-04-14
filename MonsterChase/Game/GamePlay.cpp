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
	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(GLibHelper::KeyCallback);

	{
		Timer * timer = new Timer();
		bool bQuit = false;

		SmartPtr<Actor> smartPtrActor = SmartPtr<Actor>(new Actor("Samus", Vector3(-180.0f, -100.0f, 0.0f)));

		SmartPtr<Renderer::Renderable> playerSprite = Renderer::AddRenderable(smartPtrActor, Renderer::SpriteSmartPtr(GLibHelper::CreateSprite("data\\SamusNeutral0.dds")));
		SmartPtr<Physics::RigidBody> playerRigidBody = Physics::AddRigidBodyActor(smartPtrActor, Vector3(30.0f, 30.0f, 0.0f), Vector3(5.0f, 5.0f, 0.0f), 500.0f, 0.001f);

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