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
		for (auto& tetromino : Tetrominos_)
		{
			tetromino.reset();
		}

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

		Vec2i Position(0, 0);
		for (const auto& Shape : Shapes)
		{
			auto NewTetromino = std::make_unique<Tetromino>(Position, Shape, EColor::AQUA);
			Tetrominos_.push_back(std::move(NewTetromino));

			Position.x += 4;
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
	}


	/**
	 * �ܼ� ȭ�鿡 �������� �����մϴ�.
	 */
	void Render()
	{
		for (auto& tetromino : Tetrominos_)
		{
			tetromino->Render();
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
	 * ��Ʈ�ι̳�� �Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>> Tetrominos_;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}