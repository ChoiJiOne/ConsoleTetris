#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * ���п��� �����ϴ� �����Դϴ�.
 */
template <typename Type, int32_t Dimension>
struct Vector
{
	/**
	 * ������ �⺻ �������Դϴ�.
	 * �̶�, ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	explicit Vector() noexcept 
		: Vector(static_cast<Type>(0)) { }


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector(const Type& InElement) noexcept
	{
		std::fill(Element_, Element_ + Dimension, InElement);
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector(Type&& InElement) noexcept
	{
		std::fill(Element_, Element_ + Dimension, InElement);
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vector(const Vector& InInstance) noexcept
	{
		std::copy(InInstance.Element_, InInstance.Element_ + Dimension, Element_);
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vector(Vector&& InInstance) noexcept
	{
		std::copy(InInstance.Element_, InInstance.Element_ + Dimension, Element_);
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator=(const Vector& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		std::copy(InInstance.Element_, InInstance.Element_ + Dimension, Element_);

		return *this;
	}


	/**
	 * ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator=(Vector&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		std::copy(InInstance.Element_, InInstance.Element_ + Dimension, Element_);

		return *this;
	}


	/**
	 * ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vector operator-() const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = -Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector operator+(const Vector& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] + InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector operator+(Vector&& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] + InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector operator-(const Vector& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] - InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vector operator-(Vector&& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] - InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector operator*(const Vector& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] * InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @param InInstance ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vector operator*(Vector&& InInstance) const
	{
		Vector Result;

		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Result[Index] = Element_[Index] * InInstance.Element_[Index];
		}

		return Result;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator+=(const Vector& InInstance) noexcept
	{
		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Element_[Index] += InInstance.Element_[Index];
		}

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator+=(Vector&& InInstance) noexcept
	{
		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Element_[Index] += InInstance.Element_[Index];
		}

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator-=(const Vector& InInstance) noexcept
	{
		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Element_[Index] -= InInstance.Element_[Index];
		}

		return *this;
	}


	/**
	 * �� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector& operator-=(Vector&& InInstance) noexcept
	{
		for (int32_t Index = 0; Index < Dimension; ++Index)
		{
			Element_[Index] -= InInstance.Element_[Index];
		}

		return *this;
	}


	/**
	 * ������ ���Ҹ� �ε����� �����մϴ�.
	 * �̶�, ������ ���� ������ �� �ֽ��ϴ�.
	 *
	 * @param InIndex - ������ �ε��� ���Դϴ�.
	 *
	 * @throws �ε��� ���� ������ ����� ���� ������ �����ϰ� ���α׷��� ����˴ϴ�.
	 *
	 * @return �ε����� �����ϴ� ���Ҹ� ��ȯ�մϴ�.
	 */
	Type& operator[](const int32_t& InIndex)
	{
		return Element_[InIndex];
	}


	/**
	 * ������ ���Ҹ� �ε����� �����մϴ�.
	 * �̶�, ������ ���� ������ �� �ֽ��ϴ�.
	 *
	 * @param InIndex - ������ �ε��� ���Դϴ�.
	 *
	 * @throws �ε��� ���� ������ ����� ���� ������ �����ϰ� ���α׷��� ����˴ϴ�.
	 *
	 * @return �ε����� �����ϴ� ���Ҹ� ��ȯ�մϴ�.
	 */
	Type& operator[](int32_t&& InIndex)
	{
		return Element_[InIndex];
	}


	/**
	 * ������ ���Ҹ� �ε����� �����մϴ�.
	 * �̶�, ������ ���� ������ �� �����ϴ�.
	 *
	 * @param InIndex - ������ �ε��� ���Դϴ�.
	 *
	 * @throws �ε��� ���� ������ ����� ���� ������ �����ϰ� ���α׷��� ����˴ϴ�.
	 *
	 * @return �ε����� �����ϴ� ���Ҹ� ��ȯ�մϴ�.
	 */
	const Type& operator[](const int32_t& InIndex) const
	{
		return Element_[InIndex];
	}


	/**
	 * ������ ���Ҹ� �ε����� �����մϴ�.
	 * �̶�, ������ ���� ������ �� �����ϴ�.
	 *
	 * @param InIndex - ������ �ε��� ���Դϴ�.
	 *
	 * @throws �ε��� ���� ������ ����� ���� ������ �����ϰ� ���α׷��� ����˴ϴ�.
	 *
	 * @return �ε����� �����ϴ� ���Ҹ� ��ȯ�մϴ�.
	 */
	const Type& operator[](int32_t&& InIndex) const
	{
		return Element_[InIndex];
	}


	/**
	 * ������ �����Դϴ�.
	 */
	Type Element_[Dimension];
};


/**
 * ���п��� �����ϴ� 2���� �����Դϴ�.
 */
template <typename Type>
struct Vector2 : public Vector<Type, 2>
{
	/**
	 * �⺻ �������Դϴ�.
	 */
	Vector2() : Vector<Type, 2>() {}


	/**
	 * �������Դϴ�.
	 *
	 * @param InX - ������ ù ��° �����Դϴ�.
	 * @param InY - ������ �� ��° �����Դϴ�.
	 */
	Vector2(Type InX, Type InY) noexcept
	{
		x = InX;
		y = InY;
	}


	/**
	 * 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ 2���� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ 2���� ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2& operator=(const Vector2& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Vector<Type, 2>::operator=(InInstance);

		return *this;
	}


	/**
	 * 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ 2���� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ 2���� ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vector2& operator=(Vector2&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Vector<Type, 2>::operator=(InInstance);

		return *this;
	}


	/**
	 * ������ ù ��° �����Դϴ�.
	 */
	Type& x = Element_[0];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& y = Element_[1];
};


/**
 * ���п��� �����ϴ� 3���� �����Դϴ�.
 */
template <typename Type>
struct Vector3 : public Vector<Type, 3>
{
	/**
	 * �⺻ �������Դϴ�.
	 */
	Vector3() : Vector<Type, 3>() {}


	/**
	 * �������Դϴ�.
	 *
	 * @param InX - ������ ù ��° �����Դϴ�.
	 * @param InY - ������ �� ��° �����Դϴ�.
	 * @param InZ - ������ �� ��° �����Դϴ�.
	 */
	Vector3(Type InX, Type InY, Type InZ) noexcept
	{
		x = InX;
		y = InY;
		z = InZ;
	}


	/**
	 * ������ ù ��° �����Դϴ�.
	 */
	Type& x = Element_[0];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& y = Element_[1];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& z = Element_[2];
};


/**
 * ���п��� �����ϴ� 4���� �����Դϴ�.
 */
template <typename Type>
struct Vector4 : public Vector<Type, 4>
{
	/**
	 * �⺻ �������Դϴ�.
	 */
	Vector4() : Vector<Type, 4>() {}


	/**
	 * �������Դϴ�.
	 *
	 * @param InX - ������ ù ��° �����Դϴ�.
	 * @param InY - ������ �� ��° �����Դϴ�.
	 * @param InZ - ������ �� ��° �����Դϴ�.
	 * @param InW - ������ �� ��° �����Դϴ�.
	 */
	Vector4(Type InX, Type InY, Type InZ, Type InW) noexcept
	{
		x = InX;
		y = InY;
		z = InZ;
		w = InW;
	}


	/**
	 * ������ ù ��° �����Դϴ�.
	 */
	Type& x = Element_[0];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& y = Element_[1];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& z = Element_[2];


	/**
	 * ������ �� ��° �����Դϴ�.
	 */
	Type& w = Element_[3];
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