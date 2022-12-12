#pragma once

#include <Vector.hpp>
#include <ConsoleManager.h>

#include <unordered_map>


/**
 * 테트리스 게임의 블록입니다.
 * 이때, 이 블록은 가장 작은 단위로 보드와 테트로미노에서 사용합니다.
 */
class Block
{
public:
	/**
	 * 블럭의 타입입니다.
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
	 * 블럭의 상태입니다.
	 */
	enum class EState : int32_t
	{
		EMPTY = 0,
		FILL  = 1,
		WALL  = 2
	};


public:
	/**
	 * 블럭의 기본 생성자입니다.
	 */
	Block() noexcept
	{
		Type_ = EType::NONE;
		State_ = EState::EMPTY;
	}


	/**
	 * 블럭의 생성자입니다.
	 *
	 * @param InType - 블럭의 타입입니다.
	 * @param InState - 블럭의 상태입니다.
	 */
	Block(const EType& InType, const EState& InState)
	{
		Type_ = InType;
		State_ = InState;
	}


	/**
	 * 블럭의 생성자입니다.
	 * 
	 * @param InType - 블럭의 타입입니다.
	 * @param InState - 블럭의 상태입니다.
	 * @param InPosition - 블럭의 보드상 위치입니다.
	 */
	Block(const EType& InType, const EState& InState, const Vec2i& InPosition)
	{
		Type_ = InType;
		State_ = InState;
		Position_ = InPosition;
	}


	/**
	 * 블록의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 */
	Block(Block&& InInstance) noexcept
	{
		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
		Position_ = InInstance.Position_;
	}


	/**
	 * 블록의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 객체입니다.
	 */
	Block(const Block& InInstance) noexcept
	{
		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
		Position_ = InInstance.Position_;
	}


	/**
	 * 블록의 가상 소멸자입니다.
	 */
	virtual ~Block() {}


	/**
	 * 블록의 대입 연산자입니다.
	 * 이때, 자기 자신을 대입하면 대입 연산을 수행하지 않습니다.
	 *
	 * @param InInstance - 대입할 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
		Position_ = InInstance.Position_;

		return *this;
	}


	/**
	 * 블록의 대입 연산자입니다.
	 * 이때, 자기 자신을 대입하면 대입 연산을 수행하지 않습니다.
	 *
	 * @param InInstance - 대입할 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Type_ = InInstance.Type_;
		State_ = InInstance.State_;
		Position_ = InInstance.Position_;

		return *this;
	}


private:
	/**
	 * 블럭의 타입입니다.
	 */
	EType Type_;


	/**
	 * 블럭의 상태입니다.
	 */
	EState State_;


	/**
	 * 보드 상 블럭의 현재 위치입니다.
	 */
	Vec2i Position_;
};