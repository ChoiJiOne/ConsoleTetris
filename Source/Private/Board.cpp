#include <Board.h>
#include <ConsoleManager.h>
#include <Macro.h>
#include <WorldManager.h>

Board::Board(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight) noexcept
	: Position_(InPosition)
	, Width_(InWidth)
	, Height_(InHeight)
{
	Blocks_ = std::vector<Block>(Width_ * Height_);

	for (int32_t y = 0; y < Height_; ++y)
	{
		for (int32_t x = 0; x < Width_; ++x)
		{
			Vec2i ConsolePosition = Position_ + Vec2i(x, y);

			if (x == 0 || x == Width_ - 1 || y == Height_ - 1)
			{
				SetBlock(Block(ConsolePosition, Block::EState::WALL, EColor::GRAY));

			}
			else
			{
				SetBlock(Block(ConsolePosition, Block::EState::EMPTY, EColor::BLACK));
			}
		}
	}
}

void Board::Update(float InDeltaSeconds)
{
}

void Board::Render()
{
	for (auto& block : Blocks_)
	{
		block.Render();
	}
}

int32_t Board::GetOffset(const Vec2i& InPosition)
{
	return InPosition.y * Width_ + InPosition.x;
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
