#pragma once

#include <Block.h>

#include <vector>


/**
 * 테트리스의 보드입니다.
 */
class Board : public GameObject
{
public:
	/**
	 * 보드의 생성자입니다.
	 *
	 * @param InWidth - 보드의 가로 크기입니다.
	 * @param InHeight - 보드의 세로 크기입니다.
	 */
	Board(const int32_t& InWidth, const int32_t& InHeight) noexcept;


	/**
	 * 보드의 가상 소멸자입니다.
	 */
	virtual ~Board() {}


	/**
	 * 보드의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * 보드를 업데이트합니다.
	 *
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 보드를 화면에 그립니다.
	 */
	virtual void Render() override;
};