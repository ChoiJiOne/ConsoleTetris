#pragma once

#define _CRTDBG_MAP_ALLOC

#include "Tetris.h"
#include "TetrisMenu.h"
#include "Console.h"

#include <stdexcept>
#include <memory>
#include <crtdbg.h>


/**
 * 게임 클래스입니다.
 */
class Game
{
public:
	/**
	 * 게임 클래스의 생성자입니다.
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
	 * 전체 게임을 초기화합니다.
	 * 
	 * @throws 게임 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Init();


	/**
	 * 게임을 실행합니다.
	 * 
	 * @throws 게임 실행에 실패하면 C++ 표준 예외를 던집니다.
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
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone_ = false;


	/**
	 * 게임을 플레이 하는지 확인합니다.
	 */
	bool bIsPlayGame = false;


	/**
	 * 게임 내에서 입력 처리를 수행합니다.
	 */
	Input Input_;


	/**
	 * 게임의 타이머입니다.
	 */
	Timer Timer_;


	/**
	 * 테트리스 게임입니다.
	 */
	Tetris Tetris_;


	/**
	 * 테트리스 게임의 메뉴입니다.
	 */
	TetrisMenu TetrisMenu_;
};