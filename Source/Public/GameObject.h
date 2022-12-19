#pragma once

#include <Macro.h>


/**
 * 게임 오브젝트 클래스입니다.
 * 게임 내의 오브젝트는 이 클래스를 상속받아야 합니다.
 */
class GameObject
{
public:
	/**
	 * 게임 오브젝트의 생성자입니다.
	 */
	GameObject() = default;


	/**
	 * 게임 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~GameObject();


	/**
	 * 게임 오브젝트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameObject);


	/**
	 * 게임 오브젝트를 업데이트합니다.
	 * 
	 * @param InDeltaTime - 초단위 델타 시간값입니다.
	 */
	virtual void Update(float InDeltaSeconds) = 0;


	/**
	 * 게임 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() = 0;
};