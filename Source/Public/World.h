#pragma once

#include <Macro.h>

#include <unordered_map>

class GameObject;


/**
 * 게임 오브젝트가 위치할 월드입니다.
 */
class World
{
public:
	/**
	 * 게임 월드의 디폴트 생성자입니다.
	 */
	World() = default;


	/**
	 * 게임 월드의 가상 소멸자입니다.
	 */
	virtual ~World();


	/**
	 * 명시적으로 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(World);


	/**
	 * 게임 월드에 오브젝트를 추가합니다.
	 *
	 * @param InObject - 2D 월드에 추가할 오브젝트입니다.
	 * @param InKey - 2D 월드에 추가할 오브젝트의 키 값입니다.
	 */
	void AddOjbect(GameObject* InObject, const std::size_t& InKey);


	/**
	 * 게임 월드에 오브젝트가 존재하는지 확인합니다.
	 *
	 * @param InKey - 존재하는지 확인할 오브젝트의 키 값입니다.
	 *
	 * @return 게임 월드에 존재한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsExistObject(const std::size_t& InKey);


	/**
	 * 키 값에 대응하는 게임 월드의 오브젝트를 얻습니다.
	 *
	 * @param InKey - 게임 월드에 있는 오브젝트의 키 값입니다.
	 *
	 * @return 키 값에 대응하는 게임 월드의 오브젝트가 존재하면 오브젝트의 포인터 값을, 그렇지 않으면 nullptr를 반환합니다.
	 */
	GameObject* GetObject(const std::size_t& InKey);


	/**
	 * 게임 월드에 오브젝트를 삭제합니다.
	 * 이때, 해당 오브젝트가 존재하지 않는다면 아무 동작도 하지 않습니다.
	 *
	 * @param InObject - 2D 월드에서 삭제할 오브젝트의 키 값입니다.
	 */
	void RemoveObject(const std::size_t& InKey);


private:
	/**
	 * 게임 월드 내에 존재하는 게임 오브젝트입니다.
	 */
	std::unordered_map<std::size_t, GameObject*> GameObjects_;
};