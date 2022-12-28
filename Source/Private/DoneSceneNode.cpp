#include <DoneSceneNode.h>
#include <PlaySceneNode.h>
#include <ConsoleManager.h>
#include <InputManager.h>

DoneSceneNode::DoneSceneNode()
	: SceneNode("DoneScene")
	, CurrentSelectMenu_(0)
	, TitlePosition_(Vec2i(2, 2))
	, PlayTimePosition_(Vec2i(10, 15))
	, RemoveLinePosition_(Vec2i(10, 16))
	, PlayerLevelPosition_(Vec2i(10, 17))
	, SelectMenuPosition_(Vec2i(9, 19))
{
	SelectMenu_ = {
		"RESTART",
		"QUIT"
	};
}

DoneSceneNode::~DoneSceneNode()
{
}

void DoneSceneNode::Update(float InDeltaSeconds)
{
	if (InputManager::Get().GetKeyPressState(EKeyCode::UP) == EPressState::PRESSED)
	{
		CurrentSelectMenu_--;
	}

	if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
	{
		CurrentSelectMenu_++;
	}

	CurrentSelectMenu_ = std::clamp<int32_t>(CurrentSelectMenu_, 0, static_cast<int32_t>(SelectMenu_.size()) - 1);

	if (InputManager::Get().GetKeyPressState(EKeyCode::ENTER) == EPressState::PRESSED)
	{
		RunSwitchEvent();
	}
}

void DoneSceneNode::Render()
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

	Vec2i TitleConsolePosition = TitlePosition_;
	for (const auto& TitleLine : Title)
	{
		ConsoleManager::Get().RenderText(TitleConsolePosition, TitleLine, EColor::AQUA);
		TitleConsolePosition.y += 1;
	}

	PlaySceneNode* CurrentPlaySceneNode = reinterpret_cast<PlaySceneNode*>(FindLinkNode("PlayScene"));
	ConsoleManager::Get().RenderText(
		PlayTimePosition_,
		Text::Format("TIME  %3d", static_cast<int32_t>(CurrentPlaySceneNode->GetPlayTime())),
		EColor::AQUA
	);

	ConsoleManager::Get().RenderText(
		RemoveLinePosition_,
		Text::Format("LINE  %3d", CurrentPlaySceneNode->GetRemoveLine()),
		EColor::AQUA
	);

	ConsoleManager::Get().RenderText(
		PlayerLevelPosition_,
		Text::Format("LEVEL %3d", static_cast<int32_t>(CurrentPlaySceneNode->GetPlayerLevel())),
		EColor::AQUA
	);

	Vec2i SelectMenuConsolePosition = SelectMenuPosition_;
	for (std::size_t MenuIndex = 0; MenuIndex < SelectMenu_.size(); ++MenuIndex)
	{
		ConsoleManager::Get().RenderText(
			SelectMenuConsolePosition,
			Text::Format("%s %s", (MenuIndex == CurrentSelectMenu_) ? "¢º" : "  ", SelectMenu_[MenuIndex].c_str()),
			EColor::AQUA
		);

		SelectMenuConsolePosition.y += 1;
	}
}