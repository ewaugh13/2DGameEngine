#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

void getPlayerInput(char * input);

typedef struct Character
{
	char * name;
	int x;
	int y;
}
Character;

int main()
{
	std::cout << "How many monsters do you want to start with: ";
	char * numMonstersInput = (char *)calloc(1, sizeof(char));

	getPlayerInput(numMonstersInput);
	int numMonsters = atoi(numMonstersInput);

	Character * characters = (Character *)calloc(numMonsters, sizeof(Character));

	for (int i = 0; i < numMonsters; i++)
	{
		std::cout << "What would you like to name Monster " << i << ": ";
		char * monsterName = (char *)calloc(1, sizeof(char));
		getPlayerInput(monsterName);
		characters[i].name = monsterName;
		characters[i];
	}


	// need to create 2d array of char*
	bool playing = true;
	while (playing)
	{
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
		}
	}
	// case switch with _getch() for the 5 possible characters
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
