#pragma once

#include "IActorComponent.h"

class PlayerMovement : public IActorComponent
{
public:
	PlayerMovement(int i_GridSize) : m_GridSize(i_GridSize)
	{
	}

	void BeginUpdate(Actor & i_Actor);
private:
	int m_GridSize;
	bool playing;
};

