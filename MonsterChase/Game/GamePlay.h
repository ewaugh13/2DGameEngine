#pragma once
#include "Engine.h"
#include "Point2D.h"

typedef struct Character
{
	char * name;
	Point2D position;
}
Character;

class GamePlay
{
private:
	int gridSize;
	int turnAmountGenerateMonsters;

	void monsterAI(Character * monsters, int& numMonsters);

public:
	GamePlay(int gridSize, int turnAmountGenerateMonsters);
	~GamePlay();

	void gamePlayLoop(Engine * engine, Character * player, Character * &monsters, int& numMonsters);
	void setCharacterLocation(Character * character);
};

