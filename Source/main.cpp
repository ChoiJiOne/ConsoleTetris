#include <locale.h>
#include <curses.h>
#include <iostream>

#include "ConsoleManager.h"

int main(int argc, char* argv[]) 
{
    ConsoleManager::Get().SetCursorVisible(true);

    ConsoleManager::Get().MoveCursor(3, 3);
	printw("Hello World!!");

    ConsoleManager::Get().MoveCursor(4, 3);
    printw("■■■■■■■■■■");

	refresh();
	getch();

    return 0;
}