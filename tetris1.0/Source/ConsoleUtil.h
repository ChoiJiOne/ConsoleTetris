#pragma once

#include "Common.h"

enum class EConsoleTextColor : int32_t
{
	Black       = 0,
	Blue        = 1,
	Green       = 2,
	Aqua        = 3,
	Red         = 4,
	Purple      = 5,
	Yellow      = 6,
	White       = 7,
	Gray        = 8,
	LightBlue   = 9,
	LightGreen  = 10,
	LightAqua   = 11,
	LightRed    = 12,
	LightPurple = 13,
	LightYellow = 14,
	BrightWhite = 15
};

class ConsoleUtil
{
public:
	static void SetConsoleTitle(const std::string& title);
	static void SetConsoleTextColor(EConsoleTextColor color);
	static void SetConsoleCursorVisible(bool bIsVisible);
	static void MoveConsoleCursor(int32_t x, int32_t y);
	static void ClearConsole();
	static void ShowTextInConsole(int32_t x, int32_t y, const std::string& text, EConsoleTextColor color);
};
