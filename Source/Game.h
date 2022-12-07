#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Tetris.h"
#include "Menu.h"
#include "Console.h"

#include <stdexcept>
#include <memory>
#include <crtdbg.h>


/**
 * ���� Ŭ�����Դϴ�.
 */
class Game
{
public:
	/**
	 * ���� �����Դϴ�.
	 */
	enum class EGameState
	{
		Start  = 0,
		Select = 1,
		Play   = 2,
		Paused = 3,
		Done   = 4,
	};

public:
	/**
	 * ���� Ŭ������ �������Դϴ�.
	 * �̶�, �ʱ�ȭ�� �����ϱ� ���ؼ��� Init �޼��带 ȣ���ؾ� �մϴ�.
	 */
	Game() = default;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Game(Game&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Game(const Game& InInstance) = delete;


	/**
	 * ��Ʈ���� ���� Ŭ������ �Ҹ����Դϴ�.
	 */
	virtual ~Game();


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Game& operator=(Game&& InInstance) = delete;


	/**
	 * ���� �����ڸ� ��������� �����մϴ�.
	 */
	Game& operator=(const Game& InInstance) = delete;


	/**
	 * ��ü ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @throws ���� �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init();


	/**
	 * ������ �����մϴ�.
	 * 
	 * @throws ���� ���࿡ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Run();


private:
	/**
	 * ��Ʈ���� ���� ���� �Է� ó���� �����մϴ�.
	 */
	void ProcessInput();


	/**
	 * ��Ʈ���� ������ ������ ������Ʈ�մϴ�.
	 */
	void Update();


	/**
	 * ��Ʈ���� ������ ȭ�鿡 �׸��ϴ�.
	 */
	void Draw();


private:
	/**
	 * ��Ʈ���� �޴��� �ܼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param InPosition - ��Ʈ���� ���� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	void DrawMenu(const Vec2i& InPosition);


	/**
	 * ��Ʈ���� Ÿ��Ʋ ȭ���� �׸��ϴ�.
	 *
	 * @param InPosition - �ܼ� ȭ�� ���� Ÿ��Ʋ ���� ��� ��ǥ�Դϴ�.
	 * @param InColor - Ÿ��Ʋ ȭ���� �����Դϴ�.
	 */
	void DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


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
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsQuit_ = false;


	/**
	 * ���� ������ �Է� ó���� �����մϴ�.
	 */
	Input Input_;


	/**
	 * ������ Ÿ�̸��Դϴ�.
	 */
	Timer Timer_;


	/**
	 * ��Ʈ���� �����Դϴ�.
	 */
	Tetris Tetris_;


	/**
	 * ���� ���� �����Դϴ�.
	 */
	EGameState CurrentGameState_ = EGameState::Start;


	/**
	 * ��Ʈ���� ���� �޴��Դϴ�.
	 */
	std::unordered_map<EGameState, std::unique_ptr<Menu>> Menus_;


	/**
	 * ��Ʈ���� ���� �����Դϴ�.
	 */
	int32_t Level_ = 1;
};