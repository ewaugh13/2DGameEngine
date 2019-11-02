#pragma once

#include "Engine.h"
#include "MonsterAI.h"

class GamePlay
{
public:
	GamePlay(int gridSize, int turnAmountGenerateMonsters);
	~GamePlay();

	void gamePlayLoop(Engine * engine, Character * player, Character * &monsters, unsigned int numMonsters);
	void setCharacterLocation(Character * character);

private:
	int gridSize;
	int turnAmountGenerateMonsters;
	MonsterAI monsterAIProcessor;
};

