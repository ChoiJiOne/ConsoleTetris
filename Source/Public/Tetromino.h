#pragma once

#include <GameObject.h>
#include <ConsoleManager.h>

#include <vector>


/**
 * 테트리스 테트로미노입니다.
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
		CW    = 6
	};


public:
	/**
	 * 테트로미노의 생성자입니다.
	 * 
	 * @param InBoardPosition - 테트리스 보드 상의 테트로미노 상단 원점의 좌표입니다.
	 * @param InConsolePosition - 콘솔 상의 테트로미노 상단 원점의 좌표입니다.
	 * @param InType - 테트로미노의 모양 타입입니다.
	 * @param InBlockType - 테트로미노 블럭의 색상입니다.
	 */
	explicit Tetromino(
		const Vec2i& InBoardPosition, 
		const Vec2i& InConsolePosition,
		const EShape& InType, 
		const EColor& InColor
	);


	/**
	 * 테트로미노의 생성자입니다.
	 * 이때, 이 생성자는 임의의 테트로미노를 생성합니다.
	 * 
	 * @param InBoardPosition - 테트리스 보드 상의 테트로미노 상단 원점의 좌표입니다.
	 * @param InConsolePosition - 콘솔 상의 테트로미노 상단 원점의 좌표입니다.
	 */
	explicit Tetromino(
		const Vec2i& InBoardPosition,
		const Vec2i& InConsolePosition
	);


	/**
	 * 테트로미노의 가상 소멸자입니다.
	 */
	virtual ~Tetromino() {}


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
	 * 테트로미노 움직임의 반대 방향을 얻습니다.
	 *
	 * @param InMovement - 반대 방향을 알고 싶은 움직임입니다.
	 *
	 * @return 움직임의 반대 방향을 반환합니다.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


public:
	/**
	 * 테트로미노 타입에 맞는 블럭들의 위치를 생성합니다.
	 * 
	 * @param InType - 테트로미노의 모양 타입입니다.
	 * @param InBlockType - 테트로미노 블럭의 타입입니다.
	 */
	void CreateTetrominoBlocks(const EShape& InType);


private:
	/**
	 * 테트리스 보드 상 위치입니다.
	 */
	Vec2i BoardPosition_;


	/**
	 * 콘솔 화면 상의 위치입니다.
	 */
	Vec2i ConsolePosition_;


	/**
	 * 테트로미노 블럭의 색상입니다.
	 */
	EColor Color_ = EColor::BLACK;


	/**
	 * 테트로미노 블럭들의 영역 범위입니다.
	 * 이때, 테트로미노 블럭들의 영역은 정사각형입니다.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * 테트로미노 블럭들입니다.
	 * 이때, 이 블럭들은 상대적인 좌표를 갖습니다.
	 */
	std::vector<Vec2i> BlockPositions_;
};