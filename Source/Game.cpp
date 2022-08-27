#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	for (auto& TargetTetromino : Tetrominos)
	{
		TargetTetromino.reset();
	}

	TetrisBoard.reset();
}

void Game::Init()
{
	Console::Clear();
	Console::SetTitle("ConsoleTetris");
	Console::SetCursorVisible(false);

	StartPosition = Math::Vec2i(3, 0);

	for (int32_t CountOfTetromino = 1; CountOfTetromino <= 6; ++CountOfTetromino)
	{
		std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition));
		Tetrominos.push_back(std::move(NewTetromino));
	}

	CurrentTetromino = Tetrominos.begin();

	TetrisBoard = std::make_unique<Board>(10, 20);
	TetrisBoard->RegisterTetromino(*CurrentTetromino->get());
}

void Game::Run()
{
	GameTimer.Reset();

	while (!bIsDone)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
	GameInput.Update();
	GameTimer.Tick();

	bIsDone = (GameInput.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Released);
	bCanMove = false;
	CurrentStepTime += GameTimer.DeltaTime();

	if (GameInput.GetKeyPressState(Input::EKeyType::Up) == Input::EPressState::Pressed)
	{
		bCanMove = true;
		Movement = Tetromino::EMovement::CW;
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Down) == Input::EPressState::Pressed)
	{
		bCanMove = true;
		Movement = Tetromino::EMovement::Down;
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Left) == Input::EPressState::Pressed)
	{
		bCanMove = true;
		Movement = Tetromino::EMovement::Left;
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Right) == Input::EPressState::Pressed)
	{
		bCanMove = true;
		Movement = Tetromino::EMovement::Right;
	}

	if (CurrentStepTime >= MaxStepTime)
	{
		CurrentStepTime = 0.0f;
		bCanMove = true;
		Movement = Tetromino::EMovement::Down;
	}
}

void Game::Update()
{
	if (bCanMove)
	{
		TetrisBoard->UnregisterTetromino(*CurrentTetromino->get());
		CurrentTetromino->get()->Move(Movement);

		if (!TetrisBoard->RegisterTetromino(*CurrentTetromino->get()))
		{
			CurrentTetromino->get()->Move(Tetromino::GetCountMovement(Movement));
			TetrisBoard->RegisterTetromino(*CurrentTetromino->get());

			if (Movement == Tetromino::EMovement::Down)
			{
				TetrisBoard->Update();

				CurrentTetromino = Tetrominos.erase(CurrentTetromino);
				std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition));
				Tetrominos.push_back(std::move(NewTetromino));

				TetrisBoard->RegisterTetromino(*CurrentTetromino->get());
			}
		}
	}
}

void Game::Render()
{
	Math::Vec2i BoardPosition = Math::Vec2i(5, 5);
	TetrisBoard->Draw(BoardPosition);

	Math::Vec2i TetrominoPosition = Math::Vec2i(17, 5);
	for (auto& TetrominoElement = Tetrominos.begin(); TetrominoElement != Tetrominos.end(); ++TetrominoElement)
	{
		if (TetrominoElement != CurrentTetromino)
		{
			TetrominoElement->get()->Draw(TetrominoPosition);
			TetrominoPosition.y += TetrominoElement->get()->GetAreaSize();
		}
	}
}
