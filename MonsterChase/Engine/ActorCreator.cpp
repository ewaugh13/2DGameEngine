#include "ActorCreator.h"

#include "JobSystem.h"
#include "LoadFile.h"
#include "ScopeLock.h"

namespace Engine
{
	namespace ActorCreator
	{

		Engine::Mutex ActorCreatorMutex;

		// TODO: make more universal
		void operator<<(Vector3 & vec, nlohmann::json & json_obj)
		{
			assert(json_obj.is_array() && json_obj.size() == 3);

			vec.SetX(json_obj[0]);
			vec.SetY(json_obj[1]);
			vec.SetZ(json_obj[2]);
		}

		// TODO: turn into hashmap
		static std::map<std::string, std::function<void(SmartPtr<Actor>&, nlohmann::json&)>> ComponentCreators;

		void RegisterComponentCreator(const std::string & i_ControllerName, std::function<void(SmartPtr<Actor>&, nlohmann::json&)> i_ControllerCreator)
		{
			ComponentCreators.insert({ i_ControllerName, i_ControllerCreator });
		}

		void DeregisterComponentCreator(const std::string & i_ControllerName)
		{
			auto creator = ComponentCreators.find(i_ControllerName);
			if (creator != ComponentCreators.end())
			{
				ComponentCreators.erase(i_ControllerName);
			}
		}

		SmartPtr<Actor> CreateGameObject(const std::string & i_JSONFilename)
		{
			using json = nlohmann::json;

			std::vector<uint8_t> playerContents = File::LoadFileToBuffer(i_JSONFilename);

			SmartPtr<Actor> newActor;

			if (!playerContents.empty())
			{
				json playerJSON = json::parse(playerContents);

				std::string playerName = playerJSON["name"];

				Vector3 initalPosition = Vector3::Zero;
				initalPosition << playerJSON["initial_position"];

				newActor = SmartPtr<Actor>(Actor::CreateActor(playerName.c_str(), initalPosition));

				if (playerJSON.contains("components"))
				{
					assert(playerJSON["components"].is_object());

					for (json::iterator it = playerJSON["components"].begin(); it != playerJSON["components"].end(); it++)
					{
						const std::string & componentName = it.key();

						auto componentCreator = ComponentCreators.find(componentName);
						if (componentCreator != ComponentCreators.end())
						{
							componentCreator->second(newActor, it.value());
						}
					}

				}
			}

			return newActor;
		}

		void CreateGameObjectEvent(const std::string & i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent)
		{
			SmartPtr<Actor> actor;
			{
				ScopeLock Lock(ActorCreatorMutex);
				actor = CreateGameObject(i_JSONFilename);
			}
			if (i_CreateCallBack)
			{
				i_CreateCallBack(actor);
			}
			if (i_FinishEvent != nullptr)
			{
				i_FinishEvent->Signal();
			}
		}

		void CreateGameObjectAsync(const std::string & i_JSONFilename, std::function<void(SmartPtr<Actor>&)> i_CreateCallBack, Engine::Event * i_FinishEvent)
		{
			if (!Engine::JobSystem::ShutdownRequested())
			{
				Engine::JobSystem::RunJob("CreateActor", [i_JSONFilename, i_CreateCallBack, i_FinishEvent]()
				{
					CreateGameObjectEvent(i_JSONFilename, i_CreateCallBack, i_FinishEvent);
				}, "Default");
			}
		}
	}
}