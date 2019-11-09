#pragma once

#include "Actor.h"

// interface for components
class IActorComponent
{
public:
	virtual void BeginUpdate(Actor &)
	{}
	virtual void Update(Actor &)
	{}
	virtual void EndUpdate(Actor &)
	{}
};