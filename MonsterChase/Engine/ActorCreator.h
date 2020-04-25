#pragma once

#include "Actor.h"
#include "Events.h"
#include "SmartPtr.h"

#include <functional>
#include <string>

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	void RegisterComponentCreator(const std::string & i_ControllerName, std::function<void(SmartPtr<Actor>&, nlohmann::json&)> i_ControllerCreator);
	void DeregisterComponentCreator(const std::string & i_ControllerName);

	SmartPtr<Actor> CreateGameObject(const std::string & i_JSONFilename);
	void CreateGameObjectEvent(const std::string & i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent);
	void CreateGameObjectAsync(const std::string& i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent = nullptr);
}


