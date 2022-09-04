#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Block.h"
#include "Board.h"
#include "Input.h"
#include "Console.h"
#include "Menu.h"
#include "Tetromino.h"
#include "Timer.h"
#include "Vector.h"

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
	enum class EGameState : int32_t
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
	void Draw();


private:
	/**
	 * ��Ʈ���� ������ �ܼ��� �ʱ�ȭ�մϴ�.
	 */
	void InitGameConsole();


	/**
	 * ��Ʈ���� ������ ��Ʈ�ι̳븦 �ʱ�ȭ�մϴ�.
	 */
	void InitGameTetromino();


	/**
	 * ��Ʈ���� ������ ���带 �ʱ�ȭ�մϴ�.
	 */
	void InitGameBoard();


	/**
	 * ��Ʈ���� ������ �޴��� �ʱ�ȭ�մϴ�.
	 */
	void InitGameMenu();


	/**
	 * ��Ʈ���� ���� �÷��� ������ �Է��� ó���մϴ�.
	 */
	void ProcessGamePlayInput();


 	/**
	 * ��Ʈ���� ���� �޴� ������ �Է��� ó���մϴ�.
	 */
	void ProcessGameMenuInput() ;

	 
	/** 
	 * ��Ʈ���� ���� �÷��� ���¸� ������Ʈ�մϴ�.
	 */
	void UpdateGamePlay();


	 /**
  	  * ��Ʈ���� ���� �޴� ���¸� ������Ʈ�մϴ�.
	 */
 	void UpdateGameMenu() ;

	 
	/**
	 * ��Ʈ���� ������ �����մϴ�. 
	 */
	void ResetGame();


	/**
	 * ��Ʈ���� ������ Ÿ��Ʋ ȭ���� �׸��ϴ�.
	 * 
	 * @param InPositions - �ܼ� ȭ�� ���� Ÿ��Ʋ ���� ��� ��ǥ�Դϴ�. 
	 * @param InColor - Ÿ��Ʋ ȭ���� �����Դϴ�.
	 */
	void DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


private:
	/**
	 * ���� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsDone = false;


	/**
	 * ��Ʈ�ι̳밡 ������ �� �ִ����� Ȯ���մϴ�.
	 */
	bool bCanMove = false;


	/**
	 * ��Ʈ�ι̳밡 ���� �Ʒ�ĭ���� �̵��� �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMoveToBottom = false;


	/**
	 * ���� ���� �����Դϴ�.
	 */
	EGameState CurrentGameState = EGameState::Start;


	/**
	 * ��Ʈ���� ���� ������ �Է� ó���� �����մϴ�.
	 */
	Input GameInput;


	/**
	 * ��Ʈ���� ���� ���� �����Դϴ�.
	 */
	std::unique_ptr<Board> GameBoard = nullptr;


	/**
	 * ��Ʈ���� ���� ���� ��Ʈ�ι̳���Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>> GameTetrominos;


	/**
	 * ���� ��Ʈ���� ���� ���� ��ġ�� ��Ʈ�ι̳��Դϴ�.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino;


	/**
	 * ��Ʈ���� ������ �޴��Դϴ�.
	 */
	std::unordered_map<EGameState, std::unique_ptr<Menu>> GameMenus;


	/**
	 * ��Ʈ���� ������ Ÿ�̸��Դϴ�.
	 */
	Timer GameTimer;


	/**
	 * ��Ʈ�ι̳��� �������Դϴ�.
	 */
	Vec2i StartPosition;


	/**
	 * ��Ʈ�ι̳��� ������ �����Դϴ�.
	 */
	Tetromino::EMovement Movement = Tetromino::EMovement::None;


	/**
	 * ��Ʈ���� ������ �ִ� ���� �ð��Դϴ�.
	 */
	float MaxStepTime = 1.5f;


	/**
	 * ��Ʈ���� ������ ���� ���� �ð��Դϴ�.
	 */
	float CurrentStepTime = 0.0f;


	/**
	 * ���� ������ ���� ���Դϴ�.
	 */
	int32_t CurrentRemoveLine = 0;
};