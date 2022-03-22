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
	SetupGame();


	tetrisBoard = std::make_shared<Board>();

	currTetromino = TetrominoGenerator::GenerateRandomTetromino(
		Vector2i(tetrisBoard->GetColSize() / 3, 0)
	);

	nextTetromino = TetrominoGenerator::GenerateRandomTetromino(
		Vector2i(tetrisBoard->GetColSize() / 3, 0)
	);

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

	if(!bIsWaitNextLevel)
	{
		if (inputSystem->IsCurrKeyPress("KeyUp") && !inputSystem->IsPrevKeyPress("KeyUp"))
		{
			SpinClockWiseTetrominoInBoard(*currTetromino, *tetrisBoard);
		}

		if (inputSystem->IsCurrKeyPress("KeyLeft") && !inputSystem->IsPrevKeyPress("KeyLeft"))
		{
			MoveLeftTetrominoInBoard(*currTetromino, *tetrisBoard);
		}

		if (inputSystem->IsCurrKeyPress("KeyRight") && !inputSystem->IsPrevKeyPress("KeyRight"))
		{
			MoveRightTetrominoInBoard(*currTetromino, *tetrisBoard);
		}

		if (inputSystem->IsCurrKeyPress("KeyDown") && !inputSystem->IsPrevKeyPress("KeyDown"))
		{
			if (!MoveDownTetrominoInBoard(*currTetromino, *tetrisBoard))
			{
				tetrisBoard->UpdateBoardState();

				currTetromino.reset();
				currTetromino = nextTetromino;
				nextTetromino = TetrominoGenerator::GenerateRandomTetromino(
					Vector2i(tetrisBoard->GetColSize() / 3, 0)
				);

				if (IsCrashTetrominoAndBoard(*currTetromino, *tetrisBoard))
				{
					bIsDoneGame = true;
				}
				else
				{
					AddTetrominoInBoard(*currTetromino, *tetrisBoard);
				}
			}

			userStepTime = 0.0f;
		}

		if (inputSystem->IsCurrKeyPress("KeySpace") && !inputSystem->IsPrevKeyPress("KeySpace"))
		{
			MoveBottomTetrominoInBoard(*currTetromino, *tetrisBoard);
			
			tetrisBoard->UpdateBoardState();

			currTetromino.reset();
			currTetromino = nextTetromino;
			nextTetromino = TetrominoGenerator::GenerateRandomTetromino(
				Vector2i(tetrisBoard->GetColSize() / 3, 0)
			);

			if (IsCrashTetrominoAndBoard(*currTetromino, *tetrisBoard))
			{
				bIsDoneGame = true;
			}
			else
			{
				AddTetrominoInBoard(*currTetromino, *tetrisBoard);
			}
		}
	}

	userPlayTime += globalTimer->DeltaTime();
	userStepTime += globalTimer->DeltaTime();

	if (userStepTime > gameStepTime)
	{
		if (!MoveDownTetrominoInBoard(*currTetromino, *tetrisBoard))
		{
			tetrisBoard->UpdateBoardState();

			currTetromino.reset();
			currTetromino = nextTetromino;
			nextTetromino = TetrominoGenerator::GenerateRandomTetromino(
				Vector2i(tetrisBoard->GetColSize() / 3, 0)
			);

			if (IsCrashTetrominoAndBoard(*currTetromino, *tetrisBoard))
			{
				bIsDoneGame = true;
			}
			else
			{
				AddTetrominoInBoard(*currTetromino, *tetrisBoard);
			}
		}

		userStepTime = 0.0f;
	}


	if (!bIsWaitNextLevel)
	{
		if (userPlayTime > levelPlayTime)
		{
			userPlayTime = 0.0f;
			bIsWaitNextLevel = true;

			currTetromino.reset();
			nextTetromino.reset();

			tetrisBoard->ResetBoardState();
		}
	}
	else
	{

		if (userPlayTime > waitNextPlayTime)
		 {
			userPlayTime = 0.0f;
			bIsWaitNextLevel = false;

			currTetromino = TetrominoGenerator::GenerateRandomTetromino(
				Vector2i(tetrisBoard->GetColSize() / 3, 0)
			);

			nextTetromino = TetrominoGenerator::GenerateRandomTetromino(
				Vector2i(tetrisBoard->GetColSize() / 3, 0)
			);

			AddTetrominoInBoard(*currTetromino, *tetrisBoard);
		}
	}
}

