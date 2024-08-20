#include <ncurses.h>

int main() {
    initscr();  // Start curses mode
    printw("Box Drawing:\n");

    mvaddch(1, 0, ACS_VLINE);      // Draw │
    mvaddch(1, 2, ACS_HLINE);      // Draw ─
    mvaddch(2, 0, ACS_ULCORNER);   // Draw ┌
    mvaddch(2, 2, ACS_URCORNER);   // Draw ┐
    mvaddch(3, 0, ACS_LLCORNER);   // Draw └
    mvaddch(3, 2, ACS_LRCORNER);   // Draw ┘

    refresh();  // Print it on the real screen
    getch();    // Wait for user input
    endwin();   // End curses mode
    return 0;
}
