#include "StringUtil.h"
#include "ConsoleUtil.h"

void ConsoleUtil::SetConsoleTitle(const std::string& title)
{
	system(StringUtil::StringFormat("title %s", title.c_str()).c_str());
}

void ConsoleUtil::SetConsoleTextColor(EConsoleTextColor color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void ConsoleUtil::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };

	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ConsoleUtil::SetConsoleWindow(int32_t x, int32_t y, int32_t width, int32_t height)
{
	HWND hWnd = GetConsoleWindow();
	RECT rect = { x, y, x + width, y + height };

	MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

void ConsoleUtil::MoveConsoleCursor(int32_t x, int32_t y)
{
	COORD position = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void ConsoleUtil::ClearConsole()
{
	system("cls");
}

void ConsoleUtil::ShowTextInConsole(int32_t x, int32_t y, const std::string& text, EConsoleTextColor color)
{
	MoveConsoleCursor(x, y);
	SetConsoleTextColor(color);

	std::cout << text;
}