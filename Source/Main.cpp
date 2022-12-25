#include <Block.h>
#include <Board.h>
#include <Debug.h>
#include <InputManager.h>
#include <ConsoleManager.h>
#include <Tetromino.h>
#include <Timer.h>
#include <Vector.hpp>

#include <array>
#include <list>


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
		NextTetromino_.reset();
		CurrTetromino_.reset();
		Board_.reset();

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

		StartPosition_ = Vec2i(9, 6);
		WaitPosition_ = Vec2i(19, 6);

		CurrTetromino_ = std::make_shared<Tetromino>(StartPosition_);
		CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

		NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

		Board_ = std::make_unique<Board>(Vec2i(5, 5), 12, 22);
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

			Update();
			Render();
		}
	}


private:
	/**
	 * ������ ������Ʈ�մϴ�.
	 */
	void Update()
	{
		const std::array<GameObject*, 2> Objects = {
			Board_.get(),
			CurrTetromino_.get()
		};

		for (auto& Object : Objects)
		{
			Object->Update(Timer_.GetDeltaTime());
		}

		if (CurrTetromino_->GetCurrentState() == Tetromino::EState::WAIT && Board_->GetCurrentState() == Board::EState::ACTIVE)
		{
			CurrTetromino_ = NextTetromino_;
			CurrTetromino_->SetConsolePosition(StartPosition_);
			CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

			NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

			if (CurrTetromino_->IsCollision())
			{
				bIsDone_ = true;
			}
		}
	}


	/**
	 * �ܼ� ȭ�鿡 �������� �����մϴ�.
	 */
	void Render()
	{
		const std::array<GameObject*, 3> Objects = {
			Board_.get(),
			CurrTetromino_.get(),
			NextTetromino_.get()
		};

		for (auto& Object : Objects)
		{
			Object->Render();
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
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 */
	Vec2i StartPosition_;

	
	/**
	 * ��Ʈ�ι̳��� ������Դϴ�.
	 */
	Vec2i WaitPosition_;
	

	/**
	 * ���� ��Ʈ�ι̳� �Դϴ�.
	 */
	std::shared_ptr<Tetromino> CurrTetromino_ = nullptr;


	/**
	 * ���� ��Ʈ�ι̳��Դϴ�.
	 */
	std::shared_ptr<Tetromino> NextTetromino_ = nullptr;


	/**
	 * ��Ʈ���� �����Դϴ�.
	 */
	std::unique_ptr<Board> Board_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}