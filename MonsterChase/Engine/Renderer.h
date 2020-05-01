#pragma once

#include "Renderable.h"

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace Renderer
	{
		void AddRenderable(const SmartPtr<Actor> & i_Actor, nlohmann::json & i_RenderableJSON);

		void Tick(float i_DeltaTime);

		void Init();
		void ShutDown();
	}
}

