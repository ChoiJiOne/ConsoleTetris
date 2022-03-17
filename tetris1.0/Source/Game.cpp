#include "ConsoleUtil.h"
#include "StringUtil.h"

#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Setup()
{
	ConsoleUtil::SetConsoleTitle("tetris1.0");
	ConsoleUtil::SetConsoleCursorVisible(false);
}

void Game::Run()
{
	while (!bIsDoneGame)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			bIsDoneGame = true;
		}
	}
}