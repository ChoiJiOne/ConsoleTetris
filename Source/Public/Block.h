#pragma once

#include <ConsoleManager.h>
#include <GameObject.h>
#include <Vector.hpp>


/**
 * 테트리스의 블럭입니다.
 */
class Block : public GameObject
{
public:
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
	 * 블럭의 생성자입니다.
	 * 
	 * @param InPosition - 콘솔 상의 블럭의 위치입니다.
	 * @param InState - 블럭의 상태입니다.
	 * @param InColor - 블럭의 색상입니다.
	 */
	Block(const Vec2i& InPosition, const EState& InState, const EColor& InColor)
		: Position_(InPosition)
		, State_(InState)
		, Color_(InColor)
		, Text_(GetStateText(State_)) {}


	/**
	 * 블럭의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Block(Block&& InInstance) noexcept
		: Position_(InInstance.Position_)
		, State_(InInstance.State_)
		, Color_(InInstance.Color_)
		, Text_(InInstance.Text_) {}


	/**
	 * 블럭의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Block(const Block& InInstance) noexcept
		: Position_(InInstance.Position_)
		, State_(InInstance.State_)
		, Color_(InInstance.Color_) 
		, Text_(InInstance.Text_) {}


	/**
	 * 블럭의 가상 소멸자입니다.
	 */
	virtual ~Block() {}


	/**
	 * 블럭의 대입 연산자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 * 
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(Block&& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Position_ = InInstance.Position_;
		State_ = InInstance.State_;
		Color_ = InInstance.Color_;
		Text_ = InInstance.Text_;

		return *this;
	}


	/**
	 * 블럭의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Block& operator=(const Block& InInstance) noexcept
	{
		if (this == &InInstance) return *this;

		Position_ = InInstance.Position_;
		State_ = InInstance.State_;
		Color_ = InInstance.Color_;
		Text_ = InInstance.Text_;

		return *this;
	}


	/**
	 * 블럭을 업데이트합니다.
	 * 
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 블럭을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * 블럭의 위치를 얻습니다.
	 * 
	 * @return 블럭의 위치를 반환합니다.
	 */
	Vec2i GetPosition() const { return Position_; }


	/**
	 * 블럭의 위치를 설정합니다.
	 * 
	 * @param InPosition - 설정할 블럭의 위치입니다.
	 */
	void SetPosition(const Vec2i& InPosition) { Position_ = InPosition; }


	/**
	 * 블럭의 상태를 얻습니다.
	 * 
	 * @return 블럭의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * 블럭의 상태를 설정합니다.
	 * 
	 * @param InState - 설정할 블럭의 상태입니다.
	 */
	void SetState(const EState& InState) { State_ = InState; }


private:
	/**
	 * 블럭의 상태에 대응하는 텍스트를 얻습니다.
	 * 
	 * @param InState - 블럭의 상태입니다.
	 * 
	 * @return 블럭의 상태에 대응하는 텍스트를 얻습니다.
	 */
	static std::string GetStateText(const EState& InState);


private:
	/**
	 * 블럭의 위치입니다.
	 */
	Vec2i Position_;


	/**
	 * 블럭의 상태입니다.
	 */
	EState State_ = EState::EMPTY;
	

	/**
	 * 블럭의 색상입니다.
	 */
	EColor Color_ = EColor::BLACK;


	/**
	 * 블럭 상태에 대응하는 텍스트입니다.
	 */
	std::string Text_;
};