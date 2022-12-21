#include <Block.h>

void Block::Update(float InDeltaSeconds)
{
	// 블럭은 아무런 업데이트도 하지 않습니다.
}

void Block::Render()
{
	ConsoleManager::Get().RenderText(Position_, Text_, Color_);
}

std::string Block::GetStateText(const EState& InState)
{
	std::string StateText;

	switch (InState)
	{
	case EState::EMPTY:
		StateText = "·";
		break;

	case EState::FILL:
		StateText = "■";
		break;

	case EState::WALL:
		StateText = "▩";
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined block state type...");
	}

	return StateText;
}
