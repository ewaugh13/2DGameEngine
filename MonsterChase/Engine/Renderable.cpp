#include "Renderable.h"

namespace Engine
{
	namespace Renderer
	{
		Renderable::Renderable(const Renderable & i_OtherRenderable)
		{
			m_Actor = i_OtherRenderable.m_Actor;
			m_Sprite = i_OtherRenderable.m_Sprite;
		}

		void Renderable::EndUpdate(float i_DeltaTime)
		{
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();

			SmartPtr<Actor> currentActor = m_Actor.AcquireSmartPtr();

			// if there is an actor and a sprite draw it
			if (currentActor && m_Sprite)
			{
				Vector3 actorPos = currentActor->GetPosition();
				GLib::Sprites::RenderSprite(*(m_Sprite), { actorPos.GetX(), actorPos.GetY() }, 0.0f);
			}

			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}
	}
}
