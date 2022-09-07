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
 * ��Ʈ���� ���� Ŭ�����Դϴ�.
 */
class Tetris
{
public:
	/**
	 * ��Ʈ���� ���� Ŭ������ �������Դϴ�.
	 * �̶�, �ʱ�ȭ�� �����ϱ� ���ؼ��� Init �޼��带 ȣ���ؾ� �մϴ�.
	 */
	explicit Tetris() = default;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Tetris(Tetris&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Tetris(const Tetris& InInstance) = delete;


	/**
	 * ��Ʈ���� ���� Ŭ������ �Ҹ����Դϴ�.
	 */
	virtual ~Tetris();


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Tetris& operator=(Tetris&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Tetris& operator=(const Tetris& InInstance) = delete;


	/**
	 * ��Ʈ���� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @throws �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init();


	/**
	 * ��Ʈ���� ������ �����մϴ�.
	 * 
	 * @throws ���¿� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Reset();


	/**
	 * ��Ʈ���� ������ �Է��� ó���մϴ�.
	 * 
	 * @param InInput - Ű ���¸� �����ϴ� �Է� �ý����Դϴ�.
	 */
	void ProcessInput(const Input& InInput);


	/**
	 * ��Ʈ���� ������ ������Ʈ�մϴ�.
	 * 
	 * @param InDeltaTime - ��Ÿ �ð� ���Դϴ�. ������ �ʴ����Դϴ�.
	 */
	void Update(float InDeltaTime);


	/**
	 * ��Ʈ���� ������ �ܼ� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param InPosition - ��Ʈ���� ���� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	void Draw(const Vec2i& InPosition);


	/**
	 * ��Ʈ���� ������ �ߴ��մϴ�.
	 */
	void Paused();


	/**
	 * �ߴܵ� ��Ʈ���� ������ �̾ �����մϴ�.
	 */
	void Continue();


	/**
	 * ��Ʈ���� ������ �ߴ��ߴ��� Ȯ���մϴ�.
	 * 
	 * @return ��Ʈ���� ������ �ߴ� �Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsPaused() const { return bIsPaused_; }

	
	/**
	 * ��Ʈ���� ������ ��� �� �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return ��Ʈ���� ������ ��� �� �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsProcess() const { return bIsProcess_; }


	/**
	 * �÷��̾ ������ ���� ���� ����ϴ�.
	 * 
	 * @return �÷��̾ ������ ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetRemoveLine() const { return CurrentRemoveLine_; }


	/**
	 * ��Ʈ���� ������ ���� �ð� ���� ����ϴ�.
	 */
	float GetStepTime() const { return MaxStepTime_; }


	/**
	 * ��Ʈ���� ������ ���� �ð��� �����մϴ�.
	 * �̶�, 0.5f <= InStepTime <= 1.5f �Դϴ�.
	 */
	void SetStepTime(float InStepTime);


private:
	/**
	 * ��Ʈ���� ������ ����� ��Ʈ�ι̳븦 �����ϰ� ���� ��Ʈ�ι̳븦 �����մϴ�.
	 * 
	 * @param InMaxTetromino - �ִ� ������ ��Ʈ�ι̳� ���Դϴ�.
	 */
	void CreateWaitTetromino(const int32_t& InMaxTetromino);


	/**
	 * ��Ʈ���� ������ ���带 �����ϰ�, ���� ��Ʈ�ι̳븦 ���忡 ��ġ�մϴ�.
	 * �̶�, CreateWaitTetromino�� ȣ���� �ڿ� ����Ǿ�� �մϴ�. 
	 * 
	 * @param InWidth - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param InHeight - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	void CreateBoard(const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * ��Ʈ���� ������ ��� ���� ��Ʈ�ι̳븦 ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ȭ�� ���� ���� ��� ��ǥ�Դϴ�.
	 */
	void DrawWaitTetrominos(const Vec2i & InPosition);


	/**
	 * ��Ʈ���� ������ ��Ʈ�ι̳븦 �̵���ŵ�ϴ�.
	 *
	 * @param ��Ʈ�ι̳��� �̵� �����Դϴ�.
	 *
	 * @return ��Ʈ���� ������ ��Ʈ�ι̳븦 �̵��������� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool MoveTetrominoInBoard(const Tetromino::EMovement & InMovement);


	/**
	 * ���� ��Ʈ���� ���忡 ��ġ�� ��Ʈ�ι̳븦 �����մϴ�.
	 */
	void EraseCurrentTetromino();


	/**
	 * ���� ��Ʈ�ι̳븦 ��Ʈ���� ���忡 ��ġ�մϴ�.
	 *
	 * @return ��Ʈ�ι̳� ��ġ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool BatchCurrentTetromino();


private:
	/**
	 * ��Ʈ�ι̳밡 ������ �� �ִ����� Ȯ���մϴ�.
	 */
	bool bCanMove_ = false;


	/**
	 * ��Ʈ�ι̳밡 ���� �Ʒ�ĭ���� �̵��� �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMoveToBottom_ = false;


	/**
	 * ��Ʈ���� ������ �ߴ� ���θ� Ȯ���մϴ�.
	 */
	bool bIsPaused_ = false;


	/**
	 * �÷��̾ ��Ʈ���� ������ ��� �� �� �ִ��� Ȯ���մϴ�.
	 */
	bool bIsProcess_ = true;


	/**
	 * ��Ʈ���� ���� ���� �����Դϴ�.
	 */
	std::unique_ptr<Board> Board_ = nullptr;


	/**
	 * ��Ʈ���� ���� ���� ��� ���� ��Ʈ�ι̳���Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>> WaitTetrominos_;


	/**
	 * ���� ��Ʈ���� ���� ���� ��ġ�� ��Ʈ�ι̳��Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino_;


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 */
	Vec2i StartPositionFromBoard_;


	/**
	 * ��Ʈ�ι̳��� ������ �����Դϴ�.
	 */
	Tetromino::EMovement Movement_ = Tetromino::EMovement::None;


	/**
	 * ��Ʈ���� ������ �ִ� ���� �ð��Դϴ�.
	 */
	float MaxStepTime_ = 1.5f;


	/**
	 * ��Ʈ���� ������ ���� ���� �ð��Դϴ�.
	 */
	float CurrentStepTime_ = 0.0f;


	/**
	 * ���� ������ ���� ���Դϴ�.
	 */
	int32_t CurrentRemoveLine_ = 0;


	/**
	 * Ű Ÿ�Կ� �����ϴ� ��Ʈ�ι̳��� �������Դϴ�.
	 */
	std::unordered_map<Input::EKeyType, Tetromino::EMovement> TetrominoMoveMappings_;
};