#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Tetris.h"
#include "Console.h"
#include "Menu.h"

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
	 * ������ �����Դϴ�.
	 */
	enum class EGameState : int32_t
	{
		Start  = 0,
		Play   = 1,
		Paused = 2,
		Done   = 3
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
	 * ��Ʈ���� ������ Ÿ��Ʋ ȭ���� �׸��ϴ�.
	 * 
	 * @param InPosition - �ܼ� ȭ�� ���� Ÿ��Ʋ ���� ��� ��ǥ�Դϴ�. 
	 * @param InColor - Ÿ��Ʋ ȭ���� �����Դϴ�.
	 */
	void DrawConsoleTetrisTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


private:
	/**
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsDone_ = false;


	/**
	 * ���� ���� �����Դϴ�.
	 */
	EGameState CurrentGameState_ = EGameState::Start;


	/**
	 * ���� ������ �Է� ó���� �����մϴ�.
	 */
	Input Input_;


	/**
	 * ������ �޴��Դϴ�.
	 */
	std::unordered_map<EGameState, std::unique_ptr<Menu>> Menus_;


	/**
	 * ������ Ÿ�̸��Դϴ�.
	 */
	Timer Timer_;


	/**
	 * ��Ʈ���� �����Դϴ�.
	 */
	Tetris Tetris_;
};