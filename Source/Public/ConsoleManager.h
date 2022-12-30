#pragma once

#include <Vector.hpp>
#include <Macro.h>

#include <string>


/**
 * �ܼ��� �ؽ�Ʈ �÷��Դϴ�.
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
 * �ܼ� â�� ���õ� ó���� �����ϴ� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ �̱����Դϴ�.
 */
class ConsoleManager
{
public:
	/**
	 * ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ConsoleManager);


	/**
	 * ConsoleManager�� �̱� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return ConsoleManager�� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static ConsoleManager& Get()
	{
		static ConsoleManager Instance;
		return Instance;
	}


	/**
	 * �ܼ� â�� Ÿ��Ʋ�� �����մϴ�.
	 *
	 * @param InTitle - ������ �ܼ� Ÿ��Ʋ�Դϴ�.
	 *
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetTitle(const std::string& InTitle);


	/**
	 * �ܼ� â�� �ؽ�Ʈ ������ �����մϴ�.
	 *
	 * @param InColor - ������ �����Դϴ�.
	 *
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetTextColor(const EColor& InColor);


	/**
	 * �ܼ� â�� Ŀ�� �þ� ���θ� �����մϴ�.
	 *
	 * @param bIsVisible - �ܼ� â�� Ŀ�� �þ� �����Դϴ�.
	 *
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetCursorVisible(bool bIsVisible);


	/**
	 * �ܼ� â�� ũ�⸦ �����մϴ�.
	 *
	 * @param InPosition - ȭ�� ���� ���� ��� ��ǥ�Դϴ�.
	 * @param InWidth - �ܼ� â�� ���� ũ���Դϴ�.
	 * @param InHeight - �ܼ� â�� ���� ũ���Դϴ�.
	 *
	 * @throws ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void SetWindow(const Vec2i& InPosition, const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * �ܼ� â�� Ŀ���� �̵���ŵ�ϴ�.
	 *
	 * @param InPosition - �ܼ� ���� ��ǥ�Դϴ�.
	 *
	 * @throws Ŀ�� �̵��� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void MoveCursor(const Vec2i& InPosition);


	/**
	 * �ܼ� â�� �ʱ�ȭ�մϴ�.
	 *
	 * @throws �ܼ� â �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Clear();


	/**
	 * �ܼ� â�� �ؽ�Ʈ�� �׸��ϴ�.
	 * 
	 * @param InPosition - �ܼ� ���� ��ǥ�Դϴ�.
	 * @param InText - �ܼ� â�� �׸� �ؽ�Ʈ�Դϴ�.
	 * @param InColor - �ؽ�Ʈ�� �����Դϴ�.
	 * 
	 * @throws �ܼ� â�� �ؽ�Ʈ �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void RenderText(const Vec2i& InPosition, const std::string& InText, const EColor& InColor);


	/**
	 * �ܼ� â�� �ؽ�Ʈ�� �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ���� ��ǥ�Դϴ�.
	 * @param InText - �ܼ� â�� �׸� �ؽ�Ʈ�Դϴ�.
	 * @param InColor - �ؽ�Ʈ�� �����Դϴ�.
	 *
	 * @throws �ܼ� â�� �ؽ�Ʈ �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
     */
	void RenderText(const Vec2i& InPosition, const std::wstring& InText, const EColor& InColor);


	/**
	 * Setting.Info ������ ������� ������ �����մϴ�.
	 */
	void SettingFromInfoFile();
	

private:
	/**
	 * ConsoleManager�� �������Դϴ�.
	 */
	ConsoleManager() = default;


	/**
	 * ConsoleManager�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ConsoleManager();
};