#pragma once

#include <string>

#if defined(WIN32) || defined(WIN64)
#undef DrawText
#endif


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
	 * �ܼ� â�� Ÿ��Ʋ�� �����մϴ�.
	 * 
	 * @param InTitle - ������ �ܼ� Ÿ��Ʋ�Դϴ�.
	 * 
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void SetTitle(const std::string& InTitle);


	/**
	 * �ܼ� â�� �ؽ�Ʈ ������ �����մϴ�.
	 * 
	 * @param InColor - ������ �����Դϴ�.
	 * 
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void SetTextColor(const Console::ETextColor& InColor);


	/**
	 * �ܼ� â�� Ŀ�� �þ� ���θ� �����մϴ�.
	 * 
	 * @param bIsVisible - �ܼ� â�� Ŀ�� �þ� �����Դϴ�.
	 * 
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void SetCursorVisible(bool bIsVisible);


	/**
	 * �ܼ� â�� ũ�⸦ �����մϴ�.
	 * 
	 * @param InPositionX - ȭ�� ���� ���� ����� X��ǥ�Դϴ�.
	 * @param InPositionY - ȭ�� ���� ���� ����� Y��ǥ�Դϴ�.
	 * @param InWidth - �ܼ� â�� ���� ũ���Դϴ�.
	 * @param InHeight - �ܼ� â�� ���� ũ���Դϴ�.
	 * 
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void SetWindow(const int32_t& InPositionX, const int32_t& InPositionY, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * �ܼ� â�� Ŀ���� �̵���ŵ�ϴ�.
	 * 
	 * @param InPositionX - �ܼ� ���� X��ǥ�Դϴ�.
	 * @param InPositionY - �ܼ� ���� Y��ǥ�Դϴ�.
	 * 
	 * @throws Ŀ�� �̵��� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY);


	/**
	 * �ܼ� â�� �ʱ�ȭ�մϴ�.
	 * 
	 * @throws �ܼ� â �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void Clear();


	/**
	 * �ܼ� â�� �ؽ�Ʈ�� �׸��ϴ�.
	 * 
	 * @param InPositionX - �ܼ� ���� X��ǥ�Դϴ�.
	 * @param InPositionY - �ܼ� ���� Y��ǥ�Դϴ�.
	 * @param InText - �ܼ� â�� �׸� �ؽ�Ʈ�Դϴ�.
	 * @param InColor - �ؽ�Ʈ�� �����Դϴ�.
	 * 
	 * @throws �ܼ� â�� �ؽ�Ʈ �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	static void DrawText(const int32_t& InPositionX, const int32_t& InPositionY, const std::string& InText, const ETextColor& InColor);
};
