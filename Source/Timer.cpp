#include "Timer.h"

Timer::Timer(Timer&& InInstance) noexcept
	: BaseTime_(InInstance.BaseTime_)
	, PrevTime_(InInstance.PrevTime_)
	, CurrTime_(InInstance.CurrTime_)
{
}

Timer::Timer(const Timer& InInstance) noexcept
	: BaseTime_(InInstance.BaseTime_)
	, PrevTime_(InInstance.PrevTime_)
	, CurrTime_(InInstance.CurrTime_)
{
}

Timer::~Timer()
{
}

float Timer::DeltaTime()
{
	std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>>(CurrTime_ - PrevTime_);
	return delta.count();
}

float Timer::TotalTime()
{
	std::chrono::duration<float> total = std::chrono::duration_cast<std::chrono::duration<float>>(CurrTime_ - BaseTime_);
	return total.count();
}

void Timer::Tick()
{
	PrevTime_ = CurrTime_;
	CurrTime_ = std::chrono::high_resolution_clock::now();
}

void Timer::Reset()
{
	std::chrono::high_resolution_clock::time_point CurrentTime = std::chrono::high_resolution_clock::now();

	BaseTime_ = CurrentTime;
	PrevTime_ = CurrentTime;
	CurrTime_ = CurrentTime;
}