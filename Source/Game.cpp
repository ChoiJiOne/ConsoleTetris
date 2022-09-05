#include "Macro.h"
#include "Game.h"

Game::~Game()
{
	for (auto& GameMenu : Menus_)
	{
		GameMenu.second.reset();
	}

	for (auto& GameTetromino : Tetrominos_)
	{
		GameTetromino.reset();
	}

	Board_.reset();
}

void Game::Init()
{
	InitGameConsole();
	InitGameTetromino();
	InitGameBoard();
	InitGameMenu();

	TetrominoMoveMappings_.insert( { Input::EKeyType::Up, Tetromino::EMovement::CW } );
	TetrominoMoveMappings_.insert( { Input::EKeyType::Down, Tetromino::EMovement::Down } );
	TetrominoMoveMappings_.insert( { Input::EKeyType::Left, Tetromino::EMovement::Left } );
	TetrominoMoveMappings_.insert( { Input::EKeyType::Right, Tetromino::EMovement::Right } );
	TetrominoMoveMappings_.insert( { Input::EKeyType::Space, Tetromino::EMovement::Down } );
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

	if (CurrentGameState_ == EGameState::Play)
	{
		CurrentStepTime_ += Timer_.DeltaTime();
		ProcessGamePlayInput();
	}
	else
	{
		ProcessGameMenuInput();
	}
}

void Game::Update()
{
	if (CurrentGameState_ == EGameState::Play)
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
	if (CurrentGameState_ == EGameState::Play)
	{
		Vec2i BoardPosition = Vec2i(7, 2);
		Board_->Draw(BoardPosition);

		Vec2i TetrominoPosition = Vec2i(19, 3);
		DrawTetrominos(TetrominoPosition);

		Console::DrawText(2, 2, Text::Format("%d", CurrentRemoveLine_), Console::ETextColor::White);
	}
	else
	{
		Vec2i TitlePosition = Vec2i(0, 0);
		DrawConsoleTetrisTitle(TitlePosition, Console::ETextColor::LightAqua);

		Vec2i MenuPosition = Vec2i(7, 13);
		Menus_[CurrentGameState_]->Draw(MenuPosition);
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
	StartPosition_ = Vec2i(3, 0);

	const int32_t CountOfTetromino = 6;
	for (int32_t Count = 1; Count <= CountOfTetromino; ++Count)
	{
		std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition_));
		Tetrominos_.push_back(std::move(NewTetromino));
	}

	CurrentTetromino = Tetrominos_.begin();
}

void Game::InitGameBoard()
{
	int32_t BoardWidth = 10;
	int32_t BoardHeight = 20;

	Board_ = std::make_unique<Board>(BoardWidth, BoardHeight);
	Board_->RegisterTetromino(*CurrentTetromino->get());
}

