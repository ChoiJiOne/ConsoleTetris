#include <SceneNode.h>

#include <algorithm>

SceneNode::SceneNode(const std::string& InSignature)
	: Signature_(InSignature)
{
	LoadSceneUIJson();
}

void SceneNode::LinkNode(SceneNode* InSceneNode)
{
	if (this == InSceneNode) return;

	if (std::find(LinkNodes_.begin(), LinkNodes_.end(), InSceneNode) == LinkNodes_.end())
	{
		LinkNodes_.push_back(InSceneNode);
		InSceneNode->LinkNode(this);
	}
}

void SceneNode::UnlinkNode(SceneNode* InSceneNode)
{
	if (this == InSceneNode) return;

	LinkNodes_.remove(InSceneNode);
	InSceneNode->UnlinkNode(this);
}

SceneNode* SceneNode::FindLinkNode(const std::string& InSignature)
{
	SceneNode* TargetSceneNode = nullptr;

	for (SceneNode* CurrentNode : LinkNodes_)
	{
		if (CurrentNode->GetSignature().compare(InSignature) == 0)
		{
			TargetSceneNode = CurrentNode;
			break;
		}
	}

	return TargetSceneNode;
}

void SceneNode::LoadSceneUIJson()
{
	SceneUI = LoadJsonFromFile(Text::Format("%s.json", Signature_.c_str()));
}

Vec2i SceneNode::GetUIPosition(const std::string& InUIElement)
{
	return Vec2i(SceneUI[InUIElement]["x"], SceneUI[InUIElement]["y"]);
}