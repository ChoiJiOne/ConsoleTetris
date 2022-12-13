#include <Block.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Timer.h>
#include <Vector.hpp>


/**
 * ��Ʈ���� �����Դϴ�.
 */
class Tetris
{
public:
	/**
	 * ��Ʈ���� ������ �������Դϴ�.
	 * �̶�, �����ڿ����� � �ʱ�ȭ�� �������� �ʽ��ϴ�.
	 */
	Tetris() = default;


	/**
	 * ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetris()
	{
		ConsoleManager::Get().SetCursorVisible(true);
	}


	/**
	 * ��Ʈ���� ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� �ʱ�ȭ�� �����ϸ�, C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init()
	{
		SetUnhandledExceptionFilter(UnhandledExceptionHandler);

		ConsoleManager::Get().Clear();
		ConsoleManager::Get().SetTitle("ConsoleTetris");
		ConsoleManager::Get().SetCursorVisible(false);

		Board_ = std::vector<Block>(Width_ * Height_);
		for (int32_t y = 0; y < Height_; ++y)
		{
			for (int32_t x = 0; x < Width_; ++x)
			{
				int32_t Offset = y * Width_ + x;
				Block CurrentBlock;

				if (x == 0 || x == Width_ - 1 || y == Height_ - 1)
				{
					CurrentBlock = Block(Block::EType::GRAY, Block::EState::WALL, Vec2i(x, y));
				}
				else
				{
					CurrentBlock = Block(Block::EType::GRAY, Block::EState::EMPTY, Vec2i(x, y));
				}

				Board_[Offset] = CurrentBlock;
			}
		}
	}


	/**
	 * ��Ʈ���� ������ �����մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� ���࿡ �����ϸ�, C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Run()
	{
		Timer_.Reset();

		while (!bIsDone_)
		{
			Timer_.Tick();
			InputManager::Get().Tick();

			if (InputManager::Get().GetKeyPressState(EKeyCode::ESCAPE) == EPressState::PRESSED)
			{
				bIsDone_ = true;
			}

			for (int32_t y = 0; y < Height_; ++y)
			{
				for (int32_t x = 0; x < Width_; ++x)
				{
					Block CurrentBlock = Board_[y * Width_ + x];

					if (CurrentBlock.GetState() == Block::EState::WALL)
					{
						ConsoleManager::Get().RenderText(CurrentBlock.GetPosition(), "��", EColor::GRAY);
					}
					else
					{
						ConsoleManager::Get().RenderText(CurrentBlock.GetPosition(), "��", EColor::WHITE);
					}
				}
			}
		}
	}


private:
	/**
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsDone_ = false;


	/**
	 * ���� Ÿ�̸��Դϴ�.
	 */
	Timer Timer_;


	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Width_ = 10;


	/**
	 * ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Height_ = 20;


	/**
	 * ��Ʈ���� �����Դϴ�.
	 */
	std::vector<Block> Board_;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}