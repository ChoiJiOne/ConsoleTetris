#include "Console.h"
#include "Macro.h"
#include "Block.h"

std::unordered_map<Block::EColor, Console::ETextColor> Block::BlockColorMappings = {
	{EColor::Blue,   Console::ETextColor::Blue   },
	{EColor::Green,  Console::ETextColor::Green  },
	{EColor::Aqua,   Console::ETextColor::Aqua   },
	{EColor::Red,    Console::ETextColor::Red    },
	{EColor::Purple, Console::ETextColor::Purple },
	{EColor::Yellow, Console::ETextColor::Yellow },
	{EColor::White,  Console::ETextColor::White  },
	{EColor::Gray,   Console::ETextColor::Gray   } 
	
};

void Block::Draw(const Vec2i& InPosition)
{
	Console::ETextColor ConsoleColor = Console::ETextColor::Black;

	if (Color_ == EColor::None)
	{
		Console::DrawText(InPosition.x, InPosition.y, "  ", ConsoleColor);
		return;
	}

	ConsoleColor = BlockColorMappings.at(Color_);
	Console::DrawText(InPosition.x, InPosition.y, "бс", ConsoleColor);
}