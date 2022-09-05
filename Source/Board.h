#pragma once

#include "Tetromino.h"
#include "Block.h"

#include <vector>


/**
 * ��Ʈ���� ���� Ŭ�����Դϴ�.
 */
class Board
{
public:
	/**
	 * ��Ʈ���� ���� Ŭ������ �������Դϴ�.
	 *
	 * @param InWidth - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param InHeight - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	Board(const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * ��Ʈ���� ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 */
	Board(Board&& InInstance) noexcept;


	/**
	 * ��Ʈ���� ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 */
	Board(const Board& InInstance) noexcept;


	/**
	 * ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board();


	/**
	 * ��Ʈ���� ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Board& operator=(Board&& InInstance) noexcept;


	/**
	 * ��Ʈ���� ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ���� ��ü�Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Board& operator=(const Board& InInstance) noexcept;


	/**
	 * ��Ʈ���� ���忡 ��Ʈ�ι̳븦 ����մϴ�.
	 *
	 * @param InTetromino - Board�� ����� ��Ʈ�ι̳��Դϴ�.
	 *
	 * @return ��Ʈ�ι̳븦 ����� �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool RegisterTetromino(const Tetromino& InTetromino);


	/**
	 * ��Ʈ���� ���忡 ��ϵ� ��Ʈ�ι̳븦 ��� �����մϴ�.
	 *
	 * @param InTetromino - Board�� ��� ������ ��Ʈ�ι̳��Դϴ�.
	 */
	void UnregisterTetromino(const Tetromino& InTetromino);


	/**
	 * ��Ʈ���� ���带 ������Ʈ�մϴ�.
	 * �̶�, ä���� ������ �����մϴ�.
	 *
	 * @return ��Ʈ���� ���带 ������Ʈ �ϸ鼭 ������ ������ ���� ��ȯ�մϴ�.
	 */
	int32_t Update();


	/**
	 * ��Ʈ���� ���带 �ʱ�ȭ�մϴ�.
	 */
	void Reset();


	/**
	 * ��Ʈ���� ���带 �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ȭ����� ��Ʈ���� ������ ���� ��� ��ǥ�Դϴ�.
	 *
	 * @throws �ܼ� ȭ�鿡 �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * 2���� �迭�� Offset�� ����ϴ�.
	 *
	 * @param InPositionX - 2���� �迭�� x��ǥ�Դϴ�.
	 * @param InPositionY - 2���� �迭�� y��ǥ�Դϴ�.
	 * @param InWidth - 2���� �迭�� ���� ũ���Դϴ�.
	 * @param InHeight - 2���� �迭�� ���� ũ���Դϴ�.
	 *
	 * @throws �迭�� ������ ����� C++ ǥ�ؿ��ܸ� �����ϴ�.
	 *
	 * @return (x, y)�� �����ϴ� 2���� �迭�� Offset�� ��ȯ�մϴ�.
	 */
	static int32_t GetOffset(int32_t InPositionX, int32_t InPositionY, int32_t InWidth, int32_t InHeight);


	/**
	 * 2���� �迭�� Offset�� ����ϴ�.
	 *
	 * @param InPosition - 2���� �迭�� ��ǥ�Դϴ�.
	 * @param InWidth - 2���� �迭�� ���� ũ���Դϴ�.
	 * @param InHeight - 2���� �迭�� ���� ũ���Դϴ�.
	 *
	 * @throws �迭�� ������ ����� C++ ǥ�ؿ��ܸ� �����ϴ�.
	 *
	 * @return (x, y)�� �����ϴ� 2���� �迭�� Offset�� ��ȯ�մϴ�.
	 */
	static int32_t GetOffset(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight);


	/**
	 * 2���� ��Ʈ���� ������ ����� �����մϴ�.
	 *
	 * @param InWidth - 2���� ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param InHeight - 2���� ��Ʈ���� ������ ���� ũ���Դϴ�.
	 *
	 * @return - ������ 2���� ��Ʈ���� ���带 ��ȯ�մϴ�.
	 */
	static std::vector<Block> CreateBlocks(int32_t InWidth, int32_t InHeight);


	/**
	 * 2���� ��Ʈ���� ������ ���� �ʱ�ȭ�մϴ�.
	 *
	 * @param InBlocks - �ʱ�ȭ�� ��Ʈ���� ������ ���Դϴ�.
	 * @param InWidth - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param InHeight - ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	static void SetupBlocks(std::vector<Block>& InBlocks, int32_t InWidth, int32_t InHeight);


	/**
	 * 2���� ��ǥ�� ���� 2���� �迭 ���� �ִ��� �˻��մϴ�.
	 *
	 * @param InPosition - �˻縦 ������ 2���� ��ǥ�Դϴ�.
	 * @param InWidth - 2���� �迭�� ���� ũ���Դϴ�.
	 * @param InHeight - 2���� �迭�� ���� ũ���Դϴ�.
	 *
	 * @return ��ǥ ���� 2���� ��Ʈ���� ���� ���� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool DoseIncludePosition(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight);


	/**
	 * ��Ʈ���� ���忡 ��Ʈ�ι̳븦 ����� �� �ִ��� Ȯ���մϴ�.
	 *
	 * @param InTetromino - �˻縦 ������ ��Ʈ�ι̳��Դϴ�.
	 *
	 * @return ��Ʈ�ι̳븦 ����� �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool CanRegisterTetromino(const Tetromino& InTetromino);


	/**
	 * ��Ʈ���� ������ ������ ��ü�� �� ���ִ��� Ȯ���մϴ�.
	 *
	 * @param InY - �� ���ִ��� �˻縦 ������ ������ ��ȣ �Դϴ�.
	 *
	 * @return �������� �� ���ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsFullFillLine(int32_t InY);


	/**
	 * ��Ʈ���� ������ ������ ��ü�� ������ִ��� Ȯ���մϴ�.
	 *
	 * @param InY - ������ִ��� �˻縦 ������ ������ ��ȣ�Դϴ�.
	 *
	 * @return �������� ������ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsFullEmptyLine(int32_t InY);


	/**
	 * ��Ʈ���� ������ �������� �����մϴ�.
	 *
	 * @param InY - ������ �������� ��ȣ�Դϴ�.
	 */
	void RemoveLine(int32_t InY);


	/**
	 * ��Ʈ���� ������ ä���� �����ٵ��� �����մϴ�.
	 *
	 * @return ������ ������ ���� ��ȯ�մϴ�.
	 */
	int32_t RemoveFullFillLines();


	/**
	 * ��Ʈ���� ���带 �� ������ ä��� ������Ʈ�մϴ�.
	 */
	void UpdateBoard();


private:
	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Width_;


	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Height_;


	/**
	 * ��Ʈ���� ������ ���Դϴ�.
	 */
	std::vector<Block> Blocks_;
};