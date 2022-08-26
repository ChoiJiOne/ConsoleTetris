#pragma once

#include "Common.h"

/**
 * �ܼ� ���� ����� ����ϴ� Ŭ�����Դϴ�.
 */
class Console
{
public:
	/**
	 * �ܼ��� �ؽ�Ʈ �÷��Դϴ�.
	 */
	enum class ETextColor : int32_t
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

public:
	/**
	 * 
	 */
	static void SetConsoleTitle(const std::string& title);


	/**
	 * 
	 */
	static void SetConsoleTextColor(Console::ETextColor color);


	/**
	 * 
	 */
	static void SetConsoleCursorVisible(bool bIsVisible);


	/**
	 * 
	 */
	static void SetConsoleWindow(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * 
	 */
	static void MoveConsoleCursor(int32_t x, int32_t y);


	/**
	 * 
	 */
	static void ClearConsole();


	/**
	 * 
	 */
	static void ShowTextInConsole(int32_t x, int32_t y, const std::string& text, Console::ETextColor color);
};
