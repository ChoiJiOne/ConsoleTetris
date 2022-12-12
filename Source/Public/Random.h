#pragma once

#include <cstdint>


/**
 * 임의의 정수를 생성합니다.
 *
 * @param InMinValue - 생성할 난수 범위의 최솟값입니다.
 * @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
 *
 * @return  생성된 임의의 정수를 반환합니다.
 */
int32_t GenerateRandomInt(const int32_t& InMinValue, const int32_t& InMaxValue);


 /**
  * 임의의 실수를 생성합니다.
  *
  * @param InMinValue - 생성할 난수 범위의 최솟값입니다.
  * @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
  *
  * @return  생성된 임의의 실수를 반환합니다.
  */
float GenerateRandomFloat(const float& InMinValue, const float& InMaxValue);