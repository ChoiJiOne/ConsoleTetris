#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <array>


/**
 * ���� ���� ����Դϴ�.
 */
class DoneSceneNode : public SceneNode
{
public:
	/**
	 * ���� �� ����� �������Դϴ�.
	 */
	explicit DoneSceneNode();


	/**
	 * ���� �� ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~DoneSceneNode();


	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(DoneSceneNode);


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
