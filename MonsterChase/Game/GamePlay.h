#pragma once

#include "Engine.h"
#include "Actor.h"

namespace GamePlay
{
	void TestGameLoop();

	namespace Pong
	{
		void IncrementPlayerScore(bool i_Player1Scored);
		void PongGameLoop();
	}
}

