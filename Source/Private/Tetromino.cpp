#include <Tetromino.h>
#include <InputManager.h>
#include <Macro.h>
#include <Random.h>

#include <array>

Tetromino::Tetromino(const Vec2i& InBoardPosition, const Vec2i& InConsolePosition, const EShape& InType, const EColor& InColor)
{
	BoardPosition_ = InBoardPosition;
	ConsolePosition_ = InConsolePosition;
	Color_ = InColor;
	CreateTetrominoBlocks(InType);
}

Tetromino::Tetromino(const Vec2i& InBoardPosition, const Vec2i& InConsolePosition)
{
	BoardPosition_ = InBoardPosition;
	ConsolePosition_ = InConsolePosition;

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

	Color_ = Colors[ColorIndex];
	CreateTetrominoBlocks(Shapes[ShapeIndex]);
}

void Tetromino::Update(float InDeltaSeconds)
{
}

void Tetromino::Render()
{
	for (const auto& BlockPosition : BlockPositions_)
	{
		Vec2i Position = BlockPosition + ConsolePosition_;
		ConsoleManager::Get().RenderText(Position, "бс", Color_);
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

void Tetromino::CreateTetrominoBlocks(const EShape& InType)
{
	BlockPositions_.resize(4);

	switch (InType)
	{
	case EShape::I:
		BoundSize_ = 4;
		BlockPositions_[0] = Vec2i(0, 1);
		BlockPositions_[1] = Vec2i(1, 1);
		BlockPositions_[2] = Vec2i(2, 1);
		BlockPositions_[3] = Vec2i(3, 1);
		break;

	case EShape::O:
		BoundSize_ = 4;
		BlockPositions_[0] = Vec2i(1, 1);
		BlockPositions_[1] = Vec2i(2, 1);
		BlockPositions_[2] = Vec2i(1, 2);
		BlockPositions_[3] = Vec2i(2, 2);
		break;

	case EShape::T:
		BoundSize_ = 3;
		BlockPositions_[0] = Vec2i(0, 1);
		BlockPositions_[1] = Vec2i(1, 1);
		BlockPositions_[2] = Vec2i(2, 1);
		BlockPositions_[3] = Vec2i(1, 2);
		break;

	case EShape::J:
		BoundSize_ = 3;
		BlockPositions_[0] = Vec2i(0, 1);
		BlockPositions_[1] = Vec2i(1, 1);
		BlockPositions_[2] = Vec2i(2, 1);
		BlockPositions_[3] = Vec2i(2, 2);
		break;

	case EShape::L:
		BoundSize_ = 3;
		BlockPositions_[0] = Vec2i(0, 1);
		BlockPositions_[1] = Vec2i(1, 1);
		BlockPositions_[2] = Vec2i(2, 1);
		BlockPositions_[3] = Vec2i(0, 2);
		break;

	case EShape::S:
		BoundSize_ = 3;
		BlockPositions_[0] = Vec2i(1, 0);
		BlockPositions_[1] = Vec2i(2, 0);
		BlockPositions_[2] = Vec2i(0, 1);
		BlockPositions_[3] = Vec2i(1, 1);
		break;

	case EShape::Z:
		BoundSize_ = 3;
		BlockPositions_[0] = Vec2i(0, 0);
		BlockPositions_[1] = Vec2i(0, 1);
		BlockPositions_[2] = Vec2i(1, 1);
		BlockPositions_[3] = Vec2i(2, 1);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}
