#include "Macro.h"
#include "Game.h"

Game::~Game()
{
}

void Game::Init()
{
	Console::Clear();
	Console::SetTitle("ConsoleTetris");
	Console::SetCursorVisible(false);

	Tetris_.Init();
	TetrisMenu_.Init();
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

	if (bIsPlayGame)
	{
		Tetris_.ProcessInput(Input_);
	}
	else
	{
		TetrisMenu_.ProcessInput(Input_);
	}
}

void Game::Update()
{
	if (bIsPlayGame)
	{
		Tetris_.Update(Timer_.DeltaTime());

		if (Tetris_.IsPaused())
		{
			bIsPlayGame = false;
			TetrisMenu_.SetMenuState(TetrisMenu::EMenuState::Paused);
		}

		if (!Tetris_.IsProcess())
		{
			bIsPlayGame = false;
			TetrisMenu_.SetMenuState(TetrisMenu::EMenuState::Done);
		}
	}
	else
	{
		TetrisMenu_.Update(Timer_.DeltaTime());
		bIsDone_ = TetrisMenu_.IsSelectQuitGame();

		if (TetrisMenu_.IsSwitchMenu() && TetrisMenu_.GetMenuState() == TetrisMenu::EMenuState::Play)
		{
			bIsPlayGame = true;
			Tetris_.Continue();

			float CurrentStepTime = 1.5f - (static_cast<float>(TetrisMenu_.GetSelectLevel() - 1) * 0.2f);
			Tetris_.SetStepTime(CurrentStepTime);
		}

		if (TetrisMenu_.IsSwitchMenu() && TetrisMenu_.GetMenuState() == TetrisMenu::EMenuState::Start)
		{
			Tetris_.Reset();
			Timer_.Reset();
		}
	}
}

void Game::Draw()
{
	if (bIsPlayGame)
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
		TetrisMenu_.Draw(MenuPosition);
	}
}