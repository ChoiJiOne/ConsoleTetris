#include "InputManager.h"

#include <ncurses.h>

InputManager InputManager::InputManager_;

InputManager::InputManager()
{
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

InputManager::~InputManager()
{

}