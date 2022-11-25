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

void ConsoleManager::SetCursorVisible(bool bIsVisible)
{
    if(bIsVisible)
    {
        curs_set(1);
    }
    else 
    {
        curs_set(0);
    }
}