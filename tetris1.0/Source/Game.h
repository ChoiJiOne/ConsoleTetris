#pragma once

#include "Common.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void Setup();
	void Run();

private:
	bool bIsDoneGame = false;
	bool bIsDraw     = true;
};