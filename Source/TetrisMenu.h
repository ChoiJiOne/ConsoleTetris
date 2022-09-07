#pragma once

#include "Menu.h"

#include <unordered_map>
#include <memory>


/**
 * 테트리스 메뉴 리스트 클래스입니다.
 */
class TetrisMenu
{
public:
	/**
	 * 테트리스 메뉴 상태입니다.
	 */
	enum class EMenuState
	{
		Start  = 0,
		Select = 1,
		Play   = 2,
		Paused = 3,
		Done   = 4,
	};


public:
	/**
	 * 테트리스 메뉴 리스트 클래스의 생성자입니다.
	 * 이때, 초기화를 수행하기 위해서는 Init 메서드를 호출해야 합니다.
	 */
	explicit TetrisMenu() = default;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	TetrisMenu(TetrisMenu&& InInstance) = delete;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	TetrisMenu(const TetrisMenu& InInstance) = delete;


	/**
	 * 테트리스 게임 클래스의 소멸자입니다.
	 */
	virtual ~TetrisMenu();


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	TetrisMenu& operator=(TetrisMenu&& InInstance) = delete;


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	TetrisMenu& operator=(const TetrisMenu& InInstance) = delete;


	/**
	 * 테트리스 메뉴를 초기화합니다.
	 *
	 * @throws 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Init();


	/**
	 * 테트리스 메뉴를 입력을 처리합니다.
	 *
	 * @param InInput - 키 상태를 관리하는 입력 시스템입니다.
	 */
	void ProcessInput(const Input & InInput);


	/**
	 * 테트리스 메뉴를 업데이트합니다.
	 *
	 * @param InDeltaTime - 델타 시간 값입니다. 단위는 초단위입니다.
	 */
	void Update(float InDeltaTime);


	/**
	 * 테트리스 메뉴를 콘솔 화면에 그립니다.
	 *
	 * @param InPosition - 테트리스 게임 영역의 왼쪽 상단 좌표입니다.
	 */
	void Draw(const Vec2i & InPosition);


	/**
	 * 테트리스 메뉴의 상태를 변경합니다.
	 * 
	 * @param InMenuState - 변경할 메뉴의 상태입니다.
	 */
	void SetMenuState(const EMenuState& InMenuState);


	/**
	 * 현재 테트리스 메뉴의 상태를 얻습니다.
	 * 
	 * @return 현재 테트리스 메뉴의 상태를 반환합니다.
	 */
	EMenuState GetMenuState() const { return CurrentMenuState_; }


	/**
	 * 현재 테트리스 메뉴를 얻습니다.
	 * 
	 * @return 현재 선택된 메뉴의 참조자를 반환합니다.
	 */
	const Menu& GetCurrentMenu() const;


	/**
	 * 현재 선택된 테트리스 게임 레벨을 얻습니다.
	 */
	int32_t GetSelectLevel() const { return SelectLevel_; }


	/**
	 * 테트리스 게임 종료가 선택되었는지 확인합니다.
	 * 
	 * @return 테트리스 게임 종료가 선택되었다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsSelectQuitGame() const { return bIsSelectQuitGame_; }


	/**
	 * 테트리스 게임의 메뉴가 바뀌었는지 확인합니다.
	 * 
	 * @return 테트리스 게임의 메뉴가 바뀌었다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsSwitchMenu() const { return bIsSwitchMenu_; }


private:
	/**
	 * 시작 메뉴를 업데이트합니다.
	 */
	void UpdateStartMenu();


	/**
	 * 선택 메뉴를 업데이트합니다.
	 */
	void UpdateSelectMenu();


	/**
	 * 중지 메뉴를 업데이트합니다.
	 */
	void UpdatePausedMenu();


	/**
	 * 종료 메뉴를 업데이트합니다.
	 */
	void UpdateDoneMenu();


private:
	/**
	 * 테트리스 타이틀 화면을 그립니다.
	 *
	 * @param InPosition - 콘솔 화면 상의 타이틀 왼쪽 상단 좌표입니다.
	 * @param InColor - 타이틀 화면의 색상입니다.
	 */
	void DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


private:
	/**
	 * 현재의 테트리스 게임 메뉴의 상태입니다.
	 */
	EMenuState CurrentMenuState_ = EMenuState::Start;


	/**
	 * 테트리스 게임 메뉴입니다.
	 */
	std::unordered_map<EMenuState, std::unique_ptr<Menu>> Menus_;


	/**
	 * 테트리스 게임을 종료하는지 확인합니다.
	 */
	bool bIsSelectQuitGame_ = false;


	/**
	 * 테트리스 게임 메뉴가 변경되었는지 확인합니다.
	 */
	bool bIsSwitchMenu_ = false;


	/**
	 * 현재 선택된 테트리스 게임 레벨입니다.
	 * 레벨의 범위는 1 <= Level <= 6 입니다.
	 */
	int32_t SelectLevel_ = 1;
};
