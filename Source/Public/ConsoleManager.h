#pragma once

#include <Vector.hpp>
#include <Macro.h>

#include <string>


/**
 * 콘솔의 텍스트 컬러입니다.
 */
enum class EColor : int32_t
{
	BLACK       = 0,
	BLUE        = 1,
	GREEN       = 2,
	AQUA        = 3,
	RED         = 4,
	PURPLE      = 5,
	YELLOW      = 6,
	WHITE       = 7,
	GRAY        = 8,
	LIGHTBLUE   = 9,
	LIGHTGREEN  = 10,
	LIGHTAQUA   = 11,
	LIGHTRED    = 12,
	LIGHTPURPLE = 13,
	LIGHTYELLOW = 14,
	BRIGHTWHITE = 15
};


/**
 * 콘솔 창에 관련된 처리를 수행하는 클래스입니다.
 * 이때, 이 클래스는 싱글턴입니다.
 */
class ConsoleManager
{
public:
	/**
	 * 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ConsoleManager);


	/**
	 * ConsoleManager의 싱글 인스턴스를 얻습니다.
	 * 
	 * @return ConsoleManager의 인스턴스를 반환합니다.
	 */
	static ConsoleManager& Get()
	{
		static ConsoleManager Instance;
		return Instance;
	}


	/**
	 * 콘솔 창의 타이틀을 설정합니다.
	 *
	 * @param InTitle - 설정할 콘솔 타이틀입니다.
	 *
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void SetTitle(const std::string& InTitle);


	/**
	 * 콘솔 창의 텍스트 색상을 설정합니다.
	 *
	 * @param InColor - 설정할 색상입니다.
	 *
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void SetTextColor(const EColor& InColor);


	/**
	 * 콘솔 창의 커서 시야 여부를 설정합니다.
	 *
	 * @param bIsVisible - 콘솔 창의 커서 시야 여부입니다.
	 *
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void SetCursorVisible(bool bIsVisible);


	/**
	 * 콘솔 창의 크기를 설정합니다.
	 *
	 * @param InPosition - 화면 상의 왼쪽 상단 좌표입니다.
	 * @param InWidth - 콘솔 창의 가로 크기입니다.
	 * @param InHeight - 콘솔 창의 세로 크기입니다.
	 *
	 * @throws 설정에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void SetWindow(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 콘솔 창의 커서를 이동시킵니다.
	 *
	 * @param InPosition - 콘솔 상의 좌표입니다.
	 *
	 * @throws 커서 이동에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void MoveCursor(const Vec2i& InPosition);


	/**
	 * 콘솔 창을 초기화합니다.
	 *
	 * @throws 콘솔 창 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Clear();


	/**
	 * 콘솔 창에 텍스트를 그립니다.
	 * 
	 * @param InPosition - 콘솔 상의 좌표입니다.
	 * @param InText - 콘솔 창에 그릴 텍스트입니다.
	 * @param InColor - 텍스트의 색상입니다.
	 * 
	 * @throws 콘솔 창에 텍스트 그리기를 실패하면 C++ 표준 예외를 던집니다.
	 */
	void RenderText(const Vec2i& InPosition, const std::string& InText, const EColor& InColor);


	/**
	 * 콘솔 창에 텍스트를 그립니다.
	 *
	 * @param InPosition - 콘솔 상의 좌표입니다.
	 * @param InText - 콘솔 창에 그릴 텍스트입니다.
	 * @param InColor - 텍스트의 색상입니다.
	 *
	 * @throws 콘솔 창에 텍스트 그리기를 실패하면 C++ 표준 예외를 던집니다.
     */
	void RenderText(const Vec2i& InPosition, const std::wstring& InText, const EColor& InColor);


	/**
	 * Setting.Info 파일을 기반으로 세팅을 수행합니다.
	 */
	void SettingFromInfoFile();
	

private:
	/**
	 * ConsoleManager의 생성자입니다.
	 */
	ConsoleManager() = default;


	/**
	 * ConsoleManager의 가상 소멸자입니다.
	 */
	virtual ~ConsoleManager();
};