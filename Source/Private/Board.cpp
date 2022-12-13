#include <Board.h>
#include <ConsoleManager.h>

Board::Board(const int32_t& InWidth, const int32_t& InHeight) noexcept
{
	Width_ = InWidth;
	Height_ = InHeight;
	Board_ = std::vector<Block>(Width_ * Height_);

	for (int32_t y = 0; y < Height_; ++y)
	{
		for (int32_t x = 0; x < Width_; ++x)
		{
			if (x == 0 || x == Width_ - 1 || y == Height_ - 1)
			{
				SetBlock(Block(Block::EType::GRAY, Block::EState::WALL, Vec2i(x, y)));
			}
			else
			{
				SetBlock(Block(Block::EType::GRAY, Block::EState::EMPTY, Vec2i(x, y)));
			}
		}
	}
}

Board::Board(Board&& InInstance) noexcept
{
	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Board_ = InInstance.Board_;
}

Board::Board(const Board& InInstance) noexcept
{
	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Board_ = InInstance.Board_;
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Board_ = InInstance.Board_;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Width_ = InInstance.Width_;
	Height_ = InInstance.Height_;
	Board_ = InInstance.Board_;

	return *this;
}

void Board::Update()
{
}

void Board::Render()
{
	for (int32_t y = 0; y < Height_; ++y)
	{
		for (int32_t x = 0; x < Width_; ++x)
		{
			Block BoardBlock = GetBlock(Vec2i(x, y));

			if (BoardBlock.GetState() == Block::EState::WALL)
			{
				ConsoleManager::Get().RenderText(BoardBlock.GetPosition(), "¡á", EColor::GRAY);
			}
			else
			{
				ConsoleManager::Get().RenderText(BoardBlock.GetPosition(), "¡¤", EColor::WHITE);
			}
		}
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
	return Board_[Offset];
}

void Board::SetBlock(const Block& InBlock)
{
	Vec2i Position = InBlock.GetPosition();

	CHECK((0 <= Position.x && Position.x < Width_ && 0 <= Position.y && Position.y < Height_), "out of range in board...");

	int32_t Offset = GetOffset(Position);
	Board_[Offset] = InBlock;
}