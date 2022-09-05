#pragma once

#include "Block.h"

#include <vector>


/**
 * ��Ʈ������ ��Ʈ�ι̳� Ŭ�����Դϴ�.
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
	 * ��Ʈ�ι̳� Ŭ���� �������Դϴ�.
	 *
	 * @param InAbsolutionPosition - ��Ʈ���� ���� ���� ��Ʈ�ι̳� ���� ��� ��ġ�Դϴ�.
	 * @param InType - ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param InBlockColor - ��Ʈ�ι̳� ���� �����Դϴ�.
	 */
	Tetromino(const Vec2i& InAbsolutionPosition, const EType& InType, const Block::EColor& InBlockColor);


	/**
	 * ��Ʈ�ι̳� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 */
	Tetromino(Tetromino&& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 */
	Tetromino(const Tetromino& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Tetromino& operator=(Tetromino&& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Tetromino& operator=(const Tetromino& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳븦 �������� �����մϴ�.
	 *
	 * @param InAbsolutionPosition - ��Ʈ���� ���� ���� ��Ʈ�ι̳� ���� ��� ��ġ�Դϴ�.
	 *
	 * @return �������� ������ ��Ʈ�ι̳븦 ��ȯ�մϴ�.
	 */
	static Tetromino CreateRandomTetromino(const Vec2i& InAbsolutionPosition);


	/**
	 * ��Ʈ������ ��Ʈ�ι̳� Ŭ������ �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino();


	/**
	 * ��Ʈ�ι̳��� ���� ����ϴ�.
	 *
	 * @return ��Ʈ�ι̳��� ���� ��ȯ�մϴ�.
	 */
	Block GetTetrominoBlock() const { return TetrominoBlock_; }


	/**
	 * ��Ʈ���� ���� ���� ��Ʈ�ι̳� ���� ��� ��ġ�� ����ϴ�.
	 *
	 * @return ��Ʈ���� ���� ���� ��Ʈ�ι̳� ���� ��� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetAbsolutePosition() const { return AbsolutePosition_; }


	/**
	 * ��Ʈ�ι̳� ���� ������� ��ġ�� ����ϴ�.
	 *
	 * @return ��Ʈ�ι̳� ���� ������� ��ġ�� ��ȯ�մϴ�.
	 */
	const std::vector<Vec2i>& GetRelativePositions() const { return RelativePositions_; }


	/**
	 * ��Ʈ�ι̳� �������� �ݴ� ������ ����ϴ�.
	 *
	 * @param InMovement - �ݴ� ������ �˰� ���� �������Դϴ�.
	 *
	 * @return �������� �ݴ� ������ ��ȯ�մϴ�.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


	/**
	 * ��Ʈ�ι̳��� ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	int32_t GetAreaSize() const { return AreaSize_; }


	/**
	 * ��Ʈ�ι̳븦 �����Դϴ�.
	 *
	 * @param InMovement - ��Ʈ�ι̳��� ������ ���� �Դϴ�.
	 */
	void Move(const EMovement& InMovement);


	/**
	 * ��Ʈ�ι̳븦 �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ȭ����� ��Ʈ�ι̳� ���� ����� ��ǥ�Դϴ�.
	 *
	 * @throws �ܼ� ȭ�鿡 �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * Ÿ�Կ� ���� ��Ʈ�ι̳� ���� ������� ��ġ�� �����մϴ�.
	 *
	 * @param InType - ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param OutRelativePositions - ��Ʈ�ι̳� ���� ������� ��ġ�Դϴ�.
	 * @param OutAreaSize - ��Ʈ�ι̳��� ���� ũ���Դϴ�.
	 * @param OutBoundSize - ��Ʈ�ι̳��� ũ���Դϴ�.
	 */
	static void CreateRelativePositions(const EType& InType, std::vector<Vec2i>& OutRelativePositions, int32_t& OutAreaSize, int32_t& OutBoundSize);


	/**
	 * ��Ʈ�ι̳� ���� ��� ��ġ�� �����ϰ� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param InRelativePositions - ��Ʈ�ι̳� ���� ������� ��ġ�Դϴ�.
	 * @param InTargetPosition - ��Ʈ�ι̳� ���� ��� ��ġ�� �����ϰ� �ִ��� Ȯ���� ��ǥ�Դϴ�.
	 * 
	 * @return ��Ʈ�ι̳� ���� ��� ��ġ�� �����ϰ� ������ true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool HaveRelativePosition(const std::vector<Vec2i>& InRelativePositions, const Vec2i& InTargetPosition);
	

private:
	/**
	 * ��Ʈ�ι̳��� ���Դϴ�.
	 */
	Block TetrominoBlock_;

	
	/**
	 * ��Ʈ�ι̳��� ũ���Դϴ�.
	 * �̶�, ��Ʈ�ι̳��� ������ ���簢���Դϴ�.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * ��Ʈ�ι̳��� ���� ũ���Դϴ�.
	 */
	int32_t AreaSize_ = 0;


	/**
	 * ��Ʈ���� ���� ���� ��Ʈ�ι̳� ���� ��� ��ġ�Դϴ�.
	 */
	Vec2i AbsolutePosition_;


	/**
	 * ��Ʈ�ι̳� ���� ������� ��ġ�Դϴ�.
	 */
	std::vector<Vec2i> RelativePositions_;
};