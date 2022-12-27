#include <Debug.h>
#include <InputManager.h>
#include <DoneSceneNode.h>
#include <PlaySceneNode.h>
#include <StartSceneNode.h>
#include <PauseSceneNode.h>
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
		DoneSceneNode_.reset();
		PauseSceneNode_.reset();
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
		PlaySceneNode_->SetSwitchEvent([&]() { 
			ConsoleManager::Get().Clear();

			if (InputManager::Get().GetKeyPressState(EKeyCode::ESCAPE) == EPressState::PRESSED)
			{
				CurrentSceneNode_ = PauseSceneNode_.get();
			}
			else
			{
				CurrentSceneNode_ = DoneSceneNode_.get();
			}
		});

		StartSceneNode_ = std::make_unique<StartSceneNode>();
		StartSceneNode_->SetSwitchEvent([&]() {
			ConsoleManager::Get().Clear();
			const std::string& SelectMenu = StartSceneNode_->GetCurrentSelectMenu();

			if (SelectMenu.compare("START") == 0)
			{
				PlaySceneNode_->Reset();
				CurrentSceneNode_ = PlaySceneNode_.get();
			}

			if (SelectMenu.compare("QUIT") == 0)
			{
				bIsDone_ = true;
			}
		});

		PauseSceneNode_ = std::make_unique<PauseSceneNode>();
		PauseSceneNode_->SetSwitchEvent([&]() {
			ConsoleManager::Get().Clear();
			const std::string& SelectMenu = PauseSceneNode_->GetCurrentSelectMenu();

			if (SelectMenu.compare("RESET") == 0)
			{
				CurrentSceneNode_ = StartSceneNode_.get();
			}

			if (SelectMenu.compare("CONTINUE") == 0)
			{
				CurrentSceneNode_ = PlaySceneNode_.get();
			}

			if (SelectMenu.compare("QUIT") == 0)
			{
				bIsDone_ = true;
			}
		});

		DoneSceneNode_ = std::make_unique<DoneSceneNode>();
		DoneSceneNode_->SetSwitchEvent([&]() {
			ConsoleManager::Get().Clear();
			const std::string& SelectMenu = DoneSceneNode_->GetCurrentSelectMenu();

			if (SelectMenu.compare("RESTART") == 0)
			{
				CurrentSceneNode_ = StartSceneNode_.get();
			}

			if (SelectMenu.compare("QUIT") == 0)
			{
				bIsDone_ = true;
			}
		});

		CurrentSceneNode_ = StartSceneNode_.get();
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
		CurrentSceneNode_->Update(Timer_.GetDeltaTime());
	}


	/**
	 * 콘솔 화면에 렌더링을 수행합니다.
	 */
	void Render()
	{
		CurrentSceneNode_->Render();
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
	 * 현재 씬 노드입니다.
	 */
	SceneNode* CurrentSceneNode_ = nullptr;

	
	/**
	 * 플레이 씬 노드입니다.
	 */
	std::unique_ptr<PlaySceneNode> PlaySceneNode_ = nullptr;


	/**
	 * 시작 씬 노드입니다.
	 */
	std::unique_ptr<StartSceneNode> StartSceneNode_ = nullptr;

	
	/**
	 * 중지 씬 노드입니다.
	 */
	std::unique_ptr<PauseSceneNode> PauseSceneNode_ = nullptr;


	/**
	 * 종료 씬 노드입니다.
	 */
	std::unique_ptr<DoneSceneNode> DoneSceneNode_ = nullptr;
};


int main(void)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}