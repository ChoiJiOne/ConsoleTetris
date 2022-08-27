#include "Macro.h"
#include "Console.h"
#include "Tetromino.h"

Tetromino::Tetromino(const Math::Vec2i& InAbsolutionPosition, const EType& InType, const Block::EColor& InBlockColor)
	: TetrominoBlock(Block(InBlockColor, Block::EState::Fill))
	, AbsolutePosition(InAbsolutionPosition)
{
	CreateRelativePositions(InType, RelativePositions, AreaSize, BoundSize);
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
	: TetrominoBlock(InInstance.TetrominoBlock)
	, BoundSize(InInstance.BoundSize)
	, AreaSize(InInstance.AreaSize)
	, AbsolutePosition(InInstance.AbsolutePosition)
	, RelativePositions(InInstance.RelativePositions)
{
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
	: TetrominoBlock(InInstance.TetrominoBlock)
	, BoundSize(InInstance.BoundSize)
	, AreaSize(InInstance.AreaSize)
	, AbsolutePosition(InInstance.AbsolutePosition)
	, RelativePositions(InInstance.RelativePositions)
{
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	TetrominoBlock = InInstance.TetrominoBlock;
	BoundSize = InInstance.BoundSize;
	AreaSize = InInstance.AreaSize;
	AbsolutePosition = InInstance.AbsolutePosition;
	RelativePositions = InInstance.RelativePositions;

	return *this;
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	TetrominoBlock = InInstance.TetrominoBlock;
	BoundSize = InInstance.BoundSize;
	AreaSize = InInstance.AreaSize;
	AbsolutePosition = InInstance.AbsolutePosition;
	RelativePositions = InInstance.RelativePositions;

	return *this;
}

Tetromino Tetromino::CreateRandomTetromino(const Math::Vec2i& InAbsolutionPosition)
{
	static EType Types[] = {
		EType::I,
		EType::O,
		EType::T,
		EType::J,
		EType::L,
		EType::S,
		EType::Z
	};

	static Block::EColor Colors[] = {
		Block::EColor::Blue,
		Block::EColor::Green,
		Block::EColor::Aqua,
		Block::EColor::Red,
		Block::EColor::Purple,
		Block::EColor::Yellow,
		Block::EColor::White,
	};

	int32_t TypeIndex  = Math::GenerateRandomInt<int32_t>(0, std::size(Types) - 1);
	int32_t ColorIndex = Math::GenerateRandomInt<int32_t>(0, std::size(Colors) - 1);

	return Tetromino(InAbsolutionPosition, Types[TypeIndex], Colors[ColorIndex]);
}

Tetromino::~Tetromino()
{
}

Tetromino::EMovement Tetromino::GetCountMovement(const EMovement& InMovement)
{
	EMovement CountMovement;

	switch (InMovement)
	{
	case EMovement::CW:
		CountMovement = EMovement::CCW;
		break;

	case EMovement::CCW:
		CountMovement = EMovement::CW;
		break;

	case EMovement::Down:
		CountMovement = EMovement::Up;
		break;

	case EMovement::Up:
		CountMovement = EMovement::Down;
		break;

	case EMovement::Left:
		CountMovement = EMovement::Right;
		break;

	case EMovement::Right:
		CountMovement = EMovement::Left;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type");
	}

	return CountMovement;
}

void Tetromino::Move(const EMovement& InMovement)
{
	switch (InMovement)
	{
	case EMovement::Up:
		AbsolutePosition.y -= 1;
		break;

	case EMovement::Down:
		AbsolutePosition.y += 1;
		break;

	case EMovement::Left:
		AbsolutePosition.x -= 1;
		break;

	case EMovement::Right:
		AbsolutePosition.x += 1;
		break;

	case EMovement::CCW:
		RelativePositions[0] = Math::Vec2i(RelativePositions[0].y, BoundSize - 1 - RelativePositions[0].x);
		RelativePositions[1] = Math::Vec2i(RelativePositions[1].y, BoundSize - 1 - RelativePositions[1].x);
		RelativePositions[2] = Math::Vec2i(RelativePositions[2].y, BoundSize - 1 - RelativePositions[2].x);
		RelativePositions[3] = Math::Vec2i(RelativePositions[3].y, BoundSize - 1 - RelativePositions[3].x);
		break;

	case EMovement::CW:
		RelativePositions[0] = Math::Vec2i(BoundSize - 1 - RelativePositions[0].y, RelativePositions[0].x);
		RelativePositions[1] = Math::Vec2i(BoundSize - 1 - RelativePositions[1].y, RelativePositions[1].x);
		RelativePositions[2] = Math::Vec2i(BoundSize - 1 - RelativePositions[2].y, RelativePositions[2].x);
		RelativePositions[3] = Math::Vec2i(BoundSize - 1 - RelativePositions[3].y, RelativePositions[3].x);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type");
	}
}

void Tetromino::Draw(const Math::Vec2i& InPosition)
{
	for (int32_t x = 0; x < AreaSize; ++x)
	{
		for (int32_t y = 0; y < AreaSize; ++y)
		{
			Math::Vec2i RelativePosition = Math::Vec2i(x, y);
			Math::Vec2i CurrentPosition = InPosition + RelativePosition;
			bool bHaveRelativePosition = HaveRelativePosition(RelativePositions, RelativePosition);

			if (bHaveRelativePosition)
			{
				TetrominoBlock.Draw(CurrentPosition);
			}
			else
			{
				Console::DrawText(CurrentPosition.x, CurrentPosition.y, "  ", Console::ETextColor::Black);
			}
		}
	}
}

void Tetromino::CreateRelativePositions(const EType& InType, std::vector<Math::Vec2i>& OutRelativePositions, int32_t& OutAreaSize, int32_t& OutBoundSize)
{
	OutRelativePositions.resize(4);
	OutAreaSize = 4;

	switch (InType)
	{
	case EType::I:
		OutBoundSize = 4;
		OutRelativePositions[0] = Math::Vec2i(0, 1);
		OutRelativePositions[1] = Math::Vec2i(1, 1);
		OutRelativePositions[2] = Math::Vec2i(2, 1);
		OutRelativePositions[3] = Math::Vec2i(3, 1);
		break;

	case EType::O:
		OutBoundSize = 4;
		OutRelativePositions[0] = Math::Vec2i(1, 1);
		OutRelativePositions[1] = Math::Vec2i(2, 1);
		OutRelativePositions[2] = Math::Vec2i(1, 2);
		OutRelativePositions[3] = Math::Vec2i(2, 2);
		break;

	case EType::T:
		OutBoundSize = 3;
		OutRelativePositions[0] = Math::Vec2i(0, 1);
		OutRelativePositions[1] = Math::Vec2i(1, 1);
		OutRelativePositions[2] = Math::Vec2i(2, 1);
		OutRelativePositions[3] = Math::Vec2i(1, 2);
		break;

	case EType::J:
		OutBoundSize = 3;
		OutRelativePositions[0] = Math::Vec2i(0, 1);
		OutRelativePositions[1] = Math::Vec2i(1, 1);
		OutRelativePositions[2] = Math::Vec2i(2, 1);
		OutRelativePositions[3] = Math::Vec2i(2, 2);
		break;

	case EType::L:
		OutBoundSize = 3;
		OutRelativePositions[0] = Math::Vec2i(0, 1);
		OutRelativePositions[1] = Math::Vec2i(1, 1);
		OutRelativePositions[2] = Math::Vec2i(2, 1);
		OutRelativePositions[3] = Math::Vec2i(0, 2);
		break;

	case EType::S:
		OutBoundSize = 3;
		OutRelativePositions[0] = Math::Vec2i(1, 0);
		OutRelativePositions[1] = Math::Vec2i(2, 0);
		OutRelativePositions[2] = Math::Vec2i(0, 1);
		OutRelativePositions[3] = Math::Vec2i(1, 1);
		break;

	case EType::Z:
		OutBoundSize = 3;
		OutRelativePositions[0] = Math::Vec2i(0, 0);
		OutRelativePositions[1] = Math::Vec2i(0, 1);
		OutRelativePositions[2] = Math::Vec2i(1, 1);
		OutRelativePositions[3] = Math::Vec2i(2, 1);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type");
	}
}

bool Tetromino::HaveRelativePosition(const std::vector<Math::Vec2i>& InRelativePositions, const Math::Vec2i& InTargetPosition)
{
	bool bHaveRelativePosition = false;

	for (const auto& RelativePosition : InRelativePositions)
	{
		if (RelativePosition.x == InTargetPosition.x && RelativePosition.y == InTargetPosition.y)
		{
			bHaveRelativePosition = true;
			break;
		}
	}

	return bHaveRelativePosition;
}
