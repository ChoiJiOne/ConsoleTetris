#include <curses.h>

#include "ConsoleManager.h"
#include "InputManager.h"

int main(int argc, char* argv[]) 
{
    ConsoleManager::Get().SetCursorVisible(false);

    bool bIsDone = false;
    while (!bIsDone) {
        InputManager::Get().Tick();

        if(InputManager::Get().GetKeyPressState(EKeyCode::ESC) == EPressState::PRESSED)
        {
            bIsDone = true;
        }

        if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED) 
        {
            ConsoleManager::Get().MoveCursor(1, 5);
            printw("[LEFT] : PRESSED");
        }
        else 
        {
            ConsoleManager::Get().MoveCursor(1, 5);
            printw("                ");
        }
        
        ConsoleManager::Get().Refresh();
    }

    return 0;
}