#include "Renderer.h"

#include <vector>

namespace Renderer
{
	std::vector<SmartPtr<Renderable>> Renderables;

	SmartPtr<Renderable> Renderer::AddRenderable(const SmartPtr<Actor>& i_Actor, SpriteSmartPtr i_Sprite)
	{
		SmartPtr<Renderable> newRenderableActor(new Renderable(i_Actor, i_Sprite));
		Renderables.push_back(newRenderableActor);

		return newRenderableActor;
	}

	void Renderer::Draw(float i_DeltaTime)
	{
		// IMPORTANT: Tell GLib that we want to start rendering
		GLib::BeginRendering();
		// Tell GLib that we want to render some sprites
		GLib::Sprites::BeginRendering();

		for (std::vector<SmartPtr<Renderable>>::iterator iter = Renderables.begin(); iter != Renderables.end(); iter++)
		{
			SmartPtr<Renderable> currentRenderable = *iter;

			SmartPtr<Actor> currentActor = currentRenderable->m_Actor.AcquireSmartPtr();

			// if there is an actor and a sprite draw it
			if (currentActor && currentRenderable->m_Sprite)
			{
				Vector3 actorPos = currentActor->GetPosition();
				GLib::Sprites::RenderSprite(*(currentRenderable->m_Sprite), { actorPos.GetX(), actorPos.GetY()}, 0.0f);
			}
		}

		// Tell GLib we're done rendering sprites
		GLib::Sprites::EndRendering();
		// IMPORTANT: Tell GLib we're done rendering
		GLib::EndRendering();
	}

	void ShutDown()
	{
		Renderables.clear();
		Renderables.shrink_to_fit();
	}
}
