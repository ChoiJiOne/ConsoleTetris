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
		DoneSceneNode_.reset();
		PauseSceneNode_.reset();
		StartSceneNode_.reset();
		PlaySceneNode_.reset();

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
		CurrentSceneNode_->Update(Timer_.GetDeltaTime());
	}


	/**
	 * �ܼ� ȭ�鿡 �������� �����մϴ�.
	 */
	void Render()
	{
		CurrentSceneNode_->Render();
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
	 * ���� �� ����Դϴ�.
	 */
	SceneNode* CurrentSceneNode_ = nullptr;

	
	/**
	 * �÷��� �� ����Դϴ�.
	 */
	std::unique_ptr<PlaySceneNode> PlaySceneNode_ = nullptr;


	/**
	 * ���� �� ����Դϴ�.
	 */
	std::unique_ptr<StartSceneNode> StartSceneNode_ = nullptr;

	
	/**
	 * ���� �� ����Դϴ�.
	 */
	std::unique_ptr<PauseSceneNode> PauseSceneNode_ = nullptr;


	/**
	 * ���� �� ����Դϴ�.
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