#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <Engine.h>

typedef struct Character
{
	char * name;
	int x;
	int y;
}
Character;

const int GRID_SIZE = 100;
// number of turns that go by before we generate a new monster
const int TURN_AMOUNT_GENERATE_MONSTER = 9;

void getPlayerInput(char * &input);
void setCharacterLocation(Character * character);
void gamePlayLoop(Character * player, Character * &monsters, int& numMonsters);
void monsterAI(Character * monsters, int& numMonsters);

int main()
{
	// get the number of monsters to create
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
		monsters[i].name = (char *)calloc(1, sizeof(char));
		getPlayerInput(monsters[i].name);

		setCharacterLocation(&monsters[i]);
	}

	// get the player name and set a location
	std::cout << "What would you like to name the Player" << ": ";
	char * playerName = (char *)calloc(1, sizeof(char));
	getPlayerInput(playerName);
	player->name = playerName;
	player->x, player->y = 0;

	// while loop for game loop until user input to quit
	gamePlayLoop(player, monsters, numMonsters);

	// free everything we allocated
	free(numMonstersInput);
	for (int i = 0; i < numMonsters; i++)
	{
		free(monsters[i].name);
	}
	free(monsters);
	free(player);
	free(playerName);
}

//// read player input 1 char at a time until enter a cariage return is read
//void getPlayerInput(char * &input)
//{
//	char charElement;
//	int i = 0;
//	while ((charElement = (char)_getche()) != '\r')
//	{
//		input[i] = charElement;
//		// i + 2 to store new element and possible end delimiter
//		input = (char *)realloc((void *)input, (i + 2) * sizeof(char));
//
//		i++;
//		input[i] = '\0';
//	}
//	std::cout << std::endl;
//}

//// sets a character's x and y location from a range of -100 to 100
//void setCharacterLocation(Character * character)
//{
//	int randXNegative = rand() % 2;
//	int randYNegative = rand() % 2;
//
//	character->x = rand() % GRID_SIZE;
//	character->y = rand() % GRID_SIZE;
//	if (randXNegative) { character->x *= -1; }
//	if (randYNegative) { character->y *= -1; }
//}

// does the main gameplay loop
void gamePlayLoop(Character * player, Character * &monsters, int& numMonsters)
{
	bool playing = true;
	int currentTurnCounter = 0;
	while (playing)
	{
		if (currentTurnCounter > TURN_AMOUNT_GENERATE_MONSTER)
		{
			currentTurnCounter = 0;
			numMonsters++;

			monsters = (Character *)realloc(monsters, numMonsters * sizeof(Character));

			// create new monster
			monsters[numMonsters - 1].name = (char *)calloc(2, sizeof(char));
			monsters[numMonsters - 1].name[0] = (char)(rand() % 255);
			monsters[numMonsters - 1].name[1] = '\0';

			setCharacterLocation(&monsters[numMonsters - 1]);
		}

		// print monster locations
		for (int i = 0; i < numMonsters; i++)
		{
			printf("Monster %s at [%02d,%02d]\n", monsters[i].name, monsters[i].x, monsters[i].y);
		}
		// print player location
		printf("Player %s at [%02d,%02d]\n", player->name, player->x, player->y);

		// print instructions for player
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit." << std::endl;

		monsterAI(monsters, numMonsters);

		switch (_getch())
		{
			case 'A':
			case 'a':
				player->x--;
				if (player->x < -GRID_SIZE)
					player->x = -GRID_SIZE;
				break;
			case 'D':
			case 'd':
				player->x++;
				if (player->x > GRID_SIZE)
					player->x = GRID_SIZE;
				break;
			case 'W':
			case 'w':
				player->y++;
				if (player->y > GRID_SIZE)
					player->y = GRID_SIZE;
				break;
			case 'S':
			case 's':
				player->y--;
				if (player->y < -GRID_SIZE)
					player->y = -GRID_SIZE;
				break;
			case 'Q':
			case 'q':
				playing = false;
				break;
			default:
				continue;
		}

		// destroy monster if its on the same space as a player
		int newNumMonsters = numMonsters;
		for (int i = 0; i < numMonsters; i++)
		{
			if (player->x == monsters[i].x && player->y == monsters[i].y)
			{
				newNumMonsters--;
				if (newNumMonsters > 0)
				{
					Character * monstersTemp = (Character *)calloc(newNumMonsters, sizeof(Character));

					// copy over the monsters that are in memory before and after the destroyed one
					if (i > 0)
					{
						memcpy((void*)monstersTemp, (void*)monsters, sizeof(Character) * (i));
					}
					memcpy(&monstersTemp[i], &monsters[i + 1], sizeof(Character) * (newNumMonsters - i));

					// free destroyed monster name and original monster data
					free(monsters[i].name);
					free(monsters);
					monsters = monstersTemp;
					numMonsters = newNumMonsters;
					i--;
				}
			}
		}
		currentTurnCounter++;
	}
}

void monsterAI(Character * monsters, int& numMonsters)
{
	// move the monsters in a random direction 0 being up, 1 being right, 2 being down and 3 being left
	for (int i = 0; i < numMonsters; i++)
	{
		int direction = rand() % 4;
		switch (direction)
		{
			case 0: // up
				monsters[i].y++;
				break;
			case 1: // right
				monsters[i].x++;
				break;
			case 2: // down
				monsters[i].y--;
				break;
			case 3: // left
				monsters[i].x--;
				break;
			default:
				monsters[i].x++;
		}
		// check to see if the monster went out of bounds
		if (monsters[i].x > GRID_SIZE)
			monsters[i].x = GRID_SIZE;
		else if (monsters[i].x < -GRID_SIZE)
			monsters[i].x = -GRID_SIZE;
		else if (monsters[i].y > GRID_SIZE)
			monsters[i].y = GRID_SIZE;
		else if (monsters[i].y < -GRID_SIZE)
			monsters[i].y = -GRID_SIZE;
	}
}
