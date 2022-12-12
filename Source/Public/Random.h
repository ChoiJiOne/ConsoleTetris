#pragma once

#include <cstdint>


/**
 * ������ ������ �����մϴ�.
 *
 * @param InMinValue - ������ ���� ������ �ּڰ��Դϴ�.
 * @param InMaxValue - ������ ���� ������ �ִ��Դϴ�.
 *
 * @return  ������ ������ ������ ��ȯ�մϴ�.
 */
int32_t GenerateRandomInt(const int32_t& InMinValue, const int32_t& InMaxValue);


 /**
  * ������ �Ǽ��� �����մϴ�.
  *
  * @param InMinValue - ������ ���� ������ �ּڰ��Դϴ�.
  * @param InMaxValue - ������ ���� ������ �ִ��Դϴ�.
  *
  * @return  ������ ������ �Ǽ��� ��ȯ�մϴ�.
  */
float GenerateRandomFloat(const float& InMinValue, const float& InMaxValue);