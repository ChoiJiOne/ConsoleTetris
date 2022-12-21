#include <Block.h>

void Block::Update(float InDeltaSeconds)
{
	// ���� �ƹ��� ������Ʈ�� ���� �ʽ��ϴ�.
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
		StateText = "��";
		break;

	case EState::FILL:
		StateText = "��";
		break;

	case EState::WALL:
		StateText = "��";
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined block state type...");
	}

	return StateText;
}
