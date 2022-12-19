#pragma once

#include <GameObject.h>
#include <ConsoleManager.h>

#include <vector>


/**
 * ��Ʈ���� ��Ʈ�ι̳��Դϴ�.
 */
class Tetromino : public GameObject
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
	 * @param InConsolePosition - �ܼ� ���� ��Ʈ�ι̳� ��� ������ ��ǥ�Դϴ�.
	 * @param InType - ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 * @param InBlockType - ��Ʈ�ι̳� ���� �����Դϴ�.
	 */
	explicit Tetromino(
		const Vec2i& InBoardPosition, 
		const Vec2i& InConsolePosition,
		const EShape& InType, 
		const EColor& InColor
	);


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * �̶�, �� �����ڴ� ������ ��Ʈ�ι̳븦 �����մϴ�.
	 * 
	 * @param InBoardPosition - ��Ʈ���� ���� ���� ��Ʈ�ι̳� ��� ������ ��ǥ�Դϴ�.
	 * @param InConsolePosition - �ܼ� ���� ��Ʈ�ι̳� ��� ������ ��ǥ�Դϴ�.
	 */
	explicit Tetromino(
		const Vec2i& InBoardPosition,
		const Vec2i& InConsolePosition
	);


	/**
	 * ��Ʈ�ι̳��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino() {}


	/**
	 * ��Ʈ�ι̳��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * ��Ʈ�ι̳븦 ������Ʈ�մϴ�.
	 *
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * ��Ʈ�ι̳븦 ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


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
	void CreateTetrominoBlocks(const EShape& InType);


private:
	/**
	 * ��Ʈ���� ���� �� ��ġ�Դϴ�.
	 */
	Vec2i BoardPosition_;


	/**
	 * �ܼ� ȭ�� ���� ��ġ�Դϴ�.
	 */
	Vec2i ConsolePosition_;


	/**
	 * ��Ʈ�ι̳� ���� �����Դϴ�.
	 */
	EColor Color_ = EColor::BLACK;


	/**
	 * ��Ʈ�ι̳� ������ ���� �����Դϴ�.
	 * �̶�, ��Ʈ�ι̳� ������ ������ ���簢���Դϴ�.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * ��Ʈ�ι̳� �����Դϴ�.
	 * �̶�, �� ������ ������� ��ǥ�� �����ϴ�.
	 */
	std::vector<Vec2i> BlockPositions_;
};