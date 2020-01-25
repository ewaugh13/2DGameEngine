#pragma once

#include "Windows.h"

static ULONGLONG g_LastFrameTime = 0;
static float g_LastFrameTime_ms;

class Timer
{
public:
	Timer();
	~Timer();
	
	// frame time in miliseconds
	float CalcLastFrameTime_ms();
	// returns difference of time in seconds since last frame
	float DeltaTime();
};

