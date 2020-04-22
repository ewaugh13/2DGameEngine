#pragma once

#include "Renderable.h"

namespace Engine
{
	namespace Renderer
	{
		SmartPtr<Renderable> AddRenderable(const SmartPtr<Actor> & i_Actor, const char * i_ScriptFilename);

		// Draw all sprites
		void Draw(float i_DeltaTime);

		// Clear all renderables
		void ShutDown();
	}
}

