#pragma once

namespace GamePlay
{
	//void TestGameLoop();

	namespace Pong
	{
		void IncrementPlayerScore(bool i_Player1Scored);
		bool GameActive();
		void PongGameLoop();
	}
}

