#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Block.h"
#include "Board.h"
#include "Console.h"
#include "Input.h"
#include "Tetromino.h"
#include "Timer.h"

#include <stdexcept>
#include <memory>
#include <crtdbg.h>


/**
 * ��Ʈ���� ���� Ŭ�����Դϴ�.
 */
class Game
{
public:
	/**
	 * ��Ʈ���� ���� Ŭ������ �������Դϴ�.
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
	 * ��Ʈ���� ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Init();


	/**
	 * ��Ʈ���� ������ �����մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� ���࿡ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void Run();


private:

};