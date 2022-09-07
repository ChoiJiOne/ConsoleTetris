#pragma once

#include "Menu.h"

#include <unordered_map>
#include <memory>


/**
 * ��Ʈ���� �޴� ����Ʈ Ŭ�����Դϴ�.
 */
class TetrisMenu
{
public:
	/**
	 * ��Ʈ���� �޴� �����Դϴ�.
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
	 * ��Ʈ���� �޴� ����Ʈ Ŭ������ �������Դϴ�.
	 * �̶�, �ʱ�ȭ�� �����ϱ� ���ؼ��� Init �޼��带 ȣ���ؾ� �մϴ�.
	 */
	explicit TetrisMenu() = default;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	TetrisMenu(TetrisMenu&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	TetrisMenu(const TetrisMenu& InInstance) = delete;


	/**
	 * ��Ʈ���� ���� Ŭ������ �Ҹ����Դϴ�.
	 */
	virtual ~TetrisMenu();


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	TetrisMenu& operator=(TetrisMenu&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	TetrisMenu& operator=(const TetrisMenu& InInstance) = delete;


	/**
	 * ��Ʈ���� �޴��� �ʱ�ȭ�մϴ�.
	 *
	 * @throws �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init();


	/**
	 * ��Ʈ���� �޴��� �Է��� ó���մϴ�.
	 *
	 * @param InInput - Ű ���¸� �����ϴ� �Է� �ý����Դϴ�.
	 */
	void ProcessInput(const Input & InInput);


	/**
	 * ��Ʈ���� �޴��� ������Ʈ�մϴ�.
	 *
	 * @param InDeltaTime - ��Ÿ �ð� ���Դϴ�. ������ �ʴ����Դϴ�.
	 */
	void Update(float InDeltaTime);


	/**
	 * ��Ʈ���� �޴��� �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - ��Ʈ���� ���� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	void Draw(const Vec2i & InPosition);


	/**
	 * ��Ʈ���� �޴��� ���¸� �����մϴ�.
	 * 
	 * @param InMenuState - ������ �޴��� �����Դϴ�.
	 */
	void SetMenuState(const EMenuState& InMenuState);


	/**
	 * ���� ��Ʈ���� �޴��� ���¸� ����ϴ�.
	 * 
	 * @return ���� ��Ʈ���� �޴��� ���¸� ��ȯ�մϴ�.
	 */
	EMenuState GetMenuState() const { return CurrentMenuState_; }


	/**
	 * ���� ��Ʈ���� �޴��� ����ϴ�.
	 * 
	 * @return ���� ���õ� �޴��� �����ڸ� ��ȯ�մϴ�.
	 */
	const Menu& GetCurrentMenu() const;


	/**
	 * ���� ���õ� ��Ʈ���� ���� ������ ����ϴ�.
	 */
	int32_t GetSelectLevel() const { return SelectLevel_; }


	/**
	 * ��Ʈ���� ���� ���ᰡ ���õǾ����� Ȯ���մϴ�.
	 * 
	 * @return ��Ʈ���� ���� ���ᰡ ���õǾ��ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsSelectQuitGame() const { return bIsSelectQuitGame_; }


	/**
	 * ��Ʈ���� ������ �޴��� �ٲ������ Ȯ���մϴ�.
	 * 
	 * @return ��Ʈ���� ������ �޴��� �ٲ���ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsSwitchMenu() const { return bIsSwitchMenu_; }


private:
	/**
	 * ���� �޴��� ������Ʈ�մϴ�.
	 */
	void UpdateStartMenu();


	/**
	 * ���� �޴��� ������Ʈ�մϴ�.
	 */
	void UpdateSelectMenu();


	/**
	 * ���� �޴��� ������Ʈ�մϴ�.
	 */
	void UpdatePausedMenu();


	/**
	 * ���� �޴��� ������Ʈ�մϴ�.
	 */
	void UpdateDoneMenu();


private:
	/**
	 * ��Ʈ���� Ÿ��Ʋ ȭ���� �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ȭ�� ���� Ÿ��Ʋ ���� ��� ��ǥ�Դϴ�.
	 * @param InColor - Ÿ��Ʋ ȭ���� �����Դϴ�.
	 */
	void DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


private:
	/**
	 * ������ ��Ʈ���� ���� �޴��� �����Դϴ�.
	 */
	EMenuState CurrentMenuState_ = EMenuState::Start;


	/**
	 * ��Ʈ���� ���� �޴��Դϴ�.
	 */
	std::unordered_map<EMenuState, std::unique_ptr<Menu>> Menus_;


	/**
	 * ��Ʈ���� ������ �����ϴ��� Ȯ���մϴ�.
	 */
	bool bIsSelectQuitGame_ = false;


	/**
	 * ��Ʈ���� ���� �޴��� ����Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsSwitchMenu_ = false;


	/**
	 * ���� ���õ� ��Ʈ���� ���� �����Դϴ�.
	 * ������ ������ 1 <= Level <= 6 �Դϴ�.
	 */
	int32_t SelectLevel_ = 1;
};
