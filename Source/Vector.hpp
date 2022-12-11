#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * ���п��� �����ϴ� �����Դϴ�.
 */
template <typename Type, int32_t Size>
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
		std::fill(Element_, Element_ + Size, InElement);
	}


	/**
	 * ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param InElement - ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vector(Type&& InElement) noexcept
	{
		std::fill(Element_, Element_ + Size, InElement);
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vector(const Vector& InInstance) noexcept
	{
		std::copy(InInstance.Element_, InInstance.Element_ + Size, Element_);
	}


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vector(Vector&& InInstance) noexcept
	{
		std::copy(InInstance.Element_, InInstance.Element_ + Size, Element_);
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

		std::copy(InInstance.Element_, InInstance.Element_ + Size, Element_);

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

		std::copy(InInstance.Element_, InInstance.Element_ + Size, Element_);

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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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

		for (int32_t Index = 0; Index < Size; ++Index)
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
		for (int32_t Index = 0; Index < Size; ++Index)
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
		for (int32_t Index = 0; Index < Size; ++Index)
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
		for (int32_t Index = 0; Index < Size; ++Index)
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
		for (int32_t Index = 0; Index < Size; ++Index)
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


	Type Element_[Size];
};