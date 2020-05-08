#pragma once

#include "Actor.h"

namespace Engine
{
	inline IActorComponent * Actor::GetComponent(const std::string & i_ComponentName) const
	{
		if (m_Components.size() > 0)
		{
			auto it = m_Components.find(i_ComponentName);
			if (it != m_Components.end())
			{
				return (*it).second;
			}
		}

		return nullptr;
	}
}