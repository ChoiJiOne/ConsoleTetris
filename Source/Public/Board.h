#pragma once

#include <GameObject.h>

#include <vector>


/**
 * ��Ʈ���� �����Դϴ�.
 */
class Board : public GameObject
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
	 * ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board() {}


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


private:
	/**
	 * ������ Offset�� ����ϴ�.
	 * 
	 * @param inposition - ������ (x, y) ��ǥ�Դϴ�.
	 * 
	 * @return ���� �迭 �� (x, y) ��ǥ�� offset�� ����ϴ�.
	 */
	int32_t GetOffset(const Vec2i& inposition);


	/**
	 * ������ (x, y)�� �����ϴ� ���� ����ϴ�.
	 * 
	 * @param inposition - ������ (x, y) ��ǥ�Դϴ�.
	 * 
	 * @throws ������ �迭 ������ ����� c++ ǥ�� ���ܸ� �����ϴ�.
	 * 
	 * @return ������ (x, y)�� �����ϴ� ���� ��ȯ�մϴ�.
	 */
	block getblock(const vec2i& inposition);


	/**
	 * ������ (x, y)�� �����ϴ� ���� �����մϴ�.
	 * 
	 * @param inblock - ������ ������ ���Դϴ�.
	 * 
	 * @throws ������ �迭 ������ ����� c++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void setblock(const block& inblock);


private:
	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t width_ = 0;


	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t height_ = 0;


	/**
	 * ��Ʈ���� ������ �����Դϴ�.
	 */
	std::vector<block> Board_;
};