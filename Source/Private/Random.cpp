#include <Random.h>

#include <chrono>
#include <random>

int32_t GenerateRandomInt(const int32_t& InMinValue, const int32_t& InMaxValue)
{
	int32_t MinValue = std::min<int32_t>(InMinValue, InMaxValue);
	int32_t MaxValue = std::max<int32_t>(InMinValue, InMaxValue);

	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_int_distribution<int32_t> Distribution(InMinValue, InMaxValue);

	return Distribution(Generator);
}

float GenerateRandomFloat(const float& InMinValue, const float& InMaxValue)
{
	float MinValue = std::min<float>(InMinValue, InMaxValue);
	float MaxValue = std::max<float>(InMinValue, InMaxValue);

	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_real_distribution<float> Distribution(MinValue, MaxValue);

	return Distribution(Generator);
}