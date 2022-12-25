#include <Tetromino.h>
#include <Board.h>
#include <InputManager.h>
#include <Macro.h>
#include <Random.h>
#include <Text.hpp>
#include <WorldManager.h>

#include <array>

int32_t Tetromino::CountOfTetromino_ = 0;
float Tetromino::MaxAccrueTime_ = 1.0f;

Tetromino::Tetromino(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor)
	: ConsolePosition_(InConsolePosition)
	, Shape_(InShape)
{
	TetrominoBlocks_ = CreateTetrominoBlocks(ConsolePosition_, Shape_, InColor);

	CurrentID_ = CountOfTetromino_;
	CountOfTetromino_++;

	WorldManager::Get().RegisterOjbect(this, Text::GetHash(std::to_string(CurrentID_)));
}

Tetromino::Tetromino(const Vec2i& InConsolePosition)
	: ConsolePosition_(InConsolePosition)
{
	static std::array<EShape, 7> Shapes = {
		EShape::I,
		EShape::O,
		EShape::T,
		EShape::J,
		EShape::L,
		EShape::S,
		EShape::Z
	};

	static std::array<EColor, 6> Colors = {
		EColor::BLUE,
		EColor::GREEN,
		EColor::AQUA,
		EColor::RED,
		EColor::PURPLE,
		EColor::YELLOW
	};

	int32_t ShapeIndex = GenerateRandomInt(0, static_cast<int32_t>(std::size(Shapes)) - 1);
	int32_t ColorIndex = GenerateRandomInt(0, static_cast<int32_t>(std::size(Colors)) - 1);

	Shape_ = Shapes[ShapeIndex];
	TetrominoBlocks_ = CreateTetrominoBlocks(ConsolePosition_, Shape_, Colors[ColorIndex]);

	CurrentID_ = CountOfTetromino_;
	CountOfTetromino_++;
	WorldManager::Get().RegisterOjbect(this, Text::GetHash(std::to_string(CurrentID_)));
}

Tetromino::~Tetromino()
{
	WorldManager::Get().UnregisterObject(Text::GetHash(std::to_string(CurrentID_)));
}

void Tetromino::Update(float InDeltaSeconds)
{
	if (CurrentState_ == EState::ACTIVE)
	{
		AccrueTime_ += InDeltaSeconds;

		Tetromino::EMovement Movement = GetMovementDirection();

		Board* TetrisBoard = reinterpret_cast<Board*>(WorldManager::Get().GetObject(Text::GetHash("Board")));
		TetrisBoard->RemoveBlocks(TetrominoBlocks_);

		if (Movement != EMovement::NONE)
		{
			RemoveFromConsole();

			if (CanMove(ConsolePosition_, TetrominoBlocks_, Shape_, Movement))
			{
				Move(ConsolePosition_, TetrominoBlocks_, Shape_, Movement);
			}
		}

		if (AccrueTime_ >= MaxAccrueTime_)
		{
			Movement = EMovement::DOWN;

			if (CanMove(ConsolePosition_, TetrominoBlocks_, Shape_, Movement))
			{
				Move(ConsolePosition_, TetrominoBlocks_, Shape_, Movement);
			}

			AccrueTime_ = 0.0f;
		}

		ShadowConsolePosition_ = ConsolePosition_;
		ShadowTetrominoBlocks_ = TetrominoBlocks_;

		Move(ShadowConsolePosition_, ShadowTetrominoBlocks_, Shape_, EMovement::JUMP);
		Move(ShadowConsolePosition_, ShadowTetrominoBlocks_, Shape_, GetCountMovement(EMovement::JUMP));

		if (!CanMove(ConsolePosition_, TetrominoBlocks_, Shape_, EMovement::DOWN))
		{
			CurrentState_ = EState::WAIT;
			TetrisBoard->SetCurrentState(Board::EState::WAIT);
		}

		TetrisBoard->WriteBlocks(TetrominoBlocks_);
	}
}

