#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	StartMenu.reset();

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

	const int32_t CountOfTetromino = 6;
	for (int32_t Count = 1; Count <= CountOfTetromino; ++Count)
	{
		std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition));
		Tetrominos.push_back(std::move(NewTetromino));
	}

	CurrentTetromino = Tetrominos.begin();

	TetrisBoard = std::make_unique<Board>(10, 20);
	TetrisBoard->RegisterTetromino(*CurrentTetromino->get());

	std::vector<std::string> StartMenuElement = {
		"бс Start",
		"бс Quit"
	};
	StartMenu = std::make_unique<Menu>(StartMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
}

void Game::Run()
{
	GameTimer.Reset();

	while (!bIsDone)
	{
		ProcessInput();
		Update();
		Draw();
	}
}

void Game::ProcessInput()
{
	GameInput.Update();
	GameTimer.Tick();

	bIsDone = (GameInput.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Released);
	bCanMove = false;
	CurrentStepTime += GameTimer.DeltaTime();

	if (CurrentGameState == GameState::Start)
	{
		if (GameInput.GetKeyPressState(Input::EKeyType::Up) == Input::EPressState::Pressed)
		{
			StartMenu->MoveSelect(Menu::ESelectDirection::Up);
		}

		if (GameInput.GetKeyPressState(Input::EKeyType::Down) == Input::EPressState::Pressed)
		{
			StartMenu->MoveSelect(Menu::ESelectDirection::Down);
		}

		if (GameInput.GetKeyPressState(Input::EKeyType::Enter) == Input::EPressState::Pressed)
		{
			if (StartMenu->GetCurrentSelectElement().compare("Start"))
			{
				CurrentGameState = GameState::Play;
				Console::Clear();
			}
			else if(StartMenu->GetCurrentSelectElement().compare("Quit"))
			{
				bIsDone = true;
			}
		}
	}
	else if (CurrentGameState == GameState::Play)
	{
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
}

void Game::Update()
{
	if (CurrentGameState == GameState::Start)
	{

	}
	else if (CurrentGameState == GameState::Play)
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
}

void Game::Draw()
{
	if (CurrentGameState == GameState::Start)
	{
		Math::Vec2i TitlePosition = Math::Vec2i(0, 0);
		DrawTitle(TitlePosition, Console::ETextColor::LightAqua);

		Math::Vec2i MenuPosition = Math::Vec2i(0, 12);
		StartMenu->Draw(MenuPosition);
	}
	else if (CurrentGameState == GameState::Play)
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
}

void Game::DrawTitle(const Math::Vec2i& InPosition, const Console::ETextColor& InColor)
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

	Math::Vec2i Position = InPosition;
	for (const auto& TitleLine : Title)
	{
		Console::DrawText(Position.x, Position.y, TitleLine, InColor);
		Position.y += 1;
	}
}
