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
	 * ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
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
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param InBoardPosition - ��Ʈ���� ���� ���� ��Ʈ�ι̳� ��� ������ ��ǥ�Դϴ�.
	 * @param InType - ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 * @param InBlockType - ��Ʈ�ι̳� ���� Ÿ���Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InBoardPosition, const EShape& InType, const Block::EType& InBlockType);


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * �̶�, �� �����ڴ� ������ ��Ʈ�ι̳븦 �����մϴ�.
	 * 
	 * @param InBoardPosition - ��Ʈ���� ���� ���� ��Ʈ�ι̳� ��� ������ ��ǥ�Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InBoardPosition);


	/**
	 * ��Ʈ�ι̳��� ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Tetromino(Tetromino&& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳��� ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Tetromino(const Tetromino& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino() {}


	/**
	 * ��Ʈ�ι̳��� ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Tetromino& operator=(Tetromino&& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳��� ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Tetromino& operator=(const Tetromino& InInstance) noexcept;


	/**
	 * ��Ʈ�ι̳븦 ������Ʈ�մϴ�.
	 */
	void Update();


	/**
	 * ��Ʈ�ι̳븦 ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param InPosition - ��Ʈ�ι̳��� ��� ��ǥ �������Դϴ�.
	 */
	void Render(const Vec2i& InPosition);


	/**
	 * ��Ʈ�ι̳� �������� �ݴ� ������ ����ϴ�.
	 *
	 * @param InMovement - �ݴ� ������ �˰� ���� �������Դϴ�.
	 *
	 * @return �������� �ݴ� ������ ��ȯ�մϴ�.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


public:
	/**
	 * ��Ʈ�ι̳� Ÿ�Կ� �´� ������ ��ġ�� �����մϴ�.
	 * 
	 * @param InType - ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 * @param InBlockType - ��Ʈ�ι̳� ���� Ÿ���Դϴ�.
	 */
	void CreateTetrominoBlocks(const EShape& InType, const Block::EType& InBlockType);


private:
	/**
	 * ��Ʈ���� ���� �� ��ġ�Դϴ�.
	 */
	Vec2i BoardPosition_;


	/**
	 * ��Ʈ�ι̳� ������ ���� �����Դϴ�.
	 * �̶�, ��Ʈ�ι̳� ������ ������ ���簢���Դϴ�.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * ��Ʈ�ι̳� �����Դϴ�.
	 * �̶�, �� ������ ������� ��ǥ�� �����ϴ�.
	 */
	std::vector<Block> Blocks_;
};