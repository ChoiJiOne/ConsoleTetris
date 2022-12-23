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
	 * 테트로미노의 움직임입니다.
	 */
	enum class EMovement : int32_t
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


public:
	/**
	 * 테트로미노의 생성자입니다.
	 * 
	 * @param InPosition - 테트로미노 영역의 왼쪽 상단 좌표입니다.
	 * @param InShape - 테트로미노의 모양입니다.
	 * @param InColor - 테트로미노의 색상입니다.
	 */
	explicit Tetromino(const Vec2i& InPosition, const EShape& InShape, const EColor& InColor);


	/**
	 * 테트로미노의 생성자입니다.
	 * 
	 * @param InPosition - 테트로미노 영역의 왼쪽 상단 좌표입니다.
	 */
	explicit Tetromino(const Vec2i& InPosition);


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
	 * 테트로미노를 움직입니다.
	 * 
	 * @param InMovement - 테트로미노가 움직일 방향입니다.
	 */
	void Move(const EMovement& InMovement);


	/**
	 * 테트로미노의 블럭들을 반환합니다.
	 * 
	 * @return 테트로미노 블럭 목록을 반환합니다.
	 */
	const std::vector<Block>& GetBlocks() const { return Blocks_; }


	/**
	 * 테트로미노 움직임의 반대 방향을 얻습니다.
	 *
	 * @param InMovement - 반대 방향을 알고 싶은 움직임입니다.
	 *
	 * @return 움직임의 반대 방향을 반환합니다.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


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


private:
	/**
	 * 테트로미노 타입에 맞는 블럭들의 위치를 생성합니다.
	 *
	 * @param InShape - 테트로미노의 모양 타입입니다.
	 * @param InColor - 테트로미노 블럭의 색상입니다.
	 */
	void CreateTetrominoBlocks(const EShape& InShape, const EColor& InColor);


	/**
	 * 테트로미노를 콘솔 화면 상에서 지웁니다.
	 */
	void RemoveFromConsole();


	/**
	 * 테트로미노의 움직임 방향을 얻습니다.
	 */
	EMovement GetMovementDirection() const;


	/**
	 * 테트로미노와 보드의 충돌을 검사합니다.
	 */
	bool IsCollision();


private:
	/**
	 * 테트로미노 영역의 왼쪽 상단 좌표입니다.
	 */
	Vec2i Position_;


	/**
	 * 테트로미노 영역의 크기입니다.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * 테트로미노의 블럭들입니다.
	 */
	std::vector<Block> Blocks_;


	/**
	 * 테트로미노의 아이디입니다.
	 * 이 멤버 변수는 테트로미노를 게임 월드에 등록 및 삭제할 때 사용합니다.
	 */
	int32_t ID_ = 0;


	/**
	 * 게임 플레이 중 생성된 테트로미노의 수입니다.
	 */
	static int32_t CountOfTetromino_;
};