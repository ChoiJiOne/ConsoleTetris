#include <WorldManager.h>
#include <GameObject.h>

void WorldManager::RegisterOjbect(GameObject* InObject, const std::size_t& InKey)
{
	if (IsRegisterObject(InKey)) return;

	GameObjects_.insert({ InKey, InObject });
}

bool WorldManager::IsRegisterObject(const std::size_t& InKey)
{
	return GameObjects_.find(InKey) != GameObjects_.end();
}

GameObject* WorldManager::GetObject(const std::size_t& InKey)
{
	if (!IsRegisterObject(InKey)) return nullptr;

	return GameObjects_.at(InKey);
}

void WorldManager::UnregisterObject(const std::size_t& InKey)
{
	if (!IsRegisterObject(InKey)) return;

	GameObjects_.erase(InKey);
}