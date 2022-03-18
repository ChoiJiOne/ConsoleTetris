#pragma once

#include "Common.h"

class Board
{
public:
	enum class EBlockState : int32_t
	{
		Empty = 0,
		Fill  = 1,
		Fix   = 2
	};

public:
	Board(int32_t boardRowSize = 20, int32_t boardColSize = 10);
	virtual ~Board();

	Board(Board&& instance) noexcept;
	Board& operator=(Board&& instance) noexcept;

	Board(const Board& instance) noexcept;
	Board& operator=(const Board& instance) noexcept;

	EBlockState GetBoardBlockState(int32_t x, int32_t y);
	void        SetBoardBlockState(int32_t x, int32_t y, EBlockState state);

	int32_t GetRowSize() noexcept { return rowSize; }
	int32_t GetColSize() noexcept { return colSize; }

	bool CheckInsidePositionInBoard(int32_t x, int32_t y);

	void UpdateBoardState();
	void ResetBoardState();

private:
	int32_t GetOffset(int32_t x, int32_t y, int32_t row, int32_t col);

	bool IsFullRowLine(const std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine);
	bool IsEmptyRowLine(const std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine);
	void RemoveRowLine(std::vector<EBlockState>& blocks, int32_t row, int32_t col, int32_t rowLine);

	std::vector<EBlockState> CreateBoardBlocks(int32_t row, int32_t col);
	void SetupBoardBlocks(std::vector<EBlockState>& blocks, int32_t row, int32_t col);

private:
	int32_t rowSize = 0;
	int32_t colSize = 0;
	std::vector<EBlockState> boardBlocks;
};