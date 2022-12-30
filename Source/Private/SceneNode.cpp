#include <SceneNode.h>
#include <CommandLineManager.h>
#include <Text.hpp>

#include <fstream>
#include <algorithm>

SceneNode::SceneNode(const std::string& InSignature)
	: Signature_(InSignature)
{
	SceneUIInfo_ = ParseSceneFromFile();
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

Vec2i SceneNode::GetUIPosition(const std::string& InUIElement)
{
	return SceneUIInfo_.at(InUIElement);
}

std::unordered_map<std::string, Vec2i> SceneNode::ParseSceneFromFile()
{
	std::string ContentPath = CommandLineManager::Get().GetValue("-Content");
	std::string ScenePath = ContentPath + Text::Format("%s.Scene", Signature_.c_str());

	std::ifstream SceneFile(ScenePath);
	CHECK((SceneFile.is_open()), "failed to load scene file");

	std::unordered_map<std::string, Vec2i> SceneUIInfo;

	std::string ReadLine;
	while (SceneFile)
	{
		std::getline(SceneFile, ReadLine);

		std::vector<std::string> Elements = Text::Split(ReadLine, ",");
		SceneUIInfo.insert({ Elements[0], Vec2i(std::stoi(Elements[1]), std::stoi(Elements[2])) });
	}

	SceneFile.close();
	return SceneUIInfo;
}
