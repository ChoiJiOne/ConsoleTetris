#include <locale.h>
#include <curses.h>
#include <iostream>

#include "ConsoleManager.h"

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) 
{
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    ConsoleManager::Get().SetCursorVisible(false);

    ConsoleManager::Get().MoveCursor(3, 3);
	printw("Hello World!!");

    ConsoleManager::Get().MoveCursor(4, 3);
    printw("■■■■■■■■■■");

    while (1) {
        if (kbhit()) {
            printw("Key pressed! It was: %d\n", getch());
        }

        ConsoleManager::Get().Refresh();
    }

    return 0;
}