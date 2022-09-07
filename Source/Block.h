#pragma once

#include "Vector.h"
#include "Console.h"

#include <unordered_map>


/**
 * 테트리스 게임의 블록 클래스입니다.
 * 이때, 이 블록 클래스는 가장 작은 단위로 보드와 테트로미노에서 사용합니다.
 */
class Block
{
public:
	/**
	 * 블록의 색상입니다.
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
		: Color_(EColor::None)
		, State_(EState::Empty) {}


	/**
	 * 블록 클래스의 생성자입니다.
	 *
	 * @param InColor - 블록의 색상입니다.
	 * @param InState - 블록의 상태입니다.
	 */
	Block(const EColor& InColor, const EState& InState) noexcept
		: Color_(InColor)
		, State_(InState) {}


	/**
	 * 블록 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 Block 객체입니다.
	 */
	Block(Block&& InInstance) noexcept
		: Color_(InInstance.Color_)
		, State_(InInstance.State_) {}


	/**
	 * 블록 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 Block 객체입니다.
	 */
	Block(const Block& InInstance) noexcept
		: Color_(InInstance.Color_)
		, State_(InInstance.State_) {}


	/**
	 * 블록 클래스의 대입 연산자입니다.
	 * 이때, 자기 자신을 대입하면 대입 연산을 수행하지 않습니다.
	 *
	 * @param InInstance - 복사할 Block 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color_ = InInstance.Color_;
		State_ = InInstance.State_;

		return *this;
	}


	/**
	 * 블록 클래스의 대입 연산자입니다.
	 * 이때, 자기 자신을 대입하면 대입 연산을 수행하지 않습니다.
	 *
	 * @param InInstance - 복사할 Block 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Color_ = InInstance.Color_;
		State_ = InInstance.State_;

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
	EColor GetColor() const { return Color_; }


	/**
	 * 블록의 상태를 얻습니다.
	 *
	 * @return 블록의 상태를 얻습니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * 블록을 콘솔 화면에 그립니다.
	 *
	 * @param InPosition - 블록을 그릴 콘솔 상의 좌표입니다.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * 블록의 색상입니다.
	 */
	EColor Color_;


	/**
	 * 블록의 상태입니다.
	 */
	EState State_;


	/**
	 * 블럭 색상에 대응하는 콘솔 색상입니다.
	 */
	static std::unordered_map<EColor, Console::ETextColor> BlockColorMappings;

};