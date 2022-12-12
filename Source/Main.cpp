#include <iostream>

#include "Debug.h"
#include "InputManager.h"
#include "ConsoleManager.h"
#include "Vector.hpp"


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
	}


	/**
	 * ��Ʈ���� ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� �ʱ�ȭ�� �����ϸ�, C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init()
	{
		SetUnhandledExceptionFilter(UnhandledExceptionHandler);
	}


	/**
	 * ��Ʈ���� ������ �����մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� ���࿡ �����ϸ�, C++ ǥ�� ���ܸ� �����ϴ�.
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

			if (InputManager::Get().GetKeyPressState(EKeyCode::UP) == EPressState::PRESSED)
			{
				ConsoleManager::Get().RenderText(Vec2i(10, 0), "PRESS UP", EColor::AQUA);
			}

			if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
			{
				ConsoleManager::Get().RenderText(Vec2i(10, 20), "PRESS DOWN", EColor::WHITE);
			}

			if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED)
			{
				ConsoleManager::Get().RenderText(Vec2i(0, 10), "PRESS LEFT", EColor::GRAY);
			}

			if (InputManager::Get().GetKeyPressState(EKeyCode::RIGHT) == EPressState::PRESSED)
			{
				ConsoleManager::Get().RenderText(Vec2i(20, 10), "PRESS RIGHT", EColor::GREEN);
			}
		}
	}


private:
	/**
	 * ���� ���� ���θ� Ȯ���մϴ�.
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