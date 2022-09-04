#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	for (auto& GameMenu : GameMenus)
	{
		GameMenu.second.reset();
	}

	for (auto& GameTetromino : GameTetrominos)
	{
		GameTetromino.reset();
	}

	GameBoard.reset();
}

void Game::Init()
{
	InitGameConsole();
	InitGameTetromino();
	InitGameBoard();
	InitGameMenu();

	TetrominoMoveMappings.insert( { Input::EKeyType::Up, Tetromino::EMovement::CW } );
	TetrominoMoveMappings.insert( { Input::EKeyType::Down, Tetromino::EMovement::Down } );
	TetrominoMoveMappings.insert( { Input::EKeyType::Left, Tetromino::EMovement::Left } );
	TetrominoMoveMappings.insert( { Input::EKeyType::Right, Tetromino::EMovement::Right } );
	TetrominoMoveMappings.insert( { Input::EKeyType::Space, Tetromino::EMovement::Down } );
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

	if (CurrentGameState == EGameState::Play)
	{
		CurrentStepTime += GameTimer.DeltaTime();
		ProcessGamePlayInput();
	}
	else
	{
		ProcessGameMenuInput();
	}
}

void Game::Update()
{
	if (CurrentGameState == EGameState::Play)
	{
		UpdateGamePlay();
	}
	else
	{
		UpdateGameMenu();
	}
}

void Game::Draw()
{
	if (CurrentGameState == EGameState::Play)
	{
		Vec2i BoardPosition = Vec2i(7, 2);
		GameBoard->Draw(BoardPosition);

		Vec2i TetrominoPosition = Vec2i(19, 3);
		for (auto& TetrominoElement = GameTetrominos.begin(); TetrominoElement != GameTetrominos.end(); ++TetrominoElement)
		{
			if (TetrominoElement != CurrentTetromino)
			{
				TetrominoElement->get()->Draw(TetrominoPosition);
				TetrominoPosition.y += TetrominoElement->get()->GetAreaSize();
			}
		}

		Console::DrawText(2, 2, Text::Format("%d", CurrentRemoveLine), Console::ETextColor::White);
	}
	else
	{
		Vec2i TitlePosition = Vec2i(0, 0);
		DrawConsoleTetrisTitle(TitlePosition, Console::ETextColor::LightAqua);

		Vec2i MenuPosition = Vec2i(7, 13);
		GameMenus[CurrentGameState]->Draw(MenuPosition);
	}
}

void Game::InitGameConsole()
{
	Console::Clear();
	Console::SetTitle("ConsoleTetris");
	Console::SetCursorVisible(false);
}

void Game::InitGameTetromino()
{
	StartPosition = Vec2i(3, 0);

	const int32_t CountOfTetromino = 6;
	for (int32_t Count = 1; Count <= CountOfTetromino; ++Count)
	{
		std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition));
		GameTetrominos.push_back(std::move(NewTetromino));
	}

	CurrentTetromino = GameTetrominos.begin();
}

void Game::InitGameBoard()
{
	int32_t BoardWidth = 10;
	int32_t BoardHeight = 20;

	GameBoard = std::make_unique<Board>(BoardWidth, BoardHeight);
	GameBoard->RegisterTetromino(*CurrentTetromino->get());
}

