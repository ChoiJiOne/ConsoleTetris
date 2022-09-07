#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	for (auto& MenuElement : Menus_)
	{
		MenuElement.second.reset();
	}
}

void Game::Init()
{
	Console::Clear();
	Console::SetTitle("ConsoleTetris");
	Console::SetCursorVisible(false);

	Tetris_.Init();


	std::vector<std::string> StartMenuElements = {
		"■ 게임 시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> StartMenu = std::make_unique<Menu>(StartMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Start , std::move(StartMenu) });


	std::vector<std::string> SelectMenuElements = {
		"■ Level 1",
		"■ Level 2",
		"■ Level 3",
		"■ Level 4",
		"■ Level 5",
		"■ Level 6",
	};
	std::unique_ptr<Menu> SelectMenu = std::make_unique<Menu>(SelectMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Select , std::move(SelectMenu) });


	Menus_.insert({ EGameState::Play, nullptr });


	std::vector<std::string> PausedMenuElements = {
		"■ 게임 계속 플레이",
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> PausedMenu = std::make_unique<Menu>(PausedMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Paused, std::move(PausedMenu) });


	std::vector<std::string> DoneMenuElements = {
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> DoneMenu = std::make_unique<Menu>(DoneMenuElements, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Done, std::move(DoneMenu) });
}

void Game::Run()
{
	Timer_.Reset();

	while (!bIsDone_)
	{
		ProcessInput();
		Update();
		Draw();
	}
}

void Game::ProcessInput()
{
	Input_.Update();
	Timer_.Tick();

	if (CurrentGameState_ == EGameState::Play)
	{
		Tetris_.ProcessInput(Input_);
	}
	else
	{
		Menus_[CurrentGameState_]->ProcessInput(Input_);
	}
}

void Game::Update()
{
	if (CurrentGameState_ == EGameState::Play)
	{
		Tetris_.Update(Timer_.DeltaTime());

		if (!Tetris_.IsContinue())
		{
			CurrentGameState_ = EGameState::Done;
			Console::Clear();
		}
	}
	else
	{
		if (Menus_[CurrentGameState_]->IsSwitch())
		{
			Console::Clear();

			switch (CurrentGameState_)
			{
			case EGameState::Start:
				UpdateStartMenu();
				break;

			case EGameState::Select:
				UpdateSelectMenu();
				break;

			case EGameState::Paused:
				UpdatePausedMenu();
				break;

			case EGameState::Done:
				UpdateDoneMenu();
				break;

			default:
				ENFORCE_THROW_EXCEPTION("undefined game state type");
			}
		}
	}
}

void Game::Draw()
{
	if (CurrentGameState_ == EGameState::Play)
	{
		Vec2i BoardPosition = Vec2i(9, 2);
		Tetris_.Draw(BoardPosition);

		Vec2i PlayTimePosition = Vec2i(0, 5);
		int32_t PlayTime = static_cast<int32_t>(Timer_.TotalTime());
		Console::DrawText(PlayTimePosition.x, PlayTimePosition.y, "플레이 시간", Console::ETextColor::LightGreen);
		Console::DrawText(PlayTimePosition.x, PlayTimePosition.y + 1, Text::Format("%ds", PlayTime), Console::ETextColor::LightGreen);

		Vec2i UserLevelPosition = Vec2i(0, 10);
		Console::DrawText(UserLevelPosition.x, UserLevelPosition.y, "레벨", Console::ETextColor::LightGreen);
		Console::DrawText(UserLevelPosition.x, UserLevelPosition.y + 1, Text::Format("%d", 1), Console::ETextColor::LightGreen);

		Vec2i RemoveLinePosition = Vec2i(0, 15);
		Console::DrawText(RemoveLinePosition.x, RemoveLinePosition.y, Text::Format(" 삭제한 라인", Tetris_.GetRemoveLine()), Console::ETextColor::LightGreen);
		Console::DrawText(RemoveLinePosition.x, RemoveLinePosition.y + 1, Text::Format("%d", Tetris_.GetRemoveLine()), Console::ETextColor::LightGreen);
	}
	else
	{
		Vec2i MenuPosition = Vec2i(0, 0);
		DrawMenu(MenuPosition);
	}
}

void Game::DrawMenu(const Vec2i& InPosition)
{
	Vec2i TitlePosition = InPosition;
	DrawTitle(TitlePosition, Console::ETextColor::LightAqua);

	Vec2i MenuPosition = InPosition;
	MenuPosition.x += 7;
	MenuPosition.y += 13;

	Menus_[CurrentGameState_]->Draw(MenuPosition);
}

void Game::DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor)
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

void Game::UpdateStartMenu()
{
	const std::string& CurrentSelectMenuElement = Menus_[CurrentGameState_]->GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 시작"))
	{
		Tetris_.Reset();
		Timer_.Reset();
		CurrentGameState_ = EGameState::Select;
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsDone_ = true;
	}
}

void Game::UpdateSelectMenu()
{
	const std::string& CurrentSelectMenuElement = Menus_[CurrentGameState_]->GetCurrentSelectElement();
	CurrentGameState_ = EGameState::Play;

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
			Level_ = static_cast<int32_t>(Level.back()) - 48;
			float CurrentStepTime = 1.5f - (static_cast<float>(Level_ - 1) * 0.2f);
			Tetris_.SetStepTime(CurrentStepTime);
			break;
		}
	}
}

void Game::UpdatePausedMenu()
{
	const std::string& CurrentSelectMenuElement = Menus_[CurrentGameState_]->GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 계속 플레이"))
	{
		CurrentGameState_ = EGameState::Play;
		Tetris_.SetContinue(true);
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 재시작"))
	{
		CurrentGameState_ = EGameState::Start;
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsDone_ = true;
	}
}

void Game::UpdateDoneMenu()
{
	const std::string& CurrentSelectMenuElement = Menus_[CurrentGameState_]->GetCurrentSelectElement();

	if (!CurrentSelectMenuElement.compare("■ 게임 재시작"))
	{
		CurrentGameState_ = EGameState::Start;
	}
	else if (!CurrentSelectMenuElement.compare("■ 게임 종료"))
	{
		bIsDone_ = true;
	}
}
