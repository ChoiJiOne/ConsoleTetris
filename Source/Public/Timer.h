#pragma once

#include <cstdint>


/**
 * Ÿ�̸� Ŭ�����Դϴ�.
 * �̶�, Ÿ�̸� Ŭ������ �����ڴ� �ʱ�ȭ�� �������� �����Ƿ�
 * �ݵ�� Start Ȥ�� Reset �޼��带 ȣ���ؾ� �մϴ�.
 */
class Timer
{
public:
	/**
	 * Ÿ�̸� Ŭ������ �������Դϴ�.
	 */
	Timer();


	/**
	 * Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 */
	Timer(Timer&& InInstance) noexcept
		: bIsStop_(InInstance.bIsStop_)
		, BaseTime_(InInstance.BaseTime_)
		, PausedTime_(InInstance.PausedTime_)
		, StopTime_(InInstance.StopTime_)
		, PrevTime_(InInstance.PrevTime_)
		, CurrTime_(InInstance.CurrTime_) {}


	/**
	 * Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 */
	Timer(const Timer& InInstance) noexcept
		: bIsStop_(InInstance.bIsStop_)
		, BaseTime_(InInstance.BaseTime_)
		, PausedTime_(InInstance.PausedTime_)
		, StopTime_(InInstance.StopTime_)
		, PrevTime_(InInstance.PrevTime_)
		, CurrTime_(InInstance.CurrTime_) {}


	/**
	 * Ÿ�̸� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Timer() = default;


	/**
	 * Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * Ÿ�̸��� �� ���� ��Ÿ �ð����� ����ϴ�.
	 * �̶�, �ð� ������ �ʴ����Դϴ�.
	 * 
	 * @return �� ������ ��Ÿ �ð����� ��ȯ�մϴ�.
	 */
	float GetDeltaTime() const;


	/**
	 * Ÿ�̸Ӱ� ������ �ð��� ������ ��ü �ð����� ��ȯ�մϴ�.
	 * �̶�, �ð� ������ �ʴ����Դϴ�.
	 * 
	 * @return Ÿ�̸Ӱ� ���۵� ������ ������ �ð��� ������ ��ü �ð����� ��ȯ�մϴ�.
	 */
	float GetTotalTime() const;


	/**
	 * Ÿ�̸��� ��� ���¸� �����մϴ�.
	 */
	void Reset();


	/**
	 * Ÿ�̸Ӹ� �����մϴ�.
	 * �̶�, Ÿ�̸Ӱ� �����Ǿ� �ִٸ� �߽õ� �������� ���۵˴ϴ�.
	 */
	void Start();


	/**
	 * Ÿ�̸Ӹ� ������ŵ�ϴ�.
	 */
	void Stop();


	/**
	 * Ÿ�̸Ӹ� ������Ʈ�մϴ�.
	 */
	void Tick();


private:
	/**
	 * ������ Tick ī���� ���� ����ϴ�.
	 * 
	 * @return ������ Tick ī���� ���� ����ϴ�.
	 */
	int64_t GetTickCounter();


private:
	/**
	 * Ÿ�̸��� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsStop_ = false;


	/**
	 * Ÿ�̸Ӱ� ���۵� �ð��Դϴ�.
	 */
	int64_t BaseTime_ = 0LL;


	/**
	 * Ÿ�̸Ӱ� ������ ������ ���� �ð��� �Դϴ�.
	 */
	int64_t PausedTime_ = 0LL;


	/**
	 * Ÿ�̸Ӱ� ������ �ð��Դϴ�.
	 */
	int64_t StopTime_ = 0LL;


	/**
	 * ������ Tick ȣ�� �ð��Դϴ�.
	 */
	int64_t PrevTime_ = 0LL;


	/**
	 * Tick ȣ�� �ð��Գ��ϴ�.
	 */
	int64_t CurrTime_ = 0LL;


	/**
	 * ���� ī���� ���� �������Դϴ�.
	 */
	double SecondsPerCounter_ = 0.0;
};