#include <ncurses.h>
#include <stdbool.h>
#include <locale.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);

    bool bIsDone = false;
    int32_t x = 10, y = 10;

    while(!bIsDone)
    {
        int32_t Command = getch();

        move(0, 0);
        printw("(%d, %d)", x, y);

        switch(Command)
        {
        case 'Q':
        case 'q':
            bIsDone = true;
            break;

        case KEY_LEFT:
            move(y, x);
            printw("  ");

            --x;
            move(y, x);
            printw("■");
            break;

        case KEY_RIGHT:
            move(y, x);
            printw("  ");

            ++x;
            move(y, x);
            printw("■");
            break;

        case KEY_UP:
            move(y, x);
            printw("  ");

            --y;
            move(y, x);
            printw("■");
            break;


        case KEY_DOWN:
            move(y, x);
            printw("  ");

            ++y;
            move(y, x);
            printw("■");
            break;
        }

        refresh();
    }

    curs_set(1);
    nocbreak();
    endwin();

    return 0;
}
