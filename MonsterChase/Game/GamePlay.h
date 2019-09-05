#pragma once
class GamePlay
{
private:
	int gridSize;

public:
	GamePlay(int gridSize);
	~GamePlay();

	void setCharacterLocation(Character * character);
	void monsterAI(Character * monsters, int& numMonsters);
};

