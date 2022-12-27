#include <PauseSceneNode.h>
#include <ConsoleManager.h>
#include <InputManager.h>

PauseSceneNode::PauseSceneNode()
	: SceneNode("PauseScene")
	, CurrentSelectMenu_(0)
{
	SelectMenu_ = {
		"RESET",
		"CONTINUE",
		"QUIT"
	};
}

PauseSceneNode::~PauseSceneNode()
{
}

void PauseSceneNode::Update(float InDeltaSeconds)
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

void PauseSceneNode::Render()
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

	for (std::size_t MenuIndex = 0; MenuIndex < SelectMenu_.size(); ++MenuIndex)
	{
		ConsoleManager::Get().RenderText(
			ConsolePosition,
			Text::Format("%s %s", (MenuIndex == CurrentSelectMenu_) ? "¢º" : "  ", SelectMenu_[MenuIndex].c_str()),
			EColor::AQUA
		);

		ConsolePosition.y += 1;
	}
}
