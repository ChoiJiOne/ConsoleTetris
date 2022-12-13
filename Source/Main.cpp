#include <Block.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Timer.h>
#include <Vector.hpp>


/**
 * 테트리스 게임입니다.
 */
class Tetris
{
public:
	/**
	 * 테트리스 게임의 생성자입니다.
	 * 이때, 생성자에서는 어떤 초기화도 수행하지 않습니다.
	 */
	Tetris() = default;


	/**
	 * 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		ConsoleManager::Get().SetCursorVisible(true);
	}


	/**
	 * 테트리스 게임을 초기화합니다.
	 * 
	 * @throws 테트리스 게임 초기화에 실패하면, C++ 표준 예외를 던집니다.
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
	 * 테트리스 게임을 실행합니다.
	 * 
	 * @throws 테트리스 게임 실행에 실패하면, C++ 표준 예외를 던집니다.
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
						ConsoleManager::Get().RenderText(CurrentBlock.GetPosition(), "■", EColor::GRAY);
					}
					else
					{
						ConsoleManager::Get().RenderText(CurrentBlock.GetPosition(), "·", EColor::WHITE);
					}
				}
			}
		}
	}


private:
	/**
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone_ = false;


	/**
	 * 게임 타이머입니다.
	 */
	Timer Timer_;


	/**
	 * 테트리스 보드의 가로 크기입니다.
	 */
	int32_t Width_ = 10;


	/**
	 * 테트리스 보드의 세로 크기입니다.
	 */
	int32_t Height_ = 20;


	/**
	 * 테트리스 보드입니다.
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