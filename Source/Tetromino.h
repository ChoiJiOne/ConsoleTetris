#pragma once

#include "MathUtil.h"

class Tetromino
{
public:
	enum class EShape : int32_t
	{
		I = 0,
		O = 1,
		T = 2,
		J = 3,
		L = 4,
		S = 5,
		Z = 6,
		Count = 7
	};

	enum class ESpin : int32_t
	{
		CCW = 0,
		CW  = 1
	};

	enum class EMove : int32_t
	{
		Left  = 0,
		Right = 1,
		Down  = 2,
		Up    = 3
	};

public:
	Tetromino(Vector2i absolutePos, EShape shape);
	virtual ~Tetromino();

	Tetromino(const Tetromino& instance) noexcept;
	Tetromino& operator=(const Tetromino& instance) noexcept;

	Tetromino(Tetromino&& instance) noexcept;
	Tetromino& operator=(Tetromino&& instance) noexcept;

	void Spin(ESpin spin);
	void Move(EMove move);

	Vector2i                     GetAbsolutePosition()  noexcept { return absolutePosition; }
	const std::vector<Vector2i>& GetRelativePositions() noexcept { return relativePositions; }

private:
	void GenerateRelativePositions(EShape shape);

private:
	int32_t areaSize = 0;

	Vector2i absolutePosition;
	std::vector<Vector2i> relativePositions;
};

class TetrominoGenerator
{
public:
	static std::shared_ptr<Tetromino> GenerateTetromino(const Vector2i& position, Tetromino::EShape shape)
	{
		return std::make_shared<Tetromino>(position, shape);
	}

	static std::shared_ptr<Tetromino> GenerateRandomTetromino(const Vector2i& position)
	{
		int32_t randomShape = MathUtil::GenerateRandomNumber<int32_t>(0, static_cast<int32_t>(Tetromino::EShape::Count) - 1);
		return GenerateTetromino(position, static_cast<Tetromino::EShape>(randomShape));
	}
};