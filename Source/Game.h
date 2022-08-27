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
 * 테트리스 게임 클래스입니다.
 */
class Game
{
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

};