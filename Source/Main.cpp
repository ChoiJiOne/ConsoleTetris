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
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}