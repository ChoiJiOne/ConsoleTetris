#include <Board.h>
#include <ConsoleManager.h>
#include <Macro.h>
#include <WorldManager.h>

float Board::MaxAccrueTime_ = 1.0f;

Board::Board(const Vec2i& InConsolePosition, const int32_t& InWidth, const int32_t& InHeight) noexcept
	: ConsolePosition_(InConsolePosition)
	, Width_(InWidth)
	, Height_(InHeight)
{
	Blocks_ = CreateEmptyBlocks(ConsolePosition_, Width_, Height_);

	WorldManager::Get().RegisterOjbect(this, Text::GetHash("Board"));
}

Board::~Board()
{
	WorldManager::Get().UnregisterObject(Text::GetHash("Board"));
}

void Board::Update(float InDeltaSeconds)
{
	if (State_ == EState::WAIT)
	{
		AccrueTime_ += InDeltaSeconds;

		if (AccrueTime_ >= MaxAccrueTime_)
		{
			bool bIsRemoveRowLine = false;
			int32_t RemoveYPosition = 0;

			for (int32_t y = Height_ - 2; y >= 1; --y)
			{
				if (CanRemoveRowLine(y))
				{
					bIsRemoveRowLine = true;
					RemoveYPosition = y;
					break;
				}
			}

			if (bIsRemoveRowLine)
			{
				ClearRowLine(RemoveYPosition);
			}
			else
			{
				ArrangeEmptyRowLine();
				State_ = EState::ACTIVE;
			}

			AccrueTime_ = 0.0f;
		}
	}
}

void Board::Render()
{
	for (auto& block : Blocks_)
	{
		block.Render();
	}
}

bool Board::IsCollision(const Block& InBlock)
{
	bool bIsCollision = false;

	Vec2i BoardPosition = InBlock.GetPosition() - Position_;
	Block BoardBlock = GetBlock(BoardPosition);

	if (BoardBlock.GetState() != Block::EState::EMPTY && InBlock.GetState() != Block::EState::EMPTY)
	{
		bIsCollision = true;
	}

	return bIsCollision;
}

void Board::WriteBlocks(const std::vector<Block>& InBlocks)
{
	for (const auto& WriteBlock : InBlocks)
	{
		SetBlock(WriteBlock);
	}
}

void Board::RemoveBlocks(const std::vector<Block>& InBlocks)
{
	for (const auto& RemoveBlock : InBlocks)
	{
		SetBlock(Block(RemoveBlock.GetPosition(), Block::EState::EMPTY, EColor::WHITE));
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

Block Board::GetBlock(const Vec2i& InPosition)
{
	CHECK((0 <= InPosition.x && InPosition.x < Width_ && 0 <= InPosition.y && InPosition.y < Height_), "out of range in board...");
	
	int32_t Offset = GetOffset(InPosition);
	return Blocks_[Offset];
}

void Board::SetBlock(const Block& InBlock)
{
	Vec2i Position = InBlock.GetPosition() - Position_;
	CHECK((0 <= Position.x && Position.x < Width_ && 0 <= Position.y && Position.y < Height_), "out of range in board...");

	int32_t Offset = GetOffset(Position);
	Blocks_[Offset] = InBlock;
}

void Board::OverwriteRowLine(const int32_t& InFromYPosition, const int32_t& InToYPosition)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		Block FromBlock = GetBlock(Vec2i(x, InFromYPosition));
		Block ToBlock = GetBlock(Vec2i(x, InToYPosition));

		ToBlock.SetState(FromBlock.GetState());
		ToBlock.SetColor(FromBlock.GetColor());

		SetBlock(ToBlock);
	}
}

bool Board::CanRemoveRowLine(const int32_t& InYPosition)
{
	for (int32_t x = 1; x < Width_ - 1; ++x)
	{
		if (GetBlock(Vec2i(x, InYPosition)).GetState() != Block::EState::FILL)
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
		if (GetBlock(Vec2i(x, InYPosition)).GetState() != Block::EState::EMPTY)
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
		Block BoardBlock = GetBlock(Vec2i(x, InYPosition));

		BoardBlock.SetState(Block::EState::EMPTY);
		BoardBlock.SetColor(EColor::WHITE);
		
		SetBlock(BoardBlock);
	}
}

void Board::ArrangeEmptyRowLine()
{
	/*for (int32_t y = Height_ - 2; y >= 1;)
	{
		if (IsEmptyRowLine(y))
		{
			for (int32_t OverwriteY = y - 1; OverwriteY >= 1; --OverwriteY)
			{
				OverwriteRowLine(OverwriteY, OverwriteY + 1);
			}
		}
		else
		{
			--y;
		}
	}

	ClearRowLine(1);*/

	std::vector<int32_t> NotEmptyRowLines;
	for (int32_t y = Height_ - 2; y >= 1; --y)
	{
		if (!IsEmptyRowLine(y))
		{
			NotEmptyRowLines.push_back(y);
		}
	}

	int32_t NewRowLine = Height_ - 2;
	for (int32_t NotEmptyRowLine : NotEmptyRowLines)
	{
		

		NewRowLine--;
	}

}
