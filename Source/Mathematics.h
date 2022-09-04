#pragma once

#include <cstdint>
#include <algorithm>

namespace Math
{
	/**
	 * 입력 받은 값을 특정 범위의 값으로 자릅니다.
	 *
	 * @param InValue - 범위 내로 자르고자 하는 값입니다.
	 * @param InMinValue - 범위의 최솟값입니다.
	 * @param InMaxValue - 범위의 최댓값입니다.
	 *
	 * @return  범위 내의 값으로 자른 값을 반환합니다.
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
	 * 두 값을 선형 보간합니다.
	 *
	 * @param InFirst - 보간을 수행할 두 값의 시작점입니다.
	 * @param InLast - 보간을 수행할 두 값의 끝점입니다.
	 * @param InAlpha - 두 값의 보간 비율입니다. 이때, 범위는 0 ~ 1입니다.
	 *
	 * @return  입력받은 두 값의 선형 보간값을 반환합니다.
	 */
	template<typename T>
	inline static T Lerp(const T& InFirst, const T& InLast, float InAlpha)
	{
		InAlpha = Clamp<float>(InAlpha, 0.0f, 1.0f);
		return (InFirst * (1.0f - InAlpha)) + (InLast * InAlpha);
	}
}