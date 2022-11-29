#include "ConsoleManager.h"

#include <locale.h>
#include <ncurses.h>

ConsoleManager ConsoleManager::ConsoleManager_;

ConsoleManager::ConsoleManager()
{
    setlocale(LC_ALL, "");
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
}

ConsoleManager::~ConsoleManager()
{
    endwin();
}

void ConsoleManager::SetCursorVisible(bool bIsVisible)
{
    int Mode = bIsVisible ? TRUE : FALSE;
    curs_set(Mode);
}

void ConsoleManager::MoveCursor(const int32_t& InPositionX, const int32_t& InPositionY)
{
    move(InPositionX, InPositionY);
}

void ConsoleManager::Refresh()
{
    refresh();
}

void ConsoleManager::Clear()
{
    clear();
}