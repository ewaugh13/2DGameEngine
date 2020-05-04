#include "Actor.h"

#include "LoadFile.h"
#include "RigidBody.h"

#include "GLib.h"

#include <assert.h>
#include <vector>
#include <stdlib.h>

#include "../External/nlohmann/json.hpp"

namespace Engine
{
	Actor::Actor(const char * i_name, const Vector3 & i_initalPosition, float i_zRotation) :
		m_name(i_name ? _strdup(i_name) : nullptr), m_position(i_initalPosition), m_ZRotation(i_zRotation)
	{
	}

	SmartPtr<Actor> Actor::CreateActor(const char * i_Name, Vector3 & i_InitPosition)
	{
		return SmartPtr<Actor>(new Actor(i_Name, i_InitPosition));
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

		for (std::pair<std::string, IActorComponent*> componentPair : m_Components)
		{
			assert(componentPair.second);
			if (componentPair.second != nullptr)
				delete componentPair.second;
		}
	}

	Vector3 Actor::GetVelocity() const
	{
		Physics::RigidBody * playerRigidBodyComp = dynamic_cast<Physics::RigidBody*>(GetComponent("rigidbody"));

		// if the actor has a rigid body return that velocity
		if (playerRigidBodyComp)
		{
			return playerRigidBodyComp->GetVelocity();
		}

		return Vector3::Zero;
	}

	void Actor::AddComponent(std::string i_ComponentName, IActorComponent * i_NewComponent)
	{
		m_Components.insert({ i_ComponentName, i_NewComponent });
	}

	void Actor::BeginUpdate(float i_DeltaTime)
	{
		for (std::pair<std::string, IActorComponent*> componentPair : m_Components)
		{
			assert(componentPair.second);
			if (componentPair.second != nullptr)
				componentPair.second->BeginUpdate(i_DeltaTime);
		}
	}

	void Actor::Update(float i_DeltaTime)
	{
		for (std::pair<std::string, IActorComponent*> componentPair : m_Components)
		{
			assert(componentPair.second);
			if (componentPair.second != nullptr)
				componentPair.second->Update(i_DeltaTime);
		}
	}

	void Actor::EndUpdate(float i_DeltaTime)
	{
		for (std::pair<std::string, IActorComponent*> componentPair : m_Components)
		{
			assert(componentPair.second);
			if (componentPair.second != nullptr)
				componentPair.second->EndUpdate(i_DeltaTime);
		}
	}
}