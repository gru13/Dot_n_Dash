#include <curses.h>

int main() {
    initscr();          // Start ncurses mode
    raw();              // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys
    noecho();           // Don't echo input

    printw("Box Drawing:\n");
    printw("\u2551\n"); // Unicode character for vertical line ║

    refresh();          // Print to the screen
    getch();            // Wait for user input
    endwin();           // End ncurses mode

    return 0;
}