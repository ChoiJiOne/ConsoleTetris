#pragma once

#include <Block.h>

#include <vector>


/**
 * ��Ʈ���� ��Ʈ�ι̳��Դϴ�.
 */
class Tetromino
{
public:
	/**
	 * ��Ʈ�ι̳��� Ÿ���Դϴ�.
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
	 * ��Ʈ�ι̳��� �������Դϴ�.
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
	 * ��Ʈ�ι̳� Ÿ�Կ� �´� ������ ��ġ�� �����մϴ�.
	 */


private:
	/**
	 * ��Ʈ���� ���� �� ��ġ�Դϴ�.
	 */
	Vec2i BoardPosition;


	/**
	 * ��Ʈ�ι̳� ������ ��ġ�Դϴ�.
	 * �̶�, �� ������ ������� ��ǥ�Դϴ�.
	 */
	std::vector<Block> BlockPositions_;
};