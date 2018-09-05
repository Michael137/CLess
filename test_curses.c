#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
	char c_in;
	initscr();
	noecho();
	keypad( stdscr, true );

	attron( A_BOLD );
	printw( "Starting curses test..." );
	attroff( A_BOLD );

	refresh();

	sleep( 1 /* seconds */ );

	clear();

	while( ( c_in = getch() ) != 'q' ) {
		if( c_in == 'n' )
			printw( "\n" );
		else
			printw( "%c", c_in );

		refresh();
	}

	endwin();

	return 0;
}
