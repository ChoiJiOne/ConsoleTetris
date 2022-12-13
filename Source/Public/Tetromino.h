#pragma once

#include <Block.h>

#include <vector>


/**
 * 테트리스 테트로미노입니다.
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
	 * 테트로미노 타입에 맞는 블럭들의 위치를 생성합니다.
	 */


private:
	/**
	 * 테트리스 보드 상 위치입니다.
	 */
	Vec2i BoardPosition;


	/**
	 * 테트로미노 블럭들의 위치입니다.
	 * 이때, 이 블럭들은 상대적인 좌표입니다.
	 */
	std::vector<Block> BlockPositions_;
};