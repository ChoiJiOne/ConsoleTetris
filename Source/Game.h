#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Block.h"
#include "Board.h"
#include "Input.h"
#include "Console.h"
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
	 * ��Ʈ���� ������ �����Դϴ�.
	 */
	enum class GameState : int32_t
	{
		Start  = 0,
		Play   = 1,
		Paused = 2,
		Done   = 3
	};


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
	void Render();


private:
	/**
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsDone = false;


	/**
	 * ���� ���� �����Դϴ�.
	 */
	GameState CurrentGameState = GameState::Play;


	/**
	 * ��Ʈ���� ���� ������ �Է� ó���� �����մϴ�.
	 */
	Input GameInput;


	/**
	 * ��Ʈ���� ���� ���� �����Դϴ�.
	 */
	std::unique_ptr<Board> TetrisBoard = nullptr;


	/**
	 * ��Ʈ���� ���� ���� ��Ʈ�ι̳���Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>> Tetrominos;


	/**
	 * ���� ��Ʈ���� ���� ���� ��ġ�� ��Ʈ�ι̳��Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino;


	/**
	 * ��Ʈ���� ������ Ÿ�̸��Դϴ�.
	 */
	Timer GameTimer;


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 */
	Math::Vec2i StartPosition;


	/**
	 * ��Ʈ�ι̳밡 ������ �� �ִ����� Ȯ���մϴ�.
	 */
	bool bCanMove = false;


	/**
	 * ��Ʈ�ι̳��� ������ �����Դϴ�.
	 */
	Tetromino::EMovement Movement;


	/**
	 * ��Ʈ���� ������ �ִ� ���� �ð��Դϴ�.
	 */
	float MaxStepTime = 1.5f;


	/**
	 * ��Ʈ���� ������ ���� ���� �ð��Դϴ�.
	 */
	float CurrentStepTime = 0.0f;
};