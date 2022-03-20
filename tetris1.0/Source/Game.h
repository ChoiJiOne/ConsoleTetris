#pragma once

#include "Common.h"

struct Vector2i;

class Tetromino;
class Board;

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
	void AddTetrominoInBoard(Tetromino& tetromino, Board& board);
	void RemoveTetrominoInBoard(Tetromino& tetromino, Board& board);
	bool IsCrashTetrominoAndBoard(Tetromino& tetromino, Board& board);

	bool MoveDownTetrominoInBoard(Tetromino& tetromino, Board& board);
	bool MoveLeftTetrominoInBoard(Tetromino& tetromino, Board& board);
	bool MoveRightTetrominoInBoard(Tetromino& tetromino, Board& board);

	bool SpinClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board);
	bool SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino, Board& board);

	void DrawTetrisBoard(const Vector2i& consolePos, Board& board);
	void DrawRemainTime(const Vector2i& consolePos, int32_t remainTime);
	void DrawGameLevel(const Vector2i& consolePos, int32_t level);
	void DrawPushKeyArrow(const Vector2i& consolePos);


private:
	bool bIsDoneGame = false;
	bool bIsDraw     = true;

	std::shared_ptr<Board>     tetrisBoard   = nullptr;
	std::shared_ptr<Tetromino> currTetromino = nullptr;
	std::shared_ptr<Tetromino> nextTetromino = nullptr;

	std::unordered_map<std::string, Vector2i> uiPositionCache;
};