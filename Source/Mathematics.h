#pragma once

#include <cstdint>
#include <algorithm>

namespace Math
{
	/**
	 * �Է� ���� ���� Ư�� ������ ������ �ڸ��ϴ�.
	 *
	 * @param InValue - ���� ���� �ڸ����� �ϴ� ���Դϴ�.
	 * @param InMinValue - ������ �ּڰ��Դϴ�.
	 * @param InMaxValue - ������ �ִ��Դϴ�.
	 *
	 * @return  ���� ���� ������ �ڸ� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline static T Clamp(T InValue, T InMinValue, T InMaxValue)
	{
		if (InMinValue > InMaxValue)
		{
			std::swap(InMinValue, InMaxValue);
		}

		if (InValue < InMinValue)
		{
			return InMinValue;
		}
		else if (InValue > InMaxValue)
		{
			return InMaxValue;
		}
		else
		{
			return InValue;
		}
	}


	/**
	 * �� ���� ���� �����մϴ�.
	 *
	 * @param InFirst - ������ ������ �� ���� �������Դϴ�.
	 * @param InLast - ������ ������ �� ���� �����Դϴ�.
	 * @param InAlpha - �� ���� ���� �����Դϴ�. �̶�, ������ 0 ~ 1�Դϴ�.
	 *
	 * @return  �Է¹��� �� ���� ���� �������� ��ȯ�մϴ�.
	 */
	template<typename T>
	inline static T Lerp(const T& InFirst, const T& InLast, float InAlpha)
	{
		InAlpha = Clamp<float>(InAlpha, 0.0f, 1.0f);
		return (InFirst * (1.0f - InAlpha)) + (InLast * InAlpha);
	}
}