#pragma once

#include "Actor.h"
#include "GLib.h"
#include "SmartPtr.h"

namespace Engine
{
	namespace Renderer
	{
		class SpriteDestructor
		{
		public:
			static void release(GLib::Sprites::Sprite * i_ptr) { GLib::Sprites::Release(i_ptr); }
		};

		typedef SmartPtr<GLib::Sprites::Sprite, SpriteDestructor> SpriteSmartPtr;

		class Renderable : public IActorComponent
		{

		public:

			Renderable(const SmartPtr<Actor> & i_Actor, SpriteSmartPtr & i_Sprite) :
				m_Actor(i_Actor), m_Sprite(i_Sprite)
			{
			}

			Renderable(const Renderable & i_OtherRenderable);

			~Renderable()
			{
				m_Actor.~WeakPtr();
				m_Sprite.~SmartPtr();
			}

			virtual void EndUpdate(float i_DeltaTime);

			WeakPtr<Actor> m_Actor;
			SpriteSmartPtr m_Sprite;

			inline void SetNewSprite(SpriteSmartPtr & i_NewSprite) { m_Sprite = i_NewSprite; }
		};

		class RenderableDestructor : public ComponentDestructor
		{
		public:
			static void release(Renderable * i_ptr) { delete i_ptr; }
		};
	}
}