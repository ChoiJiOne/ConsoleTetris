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
	 * 테트리스 보드의 상태입니다.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1
	};


public:
	/**
	 * 보드의 생성자입니다.
	 * 
	 * @param InConsolePosition - 콘솔 상의 보드 윈쪽 상단 좌표입니다.
	 * @param InWidth - 보드의 가로 크기입니다.
	 * @param InHeight - 보드의 세로 크기입니다.
	 */
	Board(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight) noexcept;


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
	const std::vector<Block>& GetBoardBlocks() const { return BoardBlocks_; }


	/**
	 * 보드에 블럭들을 덮어 씁니다.
	 * 
	 * @param InWriteBlocks - 덮어 쓸 블럭들입니다.
	 */
	void WriteBlocks(const std::vector<Block>& InWriteBlocks);


	/**
	 * 보드에 블럭들을 지웁니다.
	 * 
	 * @param InRemoveBlocks - 지울 블럭들입니다.
	 */
	void RemoveBlocks(const std::vector<Block>& InRemoveBlocks);


	/**
	 * 보드의 현재 상태를 얻습니다.
	 *
	 * @return 보드의 상태를 반환합니다.
	 */
	EState GetCurrentState() const { return CurrentState_; }


	/**
	 * 보드의 현재 상태를 설정합니다.
	 *
	 * @param InState - 설정할 보드의 현재 상태입니다.
	 */
	void SetCurrentState(const EState& InCurrentState) { CurrentState_ = InCurrentState; }


	/**
	 * 보드의 최대 누적 시간을 설정합니다.
	 *
	 * @param InMaxAccrueTime - 설정할 보드의 최대 누적 시간입니다.
	 */
	static void SetMaxAccrueTime(const float& InMaxAccrueTime) { MaxAccrueTime_ = InMaxAccrueTime; }

	
private:
	/**
	 * 2차원 배열의 Offset을 얻습니다.
	 * 
	 * @param InPosition - 2차원 배열의 (x, y) 좌표입니다.
	 * @param InWidth - 2차원 배열의 가로 크기입니다.
	 * @param InHeight - 2차원 배열의 세로 크기입니다.
	 * 
	 * @return 2차원 배열 상 (x, y) 좌표의 Offset을 반환합니다.
	 */
	int32_t GetOffset(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 비어있는 보드의 블럭들을 생성합니다.
	 * 
	 * @param InConsolePosition - 콘솔 상의 보드 왼쪽 상단 좌표입니다.
	 * @param InWidth - 보드의 가로 크기입니다.
	 * @param InHeight - 보드의 세로 크기입니다.
	 * 
	 * @return 비어있는 보드의 블럭들을 반환합니다.
	 */
	std::vector<Block> CreateEmptyBlocks(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 보드의 Y좌표 라인을 지울 수 있는지 검사합니다.
	 * 
	 * @param InYPositon - 검사할 보드 상의 Y좌표입니다.
	 * 
	 * @return 보드를 지울 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool CanRemoveRowLine(const int32_t& InYPosition);


	/**
	 * 보드의 Y좌표 라인이 비어있는지 검사합니다.
	 * 
	 * @param InYPositon - 검사할 보드 상의 Y좌표입니다.
	 * 
	 * @return 비어져있으면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsEmptyRowLine(const int32_t& InYPosition);


	/**
	 * 보드의 Y좌표 라인을 비웁니다.
	 * 
	 * @param InYPositon - 비울 보드 상의 Y좌표입니다.
	 */
	void ClearRowLine(const int32_t& InYPosition);


	/**
	 * 보드의 비어있는 부분을 정리합니다.
	 */
	void ArrangeEmptyRowLine();


private:
	/**
	 * 콘솔 상의 보드의 왼쪽 상단 좌표입니다.
	 */
	Vec2i ConsolePosition_;


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
	std::vector<Block> BoardBlocks_;


	/**
	 * 보드의 현재 상태입니다.
	 */
	EState CurrentState_ = EState::ACTIVE;


	/**
	 * 보드의 누적 시간입니다.
	 */
	float AccrueTime_ = 0.0f;


	/**
	 * 보드의 최대 누적 시간입니다.
	 * 이때, 기본 값은 1초입니다.
	 */
	static float MaxAccrueTime_;
};