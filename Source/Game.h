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
 * 테트리스 게임 클래스입니다.
 */
class Game
{
public:
	/**
	 * 테트리스 게임의 상태입니다.
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
	void Render();


private:
	/**
	 * 게임 종료 여부를 확인합니다.
	 */
	bool bIsDone = false;


	/**
	 * 현재 게임 상태입니다.
	 */
	GameState CurrentGameState = GameState::Play;


	/**
	 * 테트리스 게임 내에서 입력 처리를 수행합니다.
	 */
	Input GameInput;


	/**
	 * 테트리스 게임 내의 보드입니다.
	 */
	std::unique_ptr<Board> TetrisBoard = nullptr;


	/**
	 * 테트리스 게임 내의 테트로미노들입니다.
	 */
	std::list<std::unique_ptr<Tetromino>> Tetrominos;


	/**
	 * 현재 테트리스 보드 내에 배치된 테트로미노입니다.
	 */
	std::list<std::unique_ptr<Tetromino>>::iterator CurrentTetromino;


	/**
	 * 테트리스 게임의 타이머입니다.
	 */
	Timer GameTimer;


	/**
	 * 테트로미노의 시작점입니다.
	 */
	Math::Vec2i StartPosition;


	/**
	 * 테트로미노가 움직일 수 있는지를 확인합니다.
	 */
	bool bCanMove = false;


	/**
	 * 테트로미노의 움직임 방향입니다.
	 */
	Tetromino::EMovement Movement;


	/**
	 * 테트리스 게임의 최대 스텝 시간입니다.
	 */
	float MaxStepTime = 1.5f;


	/**
	 * 테트리스 게임의 현재 스텝 시간입니다.
	 */
	float CurrentStepTime = 0.0f;
};