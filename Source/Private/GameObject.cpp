#include <GameObject.h>
#include <Component.h>

GameObject::~GameObject()
{
	for (auto& OwnComponent : Components_)
	{
		OwnComponent.second.reset();
	}
}