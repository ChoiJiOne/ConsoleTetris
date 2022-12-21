#include <Tetromino.h>
#include <InputManager.h>
#include <Macro.h>
#include <Random.h>

#include <array>

Tetromino::Tetromino(const Vec2i& InPosition, const EShape& InShape, const EColor& InColor)
	: Position_(InPosition)
{
	CreateTetrominoBlocks(InShape, InColor);
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
}

void Tetromino::Update(float InDeltaSeconds)
{
}

void Tetromino::Render()
{
	for (auto& block : Blocks_)
	{
		block.Render();
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
