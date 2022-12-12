#include <iostream>

#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
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

		ConsoleManager::Get().SetCursorVisible(false);
	}


	/**
	 * 테트리스 게임을 실행합니다.
	 * 
	 * @throws 테트리스 게임 실행에 실패하면, C++ 표준 예외를 던집니다.
	 */
	void Run()
	{
		while (!bIsDone_)
		{
			InputManager::Get().Tick();

			if (InputManager::Get().GetKeyPressState(EKeyCode::ESCAPE) == EPressState::PRESSED)
			{
				bIsDone_ = true;
			}
		}
	}


private:
	/**
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone_ = false;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}