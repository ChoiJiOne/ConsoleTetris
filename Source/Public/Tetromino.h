#pragma once

#include <Block.h>

#include <vector>


/**
 * ��Ʈ������ ��Ʈ�ι̳��Դϴ�.
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
		CW    = 6,
		JUMP  = 7,
	};


public:
	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param InPosition - ��Ʈ�ι̳� ������ ���� ��� ��ǥ�Դϴ�.
	 * @param InShape - ��Ʈ�ι̳��� ����Դϴ�.
	 * @param InColor - ��Ʈ�ι̳��� �����Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InPosition, const EShape& InShape, const EColor& InColor);


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param InPosition - ��Ʈ�ι̳� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InPosition);


	/**
	 * ��Ʈ�ι̳��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino();


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
	 * ��Ʈ�ι̳븦 �����Դϴ�.
	 * 
	 * @param InMovement - ��Ʈ�ι̳밡 ������ �����Դϴ�.
	 */
	void Move(const EMovement& InMovement);


	/**
	 * ��Ʈ�ι̳��� ������ ��ȯ�մϴ�.
	 * 
	 * @return ��Ʈ�ι̳� �� ����� ��ȯ�մϴ�.
	 */
	const std::vector<Block>& GetBlocks() const { return Blocks_; }


	/**
	 * ��Ʈ�ι̳� �������� �ݴ� ������ ����ϴ�.
	 *
	 * @param InMovement - �ݴ� ������ �˰� ���� �������Դϴ�.
	 *
	 * @return �������� �ݴ� ������ ��ȯ�մϴ�.
	 */
	static EMovement GetCountMovement(const EMovement& InMovement);


	/**
	 * ������� ������ ��Ʈ�ι̳��� ���� ����ϴ�.
	 * 
	 * @return ������� ������ ��Ʈ�ι̳��� ���� ��ȯ�մϴ�.
	 */
	static int32_t GetCountOfTetromino() { return CountOfTetromino_; }


	/**
	 * ������� ������ ��Ʈ�ι̳��� ���� �ʱ�ȭ�մϴ�.
	 */
	static void ResetCountOfTetromino() { CountOfTetromino_ = 0; }


private:
	/**
	 * ��Ʈ�ι̳� Ÿ�Կ� �´� ������ ��ġ�� �����մϴ�.
	 *
	 * @param InShape - ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 * @param InColor - ��Ʈ�ι̳� ���� �����Դϴ�.
	 */
	void CreateTetrominoBlocks(const EShape& InShape, const EColor& InColor);


	/**
	 * ��Ʈ�ι̳븦 �ܼ� ȭ�� �󿡼� ����ϴ�.
	 */
	void RemoveFromConsole();


	/**
	 * ��Ʈ�ι̳��� ������ ������ ����ϴ�.
	 */
	EMovement GetMovementDirection() const;


	/**
	 * ��Ʈ�ι̳�� ������ �浹�� �˻��մϴ�.
	 */
	bool IsCollision();


private:
	/**
	 * ��Ʈ�ι̳� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2i Position_;


	/**
	 * ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 */
	int32_t BoundSize_ = 0;


	/**
	 * ��Ʈ�ι̳��� �����Դϴ�.
	 */
	std::vector<Block> Blocks_;


	/**
	 * ��Ʈ�ι̳��� ���̵��Դϴ�.
	 * �� ��� ������ ��Ʈ�ι̳븦 ���� ���忡 ��� �� ������ �� ����մϴ�.
	 */
	int32_t ID_ = 0;


	/**
	 * ���� �÷��� �� ������ ��Ʈ�ι̳��� ���Դϴ�.
	 */
	static int32_t CountOfTetromino_;
};