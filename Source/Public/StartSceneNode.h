#pragma once

#include <Vector.hpp>
#include <SceneNode.h>


/**
 * ���� ���� ����Դϴ�.
 */
class StartSceneNode : public SceneNode
{
public:
	/**
	 * ���� �� ����� �������Դϴ�.
	 */
	explicit StartSceneNode();


	/**
	 * ���� �� ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StartSceneNode();


	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartSceneNode);


	/**
	 * ���� ���� ������Ʈ�մϴ�.
	 *
	 * @param InDeltaTime - �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * ���� ���� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


private:
};
