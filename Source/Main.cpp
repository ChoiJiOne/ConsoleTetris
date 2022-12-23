#include <Block.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Tetromino.h>
#include <Timer.h>
#include <Vector.hpp>

#include <array>
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
		//Tetromino_.reset();

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

		//Tetromino_ = std::make_unique<Tetromino>(Vec2i(15, 5), Tetromino::EShape::L, EColor::GRAY);
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
		//Tetromino_->Update(Timer_.GetDeltaTime());
	}


	/**
	 * 콘솔 화면에 렌더링을 수행합니다.
	 */
	void Render()
	{
		//Tetromino_->Render();
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
	 * 테트로미노 입니다.
	 */
	//std::unique_ptr<Tetromino> Tetromino_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}