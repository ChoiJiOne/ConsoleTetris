#pragma once

#include <chrono>
#include <random>


/**
 * ������ ������ �����մϴ�.
 *
 * @param InMinValue - ������ ���� ������ �ּڰ��Դϴ�.
 * @param InMaxValue - ������ ���� ������ �ִ��Դϴ�.
 *
 * @return  ������ ������ ������ ��ȯ�մϴ�.
 */
template <typename T>
inline static int32_t GenerateRandomInt(T InMinValue, T InMaxValue)
{
	if (InMinValue > InMaxValue)
	{
		std::swap(InMinValue, InMaxValue);
	}

	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_int_distribution<T> Distribution(InMinValue, InMaxValue);

	return Distribution(Generator);
}


/**
 * ������ �Ǽ��� �����մϴ�.
 *
 * @param InMinValue - ������ ���� ������ �ּڰ��Դϴ�.
 * @param InMaxValue - ������ ���� ������ �ִ��Դϴ�.
 *
 * @return  ������ ������ �Ǽ��� ��ȯ�մϴ�.
 */
template <typename T>
inline static float GenerateRandomFloat(T InMinValue, T InMaxValue)
{
	if (InMinValue > InMaxValue)
	{
		std::swap(InMinValue, InMaxValue);
	}

	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_real_distribution<T> Distribution(InMinValue, InMaxValue);

	return Distribution(Generator);
}