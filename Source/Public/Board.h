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
	 * @param InPosition - 보드의 윈쪽 상단 좌표입니다.
	 * @param InWidth - 보드의 가로 크기입니다.
	 * @param InHeight - 보드의 세로 크기입니다.
	 */
	Board(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight) noexcept;


	/**
	 * 보드의 가상 소멸자입니다.
	 */
	virtual ~Board();


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


	/**
	 * 보드와 블럭과의 충돌을 검사합니다.
	 * 
	 * @param InBlock - 충돌을 검사할 블럭입니다.
	 * 
	 * @return 보드와 블럭이 충돌한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsCollision(const Block& InBlock);


	/**
	 * 보드의 블럭들을 얻습니다.
	 * 
	 * @return 보드의 블럭들을 반환합니다.
	 */
	const std::vector<Block>& GetBlocks() const { return Blocks_; }


	/**
	 * 보드에 블럭들을 덮어 씁니다.
	 * 
	 * @param InBlocks - 덮어 쓸 블럭들입니다.
	 */
	void WriteBlocks(const std::vector<Block>& InBlocks);


	/**
	 * 보드에 블럭들을 지웁니다.
	 * 
	 * @param InBlocks - 지울 블럭들입니다.
	 */
	void RemoveBlocks(const std::vector<Block>& InBlocks);


private:
	/**
	 * 보드의 Offset을 얻습니다.
	 * 
	 * @param InPosition - 보드의 (x, y) 좌표입니다.
	 * 
	 * @return 보드 배열 상 (x, y) 좌표의 Offset을 반환합니다.
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
	 * @throws 보드의 배열 범위를 벗어나면 c++ 표준 예외를 던집니다.
	 */
	void SetBlock(const Block& InBlock);


private:
	/**
	 * 보드의 왼쪽 상단 좌표입니다.
	 */
	Vec2i Position_;


	/**
	 * 보드의 가로 크기입니다.
	 */
	int32_t Width_ = 0;


	/**
	 * 보드의 세로 크기입니다.
	 */
	int32_t Height_ = 0;


	/**
	 * 보드의 블럭들입니다.
	 */
	std::vector<Block> Blocks_;
};