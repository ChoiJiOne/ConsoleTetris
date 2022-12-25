#include <Board.h>
#include <ConsoleManager.h>
#include <Macro.h>
#include <WorldManager.h>

float Board::MaxAccrueTime_ = 0.5f;

Board::Board(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight) noexcept
	: ConsolePosition_(InConsolePosition)
	, Width_(InWidth)
	, Height_(InHeight)
{
	BoardBlocks_ = CreateEmptyBlocks(ConsolePosition_, Width_, Height_);

	WorldManager::Get().RegisterOjbect(this, Text::GetHash("Board"));
}

Board::~Board()
{
	WorldManager::Get().UnregisterObject(Text::GetHash("Board"));
}

void Board::Update(float InDeltaSeconds)
{
	if (CurrentState_ == EState::WAIT)
	{
		AccrueTime_ += InDeltaSeconds;

		if (AccrueTime_ >= MaxAccrueTime_)
		{
			bool bHaveRemoveRowLine = false;
			int32_t RemoveYPosition = 0;

			for (int32_t y = Height_ - 2; y >= 1; --y)
			{
				if (CanRemoveRowLine(y))
				{
					bHaveRemoveRowLine = true;
					RemoveYPosition = y;
					break;
				}
			}

			if (bHaveRemoveRowLine)
			{
				ClearRowLine(RemoveYPosition);
				RemoveLine_++;
			}
			else
			{
				ArrangeEmptyRowLine();
				CurrentState_ = EState::ACTIVE;
			}

			AccrueTime_ = 0.0f;
		}
	}
}

void Board::Render()
{
	for (auto& BoardBlock : BoardBlocks_)
	{
		BoardBlock.Render();
	}
}

bool Board::IsCollision(const Block& InBlock)
{
	bool bIsCollision = false;

	Vec2i BoardPosition = InBlock.GetPosition() - ConsolePosition_;
	int32_t Offset = GetOffset(BoardPosition, Width_, Height_);

	if (BoardBlocks_[Offset].GetState() != Block::EState::EMPTY && InBlock.GetState() != Block::EState::EMPTY)
	{
		bIsCollision = true;
	}

	return bIsCollision;
}

void Board::WriteBlocks(const std::vector<Block>& InWriteBlocks)
{
	for (const auto& WriteBlock : InWriteBlocks)
	{
		Vec2i BoardPosition = WriteBlock.GetPosition() - ConsolePosition_;
		int32_t Offset = GetOffset(BoardPosition, Width_, Height_);

		BoardBlocks_[Offset] = WriteBlock;
	}
}

void Board::RemoveBlocks(const std::vector<Block>& InRemoveBlocks)
{
	for (const auto& RemoveBlock : InRemoveBlocks)
	{
		Vec2i BoardPosition = RemoveBlock.GetPosition() - ConsolePosition_;
		int32_t Offset = GetOffset(BoardPosition, Width_, Height_);

		BoardBlocks_[Offset] = Block(RemoveBlock.GetPosition(), Block::EState::EMPTY, EColor::WHITE);
	}
}

int32_t Board::GetOffset(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight)
{
	return InPosition.y * InWidth + InPosition.x;
}

std::vector<Block> Board::CreateEmptyBlocks(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight)
{
	std::vector<Block> Blocks(InWidth * InHeight);

	Vec2i BoardPosition;
	Vec2i ConsolePosition;

	for (int32_t BoardY = 0; BoardY < InHeight; ++BoardY)
	{
		for (int32_t BoardX = 0; BoardX < InWidth; ++BoardX)
		{
			BoardPosition = Vec2i(BoardX, BoardY);
			ConsolePosition = InConsolePosition + BoardPosition;
			Block NewBlock;

			NewBlock.SetPosition(ConsolePosition);

			if (BoardX == 0 || BoardX == Width_ - 1 || BoardY == 0 || BoardY == Height_ - 1)
			{
				NewBlock.SetState(Block::EState::WALL);
				NewBlock.SetColor(EColor::GRAY);

			}
			else
			{
				NewBlock.SetState(Block::EState::EMPTY);
				NewBlock.SetColor(EColor::WHITE);
			}

			Blocks[GetOffset(BoardPosition, InWidth, InHeight)] = NewBlock;
		}
	}

	return Blocks;
}

bool Board::CanRemoveRowLine(const int32_t& InYPosition)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		if (BoardBlocks_[GetOffset(Vec2i(x, InYPosition), Width_, Height_)].GetState() != Block::EState::FILL)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEmptyRowLine(const int32_t& InYPosition)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		if (BoardBlocks_[GetOffset(Vec2i(x, InYPosition), Width_, Height_)].GetState() != Block::EState::EMPTY)
		{
			return false;
		}
	}

	return true;
}

void Board::ClearRowLine(const int32_t& InYPosition)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		BoardBlocks_[GetOffset(Vec2i(x, InYPosition), Width_, Height_)].SetState(Block::EState::EMPTY);
		BoardBlocks_[GetOffset(Vec2i(x, InYPosition), Width_, Height_)].SetColor(EColor::WHITE);
	}
}

void Board::ArrangeEmptyRowLine()
{
	std::vector<Block> NewBoardBlocks = CreateEmptyBlocks(ConsolePosition_, Width_, Height_);

	for (int32_t y = Height_ - 2, CurrentRowLine = Height_ - 2; y >= 1; --y)
	{
		if (!IsEmptyRowLine(y))
		{
			for (int32_t x = 1; x < Width_ - 1; ++x)
			{
				Block& OriginBlock = BoardBlocks_[GetOffset(Vec2i(x, y), Width_, Height_)];
				Block& NewBlock = NewBoardBlocks[GetOffset(Vec2i(x, CurrentRowLine), Width_, Height_)];

				NewBlock.SetState(OriginBlock.GetState());
				NewBlock.SetColor(OriginBlock.GetColor());
			}

			CurrentRowLine--;
		}
	}

	BoardBlocks_ = NewBoardBlocks;
}
