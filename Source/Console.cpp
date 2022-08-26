#include "StringUtil.h"
#include "Console.h"

void Console::SetConsoleTitle(const std::string& title)
{
	system(StringUtil::StringFormat("title %s", title.c_str()).c_str());
}

void Console::SetConsoleTextColor(Console::ETextColor color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void Console::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };

	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Console::SetConsoleWindow(int32_t x, int32_t y, int32_t width, int32_t height)
{
	HWND hWnd = GetConsoleWindow();
	RECT rect = { x, y, x + width, y + height };

	MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

void Console::MoveConsoleCursor(int32_t x, int32_t y)
{
	COORD position = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Console::ClearConsole()
{
	system("cls");
}

void Console::ShowTextInConsole(int32_t x, int32_t y, const std::string& text, Console::ETextColor color)
{
	MoveConsoleCursor(x, y);
	SetConsoleTextColor(color);

	std::cout << text;
}