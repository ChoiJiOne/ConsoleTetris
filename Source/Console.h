#pragma once

#include <string>

#if defined(WIN32) || defined(WIN64)
#undef DrawText
#endif


/**
 * 콘솔 관련 기능을 담당하는 클래스입니다.
 */
class Console
{
public:
	/**
	 * 콘솔의 텍스트 컬러입니다.
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
	 * 콘솔 창의 타이틀을 설정합니다.
	 * 
	 * @param InTitle - 설정할 콘솔 타이틀입니다.
	 * 
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void SetTitle(const std::string& InTitle);


	/**
	 * 콘솔 창의 텍스트 색상을 설정합니다.
	 * 
	 * @param InColor - 설정할 색상입니다.
	 * 
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void SetTextColor(const Console::ETextColor& InColor);


	/**
	 * 콘솔 창의 커서 시야 여부를 설정합니다.
	 * 
	 * @param bIsVisible - 콘솔 창의 커서 시야 여부입니다.
	 * 
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void SetCursorVisible(bool bIsVisible);


	/**
	 * 콘솔 창의 크기를 설정합니다.
	 * 
	 * @param InPositionX - 화면 상의 왼쪽 상단의 X좌표입니다.
	 * @param InPositionY - 화면 상의 왼쪽 상단의 Y좌표입니다.
	 * @param InWidth - 콘솔 창의 가로 크기입니다.
	 * @param InHeight - 콘솔 창의 세로 크기입니다.
	 * 
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void SetWindow(const int32_t& InPositionX, const int32_t& InPositionY, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 콘솔 창의 커서를 이동시킵니다.
	 * 
	 * @param InPositionX - 콘솔 상의 X좌표입니다.
	 * @param InPositionY - 콘솔 상의 Y좌표입니다.
	 * 
	 * @throws 커서 이동에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY);


	/**
	 * 콘솔 창을 초기화합니다.
	 * 
	 * @throws 콘솔 창 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void Clear();


	/**
	 * 콘솔 창에 텍스트를 그립니다.
	 * 
	 * @param InPositionX - 콘솔 상의 X좌표입니다.
	 * @param InPositionY - 콘솔 상의 Y좌표입니다.
	 * @param InText - 콘솔 창에 그릴 텍스트입니다.
	 * @param InColor - 텍스트의 색상입니다.
	 * 
	 * @throws 콘솔 창에 텍스트 그리기를 실패하면 C++ 표준 예외를 던집니다.
	 */
	static void DrawText(const int32_t& InPositionX, const int32_t& InPositionY, const std::string& InText, const ETextColor& InColor);
};
