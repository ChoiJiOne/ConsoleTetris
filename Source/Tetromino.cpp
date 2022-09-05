#include "Macro.h"
#include "Console.h"
#include "Random.h"
#include "Tetromino.h"

Tetromino::Tetromino(const Vec2i& InAbsolutionPosition, const EType& InType, const Block::EColor& InBlockColor)
	: TetrominoBlock_(Block(InBlockColor, Block::EState::Fill))
	, AbsolutePosition_(InAbsolutionPosition)
{
	CreateRelativePositions(InType, RelativePositions_, AreaSize_, BoundSize_);
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
	: TetrominoBlock_(InInstance.TetrominoBlock_)
	, BoundSize_(InInstance.BoundSize_)
	, AreaSize_(InInstance.AreaSize_)
	, AbsolutePosition_(InInstance.AbsolutePosition_)
	, RelativePositions_(InInstance.RelativePositions_)
{
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
	: TetrominoBlock_(InInstance.TetrominoBlock_)
	, BoundSize_(InInstance.BoundSize_)
	, AreaSize_(InInstance.AreaSize_)
	, AbsolutePosition_(InInstance.AbsolutePosition_)
	, RelativePositions_(InInstance.RelativePositions_)
{
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	TetrominoBlock_ = InInstance.TetrominoBlock_;
	BoundSize_ = InInstance.BoundSize_;
	AreaSize_ = InInstance.AreaSize_;
	AbsolutePosition_ = InInstance.AbsolutePosition_;
	RelativePositions_ = InInstance.RelativePositions_;

	return *this;
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	TetrominoBlock_ = InInstance.TetrominoBlock_;
	BoundSize_ = InInstance.BoundSize_;
	AreaSize_ = InInstance.AreaSize_;
	AbsolutePosition_ = InInstance.AbsolutePosition_;
	RelativePositions_ = InInstance.RelativePositions_;

	return *this;
}

Tetromino Tetromino::CreateRandomTetromino(const Vec2i& InAbsolutionPosition)
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

	int32_t TypeIndex  = GenerateRandomInt<int32_t>(0, std::size(Types) - 1);
	int32_t ColorIndex = GenerateRandomInt<int32_t>(0, std::size(Colors) - 1);

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
	case EMovement::None:
		CountMovement = EMovement::None;
		break;

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
	case EMovement::None:
		break;

	case EMovement::Up:
		AbsolutePosition_.y -= 1;
		break;

	case EMovement::Down:
		AbsolutePosition_.y += 1;
		break;

	case EMovement::Left:
		AbsolutePosition_.x -= 1;
		break;

	case EMovement::Right:
		AbsolutePosition_.x += 1;
		break;

	case EMovement::CCW:
		RelativePositions_[0] = Vec2i(RelativePositions_[0].y, BoundSize_ - 1 - RelativePositions_[0].x);
		RelativePositions_[1] = Vec2i(RelativePositions_[1].y, BoundSize_ - 1 - RelativePositions_[1].x);
		RelativePositions_[2] = Vec2i(RelativePositions_[2].y, BoundSize_ - 1 - RelativePositions_[2].x);
		RelativePositions_[3] = Vec2i(RelativePositions_[3].y, BoundSize_ - 1 - RelativePositions_[3].x);
		break;

	case EMovement::CW:
		RelativePositions_[0] = Vec2i(BoundSize_ - 1 - RelativePositions_[0].y, RelativePositions_[0].x);
		RelativePositions_[1] = Vec2i(BoundSize_ - 1 - RelativePositions_[1].y, RelativePositions_[1].x);
		RelativePositions_[2] = Vec2i(BoundSize_ - 1 - RelativePositions_[2].y, RelativePositions_[2].x);
		RelativePositions_[3] = Vec2i(BoundSize_ - 1 - RelativePositions_[3].y, RelativePositions_[3].x);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type");
	}
}

void Tetromino::Draw(const Vec2i& InPosition)
{
	for (int32_t x = 0; x < AreaSize_; ++x)
	{
		for (int32_t y = 0; y < AreaSize_; ++y)
		{
			Vec2i RelativePosition = Vec2i(x, y);
			Vec2i CurrentPosition = InPosition + RelativePosition;
			bool bHaveRelativePosition = HaveRelativePosition(RelativePositions_, RelativePosition);

			if (bHaveRelativePosition)
			{
				TetrominoBlock_.Draw(CurrentPosition);
			}
			else
			{
				Console::DrawText(CurrentPosition.x, CurrentPosition.y, "  ", Console::ETextColor::Black);
			}
		}
	}
}

void Tetromino::CreateRelativePositions(const EType& InType, std::vector<Vec2i>& OutRelativePositions_, int32_t& OutAreaSize_, int32_t& OutBoundSize_)
{
	OutRelativePositions_.resize(4);
	OutAreaSize_ = 4;

	switch (InType)
	{
	case EType::I:
		OutBoundSize_ = 4;
		OutRelativePositions_[0] = Vec2i(0, 1);
		OutRelativePositions_[1] = Vec2i(1, 1);
		OutRelativePositions_[2] = Vec2i(2, 1);
		OutRelativePositions_[3] = Vec2i(3, 1);
		break;

	case EType::O:
		OutBoundSize_ = 4;
		OutRelativePositions_[0] = Vec2i(1, 1);
		OutRelativePositions_[1] = Vec2i(2, 1);
		OutRelativePositions_[2] = Vec2i(1, 2);
		OutRelativePositions_[3] = Vec2i(2, 2);
		break;

	case EType::T:
		OutBoundSize_ = 3;
		OutRelativePositions_[0] = Vec2i(0, 1);
		OutRelativePositions_[1] = Vec2i(1, 1);
		OutRelativePositions_[2] = Vec2i(2, 1);
		OutRelativePositions_[3] = Vec2i(1, 2);
		break;

	case EType::J:
		OutBoundSize_ = 3;
		OutRelativePositions_[0] = Vec2i(0, 1);
		OutRelativePositions_[1] = Vec2i(1, 1);
		OutRelativePositions_[2] = Vec2i(2, 1);
		OutRelativePositions_[3] = Vec2i(2, 2);
		break;

	case EType::L:
		OutBoundSize_ = 3;
		OutRelativePositions_[0] = Vec2i(0, 1);
		OutRelativePositions_[1] = Vec2i(1, 1);
		OutRelativePositions_[2] = Vec2i(2, 1);
		OutRelativePositions_[3] = Vec2i(0, 2);
		break;

	case EType::S:
		OutBoundSize_ = 3;
		OutRelativePositions_[0] = Vec2i(1, 0);
		OutRelativePositions_[1] = Vec2i(2, 0);
		OutRelativePositions_[2] = Vec2i(0, 1);
		OutRelativePositions_[3] = Vec2i(1, 1);
		break;

	case EType::Z:
		OutBoundSize_ = 3;
		OutRelativePositions_[0] = Vec2i(0, 0);
		OutRelativePositions_[1] = Vec2i(0, 1);
		OutRelativePositions_[2] = Vec2i(1, 1);
		OutRelativePositions_[3] = Vec2i(2, 1);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type");
	}
}

bool Tetromino::HaveRelativePosition(const std::vector<Vec2i>& InRelativePositions_, const Vec2i& InTargetPosition)
{
	bool bHaveRelativePosition = false;

	for (const auto& RelativePosition : InRelativePositions_)
	{
		if (RelativePosition.x == InTargetPosition.x && RelativePosition.y == InTargetPosition.y)
		{
			bHaveRelativePosition = true;
			break;
		}
	}

	return bHaveRelativePosition;
}
