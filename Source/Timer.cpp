#include "Timer.h"

Timer::Timer(Timer&& InInstance) noexcept
	: BaseTime(InInstance.BaseTime)
	, PrevTime(InInstance.PrevTime)
	, CurrTime(InInstance.CurrTime)
{
}

Timer::Timer(const Timer& InInstance) noexcept
	: BaseTime(InInstance.BaseTime)
	, PrevTime(InInstance.PrevTime)
	, CurrTime(InInstance.CurrTime)
{
}

Timer::~Timer()
{
}

float Timer::DeltaTime()
{
	std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>>(CurrTime - PrevTime);
	return delta.count();
}

float Timer::TotalTime()
{
	std::chrono::duration<float> total = std::chrono::duration_cast<std::chrono::duration<float>>(CurrTime - BaseTime);
	return total.count();
}

void Timer::Tick()
{
	PrevTime = CurrTime;
	CurrTime = std::chrono::high_resolution_clock::now();
}

void Timer::Reset()
{
	std::chrono::high_resolution_clock::time_point CurrentTime = std::chrono::high_resolution_clock::now();

	BaseTime = CurrentTime;
	PrevTime = CurrentTime;
	CurrTime = CurrentTime;
}