void Tetromino::Render()
{
	Board* TetrisBoard = reinterpret_cast<Board*>(WorldManager::Get().GetObject(Text::GetHash("Board")));

	if (TetrisBoard->GetCurrentState() == Board::EState::ACTIVE)
	{
		if (CurrentState_ == EState::WAIT)
		{
			for (auto& TetrominoBlock : TetrominoBlocks_)
			{
				TetrominoBlock.Render();
			}
		}
		else
		{
			for (auto& ShadowBlock : ShadowTetrominoBlocks_)
			{
				ConsoleManager::Get().RenderText(
					ShadowBlock.GetPosition(),
					"бс",
					EColor::GRAY
				);
			}
		}
	}
}

void Tetromino::SetConsolePosition(const Vec2i& InConsolePosition)
{
	RemoveFromConsole();

	for (auto& TetrominoBlock : TetrominoBlocks_)
	{
		Vec2i BlockPosition = TetrominoBlock.GetPosition();
		BlockPosition -= ConsolePosition_;
		BlockPosition += InConsolePosition;
		TetrominoBlock.SetPosition(BlockPosition);
	}

	ConsolePosition_ = InConsolePosition;
}

bool Tetromino::IsCollision()
{
	Board* TetrisBoard = reinterpret_cast<Board*>(WorldManager::Get().GetObject(Text::GetHash("Board")));

	for (const auto& TetrominoBlock : TetrominoBlocks_)
	{
		if (TetrisBoard->IsCollision(TetrominoBlock))
		{
			return true;
		}
	}

	return false;
}

std::vector<Block> Tetromino::CreateTetrominoBlocks(const Vec2i& InConsolePosition, const EShape& InShape, const EColor& InColor)
{
	std::vector<Block> TetrominoBlocks(4);

	switch (InShape)
	{
	case EShape::I:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(0, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(3, 1), Block::EState::FILL, InColor);
		break;

	case EShape::O:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(1, 2), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(2, 2), Block::EState::FILL, InColor);
		break;

	case EShape::T:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(0, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(1, 2), Block::EState::FILL, InColor);
		break;

	case EShape::J:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(0, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(2, 2), Block::EState::FILL, InColor);
		break;

	case EShape::L:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(0, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(0, 2), Block::EState::FILL, InColor);
		break;

	case EShape::S:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(1, 0), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(2, 0), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(0, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		break;

	case EShape::Z:
		TetrominoBlocks[0] = Block(InConsolePosition + Vec2i(0, 0), Block::EState::FILL, InColor);
		TetrominoBlocks[1] = Block(InConsolePosition + Vec2i(1, 0), Block::EState::FILL, InColor);
		TetrominoBlocks[2] = Block(InConsolePosition + Vec2i(1, 1), Block::EState::FILL, InColor);
		TetrominoBlocks[3] = Block(InConsolePosition + Vec2i(2, 1), Block::EState::FILL, InColor);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}

	return TetrominoBlocks;
}

