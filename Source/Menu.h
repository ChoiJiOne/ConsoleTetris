#pragma once

#include "Console.h"
#include "Mathematics.h"

#include <vector>
#include <string>
#include <algorithm>


/**
 * �޴� Ŭ�����Դϴ�.
 */
class Menu
{
public:
	/**
	 * �޴� ��� ������ �����Դϴ�.
	 */
	enum class ESelectDirection
	{
		Up   = 0,
		Down = 1
	};


public:
	/**
	 * �޴� Ŭ������ �������Դϴ�.
	 * 
	 * @param InSelectColor - �޴� �� �� ��Ҹ� �������� ���� �����Դϴ�.
	 * @param InNormalColor - �޴� �� �� ��Ҹ� �������� �ʾ��� ���� �����Դϴ�.
	 */
	explicit Menu(
		const Console::ETextColor& InSelectColor,
		const Console::ETextColor& InNormalColor
	);


	/**
	 * �޴� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Menu(Menu&& InInstance) noexcept;


	/**
	 * �޴� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 */
	Menu(const Menu& InInstance) noexcept;


	/**
	 * �޴� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Menu();


	/**
	 * �޴� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 * 
	 * @return ���縦 ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Menu& operator=(Menu&& InInstance) noexcept;


	/**
	 * �޴� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param InInstance - ���縦 ������ ��ü�Դϴ�.
	 *
	 * @return ���縦 ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Menu& operator=(const Menu& InInstance) noexcept;

	
	/**
	 * �޴��� ��Ҹ� �߰��մϴ�.
	 * 
	 * @param InName - �߰��� �޴� ����� �̸��Դϴ�.
	 */
	void AddElement(const std::string& InName);


	/**
	 * ���� ���õ� ��Ҹ� ����ϴ�.
	 */
	const std::string& GetCurrentSelectElement() const;


	/**
	 * ���� ���õ� ��Ҹ� �̵��մϴ�.
	 * 
	 * @param InSelectDirection ���� �̵� �����Դϴ�.
	 */
	void MoveSelect(const ESelectDirection& InSelectDirection);


	/**
	 * �޴��� �ܼ� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param InPosition - �ܼ� ȭ����� �޴��� ���� ��� ��ǥ�Դϴ�.
	 *
	 * @throws �ܼ� ȭ�鿡 �׸��⸦ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Draw(const Math::Vec2i& InPosition);


private:
	/**
	 * �޴� ���� ��ҵ��Դϴ�.
	 */
	std::vector<std::string> Elements;


	/**
	 * ���� ���� ���� �޴� ����Դϴ�.
	 */
	int32_t CurrentSelectElement;


	/**
	 * �޴� �� �� ��Ҹ� �������� ���� �����Դϴ�.
	 */
	Console::ETextColor SelectColor;


	/**
	 * �޴� �� �� ��Ҹ� �������� �ʾ��� ���� �����Դϴ�.
	 */
	Console::ETextColor NormalColor;
};