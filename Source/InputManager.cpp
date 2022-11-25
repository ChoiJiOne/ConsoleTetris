#include "InputManager.h"

#include <ncurses.h>

InputManager InputManager::InputManager_;

InputManager::InputManager()
{
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

InputManager::~InputManager()
{
}