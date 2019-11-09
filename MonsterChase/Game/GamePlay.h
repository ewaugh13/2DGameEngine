#pragma once

#include "Engine.h"
#include "MonsterAI.h"

extern const int GRID_SIZE;
extern bool PLAYING;

class GamePlay
{
public:
	GamePlay(int turnAmountGenerateMonsters);
	~GamePlay();

	void gamePlayLoop(Engine * engine, Actor * player, Actor ** &monsters, unsigned int &numMonsters);
	Point2D getActorLocation();

private:
	int turnAmountGenerateMonsters;
	MonsterAI monsterAIProcessor;
};

