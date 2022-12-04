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

        case KEY_LEFT:
            move(0, 0);
            printw("PRESS LEFT");
            break;

        case KEY_RIGHT:
            move(1, 0);
            printw("PRESS RIGHT");
            break;

        case KEY_UP:
            move(2, 0);
            printw("PRESS UP");
            break;

        case KEY_DOWN:
            move(3, 0);
            printw("PRESS DOWN");
            break;
        }

        refresh();
    }

    curs_set(1);
    nocbreak();
    endwin();

    return 0;
}
