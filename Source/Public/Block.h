#pragma once

#include <Vector.hpp>

#include <unordered_map>


/**
 * ��Ʈ���� ������ ����Դϴ�.
 * �̶�, �� ����� ���� ���� ������ ����� ��Ʈ�ι̳뿡�� ����մϴ�.
 */
class Block
{
public:
	/**
	 * ���� Ÿ���Դϴ�.
	 */
	enum class EType : int32_t
	{
		NONE    = 0,
		BLUE    = 1,
		GREEN   = 2,
		AQUA    = 3,
		RED     = 4,
		PURPLE  = 5,
		YELLOW  = 6,
		WHITE   = 7,
		GRAY    = 8,
	};


	/**
	 * ���� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		EMPTY = 0,
		FILL  = 1,
		WALL  = 2
	};


public:
	/**
	 * ���� �⺻ �������Դϴ�.
	 */
	Block() noexcept
	{
		Type_ = EType::NONE;
		State_ = EState::EMPTY;
	}


	/**
	 * ���� �������Դϴ�.
	 *
	 * @param InType - ���� Ÿ���Դϴ�.
	 * @param InState - ���� �����Դϴ�.
	 */
	Block(const EType& InType, const EState& InState)
	{
		Type_ = InType;
		State_ = InState;
	}


	/**
	 * ����� ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 */
	Block(Block&& InInstance) noexcept
	{
		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
	}


	/**
	 * ����� ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 */
	Block(const Block& InInstance) noexcept
	{
		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
	}


	/**
	 * ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Block() {}


	/**
	 * ����� ���� �������Դϴ�.
	 * �̶�, �ڱ� �ڽ��� �����ϸ� ���� ������ �������� �ʽ��ϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Type_ = InInstance.Type_;
		State_ = InInstance.State_;

		return *this;
	}


	/**
	 * ����� ���� �������Դϴ�.
	 * �̶�, �ڱ� �ڽ��� �����ϸ� ���� ������ �������� �ʽ��ϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Type_ = InInstance.Type_;
		State_ = InInstance.State_;

		return *this;
	}


	/**
	 * ����� Ÿ���� ����ϴ�.
	 * 
	 * @return ����� Ÿ���� ��ȯ�մϴ�.
	 */
	EType GetType() const { return Type_; }


	/**
	 * ����� ���¸� ����ϴ�.
	 * 
	 * @return ����� ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return State_; }


private:
	/**
	 * ���� Ÿ���Դϴ�.
	 */
	EType Type_;


	/**
	 * ���� �����Դϴ�.
	 */
	EState State_;
};