#include <locale.h>
#include <curses.h>
#include <iostream>

#include "ConsoleManager.h"
#include "InputManager.h"

int main(int argc, char* argv[]) 
{
    ConsoleManager::Get().SetCursorVisible(false);

    ConsoleManager::Get().MoveCursor(3, 3);
	printw("Hello World!!");

    ConsoleManager::Get().MoveCursor(4, 3);
    printw("■■■■■■■■■■");

    while (1) {
        if (InputManager::Get().IsDetectPressKeyboard()) {
            printw("Key pressed! It was: %d\n", getch());
        }

        ConsoleManager::Get().Refresh();
    }

    return 0;
}