void Game::InitGameMenu()
{
	std::vector<std::string> StartMenuElement = {
		"■ 게임 시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> StartMenu = std::make_unique<Menu>(StartMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	GameMenus.insert({ EGameState::Start , std::move(StartMenu) });

	std::vector<std::string> PausedMenuElement = {
		"■ 게임 계속 플레이",
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> PausedMenu = std::make_unique<Menu>(PausedMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	GameMenus.insert({ EGameState::Paused, std::move(PausedMenu) });

	std::vector<std::string> DoneMenuElement = {
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> DoneMenu = std::make_unique<Menu>(DoneMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	GameMenus.insert({ EGameState::Done, std::move(DoneMenu) });
}

void Game::ProcessGamePlayInput()
{
	bCanMove = false;
	bCanMoveToBottom = false;

	for (auto& TetrominoMoveMapping : TetrominoMoveMappings)
	{
		if (GameInput.GetKeyPressState(TetrominoMoveMapping.first) == Input::EPressState::Pressed)
		{
			bCanMove = true;
			Movement = TetrominoMoveMapping.second;

			if (TetrominoMoveMapping.first == Input::EKeyType::Space)
			{
				bCanMoveToBottom = true;
			}
		}
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Pressed)
	{
		CurrentGameState = EGameState::Paused;
		Console::Clear();
	}

	if (CurrentStepTime >= MaxStepTime)
	{
		CurrentStepTime = 0.0f;
		bCanMove = true;
		Movement = Tetromino::EMovement::Down;
	}
}

void Game::ProcessGameMenuInput()
{
	if (GameInput.GetKeyPressState(Input::EKeyType::Up) == Input::EPressState::Pressed)
	{
		GameMenus[CurrentGameState]->MoveSelect(Menu::ESelectDirection::Up);
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Down) == Input::EPressState::Pressed)
	{
		GameMenus[CurrentGameState]->MoveSelect(Menu::ESelectDirection::Down);
	}

	if (GameInput.GetKeyPressState(Input::EKeyType::Enter) == Input::EPressState::Pressed)
	{
		if (!GameMenus[CurrentGameState]->GetCurrentSelectElement().compare("■ 게임 시작"))
		{
			CurrentGameState = EGameState::Play;
			Console::Clear();
		}
		else if (!GameMenus[CurrentGameState]->GetCurrentSelectElement().compare("■ 게임 종료"))
		{
			bIsDone = true;
			Console::Clear();
		}
		else if (!GameMenus[CurrentGameState]->GetCurrentSelectElement().compare("■ 게임 계속 플레이"))
		{
			CurrentGameState = EGameState::Play;
			Console::Clear();
		}
		else if (!GameMenus[CurrentGameState]->GetCurrentSelectElement().compare("■ 게임 재시작"))
		{
			CurrentGameState = EGameState::Play;
			Console::Clear();

			ResetGame();
		}
	}
}

void Game::UpdateGamePlay()
{
	if (!bCanMove)
	{
		return;
	}

	if (bCanMoveToBottom)
	{
		bool bSuccess = true;

		while (bSuccess)
		{
			if (!MoveTetrominoInBoard(Movement))
			{
				bSuccess = false;

				CurrentRemoveLine += GameBoard->Update();
				EraseCurrentTetromino();

				if (!BatchCurrentTetromino())
				{
					CurrentGameState = EGameState::Done;
					Console::Clear();
				}
			}
		}

		return;
	}

	if (!MoveTetrominoInBoard(Movement))
	{
		if (Movement == Tetromino::EMovement::Down)
		{
			CurrentRemoveLine += GameBoard->Update();

			CurrentTetromino = GameTetrominos.erase(CurrentTetromino);
			EraseCurrentTetromino();

			if (!BatchCurrentTetromino())
			{
				CurrentGameState = EGameState::Done;
				Console::Clear();
			}
		}
	}
}

void Game::UpdateGameMenu()
{
}

void Game::ResetGame()
{
	for (auto& GameTetromino : GameTetrominos)
	{
		GameTetromino.reset();
	}

	GameTetrominos.resize(0);
	GameBoard.reset();

	InitGameTetromino();
	InitGameBoard();

	CurrentRemoveLine = 0;
	bCanMove = false;
	bCanMoveToBottom = false;
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

bool Game::MoveTetrominoInBoard(const Tetromino::EMovement& InMovement)
{
	bool bIsMoveTetromino = true;

	GameBoard->UnregisterTetromino(*CurrentTetromino->get());
	CurrentTetromino->get()->Move(InMovement);

	if (!GameBoard->RegisterTetromino(*CurrentTetromino->get()))
	{
		bIsMoveTetromino = false;

		CurrentTetromino->get()->Move(Tetromino::GetCountMovement(Movement));
		GameBoard->RegisterTetromino(*CurrentTetromino->get());
	}

	return bIsMoveTetromino;
}

void Game::EraseCurrentTetromino()
{
	CurrentTetromino = GameTetrominos.erase(CurrentTetromino);
}

bool Game::BatchCurrentTetromino()
{
	bool bIsSuccessBatch = true;

	std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition));
	GameTetrominos.push_back(std::move(NewTetromino));

	if (!GameBoard->RegisterTetromino(*CurrentTetromino->get()))
	{
		bIsSuccessBatch = false;
	}

	return bIsSuccessBatch;
}
