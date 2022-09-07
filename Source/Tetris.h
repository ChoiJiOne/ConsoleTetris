#pragma once

#include "Input.h"
#include "Block.h"
#include "Board.h"
#include "Tetromino.h"
#include "Timer.h"
#include "Vector.h"

#include <memory>
#include <list>
#include <algorithm>


/**
 * 테트리스 게임 클래스입니다.
 */
class Tetris
{
public:
	/**
	 * 테트리스 게임 클래스의 생성자입니다.
	 * 이때, 초기화를 수행하기 위해서는 Init 메서드를 호출해야 합니다.
	 */
	explicit Tetris() = default;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	Tetris(Tetris&& InInstance) = delete;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	Tetris(const Tetris& InInstance) = delete;


	/**
	 * 테트리스 게임 클래스의 소멸자입니다.
	 */
	virtual ~Tetris();


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	Tetris& operator=(Tetris&& InInstance) = delete;


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	Tetris& operator=(const Tetris& InInstance) = delete;


	/**
	 * 테트리스 게임을 초기화합니다.
	 *
	 * @throws 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Init();


	/**
	 * 테트리스 게임을 리셋합니다.
	 * 
	 * @throws 리셋에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Reset();


	/**
	 * 테트리스 게임의 입력을 처리합니다.
	 * 
	 * @param InInput - 키 상태를 관리하는 입력 시스템입니다.
	 */
	void ProcessInput(const Input& InInput);


	/**
	 * 테트리스 게임을 업데이트합니다.
	 * 
	 * @param InDeltaTime - 델타 시간 값입니다. 단위는 초단위입니다.
	 */
	void Update(float InDeltaTime);


	/**
	 * 테트리스 게임을 콘솔 화면에 그립니다.
	 * 
	 * @param InPosition - 테트리스 게임 영역의 왼쪽 상단 좌표입니다.
	 */
	void Draw(const Vec2i& InPosition);


	/**
	 * 테트리스 게임을 중단합니다.
	 */
	void Paused();


	/**
	 * 중단된 테트리스 게임을 이어서 시작합니다.
	 */
	void Continue();


	/**
	 * 테트리스 게임을 중단했는지 확인합니다.
	 * 
	 * @return 테트리스 게임이 중단 되었다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsPaused() const { return bIsPaused_; }

	
	/**
	 * 테트리스 게임을 계속 할 수 있는지 확인합니다.
	 * 
	 * @return 테트리스 게임을 계속 할 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsProcess() const { return bIsProcess_; }


	/**
	 * 플레이어가 삭제한 줄의 수를 얻습니다.
	 * 
	 * @return 플레이어가 삭제한 줄의 수를 반환합니다.
	 */
	int32_t GetRemoveLine() const { return CurrentRemoveLine_; }


	/**
	 * 테트리스 게임의 스텝 시간 값을 얻습니다.
	 */
	float GetStepTime() const { return MaxStepTime_; }


	/**
	 * 테트리스 게임의 스텝 시간을 설정합니다.
	 * 이때, 0.5f <= InStepTime <= 1.5f 입니다.
	 */
	void SetStepTime(float InStepTime);


private:
	/**
	 * 테트리스 게임의 대기할 테트로미노를 생성하고 현재 테트로미노를 설정합니다.
	 * 
	 * @param InMaxTetromino - 최대 생성할 테트로미노 수입니다.
	 */
	void CreateWaitTetromino(const int32_t& InMaxTetromino);


	/**
	 * 테트리스 게임의 보드를 생성하고, 현재 테트로미노를 보드에 배치합니다.
	 * 이때, CreateWaitTetromino를 호출한 뒤에 수행되어야 합니다. 
	 * 
	 * @param InWidth - 테트리스 보드의 가로 크기입니다.
	 * @param InHeight - 테트리스 보드의 세로 크기입니다.
	 */
	void CreateBoard(const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 테트리스 게임의 대기 중인 테트로미노를 화면에 그립니다.
	 *
	 * @param InPosition - 콘솔 화면 상의 왼쪽 상단 좌표입니다.
	 */
	void DrawWaitTetrominos(const Vec2i & InPosition);


	/**
	 * 테트리스 보드의 테트로미노를 이동시킵니다.
	 *
	 * @param 테트로미노의 이동 방향입니다.
	 *
	 * @return 테트리스 보드의 테트로미노를 이동시켰으면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool MoveTetrominoInBoard(const Tetromino::EMovement & InMovement);


	/**
	 * 현재 테트리스 보드에 배치된 테트로미노를 삭제합니다.
	 */
	void EraseCurrentTetromino();


	/**
	 * 현재 테트로미노를 테트리스 보드에 배치합니다.
	 *
	 * @return 테트로미노 배치에 성공하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool BatchCurrentTetromino();


private:
	/**
	 * 테트로미노가 움직일 수 있는지를 확인합니다.
	 */
	bool bCanMove_ = false;


	/**
	 * 테트로미노가 가장 아래칸으로 이동할 수 있는지 확인합니다.
	 */
	bool bCanMoveToBottom_ = false;


	/**
	 * 테트리스 게임의 중단 여부를 확인합니다.
	 */
	bool bIsPaused_ = false;


	/**
	 * 플레이어가 테트리스 게임을 계속 할 수 있는지 확인합니다.
	 */
	bool bIsProcess_ = true;


	/**
	 * 테트리스 게임 내의 보드입니다.
	 */
	std::unique_ptr<Board> Board_ = nullptr;


	/**
	 * 테트리스 게임 내의 대기 중인 테트로미노들입니다.
	 */
	std::list<std::unique_ptr<Tetromino>> WaitTetrominos_;


	/**
	 * 현재 테트리스 보드 내에 배치된 테트로미노입니다.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino_;


	/**
	 * 테트로미노의 시작점입니다.
	 */
	Vec2i StartPositionFromBoard_;


	/**
	 * 테트로미노의 움직임 방향입니다.
	 */
	Tetromino::EMovement Movement_ = Tetromino::EMovement::None;


	/**
	 * 테트리스 게임의 최대 스텝 시간입니다.
	 */
	float MaxStepTime_ = 1.5f;


	/**
	 * 테트리스 게임의 현재 스텝 시간입니다.
	 */
	float CurrentStepTime_ = 0.0f;


	/**
	 * 현재 삭제한 라인 수입니다.
	 */
	int32_t CurrentRemoveLine_ = 0;


	/**
	 * 키 타입에 대응하는 테트로미노의 움직임입니다.
	 */
	std::unordered_map<Input::EKeyType, Tetromino::EMovement> TetrominoMoveMappings_;
};