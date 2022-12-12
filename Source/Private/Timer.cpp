#include "Timer.h"
#include "Macro.h"

#include <Windows.h>

Timer::Timer()
{
	int64_t CounterPerSeconds;
	CHECK((QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&CounterPerSeconds))), "failed to query performance frequency");

	SecondsPerCounter_ = 1.0 / static_cast<double>(CounterPerSeconds);
}

Timer::~Timer()
{
}

float Timer::GetDeltaTime(const EUnit& InUnit) const
{
	return 0.0f;
}

float Timer::GetTotalTime(const EUnit& InUnit) const
{
	return 0.0f;
}

void Timer::Reset()
{
	int64_t TickTime = GetTickTime();

	bIsStop_ = false;
	BaseTime_ = TickTime;
	PausedTime_ = 0LL;
	StopTime_ = 0LL;
	PrevTime_ = TickTime;
	CurrTime_ = TickTime;
}

void Timer::Start()
{
	if (bIsStop_)
	{
		int64_t TickTime = GetTickTime();

		PausedTime_ += (TickTime - StopTime_);
		PrevTime_ = TickTime;
		StopTime_ = 0LL;
		bIsStop_ = false;
	}
}

void Timer::Stop()
{
	if (!bIsStop_)
	{
		StopTime_ = GetTickTime();
		bIsStop_ = true;
	}
}

void Timer::Tick()
{
	PrevTime_ = CurrTime_;
	CurrTime_ = GetTickTime();
}

int64_t Timer::GetTickTime()
{
	int64_t TickTime = 0LL;
	CHECK((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&TickTime))), "failed to query performance counter");

	return TickTime;
}
