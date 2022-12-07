#pragma once

#include "Block.h"

#include <vector>


/**
 * 테트리스의 테트로미노 클래스입니다.
 */
class Tetromino
{
public:
	/**
	 * 테트로미노의 타입입니다.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EType : int32_t
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
		None  = 0,
		Left  = 1,
		Right = 2,
		Down  = 3,
		Up    = 4,
		CCW   = 5,
		CW    = 6
	};


public:
	/**
	 * 테트로미노 클래스 생성자입니다.
	 *
	 * @param InAbsolutionPosition - 테트리스 보드 상의 테트로미노 왼쪽 상단 위치입니다.
	 * @param InType - 테트로미노의 타입입니다.
	 * @param InBlockColor - 테트로미노 블럭의 색깔입니다.
	 */
	Tetromino(const Vec2i& InAbsolutionPosition, const EType& InType, const Block::EColor& InBlockColor);


	/**
	 * 테트로미노 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 테트로미노 객체입니다.
	 */
	Tetromino(Tetromino&& InInstance) noexcept;


	/**
	 * 테트로미노 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사할 테트로미노 객체입니다.
	 */
	Tetromino(const Tetromino& InInstance) noexcept;


	/**
	 * 테트로미노 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사할 테트로미노 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Tetromino& operator=(Tetromino&& InInstance) noexcept;


	/**
	 * 테트로미노 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사할 테트로미노 객체입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Tetromino& operator=(const Tetromino& InInstance) noexcept;


	/**
	 * 테트로미노를 랜덤으로 생성합니다.
	 *
	 * @param InAbsolutionPosition - 테트리스 보드 상의 테트로미노 왼쪽 상단 위치입니다.
	 *
	 * @return 렌덤으로 생성된 테트로미노를 반환합니다.
	 */
	static Tetromino CreateRandomTetromino(const Vec2i& InAbsolutionPosition);


	/**
	 * 테트리스의 테트로미노 클래스의 소멸자입니다.
	 */
	virtual ~Tetromino();


	/**
	 * 테트로미노의 블럭을 얻습니다.
	 *
	 * @return 테트로미노의 블럭을 반환합니다.
	 */
	Block GetTetrominoBlock() const { return TetrominoBlock_; }


	/**
	 * 테트리스 보드 상의 테트로미노 왼쪽 상단 위치를 얻습니다.
	 *
	 * @return 테트리스 보드 상의 테트로미노 왼쪽 상단 위치를 반환합니다.
	 */
	Vec2i GetAbsolutePosition() const { return AbsolutePosition_; }


	/**
	 * 테트로미노 블럭의 상대적인 위치를 얻습니다.
	 *
	 * @return 테트로미노 블럭의 상대적인 위치를 반환합니다.
	 */
	const std::vector<Vec2i>& GetRelativePositions() const { return RelativePositions_; }


	/**
	 * 테트로미노 움직임의 반대 방향을 얻습니다.
	 *
	 * @param InMovement - 반대 방향을 알고 싶은 움직임입니다.
	 *
	 * @return 움직임의 반대 방향을 반환합니다.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


	/**
	 * 테트로미노의 영역 크기를 얻습니다.
	 * 
	 * @return 테트로미노의 영역 크기를 반환합니다.
	 */
	int32_t GetAreaSize() const { return AreaSize_; }


	/**
	 * 테트로미노를 움직입니다.
	 *
	 * @param InMovement - 테트로미노의 움직임 종류 입니다.
	 */
	void Move(const EMovement& InMovement);


	/**
	 * 테트로미노를 콘솔 화면에 그립니다.
	 *
	 * @param InPosition - 콘솔 화면상의 테트로미노 왼쪽 상단의 좌표입니다.
	 *
	 * @throws 콘솔 화면에 그리기를 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * 타입에 따른 테트로미노 블럭의 상대적인 위치를 생성합니다.
	 *
	 * @param InType - 테트로미노의 타입입니다.
	 * @param OutRelativePositions - 테트로미노 블럭의 상대적인 위치입니다.
	 * @param OutAreaSize - 테트로미노의 영역 크기입니다.
	 * @param OutBoundSize - 테트로미노의 크기입니다.
	 */
	static void CreateRelativePositions(const EType& InType, std::vector<Vec2i>& OutRelativePositions, int32_t& OutAreaSize, int32_t& OutBoundSize);


	/**
	 * 테트로미노 블럭의 상대 위치를 저장하고 있는지 확인합니다.
	 * 
	 * @param InRelativePositions - 테트로미노 블럭의 상대적인 위치입니다.
	 * @param InTargetPosition - 테트로미노 블럭의 상대 위치를 저장하고 있는지 확인할 좌표입니다.
	 * 
	 * @return 테트로미노 블럭의 상대 위치를 저장하고 있으면 true, 그렇지 않으면 false를 반환합니다.
	 */
	static bool HaveRelativePosition(const std::vector<Vec2i>& InRelativePositions, const Vec2i& InTargetPosition);
	

private:
	/**
	 * 테트로미노의 블럭입니다.
	 */
	Block TetrominoBlock_;

	
	/**
	 * 테트로미노의 크기입니다.
	 * 이때, 테트로미노의 영역은 정사각형입니다.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * 테트로미노의 영역 크기입니다.
	 */
	int32_t AreaSize_ = 0;


	/**
	 * 테트리스 보드 상의 테트로미노 왼쪽 상단 위치입니다.
	 */
	Vec2i AbsolutePosition_;


	/**
	 * 테트로미노 블럭의 상대적인 위치입니다.
	 */
	std::vector<Vec2i> RelativePositions_;
};