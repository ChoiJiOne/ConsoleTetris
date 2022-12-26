#include <SceneNode.h>

#include <algorithm>

void SceneNode::Link(SceneNode* InSceneNode)
{
	if (this == InSceneNode) return;

	if (std::find(LinkNodes_.begin(), LinkNodes_.end(), InSceneNode) == LinkNodes_.end())
	{
		LinkNodes_.push_back(InSceneNode);
	}
}

void SceneNode::Unlink(SceneNode* InSceneNode)
{
	if (this == InSceneNode) return;

	LinkNodes_.remove(InSceneNode);
}
