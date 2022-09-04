#include "Macro.h"
#include "Board.h"

Board::Board(const int32_t& InWidth, const int32_t& InHeight)
	: Width(InWidth)
	, Height(InHeight)
{
	Blocks = CreateBlocks(Width, Height);
	SetupBlocks(Blocks, Width, Height);
}

Board::Board(Board&& InInstance) noexcept
	: Width(InInstance.Width)
	, Height(InInstance.Height)
	, Blocks(InInstance.Blocks)
{
}

Board::Board(const Board& InInstance) noexcept
	: Width(InInstance.Width)
	, Height(InInstance.Height)
	, Blocks(InInstance.Blocks)
{
}

Board::~Board()
{
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width = InInstance.Width;
	Height = InInstance.Height;
	Blocks = InInstance.Blocks;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width = InInstance.Width;
	Height = InInstance.Height;
	Blocks = InInstance.Blocks;

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
	const std::vector<Vec2i> RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width, Height);
		Blocks[Offset] = TetrominoBlock;
	}

	return true;
}

void Board::UnregisterTetromino(const Tetromino& InTetromino)
{
	const Block EmptyBlock(Block::EColor::Empty, Block::EState::Empty);
	const Vec2i AbsolutePosition = InTetromino.GetAbsolutePosition();
	const std::vector<Vec2i> RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width, Height);
		Blocks[Offset] = EmptyBlock;
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
	std::vector<Block> NewBlocks = CreateBlocks(Width, Height);
	SetupBlocks(NewBlocks, Width, Height);

	Blocks = NewBlocks;
}

void Board::Draw(const Vec2i& InPosition)
{
	for (int32_t x = 0; x < Width; ++x)
	{
		for (int32_t y = 0; y < Height; ++y)
		{
			int32_t Offset = GetOffset(x, y, Width, Height);
			Vec2i CurrentPosition = InPosition + Vec2i(x, y);
			Blocks[Offset].Draw(CurrentPosition);
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
	const std::vector<Vec2i> RelativePositions = InTetromino.GetRelativePositions();

	for (const auto& RelativePosition : RelativePositions)
	{
		Vec2i BoardPosition = AbsolutePosition + RelativePosition;
		if (!DoseIncludePosition(BoardPosition, Width, Height))
		{
			return false;
		}

		int32_t Offset = GetOffset(BoardPosition.x, BoardPosition.y, Width, Height);
		if (Blocks[Offset].GetState() != Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsFullFillLine(int32_t InY)
{
	for (int32_t x = 1; x < Width - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width, Height);
		if (Blocks[Offset].GetState() == Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsFullEmptyLine(int32_t InY)
{
	for (int32_t x = 1; x < Width - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width, Height);
		if (Blocks[Offset].GetState() != Block::EState::Empty)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveLine(int32_t InY)
{
	for (int32_t x = 1; x < Width - 1; ++x)
	{
		int32_t Offset = GetOffset(x, InY, Width, Height);
		Blocks[Offset] = Block(Block::EColor::Empty, Block::EState::Empty);
	}
}

int32_t Board::RemoveFullFillLines()
{
	int32_t CountOfRemoveLine = 0;

	for (int32_t y = 0; y < Height - 1; ++y)
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
	std::vector<Block> NewBlocks = CreateBlocks(Width, Height);
	SetupBlocks(NewBlocks, Width, Height);

	for (int32_t OldY = Height - 2, NewY = Height - 2; OldY >= 0; --OldY)
	{
		if (!IsFullEmptyLine(OldY))
		{
			for (int32_t x = 1; x < Width - 1; ++x)
			{
				int32_t OldOffset = GetOffset(x, OldY, Width, Height);
				int32_t NewOffset = GetOffset(x, NewY, Width, Height);
				NewBlocks[NewOffset] = Blocks[OldOffset];
			}

			--NewY;
		}
	}

	Blocks = NewBlocks;
}