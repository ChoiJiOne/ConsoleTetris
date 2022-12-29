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
	PlayTimePosition_ = GetUIPosition("Time");

	RemoveLinePosition_ = GetUIPosition("Line");

	Level_ = ELevel::LEVEL1;
	AccruePlayTime_ = 0.0f;
	PlayerLevelPosition_ = GetUIPosition("Level");
	Tetromino::SetMaxAccrueTime(LevelToMaxAccrueTime_[Level_]);

	BoardPosition_ = GetUIPosition("Board");
	StartPosition_ = GetUIPosition("Start");
	WaitPosition_ = GetUIPosition("Wait");

	CurrTetromino_ = std::make_shared<Tetromino>(StartPosition_);
	CurrTetromino_->SetCurrentState(Tetromino::EState::ACTIVE);

	NextTetromino_ = std::make_shared<Tetromino>(WaitPosition_);

	Board_ = std::make_unique<Board>(BoardPosition_, 12, 22);
}

int32_t PlaySceneNode::GetRemoveLine() const
{
	return Board_->GetRemoveLine();
}

void PlaySceneNode::Update(float InDeltaSeconds)
{
	PlayTime_ += InDeltaSeconds;
	AccruePlayTime_ += InDeltaSeconds;

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

	if (AccruePlayTime_ >= 30.0f && Level_ != ELevel::LEVEL6)
	{
		AccruePlayTime_ = 0.0f;
		Level_ = static_cast<ELevel>(static_cast<int32_t>(Level_) + 1);
		Tetromino::SetMaxAccrueTime(LevelToMaxAccrueTime_[Level_]);
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
		Vec2i(WaitPosition_.x, WaitPosition_.y - 1),
		"NEXT",
		EColor::AQUA
	);

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
