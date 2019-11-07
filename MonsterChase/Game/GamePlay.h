#pragma once

#include "Engine.h"
#include "MonsterAI.h"

class GamePlay
{
public:
	GamePlay(int gridSize, int turnAmountGenerateMonsters);
	~GamePlay();

	void gamePlayLoop(Engine * engine, Actor * player, Actor ** &monsters, unsigned int &numMonsters);
	Point2D getActorLocation();

private:
	int gridSize;
	int turnAmountGenerateMonsters;
	MonsterAI monsterAIProcessor;
};

