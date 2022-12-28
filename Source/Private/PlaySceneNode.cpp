#include <PlaySceneNode.h>
#include <InputManager.h>
#include <GameObject.h>
#include <Board.h>
#include <Tetromino.h>

#include <array>

std::unordered_map<PlaySceneNode::ELevel, const float> PlaySceneNode::LevelToMaxAccrueTime_ = {
	{ PlaySceneNode::ELevel::LEVEL1, 1.0f },
	{ PlaySceneNode::ELevel::LEVEL2, 0.8f },
	{ PlaySceneNode::ELevel::LEVEL3, 0.6f },
	{ PlaySceneNode::ELevel::LEVEL4, 0.4f },
	{ PlaySceneNode::ELevel::LEVEL5, 0.2f },
	{ PlaySceneNode::ELevel::LEVEL6, 0.1f },
};

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

	PlayTime_ = 0.0f;
	PlayTimePosition_ = Vec2i(15, 10);

	RemoveLinePosition_ = Vec2i(15, 12);

	Level_ = ELevel::LEVEL1;
	PlayerLevelPosition_ = Vec2i(15, 14);
	Tetromino::SetMaxAccrueTime(LevelToMaxAccrueTime_[Level_]);

	StartPosition_ = Vec2i(6, 3);
	WaitPosition_ = Vec2i(15, 3);

	CurrTetromino_ = std::make_shared<Tetromino>(StartPosition_);
	CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

	NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

	Board_ = std::make_unique<Board>(Vec2i(2, 2), 12, 22);
}

void PlaySceneNode::Update(float InDeltaSeconds)
{
	PlayTime_ += InDeltaSeconds;

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

	ConsoleManager::Get().RenderText(
		PlayTimePosition_,
		Text::Format("TIME  %3d", static_cast<int32_t>(PlayTime_)),
		EColor::AQUA
	);

	ConsoleManager::Get().RenderText(
		RemoveLinePosition_,
		Text::Format("LINE  %3d", Board_->GetRemoveLine()), 
		EColor::AQUA
	);

	ConsoleManager::Get().RenderText(
		PlayerLevelPosition_,
		Text::Format("LEVEL %3d", static_cast<int32_t>(Level_)),
		EColor::AQUA
	);
}

void PlaySceneNode::CleanupAllProperties()
{
	if(NextTetromino_) NextTetromino_.reset();
	if(CurrTetromino_) CurrTetromino_.reset();
	if(Board_) Board_.reset();
}
