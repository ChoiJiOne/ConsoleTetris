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
 * 테트리스 게임 클래스입니다.
 */
class Game
{
public:
	/**
	 * 테트리스 게임의 상태입니다.
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
	 * 테트리스 게임 클래스의 생성자입니다.
	 * 이때, 초기화를 수행하기 위해서는 Init 메서드를 호출해야 합니다.
	 */
	Game() = default;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	Game(Game&& InInstance) = delete;


	/**
	 * 복사 생성자를 명시적으로 삭제합니다.
	 */
	Game(const Game& InInstance) = delete;


	/**
	 * 테트리스 게임 클래스의 소멸자입니다.
	 */
	virtual ~Game();


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	Game& operator=(Game&& InInstance) = delete;


	/**
	 * 대입 연산자를 명시적으로 삭제합니다.
	 */
	Game& operator=(const Game& InInstance) = delete;


	/**
	 * 테트리스 게임을 초기화합니다.
	 * 
	 * @throws 테트리스 게임 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Init();


	/**
	 * 테트리스 게임을 실행합니다.
	 * 
	 * @throws 테트리스 게임 실행에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Run();


private:
	/**
	 * 테트리스 게임 내에 입력 처리를 수행합니다.
	 */
	void ProcessInput();


	/**
	 * 테트리스 게임의 로직을 업데이트합니다.
	 */
	void Update();


	/**
	 * 테트리스 게임을 화면에 그립니다.
	 */
	void Draw();


private:
	/**
	 * 테트리스 게임의 콘솔을 초기화합니다.
	 */
	void InitGameConsole();


	/**
	 * 테트리스 게임의 테트로미노를 초기화합니다.
	 */
	void InitGameTetromino();


	/**
	 * 테트리스 게임의 보드를 초기화합니다.
	 */
	void InitGameBoard();


	/**
	 * 테트리스 게임의 메뉴를 초기화합니다.
	 */
	void InitGameMenu();


	/**
	 * 테트리스 게임 플레이 상태의 입력을 처리합니다.
	 */
	void ProcessGamePlayInput();


 	/**
	 * 테트리스 게임 메뉴 상태의 입력을 처리합니다.
	 */
	void ProcessGameMenuInput() ;

	 
	/** 
	 * 테트리스 게임 플레이 상태를 업데이트합니다.
	 */
	void UpdateGamePlay();


	 /**
  	  * 테트리스 게임 메뉴 상태를 업데이트합니다.
	 */
 	void UpdateGameMenu() ;

	 
	/**
	 * 테트리스 게임을 리셋합니다. 
	 */
	void ResetGame();


	/**
	 * 테트리스 게임의 타이틀 화면을 그립니다.
	 * 
	 * @param InPositions - 콘솔 화면 상의 타이틀 왼쪽 상단 좌표입니다. 
	 * @param InColor - 타이틀 화면의 색상입니다.
	 */
	void DrawTitle(const Vec2i& InPosition, const Console::ETextColor& InColor);


private:
	/**
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone = false;


	/**
	 * 테트로미노가 움직일 수 있는지를 확인합니다.
	 */
	bool bCanMove = false;


	/**
	 * 테트로미노가 가장 아래칸으로 이동할 수 있는지 확인합니다.
	 */
	bool bCanMoveToBottom = false;


	/**
	 * 현재 게임 상태입니다.
	 */
	EGameState CurrentGameState = EGameState::Start;


	/**
	 * 테트리스 게임 내에서 입력 처리를 수행합니다.
	 */
	Input GameInput;


	/**
	 * 테트리스 게임 내의 보드입니다.
	 */
	std::unique_ptr<Board> GameBoard = nullptr;


	/**
	 * 테트리스 게임 내의 테트로미노들입니다.
	 */
	std::list<std::unique_ptr<Tetromino>> GameTetrominos;


	/**
	 * 현재 테트리스 보드 내에 배치된 테트로미노입니다.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino;


	/**
	 * 테트리스 게임의 메뉴입니다.
	 */
	std::unordered_map<EGameState, std::unique_ptr<Menu>> GameMenus;


	/**
	 * 테트리스 게임의 타이머입니다.
	 */
	Timer GameTimer;


	/**
	 * 테트로미노의 시작점입니다.
	 */
	Vec2i StartPosition;


	/**
	 * 테트로미노의 움직임 방향입니다.
	 */
	Tetromino::EMovement Movement = Tetromino::EMovement::None;


	/**
	 * 테트리스 게임의 최대 스텝 시간입니다.
	 */
	float MaxStepTime = 1.5f;


	/**
	 * 테트리스 게임의 현재 스텝 시간입니다.
	 */
	float CurrentStepTime = 0.0f;


	/**
	 * 현재 삭제한 라인 수입니다.
	 */
	int32_t CurrentRemoveLine = 0;
};