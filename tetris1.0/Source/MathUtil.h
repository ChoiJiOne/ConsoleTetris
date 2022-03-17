#pragma once

#include "Common.h"

struct Vector2i
{
	Vector2i()                       noexcept : x(0), y(0) {}
	Vector2i(int32_t x_, int32_t y_) noexcept : x(x_), y(y_) {}
	Vector2i(const Vector2i& v)	     noexcept : x(v.x), y(v.y) {}
	Vector2i(Vector2i&& v)		     noexcept : x(v.x), y(v.y) {}

	Vector2i& operator=(const Vector2i& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}

	Vector2i& operator=(Vector2i&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}

	Vector2i operator-() const
	{
		return Vector2i(-x, -y);
	}

	int32_t x; int32_t y;
};

Vector2i operator+(const Vector2i& v0, const Vector2i& v1);
Vector2i operator-(const Vector2i& v0, const Vector2i& v1);
Vector2i operator*(const Vector2i& v0, const Vector2i& v1);
Vector2i operator*(const Vector2i& v, int32_t scale);
Vector2i operator*(int32_t scale, const Vector2i& v);