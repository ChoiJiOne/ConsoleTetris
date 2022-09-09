#include "Tetris.h"

Tetris::~Tetris()
{
	for (auto& WaitTetromino : WaitTetrominos_)
	{
		WaitTetromino.reset();
	}

	Board_.reset();
}

void Tetris::Init()
{
	TetrominoMoveMappings_.insert({ Input::EKeyType::Up,    Tetromino::EMovement::CW    });
	TetrominoMoveMappings_.insert({ Input::EKeyType::Down,  Tetromino::EMovement::Down  });
	TetrominoMoveMappings_.insert({ Input::EKeyType::Left,  Tetromino::EMovement::Left  });
	TetrominoMoveMappings_.insert({ Input::EKeyType::Right, Tetromino::EMovement::Right });
	TetrominoMoveMappings_.insert({ Input::EKeyType::Space, Tetromino::EMovement::Down  });

	StartPositionFromBoard_ = Vec2i(3, 0);

	Reset();
}

void Tetris::Reset()
{
	bCanMove_ = false;
	bCanMoveToBottom_ = false;
	bIsDone_ = false;
	bIsPaused_ = false;
	CurrentStepTime_ = 0.0f;
	MaxStepTime_ = 1.5f;
	CurrentRemoveLine_ = 0;

	const int32_t MaxTetromino = 6;
	CreateWaitTetromino(MaxTetromino);

	const int32_t BoardWidth = 10;
	const int32_t BoardHeight = 20;
	CreateBoard(BoardWidth, BoardHeight);
}

void Tetris::ProcessInput(const Input& InInput)
{
	if (bIsDone_ || bIsPaused_) return;

	bCanMove_ = false;
	bCanMoveToBottom_ = false;

	for (const auto& TetrominoMoveMapping : TetrominoMoveMappings_)
	{
		if (InInput.GetKeyPressState(TetrominoMoveMapping.first) == Input::EPressState::Pressed)
		{
			bCanMove_ = true;
			bCanMoveToBottom_ = (TetrominoMoveMapping.first == Input::EKeyType::Space);
			Movement_ = TetrominoMoveMapping.second;
		}
	}

	if (InInput.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Pressed) 
	{
		bIsPaused_ = true;
	}
}

void Tetris::Update(float InDeltaTime)
{
	if (bIsDone_ || bIsPaused_) return;

	CurrentStepTime_ += InDeltaTime;
	if (CurrentStepTime_ >= MaxStepTime_)
	{
		CurrentStepTime_ = 0.0f;
		bCanMove_ = true;
		Movement_ = Tetromino::EMovement::Down;
	}

	if (!bCanMove_)
	{
		return;
	}

	if (bCanMoveToBottom_)
	{
		while (true)
		{
			if (!MoveTetrominoInBoard(Movement_))
			{
				CurrentRemoveLine_ += Board_->Update();
				EraseCurrentTetromino();
				bIsDone_ = (!BatchCurrentTetromino());
				return;
			}
		}
	}

	if (!MoveTetrominoInBoard(Movement_) && Movement_ == Tetromino::EMovement::Down)
	{
		CurrentRemoveLine_ += Board_->Update();
		EraseCurrentTetromino();
		bIsDone_ = (!BatchCurrentTetromino());
	}
}

void Tetris::Draw(const Vec2i& InPosition)
{
	if (bIsDone_ || bIsPaused_) return;

	Vec2i BoardPosition = InPosition;
	Board_->Draw(BoardPosition);

	Vec2i WaitTetrominoPosition = InPosition;
	WaitTetrominoPosition.x += 12;

	DrawWaitTetrominos(WaitTetrominoPosition);
}

void Tetris::SetStepTime(float InStepTime)
{
	MaxStepTime_ = std::clamp<float>(InStepTime, 0.5f, 1.5f);
}

void Tetris::CreateWaitTetromino(const int32_t& InMaxTetromino)
{
	if (WaitTetrominos_.size() > 0) WaitTetrominos_.swap(std::list<std::unique_ptr<Tetromino>>());

	for (int32_t Count = 0; Count < InMaxTetromino; ++Count)
	{
		std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPositionFromBoard_));
		WaitTetrominos_.push_back(std::move(NewTetromino));
	}

	CurrentTetromino_ = WaitTetrominos_.begin();
}

void Tetris::CreateBoard(const int32_t& InWidth, const int32_t& InHeight)
{
	if (Board_) Board_.reset();

	Board_ = std::make_unique<Board>(InWidth, InHeight);
	Board_->RegisterTetromino(*CurrentTetromino_->get());
}

void Tetris::DrawWaitTetrominos(const Vec2i& InPosition)
{
	Vec2i TetrominoPosition = InPosition;

	for (auto& TetrominoElement = WaitTetrominos_.begin(); TetrominoElement != WaitTetrominos_.end(); ++TetrominoElement)
	{
		if (TetrominoElement != CurrentTetromino_)
		{
			TetrominoElement->get()->Draw(TetrominoPosition);
			TetrominoPosition.y += TetrominoElement->get()->GetAreaSize();
		}
	}
}

bool Tetris::MoveTetrominoInBoard(const Tetromino::EMovement& InMovement)
{
	bool bIsMoveTetromino = true;

	Board_->UnregisterTetromino(*CurrentTetromino_->get());
	CurrentTetromino_->get()->Move(InMovement);

	if (!Board_->RegisterTetromino(*CurrentTetromino_->get()))
	{
		bIsMoveTetromino = false;

		CurrentTetromino_->get()->Move(Tetromino::GetCountMovement(Movement_));
		Board_->RegisterTetromino(*CurrentTetromino_->get());
	}

	return bIsMoveTetromino;
}

void Tetris::EraseCurrentTetromino()
{
	CurrentTetromino_ = WaitTetrominos_.erase(CurrentTetromino_);
}

bool Tetris::BatchCurrentTetromino()
{
	bool bIsSuccessBatch = true;

	std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPositionFromBoard_));
	WaitTetrominos_.push_back(std::move(NewTetromino));

	if (!Board_->RegisterTetromino(*CurrentTetromino_->get()))
	{
		bIsSuccessBatch = false;
	}

	return bIsSuccessBatch;
}
