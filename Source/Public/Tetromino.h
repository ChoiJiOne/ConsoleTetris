#pragma once

#include <Block.h>

#include <vector>


/**
 * 테트리스의 테트로미노입니다.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * 테트로미노의 모양 타입입니다.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EShape : int32_t
	{
		I = 0,
		O = 1,
		T = 2,
		J = 3,
		L = 4,
		S = 5,
		Z = 6
	};


	/**
	 * 테트로미노의 움직임 방향입니다.
	 */
	enum class EDirection : int32_t
	{
		NONE  = 0,
		LEFT  = 1,
		RIGHT = 2,
		DOWN  = 3,
		UP    = 4,
		CCW   = 5,
		CW    = 6,
		JUMP  = 7,
	};


	/**
	 * 테트로미노의 상태입니다.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1
	};


public:
	/**
	 * 테트로미노의 생성자입니다.
	 * 
	 * @param InConsolePosition - 콘솔 상의 테트로미노 영역 왼쪽 상단 좌표입니다.
	 * @param InShape - 테트로미노의 모양입니다.
	 * @param InColor - 테트로미노의 색상입니다.
	 */
	explicit Tetromino(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor);


	/**
	 * 테트로미노의 생성자입니다.
	 * 
	 * @param InConsolePosition - 콘솔 상의 테트로미노 영역 왼쪽 상단 좌표입니다.
	 */
	explicit Tetromino(const Vec2i& InConsolePosition);


	/**
	 * 테트로미노의 가상 소멸자입니다.
	 */
	virtual ~Tetromino();


	/**
	 * 테트로미노의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * 테트로미노를 업데이트합니다.
	 *
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 테트로미노를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * 콘솔 상의 테트로미노 왼쪽 상단 위치를 얻습니다.
	 * 
	 * @return 테트로미노 왼쪽 상단의 좌표를 반환합니다.
	 */
	Vec2i GetConsolePosition() const { return ConsolePosition_; }


	/**
	 * 콘솔 상의 테트로미노 왼쪽 상단 위치를 설정합니다.
	 * 
	 * @param InConsolePosition - 설정할 테트로미노 왼쪽 상단의 위치입니다.
	 */
	void SetConsolePosition(const Vec2i& InConsolePosition);
	

	/**
	 * 테트로미노의 현재 상태를 얻습니다.
	 * 
	 * @return 테트로미노의 상태를 반환합니다.
	 */
	EState GetCurrentState() const { return CurrentState_; }


	/**
	 * 테트로미노의 현재 상태를 설정합니다.
	 * 
	 * @param InState - 설정할 테트로미노의 상태입니다.
	 */
	void SetCurrentState(const EState& InCurrentState) { CurrentState_ = InCurrentState; }


	/**
	 * 테트로미노와 보드의 충돌을 검사합니다.
	 *
	 * @return 테트로미노와 보드가 충돌한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsCollision();


	/**
	 * 현재까지 생성된 테트로미노의 수를 얻습니다.
	 * 
	 * @return 현재까지 생성된 테트로미노의 수를 반환합니다.
	 */
	static int32_t GetCountOfTetromino() { return CountOfTetromino_; }


	/**
	 * 현재까지 생성된 테트로미노의 수를 초기화합니다.
	 */
	static void ResetCountOfTetromino() { CountOfTetromino_ = 0; }

	
	/**
	 * 테트로미노의 최대 누적 시간을 설정합니다.
	 * 
	 * @param InMaxAccrueTime - 설정할 테트로미노의 최대 누적 시간입니다.
	 */
	static void SetMaxAccrueTime(const float& InMaxAccrueTime) { MaxAccrueTime_ = InMaxAccrueTime; }


