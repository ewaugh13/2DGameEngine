#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <assert.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /

char * MakeSentence(char * strings[]);
char ** GetUserStrings();

int main()
{
	printf("Enter words to be combined into a sentence (press enter for each word):\n");
	char ** strings = GetUserStrings();
	/* = {
	"This",
	"is",
	"a",
	"test",
	NULL
	};*/

	if (strings[0] == NULL)
	{
		printf("No words inputed to create a sentence.\n");
	}
	assert(strings[0] != NULL);

	char * pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	int i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	free(pSentence);


#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}

char * MakeSentence(char * strings[])
{
	// start out with 2 chars for the period and the end delimiter
	int sizeTotalString = 0;
	char * returnSentence = (char *)calloc(sizeTotalString, sizeof(char));

	int i = 0;
	while (strings[i] != NULL)
	{
		// add space inbetween each string
		if (i != 0)
		{
			sizeTotalString++;
			returnSentence = (char*)realloc((void*)returnSentence, sizeTotalString);
			returnSentence[sizeTotalString - 1] = ' ';
		}

		char * currentString = (char *)strings[i];

		// determine the size of the current string
		int j = 0;
		int sizeCurrString = 0;
		while (currentString[j] != '\0')
		{
			sizeCurrString++;
			j++;
		}
		sizeTotalString += sizeCurrString;

		returnSentence = (char*)realloc((void*)returnSentence, sizeTotalString);

		// start the index at the begging of copying over the current string
		for (int k = 0; k < sizeCurrString; k++)
		{
			// start the index at the begging of copying over the current string
			int indexToSet = sizeTotalString - sizeCurrString + k;
			returnSentence[indexToSet] = currentString[k];
		}

		i++;
	}

	// plus 2 for period and end delimiter
	sizeTotalString += 2;
	returnSentence = (char*)realloc((void*)returnSentence, sizeTotalString);
	returnSentence[sizeTotalString - 2] = '.';
	returnSentence[sizeTotalString - 1] = '\0';

	return returnSentence;
}

char ** GetUserStrings()
{
	// start with one for NULL at the end
	int numberOfStrings = 1;
	char ** returnStrings = (char **)calloc(numberOfStrings, sizeof(char*));

	bool readingInput = true;

	char charElement;
	int i = 0;
	while (readingInput)
	{
		charElement = (char)_getche();

		// start input for next string
		if (charElement != '\r')
		{
			// add memory to hold another string
			numberOfStrings++;
			returnStrings = (char**)realloc((void*)returnStrings, numberOfStrings * sizeof(char*));

			// allocate for current string and set first char
			char * input = (char *)calloc(2, sizeof(char));
			input[0] = charElement;

			// start at index 1 since we alreayd have the first character
			int j = 1;
			while ((charElement = (char)_getche()) != '\r')
			{
				input[j] = charElement;
				// i + 2 to store new element and possible end delimiter
				input = (char *)realloc((void *)input, (j + 2) * sizeof(char));

				j++;
				// set null term that will get replaced unless we are done reading chars
				input[j] = '\0';
			}

			returnStrings[i] = input;
			i++;

			printf("\n");
		}
		// only enter givin, done reading strings
		else
		{
			readingInput = false;
		}
	}
	// set null for end of array of strings
	returnStrings[i] = NULL;

	return returnStrings;
}
