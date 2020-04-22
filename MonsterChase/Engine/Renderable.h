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

		typedef struct Renderable
		{
			WeakPtr<Actor> m_Actor;
			SpriteSmartPtr m_Sprite;

			Renderable(const SmartPtr<Actor> & i_Actor, SpriteSmartPtr & i_Sprite) :
				m_Actor(i_Actor), m_Sprite(i_Sprite)
			{
			}

			inline void SetNewSprite(SpriteSmartPtr & i_NewSprite) { m_Sprite = i_NewSprite; }

		} Renderable;
	}
}