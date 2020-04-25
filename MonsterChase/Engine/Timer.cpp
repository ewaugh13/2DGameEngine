#include "Timer.h"

#include "Windows.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

float Timer::CalcLastFrameTime_ms()
{
	// Grab the CPU tick counter
	ULONGLONG currentTick = GetTickCount64();

	if (g_LastFrameTime)
	{
		// How many ticks(ms) have elapsed since we last did this
		g_LastFrameTime_ms = static_cast<float>(currentTick - g_LastFrameTime);
	}
	else 
	{
		g_LastFrameTime_ms = 13.3f; // Assume a 60Hz frame for first call.
	}

	if (g_LastFrameTime_ms == 0.0f)
		g_LastFrameTime_ms = 13.3f; // Assume a 60Hz frame for any calls where it would be 0

	// Note start of this frame
	g_LastFrameTime = currentTick;

	return g_LastFrameTime_ms;
}

float Timer::DeltaTime()
{
	return CalcLastFrameTime_ms() / 1000.0f;
}
