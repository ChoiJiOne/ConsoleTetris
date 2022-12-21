#include <WorldManager.h>
#include <GameObject.h>

WorldManager::~WorldManager()
{
}

void WorldManager::AddOjbect(GameObject* InObject, const std::size_t& InKey)
{
	if (IsExistObject(InKey)) return;

	GameObjects_.insert({ InKey, InObject });
}

bool WorldManager::IsExistObject(const std::size_t& InKey)
{
	return GameObjects_.find(InKey) != GameObjects_.end();
}

GameObject* WorldManager::GetObject(const std::size_t& InKey)
{
	if (!IsExistObject(InKey)) return nullptr;

	return GameObjects_.at(InKey);
}

void WorldManager::RemoveObject(const std::size_t& InKey)
{
	if (!IsExistObject(InKey)) return;

	GameObjects_.erase(InKey);
}