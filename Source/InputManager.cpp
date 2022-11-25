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

bool InputManager::IsDetectPressKeyboard()
{
    bool bIsDetect = false;
    int32_t CurrentKey = getch();

    if (CurrentKey != ERR) 
    {
        bIsDetect = true;
        ungetch(CurrentKey);
    }

    return bIsDetect;
}