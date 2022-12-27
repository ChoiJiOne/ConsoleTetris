#pragma once

#include <Vector.hpp>
#include <SceneNode.h>

#include <array>


/**
 * 정지 씬의 노드입니다.
 */
class PauseSceneNode : public SceneNode
{
public:
	/**
	 * 정지 씬 노드의 생성자입니다.
	 */
	explicit PauseSceneNode();


	/**
	 * 정지 씬 노드의 가상 소멸자입니다.
	 */
	virtual ~PauseSceneNode();


	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PauseSceneNode);


	/**
	 * 정지 씬을 업데이트합니다.
	 *
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 정지 씬을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * 현재 선택한 메뉴 요소를 얻습니다.
	 *
	 * @return 현재 선택한 메뉴 요소를 반환합니다.
	 */
	const std::string& GetCurrentSelectMenu() const { return SelectMenu_[CurrentSelectMenu_]; }


private:
	/**
	 * 정지 씬의 선택 메뉴 목록입니다.
	 */
	std::array<std::string, 3> SelectMenu_;


	/**
	 * 현재 선택 중인 메뉴 요소입니다.
	 */
	int32_t CurrentSelectMenu_ = 0;


	/**
	 * 타이틀 화면의 위치입니다.
	 */
	Vec2i TitlePosition_;


	/**
	 * 선택 메뉴의 위치입니다.
	 */
	Vec2i SelectMenuPosition_;
};
