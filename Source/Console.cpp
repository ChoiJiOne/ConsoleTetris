#include <iostream>
#include <Windows.h>

#include "Macro.h"
#include "Console.h"

void Console::_SetTitle(const std::string& InTitle)
{
	CHECK(system(Text::Format("title %s", InTitle.c_str()).c_str()), "failed to call system");
}

void Console::_SetTextColor(const Console::ETextColor& InColor)
{
	CHECK(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InColor)), "failed to set text color");
}

void Console::_SetCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	CHECK(SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo), "failed to set cursor visible");
}

void Console::_SetWindow(const int32_t& InPositionX, const int32_t& InPositionY, const int32_t& InWidth, const int32_t& InHeight)
{
	HWND ConsoleWindowHandle = GetConsoleWindow();
	RECT Rect = { 
		InPositionX, 
		InPositionY, 
		InPositionX + InWidth,
		InPositionY + InHeight
	};

	CHECK(MoveWindow(ConsoleWindowHandle, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE), "failed to move console window");
}

void Console::_MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY)
{
	COORD ConsolePosition = { static_cast<SHORT>(2 * InPositionX), static_cast<SHORT>(InPositionY) };

	CHECK(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsolePosition), "failed to move cursor");
}

void Console::_Clear()
{
	CHECK(system("cls"), "failed to clear console");
}

void Console::_DrawText(const int32_t& InPositionX, const int32_t& InPositionY, const std::string& InText, const ETextColor& InColor)
{
	_MoveCursor(InPositionX, InPositionY);
	_SetTextColor(InColor);

	std::cout << InText;
}
