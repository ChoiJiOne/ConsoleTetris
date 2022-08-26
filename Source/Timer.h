#pragma once

#include <chrono>


/**
 * ���� Ÿ�̸� Ŭ�����Դϴ�.
 */
class Timer
{
public:
	/**
	 * ���� Ÿ�̸� Ŭ������ �������Դϴ�.
	 * �̶�, Ÿ�̸Ӹ� ����ϱ� ���� �ݵ�� Reset �޼��带 ȣ���ؾ� �մϴ�.
	 */
	Timer() = default;


	/**
	 * ���� Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Timer(Timer&& InInstance) noexcept;


	/**
	 * ���� Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Timer(const Timer& InInstance) noexcept;


	/**
	 * ���� Ÿ�̸� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Timer();


	/**
	 * ��Ÿ �ð� ���� ����ϴ�. ������ �ʴ����Դϴ�.
	 * 
	 * @return ��Ÿ �ð� ���� ��ȯ�մϴ�.
	 */
	float DeltaTime();


	/**
	 * Reset�� ���ʷ� ȣ���� ������ �������� ������ �ð��� ����ϴ�.
	 * 
	 * @return ��ü �ð� ���� ��ȯ�մϴ�.
	 */
	float TotalTime();


	/**
	 * Ÿ�̸Ӹ� ������Ʈ�մϴ�.
	 */
	void Tick();


	/**
	 * Ÿ�̸Ӹ� �ʱ�ȭ �մϴ�.
	 */
	void Reset();


private:
	/**
	 * Ÿ�̸Ӹ� �ʱ�ȭ �� �����Դϴ�.
	 */
	std::chrono::high_resolution_clock::time_point BaseTime;


	/**
	 * Ÿ�̸Ӹ� ������Ʈ �ϱ� ������ �����Դϴ�.
	 */
	std::chrono::high_resolution_clock::time_point PrevTime;


	/**
	 * Ÿ�̸Ӹ� ������Ʈ�� �����Դϴ�.
	 */
	std::chrono::high_resolution_clock::time_point CurrTime;
};