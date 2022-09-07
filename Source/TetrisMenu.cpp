#include "Macro.h"
#include "TetrisMenu.h"

TetrisMenu::~TetrisMenu()
{
}

void TetrisMenu::Init()
{
	std::vector<std::string> StartMenuElements = {
		"■ 게임 시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> StartMenu = std::make_unique<Menu>(StartMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EMenuState::Start , std::move(StartMenu) });


	std::vector<std::string> SelectMenuElements = {
		"■ Level 1",
		"■ Level 2",
		"■ Level 3",
		"■ Level 4",
		"■ Level 5",
		"■ Level 6",
	};
	std::unique_ptr<Menu> SelectMenu = std::make_unique<Menu>(SelectMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EMenuState::Select , std::move(SelectMenu) });


	Menus_.insert({ EMenuState::Play, nullptr });


	std::vector<std::string> PausedMenuElements = {
		"■ 게임 계속 플레이",
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> PausedMenu = std::make_unique<Menu>(PausedMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EMenuState::Paused, std::move(PausedMenu) });


	std::vector<std::string> DoneMenuElements = {
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> DoneMenu = std::make_unique<Menu>(DoneMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EMenuState::Done, std::move(DoneMenu) });
}

void TetrisMenu::ProcessInput(const Input& InInput)
{
	if (CurrentMenuState_ == EMenuState::Play)
	{
		return;
	}

	Menus_[CurrentMenuState_]->ProcessInput(InInput);
}

void TetrisMenu::Update(float InDeltaTime)
{
	bIsSwitchMenu_ = false;

	if (CurrentMenuState_ == EMenuState::Play)
	{
		return;
	}

	if (Menus_[CurrentMenuState_]->IsSwitch())
	{
		bIsSwitchMenu_ = true;

		switch (CurrentMenuState_)
		{
		case EMenuState::Start:
			UpdateStartMenu();
			break;

		case EMenuState::Select:
			UpdateSelectMenu();
			break;

		case EMenuState::Paused:
			UpdatePausedMenu();
			break;

		case EMenuState::Done:
			UpdateDoneMenu();
			break;

		default:
			ENFORCE_THROW_EXCEPTION("undefined menu state type");
		}
	}
}

void TetrisMenu::Draw(const Vec2i& InPosition)
{
	if (CurrentMenuState_ == EMenuState::Play)
	{
		return;
	}

	Vec2i TitlePosition = InPosition;
	DrawTitle(TitlePosition, Console::ETextColor::LightAqua);

	Vec2i MenuPosition = InPosition;
	MenuPosition.x += 7;
	MenuPosition.y += 13;

	Menus_[CurrentMenuState_]->Draw(MenuPosition);
}

void TetrisMenu::SetMenuState(const EMenuState& InMenuState)
{
	Console::Clear();
	CurrentMenuState_ = InMenuState;
}

const Menu& TetrisMenu::GetCurrentMenu() const
{
	return *Menus_.at(CurrentMenuState_);
}

void TetrisMenu::UpdateStartMenu()
{
	const Menu& CurrentMenu = GetCurrentMenu();
	std::string CurrentSelectMenuElement = CurrentMenu.GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 시작"))
	{
		SetMenuState(EMenuState::Select);
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsSelectQuitGame_ = true;
	}
}

void TetrisMenu::UpdateSelectMenu()
{
	const Menu& CurrentMenu = GetCurrentMenu();
	std::string CurrentSelectMenuElement = CurrentMenu.GetCurrentSelectElement();
	SetMenuState(EMenuState::Play);

	static std::string Levels[] = {
		"■ Level 1",
		"■ Level 2",
		"■ Level 3",
		"■ Level 4",
		"■ Level 5",
		"■ Level 6",
	};

	for (const auto& Level : Levels)
	{
		if (!CurrentSelectMenuElement.compare(Level))
		{
			SelectLevel_ = static_cast<int32_t>(Level.back()) - 48;
			break;
		}
	}
}

void TetrisMenu::UpdatePausedMenu()
{
	const Menu& CurrentMenu = GetCurrentMenu();
	const std::string& CurrentSelectMenuElement = CurrentMenu.GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 계속 플레이"))
	{
		SetMenuState(EMenuState::Play);
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 재시작"))
	{
		SetMenuState(EMenuState::Start);
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsSelectQuitGame_ = true;
	}
}

void TetrisMenu::UpdateDoneMenu()
{
	const Menu& CurrentMenu = GetCurrentMenu();
	std::string CurrentSelectMenuElement = CurrentMenu.GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 재시작"))
	{
		SetMenuState(EMenuState::Start);
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsSelectQuitGame_ = true;
	}
}

void TetrisMenu::DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor)
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

	Vec2i Position = InPosition;
	for (const auto& TitleLine : Title)
	{
		Console::DrawText(Position.x, Position.y, TitleLine, InColor);
		Position.y += 1;
	}
}
