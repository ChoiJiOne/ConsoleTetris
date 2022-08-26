#pragma once

#include "Mathematics.h"

/**
 * 블록 클래스입니다.
 */
class Block
{
public:
	/**
	 * 블록의 색상입니다.
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
	 * 블럭의 상태입니다.
	 */
	enum class EState : int32_t
	{
		Empty = 0,
		Fill  = 1,
		Wall  = 2
	};


public:
	/**
	 * 블록 클래스의 생성자입니다.
	 */
	Block() noexcept
		: Color(EColor::Empty)
		, State(EState::Empty) {}


	/**
	 * 블록 클래스의 생성자입니다.
	 *
	 * @param InColor - 블록의 색상입니다.
	 * @param InState - 블록의 상태입니다.
	 */
	Block(const EColor& InColor, const EState& InState) noexcept
		: Color(InColor)
		, State(InState) {}


	/**
	 * 블록 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 Block 객체입니다.
	 */
	Block(Block&& InInstance) noexcept
		: Color(InInstance.Color)
		, State(InInstance.State) {}


	/**
	 * 블록 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 Block 객체입니다.
	 */
	Block(const Block& InInstance) noexcept
		: Color(InInstance.Color)
		, State(InInstance.State) {}


	/**
	 * 블록 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 Block 객체입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color = InInstance.Color;
		State = InInstance.State;

		return *this;
	}


	/**
	 * 블록 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 Block 객체입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color = InInstance.Color;
		State = InInstance.State;

		return *this;
	}


	/**
	 * 블록 클래스의 가상 소멸자입니다.
	 */
	virtual ~Block() {}


	/**
	 * 블록의 색상을 얻습니다.
	 *
	 * @return 블록의 색상을 반환합니다.
	 */
	EColor GetColor() const { return Color; }


	/**
	 * 블록의 상태를 얻습니다.
	 *
	 * @return 블록의 상태를 얻습니다.
	 */
	EState GetState() const { return State; }


	/**
	 * 블록을 콘솔 화면에 그립니다.
	 *
	 * @param InPosition - 블록을 그릴 콘솔 상의 좌표입니다.
	 */
	void Draw(const Math::Vec2i& InPosition);


private:
	/**
	 * 블록의 색상입니다.
	 */
	EColor Color;


	/**
	 * 블록의 상태입니다.
	 */
	EState State;
};