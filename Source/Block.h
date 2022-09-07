#pragma once

#include "Vector.h"
#include "Console.h"

#include <unordered_map>


/**
 * ��Ʈ���� ������ ��� Ŭ�����Դϴ�.
 * �̶�, �� ��� Ŭ������ ���� ���� ������ ����� ��Ʈ�ι̳뿡�� ����մϴ�.
 */
class Block
{
public:
	/**
	 * ����� �����Դϴ�.
	 */
	enum class EColor : int32_t
	{
		None   = 0,
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
		: Color_(EColor::None)
		, State_(EState::Empty) {}


	/**
	 * ��� Ŭ������ �������Դϴ�.
	 *
	 * @param InColor - ����� �����Դϴ�.
	 * @param InState - ����� �����Դϴ�.
	 */
	Block(const EColor& InColor, const EState& InState) noexcept
		: Color_(InColor)
		, State_(InState) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ Block ��ü�Դϴ�.
	 */
	Block(Block&& InInstance) noexcept
		: Color_(InInstance.Color_)
		, State_(InInstance.State_) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ Block ��ü�Դϴ�.
	 */
	Block(const Block& InInstance) noexcept
		: Color_(InInstance.Color_)
		, State_(InInstance.State_) {}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 * �̶�, �ڱ� �ڽ��� �����ϸ� ���� ������ �������� �ʽ��ϴ�.
	 *
	 * @param InInstance - ������ Block ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color_ = InInstance.Color_;
		State_ = InInstance.State_;

		return *this;
	}


	/**
	 * ��� Ŭ������ ���� �������Դϴ�.
	 * �̶�, �ڱ� �ڽ��� �����ϸ� ���� ������ �������� �ʽ��ϴ�.
	 *
	 * @param InInstance - ������ Block ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color_ = InInstance.Color_;
		State_ = InInstance.State_;

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
	EColor GetColor() const { return Color_; }


	/**
	 * ����� ���¸� ����ϴ�.
	 *
	 * @return ����� ���¸� ����ϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * ����� �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - ����� �׸� �ܼ� ���� ��ǥ�Դϴ�.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * ����� �����Դϴ�.
	 */
	EColor Color_;


	/**
	 * ����� �����Դϴ�.
	 */
	EState State_;


	/**
	 * �� ���� �����ϴ� �ܼ� �����Դϴ�.
	 */
	static std::unordered_map<EColor, Console::ETextColor> BlockColorMappings;

};