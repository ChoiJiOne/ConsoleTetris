#pragma once

#include <chrono>


/**
 * 타이머 클래스입니다.
 * 이때, 타이머 클래스의 생성자는 초기화를 수행하지 않으므로
 * 반드시 Start 혹은 Reset 메서드를 호출해야 합니다.
 */
class Timer
{
public:
	/**
	 * 타이머 클래스의 기본 생성자입니다.
	 */
	Timer() = default;


	/**
	 * 타이머 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 */
	Timer(Timer&& InInstance) noexcept
		: bIsStop_(InInstance.bIsStop_)
		, BaseTime_(InInstance.BaseTime_)
		, PausedTime_(InInstance.PausedTime_)
		, StopTime_(InInstance.StopTime_)
		, PrevTime_(InInstance.PrevTime_)
		, CurrTime_(InInstance.CurrTime_) {}


	/**
	 * 타이머 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 */
	Timer(const Timer& InInstance) noexcept
		: bIsStop_(InInstance.bIsStop_)
		, BaseTime_(InInstance.BaseTime_)
		, PausedTime_(InInstance.PausedTime_)
		, StopTime_(InInstance.StopTime_)
		, PrevTime_(InInstance.PrevTime_)
		, CurrTime_(InInstance.CurrTime_) {}


	/**
	 * 타이머 클래스의 가상 소멸자입니다.
	 */
	virtual ~Timer();


	/**
	 * 타이머 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Timer& operator=(Timer&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		bIsStop_ = InInstance.bIsStop_;
		BaseTime_ = InInstance.BaseTime_;
		PausedTime_ = InInstance.PausedTime_;
		StopTime_ = InInstance.StopTime_;
		PrevTime_ = InInstance.PrevTime_;
		CurrTime_ = InInstance.CurrTime_;

		return *this;
	}


	/**
	 * 타이머 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Timer& operator=(const Timer& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		bIsStop_ = InInstance.bIsStop_;
		BaseTime_ = InInstance.BaseTime_;
		PausedTime_ = InInstance.PausedTime_;
		StopTime_ = InInstance.StopTime_;
		PrevTime_ = InInstance.PrevTime_;
		CurrTime_ = InInstance.CurrTime_;

		return *this;
	}


	/**
	 * 타이머의 초 단위 델타 시간값을 얻습니다.
	 * 
	 * @return 초 단위의 델타 시간값을 반환합니다.
	 */
	float GetDeltaSeconds() const;


	/**
	 * 타이머의 밀리초 단위의 델타 시간값을 얻습니다.
	 * 
	 * @return 밀리초 단위의 델타 시간값을 반환합니다.
	 */
	float GetDeltaMilliseconds() const;


	/**
	 * 타이머가 중지된 시간을 제외한 전체 시간값을 반환합니다.
	 * 
	 * @return 타이머가 시작된 이후의 중지된 시간을 제외한 전체 시간값을 반환합니다.
	 */
	float GetTotalSeconds() const;


	/**
	 * 타이머가 중지된 시간을 제외한 전체 시간값을 반환합니다.
	 *
	 * @return 타이머가 시작된 이후의 중지된 시간을 제외한 전체 시간값을 반환합니다.
	 */
	float GetTotalMilliseconds() const;


	/**
	 * 타이머의 모든 상태를 리셋합니다.
	 */
	void Reset();


	/**
	 * 타이머를 시작합니다.
	 * 이때, 타이머가 중지되어 있다면 중시된 시점부터 시작됩니다.
	 */
	void Start();


	/**
	 * 타이머를 중지시킵니다.
	 */
	void Stop();


	/**
	 * 타이머를 업데이트합니다.
	 */
	void Tick();


private:
    /**
     * Milliseconds 단위의 현재 시간 Tick 값을 얻습니다.
     * 
     * @return 현재 시간의 Tick 값을 반환합니다.
     */
    uint64_t GetCurrentTick();


private:
	/**
	 * 타이머의 중지 여부를 확인합니다.
	 */
	bool bIsStop_ = false;


	/**
	 * 타이머가 시작된 시간입니다.
	 */
	uint64_t BaseTime_ = 0ULL;


	/**
	 * 타이머가 중지된 동안의 누적 시간값 입니다.
	 */
	uint64_t PausedTime_ = 0ULL;


	/**
	 * 타이머가 중지된 시간입니다.
	 */
	uint64_t StopTime_ = 0ULL;


	/**
	 * 직전의 Tick 호출 시간입니다.
	 */
	uint64_t PrevTime_ = 0ULL;


	/**
	 * Tick 호출 시간입니니다.
	 */
	uint64_t CurrTime_ = 0ULL;
};