void Tetromino::Move(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EMovement& InMovement)
{
	switch (InMovement)
	{
	case EMovement::NONE:
		break;

	case EMovement::UP:
		InConsolePosition.y -= 1;

		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition.y -= 1;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::DOWN:
		InConsolePosition.y += 1;

		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition.y += 1;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::LEFT:
		InConsolePosition.x -= 1;

		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition.x -= 1;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::RIGHT:
		InConsolePosition.x += 1;

		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition.x += 1;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::CCW:
		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition -= InConsolePosition;

			BlockPosition = Vec2i(BlockPosition.y, GetBoundSize(InShape) - 1 - BlockPosition.x);

			BlockPosition += InConsolePosition;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::CW:
		for (auto& TetrominoBlock : InTetrominoBlocks)
		{
			Vec2i BlockPosition = TetrominoBlock.GetPosition();
			BlockPosition -= InConsolePosition;

			BlockPosition = Vec2i(GetBoundSize(InShape) - 1 - BlockPosition.y, BlockPosition.x);

			BlockPosition += InConsolePosition;
			TetrominoBlock.SetPosition(BlockPosition);
		}
		break;

	case EMovement::JUMP:
		while (!IsCollision(InTetrominoBlocks))
		{
			Move(InConsolePosition, InTetrominoBlocks, InShape, EMovement::DOWN);
		}
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}

bool Tetromino::IsCollision(const std::vector<Block>& InTetrominoBlocks)
{
	Board* TetrisBoard = reinterpret_cast<Board*>(WorldManager::Get().GetObject(Text::GetHash("Board")));

	for (const auto& TetrominoBlock : InTetrominoBlocks)
	{
		if (TetrisBoard->IsCollision(TetrominoBlock))
		{
			return true;
		}
	}

	return false;
}

bool Tetromino::CanMove(Vec2i& InConsolePosition, std::vector<Block>& InTetrominoBlocks, const EShape& InShape, const EMovement& InMovement)
{
	bool bCanMove = true;

	Move(InConsolePosition, InTetrominoBlocks, InShape, InMovement);
	bCanMove = !IsCollision();
	Move(InConsolePosition, InTetrominoBlocks, InShape, GetCountMovement(InMovement));

	return bCanMove;
}

Tetromino::EMovement Tetromino::GetCountMovement(const EMovement& InMovement)
{
	EMovement CountMovement;

	switch (InMovement)
	{
	case EMovement::NONE:
		CountMovement = EMovement::NONE;
		break;

	case EMovement::CW:
		CountMovement = EMovement::CCW;
		break;

	case EMovement::CCW:
		CountMovement = EMovement::CW;
		break;

	case EMovement::DOWN:
		CountMovement = EMovement::UP;
		break;

	case EMovement::UP:
		CountMovement = EMovement::DOWN;
		break;

	case EMovement::LEFT:
		CountMovement = EMovement::RIGHT;
		break;

	case EMovement::RIGHT:
		CountMovement = EMovement::LEFT;
		break;

	case EMovement::JUMP:
		CountMovement = EMovement::UP;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type...");
	}

	return CountMovement;
}

void Tetromino::RemoveFromConsole()
{
	for (auto& TetrominoBlock : TetrominoBlocks_)
	{
		Vec2i BlockPosition = TetrominoBlock.GetPosition();
		ConsoleManager::Get().RenderText(BlockPosition, "  ", EColor::BLACK);
	}
}

Tetromino::EMovement Tetromino::GetMovementDirection() const
{
	Tetromino::EMovement Movement = EMovement::NONE;

	static std::unordered_map<EKeyCode, Tetromino::EMovement> KeyMovements = {
		{ EKeyCode::LEFT,  EMovement::LEFT  },
		{ EKeyCode::RIGHT, EMovement::RIGHT },
		{ EKeyCode::UP,    EMovement::CW    },
		{ EKeyCode::DOWN,  EMovement::DOWN  },
		{ EKeyCode::SPACE, EMovement::JUMP  }
	};

	for (const auto& KeyMovement : KeyMovements)
	{
		if (InputManager::Get().GetKeyPressState(KeyMovement.first) == EPressState::PRESSED)
		{
			Movement = KeyMovement.second;
		}
	}

	return Movement;
}

int32_t Tetromino::GetBoundSize(const EShape& InShape) const
{
	int32_t BoundSize = 0;

	switch (InShape)
	{
	case EShape::I:
		BoundSize = 4;
		break;

	case EShape::O:
		BoundSize = 4;
		break;

	case EShape::T:
		BoundSize = 3;
		break;

	case EShape::J:
		BoundSize = 3;
		break;

	case EShape::L:
		BoundSize = 3;
		break;

	case EShape::S:
		BoundSize = 3;
		break;

	case EShape::Z:
		BoundSize = 3;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}

	return BoundSize;
}
