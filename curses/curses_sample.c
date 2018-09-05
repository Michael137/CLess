#include <ncurses.h>

int main()
{
	// clears screen; initializes curses mode i.e. allocates memory, data
	// structures, etc.
	initscr();

	// Print to window buffer akin to stdscr
	printw( "Starting curses test..." );

	// Dump contents of window buffer onto screen (stdscr)
	refresh();

	// Wait for user input
	getch();

	// Tear down window and leave curses mode
	endwin();

	return 0;
}
