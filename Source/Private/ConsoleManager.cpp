#include <ConsoleManager.h>
#include <Json.h>

#include <iostream>
#include <windows.h>

void ConsoleManager::SetTitle(const std::string& InTitle)
{
	CHECK((system(Text::Format("title %s", InTitle.c_str()).c_str()) == 0), "failed to call system");
}

void ConsoleManager::SetTextColor(const EColor& InColor)
{
	CHECK(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InColor)), "failed to set text color");
}

void ConsoleManager::SetCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	CHECK(SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo), "failed to set cursor visible");
}

void ConsoleManager::SetWindow(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight)
{
	HWND ConsoleWindowHandle = GetConsoleWindow();
	RECT Rect = {
		InPosition.x,
		InPosition.y,
		InPosition.x + InWidth,
		InPosition.y + InHeight
	};

	CHECK(MoveWindow(ConsoleWindowHandle, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE), "failed to move console window");
}

void ConsoleManager::MoveCursor(const Vec2i& InPosition)
{
	COORD ConsolePosition = { static_cast<SHORT>(2 * InPosition.x), static_cast<SHORT>(InPosition.y) };

	CHECK(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsolePosition), "failed to move cursor");
}

void ConsoleManager::Clear()
{
	CHECK((system("cls") == 0), "failed to clear console");
}

void ConsoleManager::RenderText(const Vec2i& InPosition, const std::string& InText, const EColor& InColor)
{
	MoveCursor(InPosition);
	SetTextColor(InColor);

	std::cout << InText;
}

void ConsoleManager::RenderText(const Vec2i& InPosition, const std::wstring& InText, const EColor& InColor)
{
	MoveCursor(InPosition);
	SetTextColor(InColor);

	std::wcout << InText;
}

void ConsoleManager::SettingFromJson()
{
	Json Setting = LoadJsonFromFile("Setting.json");

	ConsoleManager::Get().Clear();
	ConsoleManager::Get().SetTitle(Setting["Title"]);
	ConsoleManager::Get().SetCursorVisible(Setting["CursorVisible"]);
}

ConsoleManager::~ConsoleManager()
{
	SetTextColor(EColor::WHITE);
}
