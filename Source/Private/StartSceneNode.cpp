#include <StartSceneNode.h>
#include <ConsoleManager.h>

StartSceneNode::StartSceneNode()
	: SceneNode("StartScene")
{
}

StartSceneNode::~StartSceneNode()
{
}

void StartSceneNode::Update(float InDeltaSeconds)
{
}

void StartSceneNode::Render()
{
	static std::string Title[] = {
		"   _____                      _      ",
		"  / ____|                    | |     ",
		" | |     ___  _ __  ___  ___ | | ___ ",
		" | |    / _ \\| \'_ \\/ __|/ _ \\| |/ _ \\",
		" | |___| (_) | | | \\__ \\ (_) | |  __/",
		"  \\_____\\___/|_| |_|___/\\___/|_|\\___|",
		"  _______ ______ _______ _____  _____  _____ ",
		" |__   __|  ____|__   __|  __ \\|_   _|/ ____|",
		"    | |  | |__     | |  | |__) | | | | (___  ",
		"    | |  |  __|    | |  |  _  /  | |  \\___ \\ ",
		"    | |  | |____   | |  | | \\ \\ _| |_ ____) |",
		"    |_|  |______|  |_|  |_|  \\_\\_____|_____/ ",
	};

	Vec2i ConsolePosition = Vec2i(5, 5);
	for (const auto& TitleLine : Title)
	{
		ConsoleManager::Get().RenderText(ConsolePosition, TitleLine, EColor::AQUA);
		ConsolePosition.y += 1;
	}
}
