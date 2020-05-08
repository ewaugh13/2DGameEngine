#include "GamePlay.h"
#include "GLib.h"
#include "GLibHelpers.h"

#include <crtdbg.h>
#include <Windows.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	{
		// IMPORTANT: first we need to initialize GLib
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, WINDOW_WIDTH, WINDOW_HEIGHT);

		if (bSuccess)
		{
			using namespace GamePlay;

			GLibHelper::InitalizeKeyStates();
			Pong::PongGameLoop();
			free(GLibHelper::KeyStates);
		}

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}