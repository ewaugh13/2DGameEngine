#pragma once

#include "Actor.h"

class MonsterAI
{
public:
	MonsterAI();
	~MonsterAI();

	void monsterMovement(Actor ** monsters, const int& numMonsters, const int& gridSize);
};

