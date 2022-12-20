#include <Block.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Tetromino.h>
#include <Timer.h>
#include <Vector.hpp>

#include <list>


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
		EmptyBlock_.reset();
		FillBlock_.reset();

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

		FillBlock_ = std::make_unique<Block>(Vec2i(5, 5), Block::EState::FILL, EColor::AQUA);
		EmptyBlock_ = std::make_unique<Block>(Vec2i(6, 5), Block::EState::EMPTY, EColor::RED);
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

			Update();
			Render();
		}
	}


private:
	/**
	 * 루프를 업데이트합니다.
	 */
	void Update()
	{
	}


	/**
	 * 콘솔 화면에 렌더링을 수행합니다.
	 */
	void Render()
	{
		FillBlock_->Render();
		EmptyBlock_->Render();
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
	 * 테트리스 채움 블럭입니다.
	 */
	std::unique_ptr<Block> FillBlock_ = nullptr;


	/**
	 * 테트리스 비어있는 블럭입니다.
	 */
	std::unique_ptr<Block> EmptyBlock_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}