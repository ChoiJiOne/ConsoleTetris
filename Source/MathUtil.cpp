#include "MathUtil.h"

Vector2i operator+(const Vector2i& v0, const Vector2i& v1)
{
	return Vector2i(v0.x + v1.x, v0.y + v1.y);
}

Vector2i operator-(const Vector2i& v0, const Vector2i& v1)
{
	return Vector2i(v0.x - v1.x, v0.y - v1.y);
}

Vector2i operator*(const Vector2i& v0, const Vector2i& v1)
{
	return Vector2i(v0.x * v1.x, v0.y * v1.y);
}

Vector2i operator*(const Vector2i& v, int32_t scale)
{
	return Vector2i(v.x * scale, v.y * scale);
}

Vector2i operator*(int32_t scale, const Vector2i& v)
{
	return Vector2i(v.x * scale, v.y * scale);
}