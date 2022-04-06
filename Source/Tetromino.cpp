#include "Tetromino.h"

Tetromino::Tetromino(Vector2i absolutePos, EShape shape)
	: absolutePosition(absolutePos)
{
	GenerateRelativePositions(shape);
}

Tetromino::~Tetromino()
{
}

Tetromino::Tetromino(const Tetromino& instance) noexcept
	: areaSize(instance.areaSize)
	, absolutePosition(instance.absolutePosition)
	, relativePositions(instance.relativePositions)
{
}

Tetromino& Tetromino::operator=(const Tetromino& instance) noexcept
{
	if (this == &instance) return *this;

	areaSize = instance.areaSize;
	absolutePosition = instance.absolutePosition;
	relativePositions = instance.relativePositions;

	return *this;
}

Tetromino::Tetromino(Tetromino&& instance) noexcept
	: areaSize(instance.areaSize)
	, absolutePosition(instance.absolutePosition)
	, relativePositions(instance.relativePositions)
{
}

Tetromino& Tetromino::operator=(Tetromino&& instance) noexcept
{
	if (this == &instance) return *this;

	areaSize = instance.areaSize;
	absolutePosition = instance.absolutePosition;
	relativePositions = instance.relativePositions;

	return *this;
}

void Tetromino::Spin(ESpin spin)
{
	switch (spin)
	{
	case ESpin::CW:
		relativePositions[0] = Vector2i(areaSize - 1 - relativePositions[0].y, relativePositions[0].x);
		relativePositions[1] = Vector2i(areaSize - 1 - relativePositions[1].y, relativePositions[1].x);
		relativePositions[2] = Vector2i(areaSize - 1 - relativePositions[2].y, relativePositions[2].x);
		relativePositions[3] = Vector2i(areaSize - 1 - relativePositions[3].y, relativePositions[3].x);
		break;

	case ESpin::CCW:
		relativePositions[0] = Vector2i(relativePositions[0].y, areaSize - 1 - relativePositions[0].x);
		relativePositions[1] = Vector2i(relativePositions[1].y, areaSize - 1 - relativePositions[1].x);
		relativePositions[2] = Vector2i(relativePositions[2].y, areaSize - 1 - relativePositions[2].x);
		relativePositions[3] = Vector2i(relativePositions[3].y, areaSize - 1 - relativePositions[3].x);
		break;

	default:
		throw std::exception("not support tetromino spin direction");
	}
}

void Tetromino::Move(EMove move)
{
	switch (move)
	{
	case EMove::Left:
		absolutePosition.x -= 1;
		break;

	case EMove::Right:
		absolutePosition.x += 1;
		break;

	case EMove::Down:
		absolutePosition.y += 1;
		break;

	case EMove::Up:
		absolutePosition.y -= 1;
		break;

	default:
		throw std::exception("not support tetromino move direction");
	}
}

void Tetromino::GenerateRelativePositions(EShape shape)
{
	relativePositions.resize(4);

	switch (shape)
	{
	case EShape::I:
		areaSize = 4;
		relativePositions[0] = Vector2i(0, 1);
		relativePositions[1] = Vector2i(1, 1);
		relativePositions[2] = Vector2i(2, 1);
		relativePositions[3] = Vector2i(3, 1);
		break;

	case EShape::O:
		areaSize = 4;
		relativePositions[0] = Vector2i(1, 1);
		relativePositions[1] = Vector2i(2, 1);
		relativePositions[2] = Vector2i(1, 2);
		relativePositions[3] = Vector2i(2, 2);
		break;

	case EShape::T:
		areaSize = 3;
		relativePositions[0] = Vector2i(0, 1);
		relativePositions[1] = Vector2i(1, 1);
		relativePositions[2] = Vector2i(2, 1);
		relativePositions[3] = Vector2i(1, 2);
		break;

	case EShape::J:
		areaSize = 3;
		relativePositions[0] = Vector2i(0, 1);
		relativePositions[1] = Vector2i(1, 1);
		relativePositions[2] = Vector2i(2, 1);
		relativePositions[3] = Vector2i(2, 2);
		break;

	case EShape::L:
		areaSize = 3;
		relativePositions[0] = Vector2i(0, 1);
		relativePositions[1] = Vector2i(1, 1);
		relativePositions[2] = Vector2i(2, 1);
		relativePositions[3] = Vector2i(0, 2);
		break;

	case EShape::S:
		areaSize = 3;
		relativePositions[0] = Vector2i(1, 0);
		relativePositions[1] = Vector2i(2, 0);
		relativePositions[2] = Vector2i(0, 1);
		relativePositions[3] = Vector2i(1, 1);
		break;

	case EShape::Z:
		areaSize = 3;
		relativePositions[0] = Vector2i(0, 0);
		relativePositions[1] = Vector2i(0, 1);
		relativePositions[2] = Vector2i(1, 1);
		relativePositions[3] = Vector2i(2, 1);
		break;

	default:
		throw std::exception("not support tetromino shape");
	}
}