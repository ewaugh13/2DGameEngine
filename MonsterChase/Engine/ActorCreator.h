#pragma once

#include "Actor.h"
#include "Events.h"
#include "SmartPtr.h"

#include <functional>
#include <string>

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	namespace ActorCreator
	{
		typedef struct ComponentCreators 
		{
			std::map<std::string, std::function<void(SmartPtr<Actor>&, nlohmann::json&)>> m_ComponentCreators;
		} ComponentCreator;

		void ShutDown();

		void RegisterComponentCreator(const std::string & i_ControllerName, std::function<void(SmartPtr<Actor>&, nlohmann::json&)> i_ControllerCreator);
		void DeregisterComponentCreator(const std::string & i_ControllerName);

		SmartPtr<Actor> CreateGameObject(const std::string & i_JSONFilename);
		void CreateGameObjectEvent(const std::string & i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent);
		void CreateGameObjectAsync(const std::string& i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent = nullptr);
		SmartPtr<Actor> CreateGameObject(const std::string & i_JSONFilename);
	}
}


