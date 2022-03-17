#include "ConsoleUtil.h"
#include "StringUtil.h"
#include "Tetromino.h"

#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Setup()
{
	ConsoleUtil::SetConsoleTitle("tetris1.0");
	ConsoleUtil::SetConsoleCursorVisible(false);
}

void Game::Run()
{
	Tetromino tetromino(Vector2i(3, 0), Tetromino::EShape::L);

	while (!bIsDoneGame)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			bIsDoneGame = true;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			tetromino.Spin(Tetromino::ESpin::CW);
			bIsDraw = true;
		}

		if (bIsDraw)
		{
			ConsoleUtil::ClearConsole();

			Vector2i absolPos = tetromino.GetAbsolutePosition();
			const std::vector<Vector2i> positions = tetromino.GetRelativePositions();

			for (const auto& position : positions)
			{
				ConsoleUtil::ShowTextInConsole(position.x, position.y, "бс", EConsoleTextColor::Blue);
			}

			bIsDraw = false;
		}
	}

	ConsoleUtil::SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}