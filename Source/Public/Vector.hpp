#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * ���ø� ����� 2���� �����Դϴ�.
 */
template <typename T>
struct Vector2
{
	/**
	 * ������ �⺻ �������Դϴ�.
	 * �̶�, ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vector2() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
	}


	/**
	 * ������ �������Դϴ�.
	 *
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 */
	Vector2(T&& InX, T&& InY)
	{
		x = InX;
		y = InY;
	}


	/**
	 * ������ �������Դϴ�.
	 * 
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 */
	Vector2(const T& InX, const T& InY)
	{
		x = InX;
		y = InY;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector2(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector2(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vector2(const Vector2<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vector2(Vector2<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator=(const Vector2<T>& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;

		return *this;
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator=(Vector2<T>&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		x = InInstance.x;
		y = InInstance.y;

		return *this;
	}


	/**
	 * ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vector2<T> operator-() const
	{
		return Vector2<T>(-x, -y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator+(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x + InInstance.x, y + InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator+(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x + InInstance.x, y + InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator-(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x - InInstance.x, y - InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator-(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x - InInstance.x, y - InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator*(const Vector2<T>& InInstance) const
	{
		return Vector2<T>(x * InInstance.x, y * InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector2<T> operator*(Vector2<T>&& InInstance) const
	{
		return Vector2<T>(x * InInstance.x, y * InInstance.y);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator+=(const Vector2<T>& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator+=(Vector2<T>&& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator-=(const Vector2<T>& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2<T>& operator-=(Vector2<T>&& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;

		return *this;
	}


	/**
	 * ������ ù ��° �����Դϴ�.
	 */
	T x;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T y;
};


/**
 * ���ø� ����� 3���� �����Դϴ�.
 */
template <typename T>
struct Vector3
{
	/**
	 * ������ �⺻ �������Դϴ�.
	 * �̶�, ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vector3() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
	}


	/**
	 * ������ �������Դϴ�.
	 *
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 * @param InZ - ������ z �����Դϴ�.
	 */
	Vector3(T&& InX, T&& InY, T&& InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}


	/**
	 * ������ �������Դϴ�.
	 *
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 * @param InZ - ������ z �����Դϴ�.
	 */
	Vector3(const T& InX, const T& InY, const T& InZ)
	{
		x = InX;
		y = InY;
		z = InZ;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector3(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector3(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vector3(const Vector3<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vector3(Vector3<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vector3<T> operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator+(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator+(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator-(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator-(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator*(const Vector3<T>& InInstance) const
	{
		return Vector3<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector3<T> operator*(Vector3<T>&& InInstance) const
	{
		return Vector3<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector3<T>& operator+=(const Vector3<T>& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector3<T>& operator+=(Vector3<T>&& InInstance) noexcept
	{
		x += InInstance.x;
		y += InInstance.y;
		z += InInstance.z;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector3<T>& operator-=(const Vector3<T>& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector3<T>& operator-=(Vector3<T>&& InInstance) noexcept
	{
		x -= InInstance.x;
		y -= InInstance.y;
		z -= InInstance.z;

		return *this;
	}


	/**
	 * ������ ù ��° �����Դϴ�.
	 */
	T x;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T y;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T z;
};



/**
 * ���ø� ����� 4���� �����Դϴ�.
 */
template <typename T>
struct Vector4
{
	/**
	 * ������ �⺻ �������Դϴ�.
	 * �̶�, ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vector4() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
		w = static_cast<T>(0);
	}


	/**
	 * ������ �������Դϴ�.
	 *
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 * @param InZ - ������ z �����Դϴ�.
	 * @param InW - ������ w �����Դϴ�.
	 */
	Vector4(T&& InX, T&& InY, T&& InZ, T&& InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}


	/**
	 * ������ �������Դϴ�.
	 *
	 * @param InX - ������ x �����Դϴ�.
	 * @param InY - ������ y �����Դϴ�.
	 * @param InZ - ������ z �����Դϴ�.
	 * @param InW - ������ w �����Դϴ�.
	 */
	Vector4(const T& InX, const T& InY, const T& InZ, const T& InW)
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector4(T&& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
		w = InElement;
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector4(const T& InElement) noexcept
	{
		x = InElement;
		y = InElement;
		z = InElement;
		w = InElement;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vector4(const Vector4<T>& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vector4(Vector4<T>&& InInstance) noexcept
	{
		x = InInstance.x;
		y = InInstance.y;
		z = InInstance.z;
		w = InInstance.w;
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vector4<T> operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator+(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z, w + InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator+(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x + InInstance.x, y + InInstance.y, z + InInstance.z, w + InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator-(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z, w - InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator-(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x - InInstance.x, y - InInstance.y, z - InInstance.z, w - InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator*(const Vector4<T>& InInstance) const
	{
		return Vector4<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z, w * InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector4<T> operator*(Vector4<T>&& InInstance) const
	{
		return Vector4<T>(x * InInstance.x, y * InInstance.y, z * InInstance.z, w * InInstance.w);
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
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
	 * ������ ù ��° �����Դϴ�.
	 */
	T x;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T y;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T z;


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	T w;
};


/**
 * int Ÿ���� 2���� �����Դϴ�.
 */
using Vec2i = Vector2<int32_t>;


/**
 * float Ÿ���� 2���� �����Դϴ�.
 */
using Vec2f = Vector2<float>;


/**
 * int Ÿ���� 3���� �����Դϴ�.
 */
using Vec3i = Vector3<int32_t>;


/**
 * float Ÿ���� 3���� �����Դϴ�.
 */
using Vec3f = Vector3<float>;


/**
 * int Ÿ���� 4���� �����Դϴ�.
 */
using Vec4i = Vector4<int32_t>;


/**
 * float Ÿ���� 4���� �����Դϴ�.
 */
using Vec4f = Vector4<float>;