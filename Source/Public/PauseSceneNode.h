#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <array>


/**
 * ���� ���� ����Դϴ�.
 */
class PauseSceneNode : public SceneNode
{
public:
	/**
	 * ���� �� ����� �������Դϴ�.
	 */
	explicit PauseSceneNode();


	/**
	 * ���� �� ����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PauseSceneNode();


	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PauseSceneNode);


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
	std::array<std::string, 3> SelectMenu_;


	/**
	 * ���� ���� ���� �޴� ����Դϴ�.
	 */
	int32_t CurrentSelectMenu_ = 0;


	/**
	 * Ÿ��Ʋ ȭ���� ��ġ�Դϴ�.
	 */
	Vec2i TitlePosition_;


	/**
	 * ���� �޴��� ��ġ�Դϴ�.
	 */
	Vec2i SelectMenuPosition_;
};
