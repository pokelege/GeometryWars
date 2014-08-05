#ifndef CLOCK
#define CLOCK
#include "ExportHeader.h"
#include <windows.h>

class ENGINE_SHARED Clock
{
	LARGE_INTEGER clockSpeed, startTick, intervalTick;

public:
	Clock();

	void Start();
	float Stop();
	float Interval();
	float fromStart();
};

#endif