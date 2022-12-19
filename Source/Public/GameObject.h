#pragma once

#include <Macro.h>

#include <unordered_map>
#include <memory>

class Component;


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


	/**
	 * ���� ������Ʈ�� ������Ʈ�� �߰��մϴ�.
	 * �̶�, Ű ���� �����ϴ� ������Ʈ�� �����Ѵٸ� �ƹ��� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param InKey - �߰��� ������Ʈ�� Ű���Դϴ�.
	 * @param InArgs - ������Ʈ�� �ʿ��� ���� �����Դϴ�.
	 */
	template<typename T, typename... Types>
	void AddComponent(const std::size_t& InKey, Types... InArgs)
	{
		if (HaveComponent(InKey)) return;

		std::unique_ptr<T> NewComponent = std::make_unique<T>(this, InArgs...);
		Components_.insert({ InKey, std::move(NewComponent) });
	}


	/**
	 * ���� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� ����ϴ�.
	 *
	 * @param InKey - ���� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ������Ʈ�� �����ϸ� �ּ� ���� ��ȯ, �׷��� ������ nullptr�� ��ȯ�մϴ�.
	 */
	template<typename T>
	T* GetComponent(const std::size_t& InKey)
	{
		if (!HaveComponent(InKey)) return nullptr;

		return reinterpret_cast<T*>(Components_.at(InKey).get());
	}


	/**
	 * ���� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� �����մϴ�.
	 * �̶�, Ű ���� �����ϴ� ������Ʈ�� �������� �ʴ´ٸ�, �ƹ��� ���۵� ���� �ʽ��ϴ�.
	 *
	 * @param InKey - ���� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� Ű ���Դϴ�.
	 */
	template<typename T>
	void RemoveComponent(const std::size_t& InKey)
	{
		if (!HaveComponent(InKey)) return;

		Components_.erase(InKey);
	}


	/**
	 * Ű ���� �����ϴ� ������Ʈ�� �����ϴ��� �˻��մϴ�.
	 *
	 * @param InKey - �˻縦 ������ Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ������Ʈ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool HaveComponent(const std::size_t& InKey)
	{
		return Components_.find(InKey) != Components_.end();
	}


private:
	/**
	 * ���� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�Դϴ�.
	 */
	std::unordered_map<std::size_t, std::unique_ptr<Component>> Components_;
};