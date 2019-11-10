#pragma once

#include "Engine.h"
#include "Actor.h"

extern const int GRID_SIZE;
extern bool PLAYING;

const int TELEPORT_PERCENT = 10;

class GamePlay
{
public:
	GamePlay(int turnAmountGenerateMonsters);
	~GamePlay();

	void gamePlayLoop(Engine * engine, Actor * player, Actor ** &monsters, unsigned int &numMonsters);

private:
	int turnAmountGenerateMonsters;
};

