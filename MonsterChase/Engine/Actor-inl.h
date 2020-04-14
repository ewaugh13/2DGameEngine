#pragma once

#include "Actor.h"

namespace MyEngine
{
	template<typename ComponentType>
	inline IActorComponent * Actor::GetComponent()
	{
		for (auto & component : this->m_Components)
		{
			if (ComponentType component = dynamic_cast<ComponentType>(component))
			{
				return component;
			}
		}
		return nullptr;
	}
}