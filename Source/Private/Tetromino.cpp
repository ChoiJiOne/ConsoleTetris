#include <Tetromino.h>
#include <Board.h>
#include <InputManager.h>
#include <Macro.h>
#include <Random.h>
#include <Text.hpp>
#include <WorldManager.h>

#include <array>

int32_t Tetromino::CountOfTetromino_ = 0;

Tetromino::Tetromino(const Vec2i& InPosition, const EShape& InShape, const EColor& InColor)
	: Position_(InPosition)
{
	CreateTetrominoBlocks(InShape, InColor);

	ID_ = CountOfTetromino_;
	CountOfTetromino_++;
	WorldManager::Get().RegisterOjbect(this, Text::GetHash(std::to_string(ID_)));
}

Tetromino::Tetromino(const Vec2i& InPosition)
	: Position_(InPosition)
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

	CreateTetrominoBlocks(Shapes[ShapeIndex], Colors[ColorIndex]);

	ID_ = CountOfTetromino_;
	CountOfTetromino_++;
	WorldManager::Get().RegisterOjbect(this, Text::GetHash(std::to_string(ID_)));
}

Tetromino::~Tetromino()
{
	WorldManager::Get().UnregisterObject(Text::GetHash(std::to_string(ID_)));
}

void Tetromino::Update(float InDeltaSeconds)
{
	Tetromino::EMovement Movement = GetMovementDirection();

	if (Movement != EMovement::NONE)
	{
		RemoveFromConsole();
		Move(Movement);

		if (IsCollision())
		{
			EMovement CountMovement = GetCountMovement(Movement);
			Move(CountMovement);
		}
	}
}

void Tetromino::Render()
{
	for (auto& block : Blocks_)
	{
		block.Render();
	}
}

void Tetromino::Move(const EMovement& InMovement)
{
	switch (InMovement)
	{
	case EMovement::NONE:
		break;

	case EMovement::UP:
		Position_.y -= 1;

		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition.y -= 1;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::DOWN:
		Position_.y += 1;

		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition.y += 1;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::LEFT:
		Position_.x -= 1;

		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition.x -= 1;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::RIGHT:
		Position_.x += 1;

		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition.x += 1;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::CCW:
		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition -= Position_;

			BlockPosition = Vec2i(BlockPosition.y, BoundSize_ - 1 - BlockPosition.x);

			BlockPosition += Position_;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::CW:
		for (auto& block : Blocks_)
		{
			Vec2i BlockPosition = block.GetPosition();
			BlockPosition -= Position_;

			BlockPosition = Vec2i(BoundSize_ - 1 - BlockPosition.y, BlockPosition.x);

			BlockPosition += Position_;
			block.SetPosition(BlockPosition);
		}
		break;

	case EMovement::JUMP:
		while (!IsCollision())
		{
			Move(EMovement::DOWN);
		}
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
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

void Tetromino::CreateTetrominoBlocks(const EShape& InShape, const EColor& InColor)
{
	Blocks_.resize(4);

	switch (InShape)
	{
	case EShape::I:
		BoundSize_ = 4;
		Blocks_[0] = Block(Position_ + Vec2i(0, 1), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(3, 1), Block::EState::FILL, InColor);
		break;

	case EShape::O:
		BoundSize_ = 4;
		Blocks_[0] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(1, 2), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(2, 2), Block::EState::FILL, InColor);
		break;

	case EShape::T:
		BoundSize_ = 3;
		Blocks_[0] = Block(Position_ + Vec2i(0, 1), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(1, 2), Block::EState::FILL, InColor);
		break;

	case EShape::J:
		BoundSize_ = 3;
		Blocks_[0] = Block(Position_ + Vec2i(0, 1), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(2, 2), Block::EState::FILL, InColor);
		break;

	case EShape::L:
		BoundSize_ = 3;
		Blocks_[0] = Block(Position_ + Vec2i(0, 1), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(0, 2), Block::EState::FILL, InColor);
		break;

	case EShape::S:
		BoundSize_ = 3;
		Blocks_[0] = Block(Position_ + Vec2i(1, 0), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(2, 0), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(0, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		break;

	case EShape::Z:
		BoundSize_ = 3;
		Blocks_[0] = Block(Position_ + Vec2i(0, 0), Block::EState::FILL, InColor);
		Blocks_[1] = Block(Position_ + Vec2i(1, 0), Block::EState::FILL, InColor);
		Blocks_[2] = Block(Position_ + Vec2i(1, 1), Block::EState::FILL, InColor);
		Blocks_[3] = Block(Position_ + Vec2i(2, 1), Block::EState::FILL, InColor);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}

void Tetromino::RemoveFromConsole()
{
	for (auto& block : Blocks_)
	{
		Vec2i BlockPosition = block.GetPosition();
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

bool Tetromino::IsCollision()
{
	Board* board = reinterpret_cast<Board*>(WorldManager::Get().GetObject(Text::GetHash("Board")));

	for (const auto& block : Blocks_)
	{
		if (board->IsCollision(block))
		{
			return true;
		}
	}

	return false;
}
