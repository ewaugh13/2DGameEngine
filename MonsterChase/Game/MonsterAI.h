#pragma once

#include "Character.h"

class MonsterAI
{
public:
	MonsterAI();
	~MonsterAI();

	void monsterMovement(Character * monsters, const int& numMonsters, const int& gridSize);
};

