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
		NextTetromino_.reset();
		CurrTetromino_.reset();
		Board_.reset();

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

		StartPosition_ = Vec2i(9, 6);
		WaitPosition_ = Vec2i(19, 6);

		CurrTetromino_ = std::make_shared<Tetromino>(StartPosition_);
		CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

		NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

		Board_ = std::make_unique<Board>(Vec2i(5, 5), 12, 22);
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
	 * 콘솔 화면에 렌더링을 수행합니다.
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
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone_ = false;


	/**
	 * 게임 타이머입니다.
	 */
	Timer Timer_;

	
	/**
	 * 테트로미노의 시작점입니다.
	 */
	Vec2i StartPosition_;

	
	/**
	 * 테트로미노의 대기점입니다.
	 */
	Vec2i WaitPosition_;
	

	/**
	 * 현재 테트로미노 입니다.
	 */
	std::shared_ptr<Tetromino> CurrTetromino_ = nullptr;


	/**
	 * 다음 테트로미노입니다.
	 */
	std::shared_ptr<Tetromino> NextTetromino_ = nullptr;


	/**
	 * 테트리스 보드입니다.
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