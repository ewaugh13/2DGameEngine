#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

typedef struct Character
{
	char * name;
	int x;
	int y;
}
Character;

void getPlayerInput(char * input);
void setCharacterLocation(Character * character);
void gamePlayLoop(Character * player, Character * monsters, int numMonsters);

int main()
{
	std::cout << "How many monsters do you want to start with: ";
	char * numMonstersInput = (char *)calloc(1, sizeof(char));

	getPlayerInput(numMonstersInput);
	int numMonsters = atoi(numMonstersInput);

	Character * monsters = (Character *)calloc(numMonsters, sizeof(Character));
	Character * player = (Character *)calloc(1, sizeof(Character));

	// get each monster name and set a location
	for (int i = 0; i < numMonsters; i++)
	{
		std::cout << "What would you like to name Monster " << i << ": ";
		monsters[i].name = (char*)calloc(1, sizeof(char*));
		getPlayerInput(monsters[i].name);

		setCharacterLocation(&monsters[i]);
	}

	// get the player name and set a location
	std::cout << "What would you like to name the Player" << ": ";
	char * playerName = (char *)calloc(1, sizeof(char));
	getPlayerInput(playerName);
	player->name = playerName;
	player->x, player->y = 0;

	std::cout << "end";

	free(numMonstersInput);
	free(monsters);
	free(player);
	free(playerName);
}

void getPlayerInput(char * input)
{
	char charelement;
	int i = 0;
	while ((charelement = (char)_getche()) != '\r')
	{
		input[i] = charelement;
		// i + 2 to store new element and possible end delimiter
		input = (char *)realloc((void *)input, (i + 2) * sizeof(char));

		i++;
		input[i] = '\0';
	}
	std::cout << std::endl;
}

// sets a character's x and y location from a range of -100 to 100
void setCharacterLocation(Character * character)
{
	int randXNegative = rand() % 2;
	int randYNegative = rand() % 2;

	character->x = rand() % 100;
	character->y = rand() % 100;
	if (randXNegative) { character->x *= -1; }
	if (randYNegative) { character->y *= -1; }
}

void gamePlayLoop(Character * player, Character * monsters, int numMonsters)
{
	player;
	monsters;
	bool playing = true;
	while (playing)
	{
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;
		// print monster locations
		for (int i = 0; i < numMonsters; i++)
		{

		}
		// print player location


		// TODO: need to print all the locations of the monsters
		// TODO: need to print the location of the player
		switch (_getch())
		{
			case 'A':
			case 'a':
				break;
			case 'D':
			case 'd':
				break;
			case 'W':
			case 'w':
				break;
			case 'S':
			case 's':
				break;
			case 'Q':
			case 'q':
				playing = false;
				break;
			default:
				continue;
		}
	}
}
