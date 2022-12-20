#pragma once

#include <ConsoleManager.h>
#include <GameObject.h>
#include <Vector.hpp>


/**
 * ��Ʈ������ ���Դϴ�.
 */
class Block : public GameObject
{
public:
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
	 * ���� �������Դϴ�.
	 * 
	 * @param InPosition - �ܼ� ���� ���� ��ġ�Դϴ�.
	 * @param InState - ���� �����Դϴ�.
	 * @param InColor - ���� �����Դϴ�.
	 */
	Block(const Vec2i& InPosition, const EState& InState, const EColor& InColor)
		: Position_(InPosition)
		, State_(InState)
		, Color_(InColor)
		, Text_(GetStateText(State_)) {}


	/**
	 * ���� ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Block(Block&& InInstance) noexcept
		: Position_(InInstance.Position_)
		, State_(InInstance.State_)
		, Color_(InInstance.Color_)
		, Text_(InInstance.Text_) {}


	/**
	 * ���� ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Block(const Block& InInstance) noexcept
		: Position_(InInstance.Position_)
		, State_(InInstance.State_)
		, Color_(InInstance.Color_) 
		, Text_(InInstance.Text_) {}


	/**
	 * ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Block() {}


	/**
	 * ���� ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * ���� ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * ���� ������Ʈ�մϴ�.
	 * 
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * ���� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * ���� ��ġ�� ����ϴ�.
	 * 
	 * @return ���� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetPosition() const { return Position_; }


	/**
	 * ���� ��ġ�� �����մϴ�.
	 * 
	 * @param InPosition - ������ ���� ��ġ�Դϴ�.
	 */
	void SetPosition(const Vec2i& InPosition) { Position_ = InPosition; }


	/**
	 * ���� ���¸� ����ϴ�.
	 * 
	 * @return ���� ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * ���� ���¸� �����մϴ�.
	 * 
	 * @param InState - ������ ���� �����Դϴ�.
	 */
	void SetState(const EState& InState) { State_ = InState; }


private:
	/**
	 * ���� ���¿� �����ϴ� �ؽ�Ʈ�� ����ϴ�.
	 * 
	 * @param InState - ���� �����Դϴ�.
	 * 
	 * @return ���� ���¿� �����ϴ� �ؽ�Ʈ�� ����ϴ�.
	 */
	static std::string GetStateText(const EState& InState);


private:
	/**
	 * ���� ��ġ�Դϴ�.
	 */
	Vec2i Position_;


	/**
	 * ���� �����Դϴ�.
	 */
	EState State_ = EState::EMPTY;
	

	/**
	 * ���� �����Դϴ�.
	 */
	EColor Color_ = EColor::BLACK;


	/**
	 * �� ���¿� �����ϴ� �ؽ�Ʈ�Դϴ�.
	 */
	std::string Text_;
};