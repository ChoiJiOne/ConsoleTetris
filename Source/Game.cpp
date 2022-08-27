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
	TetrisBoard->Draw(Math::Vec2i(0, 3));

	std::list<std::unique_ptr<Tetromino>>::iterator Iter = Tetrominos.begin();

	int32_t y = 3;
	Iter++;
	for (; Iter != Tetrominos.end(); ++Iter)
	{
		Iter->get()->Draw(Math::Vec2i(12, y));
		y += 4;
	}
}
