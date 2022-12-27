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
	 * ��Ʈ�ι̳��� ������ �����Դϴ�.
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
	 * ��Ʈ�ι̳��� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1
	};


public:
	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param InConsolePosition - �ܼ� ���� ��Ʈ�ι̳� ���� ���� ��� ��ǥ�Դϴ�.
	 * @param InShape - ��Ʈ�ι̳��� ����Դϴ�.
	 * @param InColor - ��Ʈ�ι̳��� �����Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor);


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param InConsolePosition - �ܼ� ���� ��Ʈ�ι̳� ���� ���� ��� ��ǥ�Դϴ�.
	 */
	explicit Tetromino(const Vec2i& InConsolePosition);


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
	 * �ܼ� ���� ��Ʈ�ι̳� ���� ��� ��ġ�� ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳� ���� ����� ��ǥ�� ��ȯ�մϴ�.
	 */
	Vec2i GetConsolePosition() const { return ConsolePosition_; }


	/**
	 * �ܼ� ���� ��Ʈ�ι̳� ���� ��� ��ġ�� �����մϴ�.
	 * 
	 * @param InConsolePosition - ������ ��Ʈ�ι̳� ���� ����� ��ġ�Դϴ�.
	 */
	void SetConsolePosition(const Vec2i& InConsolePosition);
	

	/**
	 * ��Ʈ�ι̳��� ���� ���¸� ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� ���¸� ��ȯ�մϴ�.
	 */
	EState GetCurrentState() const { return CurrentState_; }


	/**
	 * ��Ʈ�ι̳��� ���� ���¸� �����մϴ�.
	 * 
	 * @param InState - ������ ��Ʈ�ι̳��� �����Դϴ�.
	 */
	void SetCurrentState(const EState& InCurrentState) { CurrentState_ = InCurrentState; }


	/**
	 * ��Ʈ�ι̳�� ������ �浹�� �˻��մϴ�.
	 *
	 * @return ��Ʈ�ι̳�� ���尡 �浹�Ѵٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsCollision();


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

	
	/**
	 * ��Ʈ�ι̳��� �ִ� ���� �ð��� �����մϴ�.
	 * 
	 * @param InMaxAccrueTime - ������ ��Ʈ�ι̳��� �ִ� ���� �ð��Դϴ�.
	 */
	static void SetMaxAccrueTime(const float& InMaxAccrueTime) { MaxAccrueTime_ = InMaxAccrueTime; }


private:
	/**
	 * ��Ʈ�ι̳� ����� �����մϴ�.
	 *
	 * @param InConsolePosition - �ܼ� ���� ��Ʈ�ι̳� ���� ���� ��� ��ǥ�Դϴ�.
	 * @param InShape - ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 * @param InColor - ��Ʈ�ι̳� ���� �����Դϴ�.
	 * 
	 * @return ��Ʈ�ι̳� ������ ��ȯ�մϴ�.
	 */
	std::vector<Block> CreateTetrominoBlocks(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor);


	/**
	 * ��Ʈ�ι̳� ������ Ư�� �������� �����Դϴ�.
	 * 
	 * @param InConsolePosition - ������ ��Ʈ�ι̳��� �ܼ� �� ���� ��� ��ǥ�Դϴ�.
	 * @param InTetrominoBlocks - ������ ��Ʈ�ι̳��� ���Դϴ�.
	 * @param InShape - ��Ʈ�ι̳��� ����Դϴ�.
	 * @param InDirection - ��Ʈ�ι̳��� ������ �����Դϴ�.
	 */
	void Move(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EDirection& InDirection);


	/**
	 * ��Ʈ�ι̳� ������ ����� �浹�ϴ��� �˻��մϴ�.
	 * 
	 * @param InTetrominoBlocks - �浹�ϴ��� �˻��� ��Ʈ�ι̳��� ���Դϴ�.
	 * 
	 * @param ��Ʈ�ι̳� ����� �浹�ϸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsCollision(const std::vector<Block>& InTetrominoBlocks);


	/**
	 * ��Ʈ�ι̳밡 ������ �� �ִ��� Ȯ���մϴ�.
	 *
	 * @param InConsolePosition - �˻��� ��Ʈ�ι̳��� �ܼ� �� ���� ��� ��ǥ�Դϴ�.
	 * @param InTetrominoBlocks - �˻��� ��Ʈ�ι̳��� ���Դϴ�.
	 * @param InShape - �˻��� ��Ʈ�ι̳��� ����Դϴ�.
	 * @param InDirection - ��Ʈ�ι̳밡 ������ �� �ִ��� Ȯ���� �����Դϴ�.
	 *
	 * @return ��Ʈ�ι̳밡 ������ �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool CanMove(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EDirection& InDirection);


	/**
	 * ��Ʈ�ι̳븦 �ܼ� ȭ�� �󿡼� ����ϴ�.
	 */
	void RemoveFromConsole();


	/**
	 * ��Ʈ�ι̳��� ������ ������ ����ϴ�.
	 */
	EDirection GetMovementDirection() const;


	/**
	 * ��Ʈ�ι̳��� ���� ũ���� ����ϴ�.
	 * 
	 * @param InShape - ��Ʈ�ι̳��� ���� ũ�⸦ ���� ��Ʈ�ι̳��� ����Դϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	int32_t GetBoundSize(const EShape& InShape) const;


	/**
	 * ��Ʈ�ι̳� �������� �ݴ� ������ ����ϴ�.
	 *
	 * @param InDirection - �ݴ� ������ �˰� ���� �������Դϴ�.
	 *
	 * @return �������� �ݴ� ������ ��ȯ�մϴ�.
	 */
	static EDirection GetCountDirection(const EDirection& InDirection);


private:
	/**
	 * �ܼ� ���� ��Ʈ�ι̳� ���� ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2i ConsolePosition_;


	/**
	 * ��Ʈ�ι̳��� ����Դϴ�.
	 */
	EShape Shape_;


	/**
	 * ��Ʈ�ι̳��� �����Դϴ�.
	 */
	std::vector<Block> TetrominoBlocks_;


	/**
	 * ��Ʈ�ι̳��� ���� �����Դϴ�.
	 */
	EState CurrentState_ = EState::WAIT;


	/**
	 * ���� ��Ʈ�ι̳��� ���̵��Դϴ�.
	 * �� ��� ������ ��Ʈ�ι̳븦 ���� ���忡 ��� �� ������ �� ����մϴ�.
	 */
	int32_t CurrentID_ = 0;


	/**
	 * �ܼ� ȭ�� ���� ��Ʈ�ι̳� �׸��� ��� ��ġ�Դϴ�.
	 */
	Vec2i ShadowConsolePosition_;


	/**
	 * ��Ʈ�ι̳� �׸����� ��ġ�Դϴ�.
	 */
	std::vector<Block> ShadowTetrominoBlocks_;


	/**
	 * ���� �÷��� �� ������ ��Ʈ�ι̳��� ���Դϴ�.
	 */
	static int32_t CountOfTetromino_;


	/**
	 * ��Ʈ�ι̳��� ���� �ð��Դϴ�.
	 */
	float AccrueTime_ = 0.0f;


	/**
	 * ��Ʈ�ι̳��� �ִ� ���� �ð��Դϴ�.
	 * �̶�, �⺻ ���� 1���Դϴ�.
	 */
	static float MaxAccrueTime_;
};