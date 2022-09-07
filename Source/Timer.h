#pragma once

#include <chrono>


/**
 * 게임 타이머 클래스입니다.
 */
class Timer
{
public:
	/**
	 * 게임 타이머 클래스의 생성자입니다.
	 * 이때, 타이머를 사용하기 전에 반드시 Reset 메서드를 호출해야 합니다.
	 */
	Timer() = default;


	/**
	 * 게임 타이머 클래스의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사할 객체입니다.
	 */
	Timer(Timer&& InInstance) noexcept;


	/**
	 * 게임 타이머 클래스의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사할 객체입니다.
	 */
	Timer(const Timer& InInstance) noexcept;


	/**
	 * 게임 타이머 클래스의 가상 소멸자입니다.
	 */
	virtual ~Timer();


	/**
	 * 게임 타이머 클래스의 대입 연산자입니다.
	 * 
	 * @param InInstance - 복사할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Timer& operator=(Timer&& InInstance) noexcept;


	/**
	 * 게임 타이머 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Timer& operator=(const Timer& InInstance) noexcept;


	/**
	 * 델타 시간 값을 얻습니다. 단위는 초단위입니다.
	 * 
	 * @return 델타 시간 값을 반환합니다.
	 */
	float DeltaTime();


	/**
	 * Reset을 최초로 호출한 시점을 기준으로 누적된 시간을 얻습니다.
	 * 
	 * @return 전체 시간 값을 반환합니다.
	 */
	float TotalTime();


	/**
	 * 타이머를 업데이트합니다.
	 */
	void Tick();


	/**
	 * 타이머를 초기화 합니다.
	 */
	void Reset();


private:
	/**
	 * 타이머를 초기화 한 시점입니다.
	 */
	std::chrono::high_resolution_clock::time_point BaseTime_;


	/**
	 * 타이머를 업데이트 하기 이전의 시점입니다.
	 */
	std::chrono::high_resolution_clock::time_point PrevTime_;


	/**
	 * 타이머를 업데이트한 시점입니다.
	 */
	std::chrono::high_resolution_clock::time_point CurrTime_;
};