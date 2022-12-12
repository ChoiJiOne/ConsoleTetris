#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * 템플릿 기반의 2차원 벡터입니다.
 */
template <typename T>
struct Vector2
{
	/**
	 * 벡터의 기본 생성자입니다.
	 * 이때, 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector2() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
	}


	/**
	 * 벡터의 생성자입니다.
	 *
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 */
	Vector2(T&& InX, T&& InY)
	{
		x = InX;
		y = InY;
	}


	/**
	 * 벡터의 생성자입니다.
	 * 
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 */
	Vector2(const T& InX, const T& InY)
	{
		x = InX;
		y = InY;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector2(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector2(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector2(const Vector2<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector2(Vector2<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator=(const Vector2<T>& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;

		return *this;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator=(Vector2<T>&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;

		return *this;
	}


	/**
	 * 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector2<T> operator-() const
	{
		return Vector2<T>(-x, -y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector2<T> operator+(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x + InInstance.x, y + InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector2<T> operator+(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x + InInstance.x, y + InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector2<T> operator-(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x - InInstance.x, y - InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector2<T> operator-(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x - InInstance.x, y - InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector2<T> operator*(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x * InInstance.x, y * InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector2<T> operator*(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x * InInstance.x, y * InInstance.y);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator+=(const Vector2<T>& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator+=(Vector2<T>&& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator-=(const Vector2<T>& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator-=(Vector2<T>&& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;

		return *this;
	}


	/**
	 * 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * 벡터의 두 번째 원소입니다.
	 */
	T y;
};


/**
 * 템플릿 기반의 3차원 벡터입니다.
 */
template <typename T>
struct Vector3
{
	/**
	 * 벡터의 기본 생성자입니다.
	 * 이때, 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector3() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
	}


	/**
	 * 벡터의 생성자입니다.
	 *
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 * @param InZ - 벡터의 z 성분입니다.
	 */
	Vector3(T&& InX, T&& InY, T&& InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}


	/**
	 * 벡터의 생성자입니다.
	 *
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 * @param InZ - 벡터의 z 성분입니다.
	 */
	Vector3(const T& InX, const T& InY, const T& InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector3(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector3(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector3(const Vector3<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector3(Vector3<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator=(const Vector3<T>& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;

		return *this;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator=(Vector3<T>&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;

		return *this;
	}


	/**
	 * 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector3<T> operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector3<T> operator+(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector3<T> operator+(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector3<T> operator-(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector3<T> operator-(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector3<T> operator*(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector3<T> operator*(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator+=(const Vector3<T>& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator+=(Vector3<T>&& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator-=(const Vector3<T>& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator-=(Vector3<T>&& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;

		return *this;
	}


	/**
	 * 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * 벡터의 두 번째 원소입니다.
	 */
	T y;


	/**
	 * 벡터의 세 번째 원소입니다.
	 */
	T z;
};



/**
 * 템플릿 기반의 4차원 벡터입니다.
 */
template <typename T>
struct Vector4
{
	/**
	 * 벡터의 기본 생성자입니다.
	 * 이때, 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector4() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
		w = static_cast<T>(0);
	}


	/**
	 * 벡터의 생성자입니다.
	 *
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 * @param InZ - 벡터의 z 성분입니다.
	 * @param InW - 벡터의 w 성분입니다.
	 */
	Vector4(T&& InX, T&& InY, T&& InZ, T&& InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}


	/**
	 * 벡터의 생성자입니다.
	 *
	 * @param InX - 벡터의 x 성분입니다.
	 * @param InY - 벡터의 y 성분입니다.
	 * @param InZ - 벡터의 z 성분입니다.
	 * @param InW - 벡터의 w 성분입니다.
	 */
	Vector4(const T& InX, const T& InY, const T& InZ, const T& InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector4(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
		w = InElement;
	}


	/**
	 * 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param InElement - 모든 원소를 초기화 할 값입니다.
	 */
	Vector4(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
		w = InElement;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector4(const Vector4<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;
	}


	/**
	 * 벡터의 복사 생성자입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector4(Vector4<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator=(const Vector4<T>& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;

		return *this;
	}


	/**
	 * 벡터의 대입 연산자 입니다.
	 *
	 * @param InInstance - 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator=(Vector4<T>&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;

		return *this;
	}


	/**
	 * 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector4<T> operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector4<T> operator+(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z, w + InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param InInstance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector4<T> operator+(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z, w + InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector4<T> operator-(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z, w - InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param InInstance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector4<T> operator-(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z, w - InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector4<T> operator*(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z, w * InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param InInstance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector4<T> operator*(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z, w * InInstance.w);
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator+=(const Vector4<T>& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;
		w += InInstance.w;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator+=(Vector4<T>&& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;
		w += InInstance.w;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator-=(const Vector4<T>& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;
		w -= InInstance.w;

		return *this;
	}


	/**
	 * 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator-=(Vector4<T>&& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;
		w -= InInstance.w;

		return *this;
	}


	/**
	 * 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * 벡터의 두 번째 원소입니다.
	 */
	T y;


	/**
	 * 벡터의 세 번째 원소입니다.
	 */
	T z;


	/**
	 * 벡터의 네 번째 원소입니다.
	 */
	T w;
};


/**
 * int 타입의 2차원 벡터입니다.
 */
using Vec2i = Vector2<int32_t>;


/**
 * float 타입의 2차원 벡터입니다.
 */
using Vec2f = Vector2<float>;


/**
 * int 타입의 3차원 벡터입니다.
 */
using Vec3i = Vector3<int32_t>;


/**
 * float 타입의 3차원 벡터입니다.
 */
using Vec3f = Vector3<float>;


/**
 * int 타입의 4차원 벡터입니다.
 */
using Vec4i = Vector4<int32_t>;


/**
 * float 타입의 4차원 벡터입니다.
 */
using Vec4f = Vector4<float>;