#include "GameTimer.h"

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

float GameTimer::DeltaTime()
{
	std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>>(currTime - prevTime);
	return delta.count();
}

float GameTimer::TotalTime()
{
	std::chrono::duration<float> total = std::chrono::duration_cast<std::chrono::duration<float>>(currTime - baseTime);
	return total.count();
}

void GameTimer::Tick()
{
	prevTime = currTime;
	currTime = std::chrono::high_resolution_clock::now();
}

void GameTimer::Reset()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

	baseTime = currentTime;
	prevTime = currentTime;
	currTime = currentTime;
}