#include "Board.h"
#include "ConsoleUtil.h"
#include "GameTimer.h"
#include "InputSystem.h"
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

	globalTimer.reset();
	inputSystem.reset();
}

void Game::Setup()
{
	ConsoleUtil::SetConsoleTitle("tetris1.0");
	ConsoleUtil::SetConsoleCursorVisible(false);

	inputSystem = std::make_shared<InputSystem>();
	globalTimer = std::make_shared<GameTimer>();

	uiPositionCache["tetrisBoard"]   = Vector2i(10, 0);
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
	globalTimer->Reset();

	while (!bIsDoneGame)
	{
		globalTimer->Tick();

		Update();
		Draw();
	}

	ConsoleUtil::ClearConsole();
	ConsoleUtil::ShowTextInConsole(0, 0, "thank you for your play", EConsoleTextColor::BrightWhite);
}

void Game::Update()
{
	inputSystem->Update();

	if (inputSystem->IsCurrKeyPress("KeyEscape"))
	{
		bIsDoneGame = true;
	}

	if (inputSystem->IsCurrKeyPress("KeyUp") && !inputSystem->IsPrevKeyPress("KeyUp"))
	{
		if (SpinClockWiseTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (inputSystem->IsCurrKeyPress("KeyDown") && !inputSystem->IsPrevKeyPress("KeyDown"))
	{
		if (MoveDownTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (inputSystem->IsCurrKeyPress("KeyLeft") && !inputSystem->IsPrevKeyPress("KeyLeft"))
	{
		if (MoveLeftTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			bIsDraw = true;
		}
	}

	if (inputSystem->IsCurrKeyPress("KeyRight") && !inputSystem->IsPrevKeyPress("KeyRight"))
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
		DrawTetrisBoard(uiPositionCache["tetrisBoard"], *tetrisBoard);
		
		DrawRemainTime(uiPositionCache["remainingTime"], 10);
		DrawGameLevel(uiPositionCache["level"], 1);
		DrawPushKeyArrow(uiPositionCache["keyArrow"]);

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

void Game::DrawTetrisBoard(const Vector2i& consolePos, Board& board)
{
	int32_t rowSize = board.GetRowSize();
	int32_t colSize = board.GetColSize();

	for (int32_t y = 0; y < rowSize; ++y)
	{
		for (int32_t x = 0; x < colSize; ++x)
		{
			Board::EBlockState state = board.GetBoardBlockState(x, y);

			if (state == Board::EBlockState::Fix)
			{
				ConsoleUtil::ShowTextInConsole(x + consolePos.x, y + consolePos.y, "��", EConsoleTextColor::LightGreen);
			}
			else if (state == Board::EBlockState::Fill)
			{
				ConsoleUtil::ShowTextInConsole(x + consolePos.x, y + consolePos.y, "��", EConsoleTextColor::LightBlue);
			}
			else
			{
				ConsoleUtil::ShowTextInConsole(x + consolePos.x, y + consolePos.y, "  ", EConsoleTextColor::Black);
			}
		}
	}
}

void Game::DrawRemainTime(const Vector2i& consolePos, int32_t remainTime)
{
	ConsoleUtil::ShowTextInConsole(
		consolePos.x,
		consolePos.y,
		StringUtil::StringFormat("���� �ð� : %2d", remainTime),
		(remainTime > 10 ? EConsoleTextColor::BrightWhite : EConsoleTextColor::Red)
	);
}

void Game::DrawGameLevel(const Vector2i& consolePos, int32_t level)
{
	ConsoleUtil::ShowTextInConsole(
		consolePos.x,
		consolePos.y,
		StringUtil::StringFormat("���� ���� : %2d", level),
		EConsoleTextColor::BrightWhite
	);
}

void Game::DrawPushKeyArrow(const Vector2i& consolePos)
{
	ConsoleUtil::ShowTextInConsole(    consolePos.x,     consolePos.y, "��", EConsoleTextColor::Green);
	ConsoleUtil::ShowTextInConsole(consolePos.x - 1,     consolePos.y, "��", EConsoleTextColor::Green);
	ConsoleUtil::ShowTextInConsole(consolePos.x + 1,     consolePos.y, "��", EConsoleTextColor::Green);
	ConsoleUtil::ShowTextInConsole(    consolePos.x, consolePos.y - 1, "��", EConsoleTextColor::Green);
	ConsoleUtil::ShowTextInConsole(    consolePos.x, consolePos.y + 1, "��", EConsoleTextColor::Green);
}
