#define _CRTDBG_MAP_ALLOC

#include <stdexcept>
#include <crtdbg.h>

#include "Console.h"

int main(void)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Console::_DrawText(10, 10, "Hello World", Console::ETextColor::BrightWhite);

	return 0;
}