#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	for (auto& GameMenu : Menus_)
	{
		GameMenu.second.reset();
	}
}

void Game::Init()
{
	Console::Clear();
	Console::SetTitle("ConsoleTetris");
	Console::SetCursorVisible(false);

	std::vector<std::string> StartMenuElement = {
		"■ 게임 시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> StartMenu = std::make_unique<Menu>(StartMenuElement, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Start , std::move(StartMenu) });

	std::vector<std::string> PausedMenuElement = {
		"■ 게임 계속 플레이",
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> PausedMenu = std::make_unique<Menu>(PausedMenuElement, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Paused, std::move(PausedMenu) });

	std::vector<std::string> DoneMenuElement = {
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> DoneMenu = std::make_unique<Menu>(DoneMenuElement, Console::ETextColor::LightBlue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Done, std::move(DoneMenu) });

	Tetris_.Init();
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
		Menus_[CurrentGameState_]->PrecessInput(Input_);
	}
}

void Game::Update()
{
	if (CurrentGameState_ == EGameState::Play)
	{
		Tetris_.Update(Timer_.DeltaTime());

		if (!Tetris_.IsContinue())
		{
			CurrentGameState_ = EGameState::Paused;
			Console::Clear();
		}
	}
	else
	{
		if (Menus_[CurrentGameState_]->IsSwitch())
		{
			std::string CurrentSelectElement = Menus_[CurrentGameState_]->GetCurrentSelectElement();
			Console::Clear();

			static std::pair<std::string, EGameState> MenuElements[] = {
				{ "■ 게임 시작",       EGameState::Play },
				{ "■ 게임 종료",       EGameState::Exit},
				{ "■ 게임 계속 플레이", EGameState::Play},
				{ "■ 게임 재시작",     EGameState::Play},
			};

			for (const auto& MenuElement : MenuElements)
			{
				if (!CurrentSelectElement.compare(MenuElement.first))
				{
					CurrentGameState_ = MenuElement.second;

					if (!CurrentSelectElement.compare("■ 게임 종료"))
					{
						bIsDone_ = true;
					}

					if (!CurrentSelectElement.compare("■ 게임 계속 플레이"))
					{
						Tetris_.SetContinue(true);
					}

					if (!CurrentSelectElement.compare("■ 게임 재시작"))
					{
						Tetris_.Reset();
						Timer_.Reset();
					}

					break;
				}
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
		Console::DrawText(PlayTimePosition.x, PlayTimePosition.y, Text::Format(" 플레이 시간:%ds", PlayTime), Console::ETextColor::LightGreen);

		Vec2i UserLevelPosition = Vec2i(0, 10);
		Console::DrawText(UserLevelPosition.x, UserLevelPosition.y, Text::Format(" 레벨:%d", 1), Console::ETextColor::LightGreen);

		Vec2i RemoveLinePosition = Vec2i(0, 15);
		Console::DrawText(RemoveLinePosition.x, RemoveLinePosition.y, Text::Format(" 삭제한 라인:%d", Tetris_.GetRemoveLine()), Console::ETextColor::LightGreen);
	}
	else
	{
		Vec2i TitlePosition = Vec2i(0, 0);
		DrawConsoleTetrisTitle(TitlePosition, Console::ETextColor::LightAqua);

		if (CurrentGameState_ != EGameState::Exit)
		{
			Vec2i MenuPosition = Vec2i(7, 13);
			Menus_[CurrentGameState_]->Draw(MenuPosition);
		}
	}
}

void Game::DrawConsoleTetrisTitle(const Vec2i& InPosition, const Console::ETextColor& InColor)
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