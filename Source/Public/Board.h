#pragma once

#include <Block.h>

#include <vector>


/**
 * 테트리스 보드입니다.
 */
class Board
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
	 * 보드의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Board(Board&& InInstance) noexcept;


	/**
	 * 보드의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Board(const Board& InInstance) noexcept;


	/**
	 * 보드의 가상 소멸자입니다.
	 */
	virtual ~Board() {}


	/**
	 * 보드의 복사 생성자입니다.
	 * 
	 * @param InInstance - 대입할 객체입니다.
	 * 
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Board& operator=(Board&& InInstance) noexcept;


	/**
	 * 보드의 복사 생성자입니다.
	 *
	 * @param InInstance - 대입할 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Board& operator=(const Board& InInstance) noexcept;


	/**
	 * 보드를 업데이트합니다.
	 */
	void Update();


	/**
	 * 보드를 콘솔 화면에 그립니다.
	 */
	void Render();


private:
	/**
	 * 보드의 Offset을 얻습니다.
	 * 
	 * @param InPosition - 보드의 (x, y) 좌표입니다.
	 * 
	 * @return 보드 배열 상 (x, y) 좌표의 Offset을 얻습니다.
	 */
	int32_t GetOffset(const Vec2i& InPosition);


	/**
	 * 보드의 (x, y)에 대응하는 블럭을 얻습니다.
	 * 
	 * @param InPosition - 보드의 (x, y) 좌표입니다.
	 * 
	 * @throws 보드의 배열 범위를 벗어나면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 보드의 (x, y)에 대응하는 블럭을 반환합니다.
	 */
	Block GetBlock(const Vec2i& InPosition);


	/**
	 * 보드의 (x, y)에 대응하는 블럭을 설정합니다.
	 * 
	 * @param InBlock - 설정할 보드의 블럭입니다.
	 * 
	 * @throws 보드의 배열 범위를 벗어나면 C++ 표준 예외를 던집니다.
	 */
	void SetBlock(const Block& InBlock);


private:
	/**
	 * 테트리스 보드의 가로 크기입니다.
	 */
	int32_t Width_ = 0;


	/**
	 * 테트리스 보드의 세로 크기입니다.
	 */
	int32_t Height_ = 0;


	/**
	 * 테트리스 보드의 상태입니다.
	 */
	std::vector<Block> Board_;
};