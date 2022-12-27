#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <array>


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


	/**
	 * ���� ������ �޴� ��Ҹ� ����ϴ�.
	 * 
	 * @return ���� ������ �޴� ��Ҹ� ��ȯ�մϴ�.
	 */
	const std::string& GetCurrentSelectMenu() const { return SelectMenu_[CurrentSelectMenu_]; }


private:
	/**
	 * ���� ���� ���� �޴� ����Դϴ�.
	 */
	std::array<std::string, 2> SelectMenu_;


	/**
	 * ���� ���� ���� �޴� ����Դϴ�.
	 */
	int32_t CurrentSelectMenu_ = 0;
};
