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

		std::array<Tetromino::EShape, 7> Shapes = {
			Tetromino::EShape::I,
			Tetromino::EShape::O,
			Tetromino::EShape::T,
			Tetromino::EShape::J,
			Tetromino::EShape::L,
			Tetromino::EShape::S,
			Tetromino::EShape::Z
		};

		Tetromino_ = std::make_unique<Tetromino>(Vec2i(0, 0), Tetromino::EShape::L, EColor::GRAY);
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
		if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().Clear();
			Tetromino_->Move(Tetromino::EMovement::LEFT);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::RIGHT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().Clear();
			Tetromino_->Move(Tetromino::EMovement::RIGHT);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::UP) == EPressState::PRESSED)
		{
			ConsoleManager::Get().Clear();
			Tetromino_->Move(Tetromino::EMovement::UP);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
		{
			ConsoleManager::Get().Clear();
			Tetromino_->Move(Tetromino::EMovement::DOWN);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::SPACE) == EPressState::PRESSED)
		{
			ConsoleManager::Get().Clear();
			Tetromino_->Move(Tetromino::EMovement::CW);
		}
	}


	/**
	 * �ܼ� ȭ�鿡 �������� �����մϴ�.
	 */
	void Render()
	{
		Tetromino_->Render();
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
	 * ��Ʈ�ι̳� �Դϴ�.
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