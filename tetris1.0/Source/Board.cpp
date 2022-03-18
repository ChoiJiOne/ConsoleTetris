#include "Board.h"

int32_t Board::GetOffset(int32_t x, int32_t y, int32_t row, int32_t col)
{
	if (!(0 <= x && x < col) &&
		!(0 <= y && y < row))
	{
		throw std::exception("out of range in board");
	}

	return y * col + x;
}

bool Board::IsFullRowLine(const std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		if (blocks[GetOffset(x, rowLine, row, col)] != EBlockState::Fill)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEmptyRowLine(const std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		if (blocks[GetOffset(x, rowLine, row, col)] != EBlockState::Empty)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveRowLine(std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		blocks[GetOffset(x, rowLine, row, col)] = EBlockState::Empty;
	}
}

std::vector<Board::EBlockState> Board::CreateBoardBlocks(int32_t row, int32_t col)
{
	return std::vector<EBlockState>(row * col, EBlockState::Empty);
}

void Board::SetupBoardBlocks(std::vector<EBlockState>& blocks, int32_t row, int32_t col)
{
	std::fill(blocks.begin(), blocks.end(), EBlockState::Empty);

	for (int32_t y = 0; y < row; ++y)
	{
		if (y == row - 1)
		{
			for (int32_t x = 0; x < col; ++x)
			{
				blocks[GetOffset(x, y, row, col)] = EBlockState::Fix;
			}
		}
		else
		{
			blocks[GetOffset(      0, y, row, col)] = EBlockState::Fix;
			blocks[GetOffset(col - 1, y, row, col)] = EBlockState::Fix;
		}
	}
}

Board::Board(int32_t boardRowSize, int32_t boardColSize)
	: rowSize(boardRowSize)
	, colSize(boardColSize)
{
	boardBlocks = CreateBoardBlocks(rowSize, colSize);
	SetupBoardBlocks(boardBlocks, rowSize, colSize);
}

Board::~Board()
{
}

Board::Board(Board&& instance) noexcept
	: rowSize(instance.rowSize)
	, colSize(instance.colSize)
	, boardBlocks(instance.boardBlocks)
{
}

Board& Board::operator=(Board&& instance) noexcept
{
	if (this == &instance) return *this;

	rowSize = instance.rowSize;
	colSize = instance.colSize;
	boardBlocks = instance.boardBlocks;

	return *this;
}

Board::Board(const Board& instance) noexcept
	: rowSize(instance.rowSize)
	, colSize(instance.colSize)
	, boardBlocks(instance.boardBlocks)
{
}

Board& Board::operator=(const Board& instance) noexcept
{
	if (this == &instance) return *this;

	rowSize = instance.rowSize;
	colSize = instance.colSize;
	boardBlocks = instance.boardBlocks;

	return *this;
}

Board::EBlockState Board::GetBoardBlockState(int32_t x, int32_t y)
{
	int32_t offset = GetOffset(x, y, rowSize, colSize);
	return boardBlocks[offset];
}

void Board::SetBoardBlockState(int32_t x, int32_t y, EBlockState state)
{
	int32_t offset = GetOffset(x, y, rowSize, colSize);
	boardBlocks[offset] = state;
}

bool Board::CheckInsidePositionInBoard(int32_t x, int32_t y)
{
	return ((0 <= x && x < colSize) && (0 <= y && y < rowSize));
}

void Board::UpdateBoardState()
{
	bool bIsUpdate = false;

	for (int32_t y = 0; y < rowSize - 1; ++y)
	{
		if (IsFullRowLine(boardBlocks, rowSize, colSize, y))
		{
			RemoveRowLine(boardBlocks, rowSize, colSize, y);
			bIsUpdate = true;
		}
	}

	if (bIsUpdate)
	{
		std::vector<EBlockState> tempBlocks = CreateBoardBlocks(rowSize, colSize);
		SetupBoardBlocks(tempBlocks, rowSize, colSize);

		for (int32_t y = rowSize - 2, colLine = rowSize - 2; y >= 0; --y)
		{
			if (!IsEmptyRowLine(boardBlocks, rowSize, colSize, y))
			{
				for (int32_t x = 1; x < colSize - 1; ++x)
				{
					tempBlocks[GetOffset(x, colLine, rowSize, colSize)] = boardBlocks[GetOffset(x, y, rowSize, colSize)];
				}

				colLine--;
			}
		}

		boardBlocks = tempBlocks;
	}
}

void Board::ResetBoardState()
{
	SetupBoardBlocks(boardBlocks, rowSize, colSize);
}
