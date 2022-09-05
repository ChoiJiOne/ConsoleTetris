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
	bIsContinue_ = true;
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
	bCanMove_ = false;
	bCanMoveToBottom_ = false;

	for (const auto& TetrominoMoveMapping : TetrominoMoveMappings_)
	{
		if (InInput.GetKeyPressState(TetrominoMoveMapping.first) == Input::EPressState::Pressed)
		{
			bCanMove_ = true;
			Movement_ = TetrominoMoveMapping.second;

			if (TetrominoMoveMapping.first == Input::EKeyType::Space)
			{
				bCanMoveToBottom_ = true;
			}
		}
	}

	if (InInput.GetKeyPressState(Input::EKeyType::Escape) == Input::EPressState::Pressed)
	{
		bIsContinue_ = false;
	}
}

void Tetris::Update(float InDeltaTime)
{
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
					bIsContinue_ = false;
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
			EraseCurrentTetromino();

			if (!BatchCurrentTetromino())
			{
				bIsContinue_ = false;
			}
		}
	}
}

void Tetris::Draw(const Vec2i& InPosition)
{
	Vec2i BoardPosition = InPosition;
	Board_->Draw(BoardPosition);

	Vec2i WaitTetrominoPosition = InPosition;
	WaitTetrominoPosition.x += 12;
	WaitTetrominoPosition.y += 1;

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

	std::unique_ptr<Tetromino> NewTetromino = std::make_unique<Tetromino>(Tetromino::CreateRandomTetromino(StartPosition_));
	WaitTetrominos_.push_back(std::move(NewTetromino));

	if (!Board_->RegisterTetromino(*CurrentTetromino_->get()))
	{
		bIsSuccessBatch = false;
	}

	return bIsSuccessBatch;
}
