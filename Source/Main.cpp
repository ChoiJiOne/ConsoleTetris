#include <ncurses.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);

    bool bIsDone = false;
    while(!bIsDone)
    {
        switch(getch())
        {
        case 'Q':
        case 'q':
            bIsDone = true;
            break;
        }
    }

    endwin();
    return 0;
}
