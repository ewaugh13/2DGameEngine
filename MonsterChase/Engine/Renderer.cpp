#include "Renderer.h"

#include "ActorCreator.h"
#include "GLibHelpers.h"
#include "LoadFile.h"
#include "ScopeLock.h"

#include <assert.h>
#include <vector>

namespace Engine
{
	namespace Renderer
	{
		bool bShutdown = false;

		std::vector<SmartPtr<Renderable, RenderableDestructor>> AllRenderables;

		std::vector<SmartPtr<Renderable, RenderableDestructor>> NewRenderables;
		Engine::Mutex NewRenderablesMutex;

		void AddRenderable(const SmartPtr<Actor> & i_Actor, nlohmann::json & i_RenderableJSON)
		{
			if (!bShutdown)
			{
				using json = nlohmann::json;

				assert(i_RenderableJSON["sprite"].is_string());

				std::string spriteFilePath = i_RenderableJSON["sprite"];

				SpriteSmartPtr sprite = SpriteSmartPtr(GLibHelper::CreateSprite(spriteFilePath.c_str()));

				SmartPtr<Renderable, RenderableDestructor> newRenderableActor(new Renderable(i_Actor, sprite));

				{
					ScopeLock Lock(NewRenderablesMutex);
					NewRenderables.push_back(newRenderableActor);
				}
			}
		}

		void CheckForNewRenderables()
		{
			ScopeLock Lock(NewRenderablesMutex);
			for (std::vector<SmartPtr<Renderable, RenderableDestructor>>::iterator iter = NewRenderables.begin(); iter != NewRenderables.end(); iter++)
			{
				SmartPtr<Renderable, RenderableDestructor> renderable = *iter;

				SmartPtr<Actor> currentActor = renderable->GetActor().AcquireSmartPtr();
				if (currentActor)
				{
					currentActor->AddComponent("renderable", renderable.operator->());
				}

				AllRenderables.push_back(*iter);
			}

			NewRenderables.clear();
		}

		void Tick(float i_DeltaTime)
		{
			CheckForNewRenderables();
		}

		void Init()
		{
			using namespace std::placeholders;

			ActorCreator::RegisterComponentCreator("renderable", std::bind(AddRenderable, _1, _2));
		}

		void ShutDown()
		{
			bShutdown = true;

			AllRenderables.clear();
			AllRenderables.shrink_to_fit();
			AllRenderables.~vector();

			ActorCreator::DeregisterComponentCreator("renderable");

			{
				ScopeLock Lock(NewRenderablesMutex);
				NewRenderables.clear();
				NewRenderables.shrink_to_fit();
				NewRenderables.~vector();
			}
		}
	}
}
