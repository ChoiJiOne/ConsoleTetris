#include <Debug.h>
#include <InputManager.h>
#include <PlaySceneNode.h>
#include <StartSceneNode.h>
#include <ConsoleManager.h>
#include <Timer.h>
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
		StartSceneNode_.reset();
		PlaySceneNode_.reset();

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

		PlaySceneNode_ = std::make_unique<PlaySceneNode>();
		PlaySceneNode_->SetSwitchEvent([&]() { bIsDone_ = true; });
		PlaySceneNode_->Reset();

		StartSceneNode_ = std::make_unique<StartSceneNode>();
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
		//PlaySceneNode_->Update(Timer_.GetDeltaTime());
	}


	/**
	 * 콘솔 화면에 렌더링을 수행합니다.
	 */
	void Render()
	{
		//PlaySceneNode_->Render();
		StartSceneNode_->Render();
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
	 * 플레이 씬 노드입니다.
	 */
	std::unique_ptr<PlaySceneNode> PlaySceneNode_ = nullptr;


	/**
	 * 시작 씬 노드입니다.
	 */
	std::unique_ptr<StartSceneNode> StartSceneNode_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}