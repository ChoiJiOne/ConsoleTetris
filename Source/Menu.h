#pragma once

#include "Console.h"
#include "Mathematics.h"

#include <vector>
#include <string>
#include <algorithm>


/**
 * 메뉴 클래스입니다.
 */
class Menu
{
public:
	/**
	 * 메뉴 요소 선택의 방향입니다.
	 */
	enum class ESelectDirection
	{
		Up   = 0,
		Down = 1
	};


public:
	/**
	 * 메뉴 클래스의 생성자입니다.
	 * 
	 * @param InSelectColor - 메뉴 중 한 요소를 선택했을 때의 색상입니다.
	 * @param InNormalColor - 메뉴 중 한 요소를 선택하지 않았을 떄의 생상입니다.
	 */
	explicit Menu(
		const Console::ETextColor& InSelectColor,
		const Console::ETextColor& InNormalColor
	);


	/**
	 * 메뉴 클래스의 복사 생성자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Menu(Menu&& InInstance) noexcept;


	/**
	 * 메뉴 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 객체입니다.
	 */
	Menu(const Menu& InInstance) noexcept;


	/**
	 * 메뉴 클래스의 가상 소멸자입니다.
	 */
	virtual ~Menu();


	/**
	 * 메뉴 클래스의 대입 연산자입니다.
	 * 
	 * @param InInstance - 복사를 수행할 객체입니다.
	 * 
	 * @return 복사를 수행한 객체의 참조자를 반환합니다.
	 */
	Menu& operator=(Menu&& InInstance) noexcept;


	/**
	 * 메뉴 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 객체입니다.
	 *
	 * @return 복사를 수행한 객체의 참조자를 반환합니다.
	 */
	Menu& operator=(const Menu& InInstance) noexcept;

	
	/**
	 * 메뉴의 요소를 추가합니다.
	 * 
	 * @param InName - 추가할 메뉴 요소의 이름입니다.
	 */
	void AddElement(const std::string& InName);


	/**
	 * 현재 선택된 요소를 얻습니다.
	 */
	const std::string& GetCurrentSelectElement() const;


	/**
	 * 현재 선택된 요소를 이동합니다.
	 * 
	 * @param InSelectDirection 선택 이동 방향입니다.
	 */
	void MoveSelect(const ESelectDirection& InSelectDirection);


	/**
	 * 메뉴를 콘솔 화면에 그립니다.
	 * 
	 * @param InPosition - 콘솔 화면상의 메뉴의 왼쪽 상단 좌표입니다.
	 *
	 * @throws 콘솔 화면에 그리기를 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Draw(const Math::Vec2i& InPosition);


private:
	/**
	 * 메뉴 내의 요소들입니다.
	 */
	std::vector<std::string> Elements;


	/**
	 * 현재 선택 중인 메뉴 요소입니다.
	 */
	int32_t CurrentSelectElement;


	/**
	 * 메뉴 중 한 요소를 선택했을 때의 색상입니다.
	 */
	Console::ETextColor SelectColor;


	/**
	 * 메뉴 중 한 요소를 선택하지 않았을 때의 색상입니다.
	 */
	Console::ETextColor NormalColor;
};