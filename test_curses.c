#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
	char c_in = '\0', c_prev = '\0';
	int row = 0, col = 0, cur_col = 0, cur_row = 0, ctr = 0;

	initscr();
	noecho();
	keypad( stdscr, true );

	attron( A_BOLD );
	printw( "Starting curses test..." );
	attroff( A_BOLD );

	refresh();

	sleep( 1 /* seconds */ );

	clear();

	while( 1 ) {
		c_in = getch();
		getmaxyx( stdscr, row, col );
		getyx( stdscr, cur_row, cur_col );

		ctr = ( ctr == row ) ? 0 : ctr + 1;
		mvprintw( ctr, col - 10, "%d %d", row, col );
		wmove( stdscr, cur_row, cur_col );

		switch( c_in ) {
		case 'n':
			if( c_prev == 'n' ) printw( "\n" );
			break;
		case 'l':
			if( c_prev == 'l' ) {
				clear();
				wmove( stdscr, 0, 0 );
			}
			break;
		case 'q':
			if( c_prev == 'q' ) goto EXIT;
		case 'c':
			if( c_prev == 'c' )
			{
				start_color();
				init_pair( 137, COLOR_MAGENTA, COLOR_BLUE );
				mvchgat( cur_row, cur_col - 1, 2, A_BLINK, 137, NULL );
			}
		default:
			printw( "%c", c_in );
		}

		refresh();
		c_prev = c_in;
	}

EXIT:
	attron( A_REVERSE | A_BLINK );
	mvprintw( row - 1, 0, "Exiting..." );
	refresh();
	sleep( 2 /* seconds */ );
	endwin();

	return 0;
}
