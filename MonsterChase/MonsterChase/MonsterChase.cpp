#include "Allocators.h"
#include "Engine.h"
#include "GamePlay.h"
#include "GLib.h"
#include "GLibHelpers.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <Windows.h>

extern const int WINDOW_WIDTH = 800;
extern const int WINDOW_HEIGHT = 800;

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (bSuccess)
	{
		GLibHelper::InitalizeKeyStates();
		GamePlay::Pong();
	}

	// need to free key states info
	free(GLibHelper::KeyStates);

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}