void Game::Draw()
{
	DrawTetrisBoard(uiPositionCache["tetrisBoard"], *tetrisBoard);

	DrawRemainTime(uiPositionCache["remainingTime"], static_cast<int32_t>(levelPlayTime - userPlayTime));
	DrawGameLevel(uiPositionCache["level"], userLevel);
	DrawPushKeyArrow(uiPositionCache["keyArrow"]);
}

void Game::SetupGame()
{
	ConsoleUtil::ClearConsole();          
	ConsoleUtil::SetConsoleTitle("tetris1.0");
	ConsoleUtil::SetConsoleCursorVisible(false);

	inputSystem = std::make_shared<InputSystem>();
	globalTimer = std::make_shared<GameTimer>();

	uiPositionCache["tetrisBoard"]   = Vector2i(10, 0);
	uiPositionCache["remainingTime"] = Vector2i(22, 8);
	uiPositionCache["level"]         = Vector2i(22, 9);
	uiPositionCache["keyArrow"]      = Vector2i(24, 12);

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

void Game::MoveLeftTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Move(Tetromino::EMove::Left);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Move(Tetromino::EMove::Right);
	}

	AddTetrominoInBoard(tetromino, board);
}

void Game::MoveRightTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Move(Tetromino::EMove::Right);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Move(Tetromino::EMove::Left);
	}

	AddTetrominoInBoard(tetromino, board);
}

void Game::MoveBottomTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	RemoveTetrominoInBoard(tetromino, board);

	while (true)
	{
		tetromino.Move(Tetromino::EMove::Down);

		if (IsCrashTetrominoAndBoard(tetromino, board))
		{
			tetromino.Move(Tetromino::EMove::Up);
			break;
		}
	}

	AddTetrominoInBoard(tetromino, board);
}

void Game::SpinClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Spin(Tetromino::ESpin::CW);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Spin(Tetromino::ESpin::CCW);
	}

	AddTetrominoInBoard(tetromino, board);
}

void Game::SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board)
{
	RemoveTetrominoInBoard(tetromino, board);

	tetromino.Spin(Tetromino::ESpin::CCW);

	if (IsCrashTetrominoAndBoard(tetromino, board))
	{
		tetromino.Spin(Tetromino::ESpin::CW);
	}

	AddTetrominoInBoard(tetromino, board);
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
				ConsoleUtil::ShowTextInConsole(x + consolePos.x, y + consolePos.y, "■", EConsoleTextColor::LightGreen);
			}
			else if (state == Board::EBlockState::Fill)
			{
				ConsoleUtil::ShowTextInConsole(x + consolePos.x, y + consolePos.y, "■", EConsoleTextColor::LightBlue);
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
		StringUtil::StringFormat("남은 시간 : %2d", remainTime),
		(remainTime > 10 ? EConsoleTextColor::BrightWhite : EConsoleTextColor::Red)
	);
}

void Game::DrawGameLevel(const Vector2i& consolePos, int32_t level)
{
	ConsoleUtil::ShowTextInConsole(
		consolePos.x,
		consolePos.y,
		StringUtil::StringFormat("현재 레벨 : %2d", level),
		EConsoleTextColor::BrightWhite
	);
}

void Game::DrawPushKeyArrow(const Vector2i& consolePos)
{
	ConsoleUtil::ShowTextInConsole(
		consolePos.x, consolePos.y, "■", 
		inputSystem->IsCurrKeyPress("KeySpace") ? EConsoleTextColor::LightRed : EConsoleTextColor::BrightWhite
	);

	ConsoleUtil::ShowTextInConsole(
		consolePos.x - 1, consolePos.y, "←",  
		inputSystem->IsCurrKeyPress("KeyLeft") ? EConsoleTextColor::LightRed : EConsoleTextColor::BrightWhite
	);

	ConsoleUtil::ShowTextInConsole(
		consolePos.x + 1, consolePos.y, "→", 
		inputSystem->IsCurrKeyPress("KeyRight") ? EConsoleTextColor::LightRed : EConsoleTextColor::BrightWhite
	);

	ConsoleUtil::ShowTextInConsole(
		consolePos.x, consolePos.y - 1, "↑",  
		inputSystem->IsCurrKeyPress("KeyUp") ? EConsoleTextColor::LightRed : EConsoleTextColor::BrightWhite
	);

	ConsoleUtil::ShowTextInConsole(
		consolePos.x, consolePos.y + 1, "↓", 
		inputSystem->IsCurrKeyPress("KeyDown") ? EConsoleTextColor::LightRed : EConsoleTextColor::BrightWhite
	);
}
