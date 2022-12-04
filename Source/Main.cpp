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
        int32_t Command = getch();

        switch(Command)
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
