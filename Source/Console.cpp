#include <iostream>
#include <Windows.h>

#include "Macro.h"
#include "Console.h"

void Console::SetTitle(const std::string& InTitle)
{
	CHECK((system(Text::Format("title %s", InTitle.c_str()).c_str()) == 0), "failed to call system");
}

void Console::SetTextColor(const Console::ETextColor& InColor)
{
	CHECK(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InColor)), "failed to set text color");
}

void Console::SetCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	CHECK(SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo), "failed to set cursor visible");
}

void Console::SetWindow(const int32_t& InPositionX, const int32_t& InPositionY, const int32_t& InWidth, const int32_t& InHeight)
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

void Console::MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY)
{
	COORD ConsolePosition = { static_cast<SHORT>(2 * InPositionX), static_cast<SHORT>(InPositionY) };

	CHECK(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsolePosition), "failed to move cursor");
}

void Console::Clear()
{
	CHECK((system("cls") == 0), "failed to clear console");
}

void Console::DrawText(const int32_t& InPositionX, const int32_t& InPositionY, const std::string& InText, const ETextColor& InColor)
{
	MoveCursor(InPositionX, InPositionY);
	SetTextColor(InColor);

	std::cout << InText;
}
