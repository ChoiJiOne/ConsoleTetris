#define _CRTDBG_MAP_ALLOC

#include <stdexcept>
#include <crtdbg.h>

#include "Game.h"

int main(void)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		std::unique_ptr<Game> Tetris = std::make_unique<Game>();
		Tetris->Init();
		Tetris->Run();
	}
	catch (const std::exception& Exception)
	{
		Console::Clear();
		Console::DrawText(0, 0, Exception.what(), Console::ETextColor::Red);
	}

	return 0;
}