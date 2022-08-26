#include "Console.h"
#include "Macro.h"
#include "Block.h"

void Block::Draw(const Math::Vec2i& InPosition)
{
	if (Color == EColor::Empty)
	{
		return;
	}

	Console::ETextColor ConsoleColor = Console::ETextColor::Black;

	switch (Color)
	{
	case EColor::Blue:
		ConsoleColor = Console::ETextColor::Blue;
		break;

	case EColor::Green:
		ConsoleColor = Console::ETextColor::Green;
		break;

	case EColor::Aqua:
		ConsoleColor = Console::ETextColor::Aqua;
		break;

	case EColor::Red:
		ConsoleColor = Console::ETextColor::Red;
		break;

	case EColor::Purple:
		ConsoleColor = Console::ETextColor::Purple;
		break;

	case EColor::Yellow:
		ConsoleColor = Console::ETextColor::Yellow;
		break;

	case EColor::White:
		ConsoleColor = Console::ETextColor::White;
		break;

	case EColor::Gray:
		ConsoleColor = Console::ETextColor::Gray;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined color type");
		break;
	}

	Console::_DrawText(InPosition.x, InPosition.y, "бс", ConsoleColor);
}