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
};