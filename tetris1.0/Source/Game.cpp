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
	nextTetromino.reset();
	currTetromino.reset();
	tetrisBoard.reset();
}

void Game::Setup()
{
	ConsoleUtil::SetConsoleTitle("tetris1.0");
	ConsoleUtil::SetConsoleCursorVisible(false);

	uiPositionCache["tetrisBoard"]   = Vector2i(10, 0);
	uiPositionCache["nextTetromino"] = Vector2i(22, 2);
	uiPositionCache["remainingTime"] = Vector2i(22, 8);
	uiPositionCache["level"]         = Vector2i(22, 9);
	uiPositionCache["keyArrow"]      = Vector2i(24, 12);
	
	tetrisBoard = std::make_shared<Board>();
	currTetromino = TetrominoGenerator::GenerateRandomTetromino(Vector2i(tetrisBoard->GetColSize() / 3, 0));
	nextTetromino = TetrominoGenerator::GenerateRandomTetromino(Vector2i(tetrisBoard->GetColSize() / 3, 0));

	AddTetrominoInBoard(*currTetromino, *tetrisBoard);
}

void Game::Run()
{
	while (!bIsDoneGame)
	{
		Update();
		Draw();
	}

	ConsoleUtil::ClearConsole();
	ConsoleUtil::ShowTextInConsole(0, 0, "thank you for your play", EConsoleTextColor::BrightWhite);
}

void Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		bIsDoneGame = true;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (SpinClockWiseTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (MoveDownTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (MoveLeftTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		if (MoveRightTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}
}

void Game::Draw()
{
	if (bIsDraw)
	{
		ConsoleUtil::ClearConsole();

		Vector2i boardPos = uiPositionCache["tetrisBoard"];
		int32_t rowSize = tetrisBoard->GetRowSize();
		int32_t colSize = tetrisBoard->GetColSize();

		for (int32_t y = 0; y < rowSize; ++y)
		{
			for (int32_t x = 0; x < colSize; ++x)
			{
				Board::EBlockState state = tetrisBoard->GetBoardBlockState(x, y);

				if (state == Board::EBlockState::Fix)
				{
					ConsoleUtil::ShowTextInConsole(x + boardPos.x, y + boardPos.y, "■", EConsoleTextColor::Green);
				}
				else if (state == Board::EBlockState::Fill)
				{
					ConsoleUtil::ShowTextInConsole(x + boardPos.x, y + boardPos.y, "■", EConsoleTextColor::Blue);
				}
			}
		}

		Vector2i nextTetrominoPos = uiPositionCache["nextTetromino"];
		ConsoleUtil::ShowTextInConsole(nextTetrominoPos.x, nextTetrominoPos.y, "다음 테트로미노", EConsoleTextColor::Green);
		const std::vector<Vector2i>& positions = nextTetromino->GetRelativePositions();

		for (const auto& position : positions)
		{
			Vector2i consolePos = nextTetrominoPos + position;
			ConsoleUtil::ShowTextInConsole(consolePos.x + 1, consolePos.y + 1, "■", EConsoleTextColor::Blue);
			ConsoleUtil::ShowTextInConsole(consolePos.x + 1, consolePos.y + 1, "■", EConsoleTextColor::Blue);
		}

		Vector2i remainingTimePos = uiPositionCache["remainingTime"];
		ConsoleUtil::ShowTextInConsole(remainingTimePos.x, remainingTimePos.y, "남은 시간 : s", EConsoleTextColor::Green);

		Vector2i levelPos = uiPositionCache["level"];
		ConsoleUtil::ShowTextInConsole(levelPos.x, levelPos.y, "현재 레벨 : ", EConsoleTextColor::Green);

		Vector2i keyArrowPos = uiPositionCache["keyArrow"];
		ConsoleUtil::ShowTextInConsole(keyArrowPos.x, keyArrowPos.y, "■", EConsoleTextColor::Green);
		ConsoleUtil::ShowTextInConsole(keyArrowPos.x - 1, keyArrowPos.y, "←", EConsoleTextColor::Green);
		ConsoleUtil::ShowTextInConsole(keyArrowPos.x + 1, keyArrowPos.y, "→", EConsoleTextColor::Green);
		ConsoleUtil::ShowTextInConsole(keyArrowPos.x, keyArrowPos.y - 1, "↑", EConsoleTextColor::Green);
		ConsoleUtil::ShowTextInConsole(keyArrowPos.x, keyArrowPos.y + 1, "↓", EConsoleTextColor::Green);

		bIsDraw = false;
	}
}

void Game::AddTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	const std::vector<Vector2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vector2i absolPos = tetromino.GetAbsolutePosition() + position;
		board.SetBoardBlockState(absolPos.x, absolPos.y, Board::EBlockState::Fill);
	}
}

void Game::RemoveTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	const std::vector<Vector2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vector2i boardPos = tetromino.GetAbsolutePosition() + position;
		board.SetBoardBlockState(boardPos.x, boardPos.y, Board::EBlockState::Empty);
	}
}

bool Game::IsCrashTetrominoAndBoard(Tetromino& tetromino, Board& board)
{
	const std::vector<Vector2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vector2i boardPos = tetromino.GetAbsolutePosition() + position;

		if (!board.CheckInsidePositionInBoard(boardPos.x, boardPos.y))
		{
			return true;
		}
		
		if (board.GetBoardBlockState(boardPos.x, boardPos.y) != Board::EBlockState::Empty)
		{
			return true;
		}
	}

	return false;
}

bool Game::MoveDownTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino, board);
	
	tetromino.Move(Tetromino::EMove::Down);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Move(Tetromino::EMove::Up);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino, board);
	return bCanMove;
}

bool Game::MoveLeftTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Move(Tetromino::EMove::Left);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Move(Tetromino::EMove::Right);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino, board);
	return bCanMove;
}

bool Game::MoveRightTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Move(Tetromino::EMove::Right);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Move(Tetromino::EMove::Left);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino, board);
	return bCanMove;
}

bool Game::SpinClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Spin(Tetromino::ESpin::CW);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Spin(Tetromino::ESpin::CCW);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino, board);
	return bCanMove;
}

bool Game::SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Spin(Tetromino::ESpin::CCW);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Spin(Tetromino::ESpin::CW);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino, board);
	return bCanMove;
}
