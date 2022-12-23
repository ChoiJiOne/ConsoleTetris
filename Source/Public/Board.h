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
	 * ������ �������Դϴ�.
	 * 
	 * @param InPosition - ������ ���� ��� ��ǥ�Դϴ�.
	 * @param InWidth - ������ ���� ũ���Դϴ�.
	 * @param InHeight - ������ ���� ũ���Դϴ�.
	 */
	Board(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight) noexcept;


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
	const std::vector<Block>& GetBlocks() const { return Blocks_; }


	/**
	 * ���忡 ������ ���� ���ϴ�.
	 * 
	 * @param InBlocks - ���� �� �����Դϴ�.
	 */
	void WriteBlocks(const std::vector<Block>& InBlocks);


	/**
	 * ���忡 ������ ����ϴ�.
	 * 
	 * @param InBlocks - ���� �����Դϴ�.
	 */
	void RemoveBlocks(const std::vector<Block>& InBlocks);


private:
	/**
	 * ������ Offset�� ����ϴ�.
	 * 
	 * @param InPosition - ������ (x, y) ��ǥ�Դϴ�.
	 * 
	 * @return ���� �迭 �� (x, y) ��ǥ�� Offset�� ��ȯ�մϴ�.
	 */
	int32_t GetOffset(const Vec2i& InPosition);


	/**
	 * ������ (x, y)�� �����ϴ� ���� ����ϴ�.
	 *
	 * @param InPosition - ������ (x, y) ��ǥ�Դϴ�.
	 *
	 * @throws ������ �迭 ������ ����� C++ ǥ�� ���ܸ� �����ϴ�.
	 *
	 * @return ������ (x, y)�� �����ϴ� ���� ��ȯ�մϴ�.
	 */
	Block GetBlock(const Vec2i& InPosition);


	/**
	 * ������ (x, y)�� �����ϴ� ���� �����մϴ�.
	 *
	 * @param InBlock - ������ ������ ���Դϴ�.
	 *
	 * @throws ������ �迭 ������ ����� c++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetBlock(const Block& InBlock);


private:
	/**
	 * ������ ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2i Position_;


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
	std::vector<Block> Blocks_;
};