void Game::InitGameMenu()
{
	std::vector<std::string> StartMenuElement = {
		"■ 게임 시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> StartMenu = std::make_unique<Menu>(StartMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Start , std::move(StartMenu) });

	std::vector<std::string> PausedMenuElement = {
		"■ 게임 계속 플레이",
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> PausedMenu = std::make_unique<Menu>(PausedMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Paused, std::move(PausedMenu) });

	std::vector<std::string> DoneMenuElement = {
		"■ 게임 재시작",
		"■ 게임 종료",
	};
	std::unique_ptr<Menu> DoneMenu = std::make_unique<Menu>(DoneMenuElement, Console::ETextColor::Blue, Console::ETextColor::White);
	Menus_.insert({ EGameState::Done, std::move(DoneMenu) });
}

void Game::ProcessGamePlayInput()
{
	bCanMove_ = false;
	bCanMoveToBottom_ = false;

	for (auto& TetrominoMoveMapping : TetrominoMoveMappings_)
	{
		if (Input_.GetKeyPressState(TetrominoMoveMapping.first) == Input::EPressState::Pressed)
		{
			bCanMove_ = true;
			Movement_ = TetrominoMoveMapping.second;

			if (TetrominoMoveMapping.first == Input::EKeyType::Space)
			{
				bCanMoveToBottom_ = true;
			}
		}
	}

	if (Input_.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Pressed)
	{
		CurrentGameState_ = EGameState::Paused;
		Console::Clear();
	}

	if (CurrentStepTime_ >= MaxStepTime_)
	{
		CurrentStepTime_ = 0.0f;
		bCanMove_ = true;
		Movement_ = Tetromino::EMovement::Down;
	}
}

void Game::ProcessGameMenuInput()
{
	if (Input_.GetKeyPressState(Input::EKeyType::Up) == Input::EPressState::Pressed)
	{
		Menus_[CurrentGameState_]->MoveSelect(Menu::ESelectDirection::Up);
	}

	if (Input_.GetKeyPressState(Input::EKeyType::Down) == Input::EPressState::Pressed)
	{
		Menus_[CurrentGameState_]->MoveSelect(Menu::ESelectDirection::Down);
	}

	if (Input_.GetKeyPressState(Input::EKeyType::Enter) == Input::EPressState::Pressed)
	{
		if (!Menus_[CurrentGameState_]->GetCurrentSelectElement().compare("■ 게임 시작"))
		{
			CurrentGameState_ = EGameState::Play;
			Console::Clear();
		}
		else if (!Menus_[CurrentGameState_]->GetCurrentSelectElement().compare("■ 게임 종료"))
		{
			bIsDone_ = true;
			Console::Clear();
		}
		else if (!Menus_[CurrentGameState_]->GetCurrentSelectElement().compare("■ 게임 계속 플레이"))
		{
			CurrentGameState_ = EGameState::Play;
			Console::Clear();
		}
		else if (!Menus_[CurrentGameState_]->GetCurrentSelectElement().compare("■ 게임 재시작"))
		{
			CurrentGameState_ = EGameState::Play;
			Console::Clear();

			ResetGame();
		}
	}
}

void Game::UpdateGamePlay()
{
	if (!bCanMove_)
	{
		return;
	}

	if (bCanMoveToBottom_)
	{
		bool bSuccess = true;

		while (bSuccess)
		{
			if (!MoveTetrominoInBoard(Movement_))
			{
				bSuccess = false;

				CurrentRemoveLine_ += Board_->Update();
				EraseCurrentTetromino();

				if (!BatchCurrentTetromino())
				{
					CurrentGameState_ = EGameState::Done;
					Console::Clear();
				}
			}
		}

		return;
	}

	if (!MoveTetrominoInBoard(Movement_))
	{
		if (Movement_ == Tetromino::EMovement::Down)
		{
			CurrentRemoveLine_ += Board_->Update();

			CurrentTetromino = Tetrominos_.erase(CurrentTetromino);
			EraseCurrentTetromino();

			if (!BatchCurrentTetromino())
			{
				CurrentGameState_ = EGameState::Done;
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
	for (auto& GameTetromino : Tetrominos_)
	{
		GameTetromino.reset();
	}

	Tetrominos_.resize(0);
	Board_.reset();

	InitGameTetromino();
	InitGameBoard();

	CurrentRemoveLine_ = 0;
	bCanMove_ = false;
	bCanMoveToBottom_ = false;
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

void Game::DrawTetrominos(const Vec2i& InPosition)
{
	Vec2i TetrominoPosition = InPosition;

	for (auto& TetrominoElement = Tetrominos_.begin(); TetrominoElement != Tetrominos_.end(); ++TetrominoElement)
	{
		if (TetrominoElement != CurrentTetromino)
		{
			TetrominoElement->get()->Draw(TetrominoPosition);
			TetrominoPosition.y += TetrominoElement->get()->GetAreaSize();
		}
	}
}

bool Game::MoveTetrominoInBoard(const Tetromino::EMovement& InMovement_)
{
	bool bIsMoveTetromino = true;

	Board_->UnregisterTetromino(*CurrentTetromino->get());
	CurrentTetromino->get()->Move(InMovement_);

	if (!Board_->RegisterTetromino(*CurrentTetromino->get()))
	{
		bIsMoveTetromino = false;

		CurrentTetromino->get()->Move(Tetromino::GetCountMovement(Movement_));
		Board_->RegisterTetromino(*CurrentTetromino->get());
	}

	return bIsMoveTetromino;
}

void Game::EraseCurrentTetromino()
{
	CurrentTetromino = Tetrominos_.erase(CurrentTetromino);
}

bool Game::BatchCurrentTetromino()
{
	bool bIsSuccessBatch = true;

	std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition_));
	Tetrominos_.push_back(std::move(NewTetromino));

	if (!Board_->RegisterTetromino(*CurrentTetromino->get()))
	{
		bIsSuccessBatch = false;
	}

	return bIsSuccessBatch;
}
