#pragma once

#include <Block.h>

#include <vector>


/**
 * ��Ʈ���� �����Դϴ�.
 */
class Board
{
public:
	/**
	 * ������ �������Դϴ�.
	 * 
	 * @param InWidth - ������ ���� ũ���Դϴ�.
	 * @param InHeight - ������ ���� ũ���Դϴ�.
	 */
	Board(const int32_t& InWidth, const int32_t& InHeight) noexcept;


	/**
	 * ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Board(Board&& InInstance) noexcept;


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Board(const Board& InInstance) noexcept;


	/**
	 * ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board() {}


	/**
	 * ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ������ ��ü�Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Board& operator=(Board&& InInstance) noexcept;


	/**
	 * ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Board& operator=(const Board& InInstance) noexcept;


	/**
	 * ���带 ������Ʈ�մϴ�.
	 */
	void Update();


	/**
	 * ���带 �ܼ� ȭ�鿡 �׸��ϴ�.
	 */
	void Render();


private:
	/**
	 * ������ Offset�� ����ϴ�.
	 * 
	 * @param InPosition - ������ (x, y) ��ǥ�Դϴ�.
	 * 
	 * @return ���� �迭 �� (x, y) ��ǥ�� Offset�� ����ϴ�.
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
	 * @throws ������ �迭 ������ ����� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetBlock(const Block& InBlock);


private:
	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Width_ = 0;


	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Height_ = 0;


	/**
	 * ��Ʈ���� ������ �����Դϴ�.
	 */
	std::vector<Block> Board_;
};