private:
	/**
	 * 테트로미노 블럭들울 생성합니다.
	 *
	 * @param InConsolePosition - 콘솔 상의 테트로미노 영역 왼쪽 상단 좌표입니다.
	 * @param InShape - 테트로미노의 모양 타입입니다.
	 * @param InColor - 테트로미노 블럭의 색상입니다.
	 * 
	 * @return 테트로미노 블럭들을 반환합니다.
	 */
	std::vector<Block> CreateTetrominoBlocks(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor);


	/**
	 * 테트로미노 블럭들을 특정 방향으로 움직입니다.
	 * 
	 * @param InConsolePosition - 움직일 테트로미노의 콘솔 상 왼쪽 상단 좌표입니다.
	 * @param InTetrominoBlocks - 움직일 테트로미노의 블럭입니다.
	 * @param InShape - 테트로미노의 모양입니다.
	 * @param InDirection - 테트로미노의 움직임 방향입니다.
	 */
	void Move(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EDirection& InDirection);


	/**
	 * 테트로미노 블럭들이 보드와 충돌하는지 검사합니다.
	 * 
	 * @param InTetrominoBlocks - 충돌하는지 검사할 테트로미노의 블럭입니다.
	 * 
	 * @param 테트로미노 블럭들과 충돌하면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsCollision(const std::vector<Block>& InTetrominoBlocks);


	/**
	 * 테트로미노가 움직일 수 있는지 확인합니다.
	 *
	 * @param InConsolePosition - 검사할 테트로미노의 콘솔 상 왼쪽 상단 좌표입니다.
	 * @param InTetrominoBlocks - 검사할 테트로미노의 블럭입니다.
	 * @param InShape - 검사할 테트로미노의 모양입니다.
	 * @param InDirection - 테트로미노가 움직일 수 있는지 확인할 방향입니다.
	 *
	 * @return 테트로미노가 움직일 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool CanMove(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EDirection& InDirection);


	/**
	 * 테트로미노를 콘솔 화면 상에서 지웁니다.
	 */
	void RemoveFromConsole();


	/**
	 * 테트로미노의 움직임 방향을 얻습니다.
	 */
	EDirection GetMovementDirection() const;


	/**
	 * 테트로미노의 영역 크기을 얻습니다.
	 * 
	 * @param InShape - 테트로미노의 영역 크기를 얻을 테트로미노의 모양입니다.
	 * 
	 * @return 테트로미노의 영역 크기를 반환합니다.
	 */
	int32_t GetBoundSize(const EShape& InShape) const;


	/**
	 * 테트로미노 움직임의 반대 방향을 얻습니다.
	 *
	 * @param InDirection - 반대 방향을 알고 싶은 움직임입니다.
	 *
	 * @return 움직임의 반대 방향을 반환합니다.
	 */
	static EDirection GetCountDirection(const EDirection& InDirection);


private:
	/**
	 * 콘솔 상의 테트로미노 영역 왼쪽 상단 좌표입니다.
	 */
	Vec2i ConsolePosition_;


	/**
	 * 테트로미노의 모양입니다.
	 */
	EShape Shape_;


	/**
	 * 테트로미노의 블럭들입니다.
	 */
	std::vector<Block> TetrominoBlocks_;


	/**
	 * 테트로미노의 현재 상태입니다.
	 */
	EState CurrentState_ = EState::WAIT;


	/**
	 * 현재 테트로미노의 아이디입니다.
	 * 이 멤버 변수는 테트로미노를 게임 월드에 등록 및 삭제할 때 사용합니다.
	 */
	int32_t CurrentID_ = 0;


	/**
	 * 콘솔 화면 상의 테트로미노 그림자 상단 위치입니다.
	 */
	Vec2i ShadowConsolePosition_;


	/**
	 * 테트로미노 그림자의 위치입니다.
	 */
	std::vector<Block> ShadowTetrominoBlocks_;


	/**
	 * 게임 플레이 중 생성된 테트로미노의 수입니다.
	 */
	static int32_t CountOfTetromino_;


	/**
	 * 테트로미노의 누적 시간입니다.
	 */
	float AccrueTime_ = 0.0f;


	/**
	 * 테트로미노의 최대 누적 시간입니다.
	 * 이때, 기본 값은 1초입니다.
	 */
	static float MaxAccrueTime_;
};