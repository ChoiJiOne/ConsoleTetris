#include <Tetromino.h>
#include <ConsoleManager.h>
#include <InputManager.h>
#include <Macro.h>
#include <Random.h>

#include <array>

Tetromino::Tetromino(const Vec2i& InBoardPosition, const EShape& InType, const Block::EType& InBlockType)
{
	BoardPosition_ = InBoardPosition;
	CreateTetrominoBlocks(InType, InBlockType);
}

Tetromino::Tetromino(const Vec2i& InBoardPosition)
{
	BoardPosition_ = InBoardPosition;

	static std::array<EShape, 7> Shapes = {
		EShape::I,
		EShape::O,
		EShape::T,
		EShape::J,
		EShape::L,
		EShape::S,
		EShape::Z
	};

	static std::array<Block::EType, 6> BlockTypes = {
		Block::EType::BLUE,
		Block::EType::GREEN,
		Block::EType::AQUA,
		Block::EType::RED,
		Block::EType::PURPLE,
		Block::EType::YELLOW
	};

	int32_t ShapeIndex = GenerateRandomInt(0, static_cast<int32_t>(std::size(Shapes)) - 1);
	int32_t BlockTypeIndex = GenerateRandomInt(0, static_cast<int32_t>(std::size(BlockTypes)) - 1);

	CreateTetrominoBlocks(Shapes[ShapeIndex], BlockTypes[BlockTypeIndex]);
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
{
	BoardPosition_ = InInstance.BoardPosition_;
	BoundSize_ = InInstance.BoundSize_;
	Blocks_ = InInstance.Blocks_;
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
{
	BoardPosition_ = InInstance.BoardPosition_;
	BoundSize_ = InInstance.BoundSize_;
	Blocks_ = InInstance.Blocks_;
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardPosition_ = InInstance.BoardPosition_;
	BoundSize_ = InInstance.BoundSize_;
	Blocks_ = InInstance.Blocks_;

	return *this;
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardPosition_ = InInstance.BoardPosition_;
	BoundSize_ = InInstance.BoundSize_;
	Blocks_ = InInstance.Blocks_;

	return *this;
}

void Tetromino::Update()
{
}

void Tetromino::Render(const Vec2i& InPosition)
{
	for (const auto& block : Blocks_)
	{
		block.Render(InPosition);
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

void Tetromino::CreateTetrominoBlocks(const EShape& InType, const Block::EType& InBlockType)
{
	Blocks_.resize(4);

	switch (InType)
	{
	case EShape::I:
		BoundSize_ = 4;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(3, 1));
		break;

	case EShape::O:
		BoundSize_ = 4;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 2));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 2));
		break;

	case EShape::T:
		BoundSize_ = 3;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 2));
		break;

	case EShape::J:
		BoundSize_ = 3;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 2));
		break;

	case EShape::L:
		BoundSize_ = 3;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 2));
		break;

	case EShape::S:
		BoundSize_ = 3;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 0));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 0));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		break;

	case EShape::Z:
		BoundSize_ = 3;
		Blocks_[0] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 0));
		Blocks_[1] = Block(InBlockType, Block::EState::FILL, Vec2i(0, 1));
		Blocks_[2] = Block(InBlockType, Block::EState::FILL, Vec2i(1, 1));
		Blocks_[3] = Block(InBlockType, Block::EState::FILL, Vec2i(2, 1));
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}
