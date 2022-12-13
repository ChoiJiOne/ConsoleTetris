#include <Block.h>
#include <ConsoleManager.h>

void Block::Render(const Vec2i& InPosition) const
{
	Vec2i ConsolePosition = InPosition + Position_;
	EColor Color = static_cast<EColor>(Type_);
	std::string Text = (State_ == EState::EMPTY) ? "¡¤" : "¡á";
	
	ConsoleManager::Get().RenderText(ConsolePosition, Text, Color);
}