#include "Macro.h"
#include "Board.h"

Board::Board(const int32_t& InWidth, const int32_t& InHeight)
	: Width_(InWidth)
	, Height_(InHeight)
{
	Blocks_ = CreateBlocks(Width_, Height_);
	SetupBlocks(Blocks_, Width_, Height_);
}

Board::Board(Board&& InInstance) noexcept
	: Width_(InInstance.Width_)
	, Height_(InInstance.Height_)
	, Blocks_(InInstance.Blocks_)
{
}

Board::Board(const Board& InInstance) noexcept
	: Width_(InInstance.Width_)
	, Height_(InInstance.Height_)
	, Blocks_(InInstance.Blocks_)
{
}

Board::~Board()
{
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Blocks_ = InInstance.Blocks_;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Blocks_ = InInstance.Blocks_;

	return *this;
}

bool Board::RegisterTetromino(const Tetromino& InTetromino)
{
	if (!CanRegisterTetromino(InTetromino))
	{
		return false;
	}

	const Block TetrominoBlock = InTetromino.GetTetrominoBlock();
	const Vec2i AbsolutePosition = InTetromino.GetAbsolutePosition();
	const std::vector<Vec2i>& RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_);
		Blocks_[Offset] = TetrominoBlock;
	}

	return true;
}

void Board::UnregisterTetromino(const Tetromino& InTetromino)
{
	const Block EmptyBlock(Block::EColor::None, Block::EState::Empty);
	const Vec2i AbsolutePosition = InTetromino.GetAbsolutePosition();
	const std::vector<Vec2i>& RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_);
		Blocks_[Offset] = EmptyBlock;
	}
}

int32_t Board::Update()
{
	int32_t CountOfRemoveLine = RemoveFullFillLines();
	bool bCanUpdate = (CountOfRemoveLine > 0) ? true : false;

	if (bCanUpdate)
	{
		UpdateBoard();
	}

	return CountOfRemoveLine;
}

void Board::Reset()
{
	std::vector<Block> NewBlocks = CreateBlocks(Width_, Height_);
	SetupBlocks(NewBlocks, Width_, Height_);

	Blocks_ = NewBlocks;
}

void Board::Draw(const Vec2i& InPosition)
{
	for (int32_t x = 0; x < Width_; ++x)
	{
		for (int32_t y = 0; y < Height_; ++y)
		{
			int32_t Offset = GetOffset(x, y, Width_, Height_);
			Vec2i CurrentPosition = InPosition + Vec2i(x, y);
			Blocks_[Offset].Draw(CurrentPosition);
		}
	}
}

int32_t Board::GetOffset(int32_t InPositionX, int32_t InPositionY, int32_t InWidth, int32_t InHeight)
{
	CHECK(((0 <= InPositionX && InPositionX < InWidth) && (0 <= InPositionY && InPositionY < InHeight)), "out of range in array");
	return (InWidth * InPositionY + InPositionX);
}

int32_t Board::GetOffset(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight)
{
	return GetOffset(InPosition.x, InPosition.y, InWidth, InHeight);
}

std::vector<Block> Board::CreateBlocks(int32_t InWidth, int32_t InHeight)
{
	int32_t NewBlocksSize = InWidth * InHeight;
	return std::vector<Block>(NewBlocksSize);
}

void Board::SetupBlocks(std::vector<Block>& InBlocks, int32_t InWidth, int32_t InHeight)
{
	for (int32_t y = 0; y < InHeight; ++y)
	{
		if (y == InHeight - 1)
		{
			for (int32_t x = 0; x < InWidth; ++x)
			{
				InBlocks[GetOffset(x, y, InWidth, InHeight)] = Block(Block::EColor::Gray, Block::EState::Wall);
			}
		}
		else
		{
			InBlocks[GetOffset(0, y, InWidth, InHeight)] = Block(Block::EColor::Gray, Block::EState::Wall);
			InBlocks[GetOffset(InWidth - 1, y, InWidth, InHeight)] = Block(Block::EColor::Gray, Block::EState::Wall);
		}
	}
}

bool Board::DoseIncludePosition(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight)
{
	return (0 <= InPosition.x && InPosition.x < InWidth) && (0 <= InPosition.y && InPosition.y < InHeight);
}

bool Board::CanRegisterTetromino(const Tetromino& InTetromino)
{
	const Block TetrominoBlock = InTetromino.GetTetrominoBlock();
	const Vec2i AbsolutePosition = InTetromino.GetAbsolutePosition();
	const std::vector<Vec2i>& RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		if (!DoseIncludePosition(BoardPosition, Width_, Height_))
		{
			return false;
		}

		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_);
		if (Blocks_[Offset].GetState() != Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsFullFillLine(int32_t InY)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width_, Height_);
		if (Blocks_[Offset].GetState() == Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsFullEmptyLine(int32_t InY)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width_, Height_);
		if (Blocks_[Offset].GetState() != Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveLine(int32_t InY)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width_, Height_);
		Blocks_[Offset] = Block(Block::EColor::None, Block::EState::Empty);
	}
}

int32_t Board::RemoveFullFillLines()
{
	int32_t CountOfRemoveLine = 0;

	for (int32_t y = 0; y < Height_ - 1; ++y)
	{
		if (IsFullFillLine(y))
		{
			CountOfRemoveLine++;
			RemoveLine(y);
		}
	}

	return CountOfRemoveLine;
}

void Board::UpdateBoard()
{
	std::vector<Block> NewBlocks = CreateBlocks(Width_, Height_);
	SetupBlocks(NewBlocks, Width_, Height_);

	for (int32_t OldY = Height_ - 2, NewY = Height_ - 2; OldY >= 0; --OldY)
	{
		if (!IsFullEmptyLine(OldY))
		{
			for (int32_t x = 1; x < Width_ - 1; ++x)
			{
				int32_t OldOffset = GetOffset(x, OldY, Width_, Height_);
				int32_t NewOffset = GetOffset(x, NewY, Width_, Height_);
				NewBlocks[NewOffset] = Blocks_[OldOffset];
			}

			--NewY;
		}
	}

	Blocks_ = NewBlocks;
}