#pragma once

#include <Macro.h>


/**
 * ���� ������Ʈ Ŭ�����Դϴ�.
 * ���� ���� ������Ʈ�� �� Ŭ������ ��ӹ޾ƾ� �մϴ�.
 */
class GameObject
{
public:
	/**
	 * ���� ������Ʈ�� �������Դϴ�.
	 */
	GameObject() = default;


	/**
	 * ���� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameObject();


	/**
	 * ���� ������Ʈ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameObject);


	/**
	 * ���� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) = 0;


	/**
	 * ���� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() = 0;
};