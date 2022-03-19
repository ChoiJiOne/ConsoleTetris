#pragma once

#include "Common.h"

class GameTimer
{
public:
	GameTimer();
	virtual ~GameTimer();

	float DeltaTime();
	float TotalTime();

	void Tick();
	void Reset();

private:
	std::chrono::high_resolution_clock::time_point baseTime;
	std::chrono::high_resolution_clock::time_point prevTime;
	std::chrono::high_resolution_clock::time_point currTime;
};