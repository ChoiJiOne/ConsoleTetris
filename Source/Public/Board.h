#pragma once

#include <Block.h>

#include <vector>


/**
 * ��Ʈ������ �����Դϴ�.
 */
class Board : public GameObject
{
public:
	/**
	 * ��Ʈ���� ������ �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1
	};


public:
	/**
	 * ������ �������Դϴ�.
	 * 
	 * @param InConsolePosition - �ܼ� ���� ���� ���� ��� ��ǥ�Դϴ�.
	 * @param InWidth - ������ ���� ũ���Դϴ�.
	 * @param InHeight - ������ ���� ũ���Դϴ�.
	 */
	Board(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight) noexcept;


	/**
	 * ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board();


	/**
	 * ������ ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * ���带 ������Ʈ�մϴ�.
	 *
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * ���带 ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * ����� ������ �浹�� �˻��մϴ�.
	 * 
	 * @param InBlock - �浹�� �˻��� ���Դϴ�.
	 * 
	 * @return ����� ���� �浹�Ѵٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsCollision(const Block& InBlock);


	/**
	 * ������ ������ ����ϴ�.
	 * 
	 * @return ������ ������ ��ȯ�մϴ�.
	 */
	const std::vector<Block>& GetBoardBlocks() const { return BoardBlocks_; }


	/**
	 * ���忡 ������ ���� ���ϴ�.
	 * 
	 * @param InWriteBlocks - ���� �� �����Դϴ�.
	 */
	void WriteBlocks(const std::vector<Block>& InWriteBlocks);


	/**
	 * ���忡 ������ ����ϴ�.
	 * 
	 * @param InRemoveBlocks - ���� �����Դϴ�.
	 */
	void RemoveBlocks(const std::vector<Block>& InRemoveBlocks);


	/**
	 * ������ ���� ���¸� ����ϴ�.
	 *
	 * @return ������ ���¸� ��ȯ�մϴ�.
	 */
	EState GetCurrentState() const { return CurrentState_; }


	/**
	 * ������ ���� ���¸� �����մϴ�.
	 *
	 * @param InState - ������ ������ ���� �����Դϴ�.
	 */
	void SetCurrentState(const EState& InCurrentState) { CurrentState_ = InCurrentState; }


	/**
	 * ������ �ִ� ���� �ð��� �����մϴ�.
	 *
	 * @param InMaxAccrueTime - ������ ������ �ִ� ���� �ð��Դϴ�.
	 */
	static void SetMaxAccrueTime(const float& InMaxAccrueTime) { MaxAccrueTime_ = InMaxAccrueTime; }

	
private:
	/**
	 * 2���� �迭�� Offset�� ����ϴ�.
	 * 
	 * @param InPosition - 2���� �迭�� (x, y) ��ǥ�Դϴ�.
	 * @param InWidth - 2���� �迭�� ���� ũ���Դϴ�.
	 * @param InHeight - 2���� �迭�� ���� ũ���Դϴ�.
	 * 
	 * @return 2���� �迭 �� (x, y) ��ǥ�� Offset�� ��ȯ�մϴ�.
	 */
	int32_t GetOffset(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * ����ִ� ������ ������ �����մϴ�.
	 * 
	 * @param InConsolePosition - �ܼ� ���� ���� ���� ��� ��ǥ�Դϴ�.
	 * @param InWidth - ������ ���� ũ���Դϴ�.
	 * @param InHeight - ������ ���� ũ���Դϴ�.
	 * 
	 * @return ����ִ� ������ ������ ��ȯ�մϴ�.
	 */
	std::vector<Block> CreateEmptyBlocks(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * ������ Y��ǥ ������ ���� �� �ִ��� �˻��մϴ�.
	 * 
	 * @param InYPositon - �˻��� ���� ���� Y��ǥ�Դϴ�.
	 * 
	 * @return ���带 ���� �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool CanRemoveRowLine(const int32_t& InYPosition);


	/**
	 * ������ Y��ǥ ������ ����ִ��� �˻��մϴ�.
	 * 
	 * @param InYPositon - �˻��� ���� ���� Y��ǥ�Դϴ�.
	 * 
	 * @return ����������� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsEmptyRowLine(const int32_t& InYPosition);


	/**
	 * ������ Y��ǥ ������ ���ϴ�.
	 * 
	 * @param InYPositon - ��� ���� ���� Y��ǥ�Դϴ�.
	 */
	void ClearRowLine(const int32_t& InYPosition);


	/**
	 * ������ ����ִ� �κ��� �����մϴ�.
	 */
	void ArrangeEmptyRowLine();


private:
	/**
	 * �ܼ� ���� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2i ConsolePosition_;


	/**
	 * ������ ���� ũ���Դϴ�.
	 */
	int32_t Width_ = 0;


	/**
	 * ������ ���� ũ���Դϴ�.
	 */
	int32_t Height_ = 0;


	/**
	 * ������ �����Դϴ�.
	 */
	std::vector<Block> BoardBlocks_;


	/**
	 * ������ ���� �����Դϴ�.
	 */
	EState CurrentState_ = EState::ACTIVE;


	/**
	 * ������ ���� �ð��Դϴ�.
	 */
	float AccrueTime_ = 0.0f;


	/**
	 * ������ �ִ� ���� �ð��Դϴ�.
	 * �̶�, �⺻ ���� 1���Դϴ�.
	 */
	static float MaxAccrueTime_;
};