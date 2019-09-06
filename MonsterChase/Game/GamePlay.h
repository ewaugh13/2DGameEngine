#pragma once

typedef struct Character
{
	char * name;
	//TODO needs to be point 2d
	int x;
	int y;
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

	void gamePlayLoop(Character * player, Character * &monsters, int& numMonsters);
	void setCharacterLocation(Character * character);
};

