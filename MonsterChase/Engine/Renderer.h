#pragma once

#include "Renderable.h"

namespace Renderer
{
	SmartPtr<Renderable> AddRenderable(const SmartPtr<Actor> & i_Actor, SpriteSmartPtr i_Sprite = SpriteSmartPtr());

	// Draw all sprites
	void Draw(float i_DeltaTime);

	// Clear all renderables
	void ShutDown();
}

