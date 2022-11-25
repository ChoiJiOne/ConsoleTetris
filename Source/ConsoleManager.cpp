#include "ConsoleManager.h"

#include <locale.h>
#include <ncurses.h>

ConsoleManager ConsoleManager::ConsoleManager_;

ConsoleManager::ConsoleManager()
{
    setlocale(LC_ALL, "");
    initscr();
}

ConsoleManager::~ConsoleManager()
{
    endwin();
}