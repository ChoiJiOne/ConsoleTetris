#include <Board.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Tetromino.h>
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
		Tetromino_.reset();
		//Board_.reset();

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

		//Board_ = std::make_unique<Board>(10, 20);
		Tetromino_ = std::make_unique<Tetromino>(Vec2i(3, 0), Vec2i(0, 0));
		Tetromino_->SetState(Tetromino::EState::ACTIVE);
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

			Tetromino_->Update(Timer_.GetDeltaTime());
			Tetromino_->Render();
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
	 * ��Ʈ���� �����Դϴ�.
	 */
	//std::unique_ptr<Board> Board_ = nullptr;


	/**
	 * ��Ʈ���� ��Ʈ�ι̳��Դϴ�.
	 */
	std::unique_ptr<Tetromino> Tetromino_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}