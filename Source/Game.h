#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Tetris.h"
#include "TetrisMenu.h"
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
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsDone_ = false;


	/**
	 * ������ �÷��� �ϴ��� Ȯ���մϴ�.
	 */
	bool bIsPlayGame = false;


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
	 * ��Ʈ���� ������ �޴��Դϴ�.
	 */
	TetrisMenu TetrisMenu_;
};