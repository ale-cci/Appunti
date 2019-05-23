#include <ncurses.h>
#include <unistd.h>

#define DELAY 3000000

int main(int argc, char *argv[]) {
    int max_x, max_y;

    initscr();
    noecho();
    curs_set(FALSE);

    while(1) {
        // Update screen here
        getmaxyx(stdscr, max_y, max_x);





        clear();
        mvprintw(0, 0, "Test");
        mvhline(1, 0, 0, max_x);
        refresh();

        usleep(DELAY);
    }

    endwin();
}
