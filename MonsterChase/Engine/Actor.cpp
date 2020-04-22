#include "Actor.h"
#include "LoadFile.h"

#include <assert.h>
#include <vector>
#include <stdlib.h>

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	// TODO: make more universal
	void operator<<(Vector3 & vec, nlohmann::json & json_obj)
	{
		assert(json_obj.is_array() && json_obj.size() == 3);

		vec.SetX(json_obj[0]);
		vec.SetY(json_obj[1]);
		vec.SetZ(json_obj[2]);
	}

	SmartPtr<Actor> Actor::CreateActor(const char * i_ScriptFilename)
	{
		using json = nlohmann::json;

		std::vector<uint8_t> playerData = File::LoadFileToBuffer(i_ScriptFilename);

		if (!playerData.empty())
		{
			json playerJSON = json::parse(playerData);

			std::string playerName = playerJSON["name"];

			Vector3 initalPosition = Vector3::Zero;
			initalPosition << playerJSON["initial_position"];

			return SmartPtr<Actor>(new Actor(playerName.c_str(), initalPosition));
		}

		return SmartPtr<Actor>();
	}

	Actor::Actor(const char * i_name, const Vector3 & i_initalPosition) :
		m_name(i_name ? _strdup(i_name) : nullptr), m_position(i_initalPosition)
	{
	}

	Actor::Actor(const Actor & i_OtherActor) :
		m_name(i_OtherActor.m_name), m_position(i_OtherActor.m_position), m_Components(i_OtherActor.m_Components)
	{
	}

	Actor::~Actor()
	{
		if (m_name)
		{
			free(m_name);
		}

		for (size_t i = 0; i < m_Components.size(); i++)
		{
			assert(m_Components[i]);
			delete m_Components[i];
		}
	}

	void Actor::AddComponent(IActorComponent * m_pNewComponent)
	{
		this->m_Components.push_back(m_pNewComponent);
	}

	void Actor::BeginUpdate()
	{
		const size_t count = this->m_Components.size();
		for (size_t i = 0; i < count; i++)
		{
			assert(this->m_Components[i]);
			m_Components[i]->BeginUpdate(*this);
		}
	}

	void Actor::Update()
	{
		const size_t count = this->m_Components.size();
		for (size_t i = 0; i < count; i++)
		{
			assert(this->m_Components[i]);
			m_Components[i]->Update(*this);
		}
	}

	void Actor::EndUpdate()
	{
		const size_t count = this->m_Components.size();
		for (size_t i = 0; i < count; i++)
		{
			assert(this->m_Components[i]);
			m_Components[i]->EndUpdate(*this);
		}
	}
}