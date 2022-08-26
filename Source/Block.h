#pragma once

#include "Mathematics.h"

/**
 * ��� Ŭ�����Դϴ�.
 */
class Block
{
public:
	/**
	 * ����� �����Դϴ�.
	 */
	enum class EColor : int32_t
	{
		Empty  = 0,
		Blue   = 1,
		Green  = 2,
		Aqua   = 3,
		Red    = 4,
		Purple = 5,
		Yellow = 6,
		White  = 7,
		Gray   = 8,
	};


	/**
	 * ���� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		Empty = 0,
		Fill  = 1,
		Wall  = 2
	};


public:
	/**
	 * ��� Ŭ������ �������Դϴ�.
	 */
	Block() noexcept
		: Color(EColor::Empty)
		, State(EState::Empty) {}


	/**
	 * ��� Ŭ������ �������Դϴ�.
	 *
	 * @param InColor - ����� �����Դϴ�.
	 * @param InState - ����� �����Դϴ�.
	 */
	Block(const EColor& InColor, const EState& InState) noexcept
		: Color(InColor)
		, State(InState) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ Block ��ü�Դϴ�.
	 */
	Block(Block&& InInstance) noexcept
		: Color(InInstance.Color)
		, State(InInstance.State) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ Block ��ü�Դϴ�.
	 */
	Block(const Block& InInstance) noexcept
		: Color(InInstance.Color)
		, State(InInstance.State) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ Block ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color = InInstance.Color;
		State = InInstance.State;

		return *this;
	}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ Block ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color = InInstance.Color;
		State = InInstance.State;

		return *this;
	}


	/**
	 * ��� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Block() {}


	/**
	 * ����� ������ ����ϴ�.
	 *
	 * @return ����� ������ ��ȯ�մϴ�.
	 */
	EColor GetColor() const { return Color; }


	/**
	 * ����� ���¸� ����ϴ�.
	 *
	 * @return ����� ���¸� ����ϴ�.
	 */
	EState GetState() const { return State; }


	/**
	 * ����� �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - ����� �׸� �ܼ� ���� ��ǥ�Դϴ�.
	 */
	void Draw(const Math::Vec2i& InPosition);


private:
	/**
	 * ����� �����Դϴ�.
	 */
	EColor Color;


	/**
	 * ����� �����Դϴ�.
	 */
	EState State;
};