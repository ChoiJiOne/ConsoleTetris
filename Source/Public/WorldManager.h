#pragma once

#include <Macro.h>

#include <unordered_map>

class GameObject;


/**
 * ���� ������Ʈ�� ��ġ�� �����Դϴ�.
 * �̶�, �� Ŭ������ �̱����Դϴ�.
 */
class WorldManager
{
public:
	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(WorldManager);


	/**
	 * WorldManager�� �̱� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return WorldManager�� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static WorldManager& Get()
	{
		static WorldManager Instance;
		return Instance;
	}


	/**
	 * ���� ���忡 ������Ʈ�� ����մϴ�.
	 *
	 * @param InObject - 2D ���忡 ����� ������Ʈ�Դϴ�.
	 * @param InKey - 2D ���忡 �߰��� ������Ʈ�� Ű ���Դϴ�.
	 */
	void RegisterOjbect(GameObject* InObject, const std::size_t& InKey);


	/**
	 * ���� ���忡 ������Ʈ�� ��ϵǾ����� Ȯ���մϴ�.
	 *
	 * @param InKey - ��ϵǾ����� Ȯ���� ������Ʈ�� Ű ���Դϴ�.
	 *
	 * @return ���� ���忡 ��� �Ǿ��ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsRegisterObject(const std::size_t& InKey);


	/**
	 * Ű ���� �����ϴ� ���� ������ ������Ʈ�� ����ϴ�.
	 *
	 * @param InKey - ���� ���忡 �ִ� ������Ʈ�� Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���� ������ ������Ʈ�� �����ϸ� ������Ʈ�� ������ ����, �׷��� ������ nullptr�� ��ȯ�մϴ�.
	 */
	GameObject* GetObject(const std::size_t& InKey);


	/**
	 * ���� ���忡 ������Ʈ�� ��� �����մϴ�.
	 * �̶�, �ش� ������Ʈ�� �������� �ʴ´ٸ� �ƹ� ���۵� ���� �ʽ��ϴ�.
	 *
	 * @param InKey - ���� ���忡�� ��� ������ ������Ʈ�� Ű ���Դϴ�.
	 */
	void UnregisterObject(const std::size_t& InKey);


private:
	/**
	 * ���� ������ �������Դϴ�.
	 */
	WorldManager() = default;


	/**
	 * ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~WorldManager() = default;


private:
	/**
	 * ���� ���� ���� �����ϴ� ���� ������Ʈ�Դϴ�.
	 */
	std::unordered_map<std::size_t, GameObject*> GameObjects_;
};