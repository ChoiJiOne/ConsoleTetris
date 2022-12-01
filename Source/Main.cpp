#include <ncurses.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(0);
    curs_set(0);

    bool bIsDone = false;
    
    while(!bIsDone)
    {
        switch(getch())
        {
        case KEY_LEFT:
            bIsDone = true;
            break;

        case KEY_RIGHT:
            bIsDone = true;
            break;
        }
    }

    endwin();
    return 0;
}
