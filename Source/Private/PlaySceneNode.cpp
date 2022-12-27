#include <PlaySceneNode.h>
#include <InputManager.h>
#include <GameObject.h>
#include <Board.h>
#include <Tetromino.h>

#include <array>

PlaySceneNode::PlaySceneNode()
	: SceneNode("PlayScene")
{
}

PlaySceneNode::~PlaySceneNode()
{
	CleanupAllProperties();
}

void PlaySceneNode::Reset()
{
	CleanupAllProperties();

	StartPosition_ = Vec2i(9, 6);
	WaitPosition_ = Vec2i(19, 6);

	CurrTetromino_ = std::make_shared<Tetromino>(StartPosition_);
	CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

	NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

	Board_ = std::make_unique<Board>(Vec2i(5, 5), 12, 22);
}

void PlaySceneNode::Update(float InDeltaSeconds)
{
	if (InputManager::Get().GetKeyPressState(EKeyCode::ESCAPE) == EPressState::PRESSED)
	{
		RunSwitchEvent();
	}

	const std::array<GameObject*, 2> Objects = {
			Board_.get(),
			CurrTetromino_.get()
	};

	for (auto& Object : Objects)
	{
		Object->Update(InDeltaSeconds);
	}

	if (CurrTetromino_->GetCurrentState() == Tetromino::EState::WAIT && Board_->GetCurrentState() == Board::EState::ACTIVE)
	{
		CurrTetromino_ = NextTetromino_;
		CurrTetromino_->SetConsolePosition(StartPosition_);
		CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

		NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

		if (CurrTetromino_->IsCollision())
		{
			RunSwitchEvent();
		}
	}
}

void PlaySceneNode::Render()
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

void PlaySceneNode::CleanupAllProperties()
{
	if(NextTetromino_) NextTetromino_.reset();
	if(CurrTetromino_) CurrTetromino_.reset();
	if(Board_) Board_.reset();
}
