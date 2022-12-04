#include <ncurses.h>
#include <stdbool.h>
#include <locale.h>

#include "Timer.h"

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

    Timer timer;
    timer.Reset();

    while(!bIsDone)
    {
        timer.Tick();

        int32_t Command = getch();

        float delta = timer.GetDeltaSeconds();

        move(0, 0);
        printw("(%d, %d) TOTAL : %3d, DELTA : %10f", 
        x, y, static_cast<int32_t>(timer.GetTotalSeconds()), delta);

        move(y, x);
        printw("  ");

        x += static_cast<int32_t>(timer.GetDeltaMilliseconds() / 800.0f);

        move(y, x);
        printw("■");


        switch(Command)
        {
        case 'Q':
        case 'q':
            bIsDone = true;
            break;
        }

        refresh();
    }

    curs_set(1);
    nocbreak();
    endwin();

    return 0;
}
