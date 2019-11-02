#include <conio.h>

extern bool HeapManager_UnitTest();

int main(int i_argc, char ** i_argl)
{
	HeapManager_UnitTest();
	_getch();
	
	return 0;
}