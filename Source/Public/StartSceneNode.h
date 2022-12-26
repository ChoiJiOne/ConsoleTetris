#pragma once

#include <Vector.hpp>
#include <SceneNode.h>


/**
 * 시작 씬의 노드입니다.
 */
class StartSceneNode : public SceneNode
{
public:
	/**
	 * 시작 씬 노드의 생성자입니다.
	 */
	explicit StartSceneNode();


	/**
	 * 시작 씬 노드의 가상 소멸자입니다.
	 */
	virtual ~StartSceneNode();


	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartSceneNode);


	/**
	 * 시작 씬을 업데이트합니다.
	 *
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) override;


	/**
	 * 시작 씬을 화면에 그립니다.
	 */
	virtual void Render() override;


private:
};
