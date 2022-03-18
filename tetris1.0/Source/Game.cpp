#include "Board.h"
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
	Tetromino tetromino(Vector2i(4, 0), Tetromino::EShape::L);
	Board board;

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
				ConsoleUtil::ShowTextInConsole(absolPos.x + position.x, absolPos.y + position.y, "бс", EConsoleTextColor::Blue);
			}

			Vector2i boardPos = Vector2i(0, 0);
			int32_t rowSize = board.GetRowSize();
			int32_t colSize = board.GetColSize();

			for (int32_t y = 0; y < rowSize; ++y)
			{
				for (int32_t x = 0; x < colSize; ++x)
				{
					Board::EBlockState state = board.GetBoardBlockState(x, y);

					if (state == Board::EBlockState::Fill || state == Board::EBlockState::Fix)
					{
						ConsoleUtil::ShowTextInConsole(x + boardPos.x, y + boardPos.y, "бс", EConsoleTextColor::Green);
					}
				}
			}

			bIsDraw = false;
		}
	}

	ConsoleUtil::SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}