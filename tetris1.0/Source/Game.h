#pragma once

#include "Common.h"

struct Vector2i;

class InputSystem;
class Tetromino;
class Board;
class GameTimer;

class Game
{
public:
	Game();
	virtual ~Game();

	void Setup();
	void Run();

	void Update();
	void Draw();

private:
	void SetupGame();

	void UpdatePlay();
	void UpdateWait();

	void DrawPlay();
	void DrawWait();

	void AddTetrominoInBoard(Tetromino& tetromino, Board& board);
	void RemoveTetrominoInBoard(Tetromino& tetromino, Board& board);
	bool IsCrashTetrominoAndBoard(Tetromino& tetromino, Board& board);

	bool MoveDownTetrominoInBoard(Tetromino& tetromino, Board& board);
	void MoveLeftTetrominoInBoard(Tetromino& tetromino, Board& board);
	void MoveRightTetrominoInBoard(Tetromino& tetromino, Board& board);
	void MoveBottomTetrominoInBoard(Tetromino& tetromino, Board& board);

	void SpinClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board);
	void SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board);

	void DrawTetrisBoard(const Vector2i& consolePos, Board& board);
	void DrawRemainTime(const Vector2i& consolePos, int32_t remainTime);
	void DrawGameLevel(const Vector2i& consolePos, int32_t level);
	void DrawPushKeyArrow(const Vector2i& consolePos);
	void DrawCountDown(const Vector2i& consolePos, int32_t waitTime);

private:
	std::shared_ptr<InputSystem> inputSystem = nullptr;
	std::shared_ptr<GameTimer>   globalTimer = nullptr;

	std::unordered_map<std::string, Vector2i> uiPositionCache;

	bool bIsDoneGame  = false;
	bool bIsWaitNextLevel = true;

	std::shared_ptr<Board>     tetrisBoard   = nullptr;
	std::shared_ptr<Tetromino> currTetromino = nullptr;
	std::shared_ptr<Tetromino> nextTetromino = nullptr;

	int32_t userLevel  = 0;
	float userPlayTime = 0.0f;
	float userStepTime = 0.0f;
	float waitTime     = 0.0f;

	const float gamePlayTime = 100.0f;
	const float gameWaitTime = 3.0f;
};