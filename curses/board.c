#include "constants.h"
#include <ncurses.h>
#include <stdbool.h>

void draw_board_border( WINDOW** board )
{
	wborder( *board, '|', '|', '-', '-', '+', '+', '+', '+' );
	// int y, x, maxy, maxx;
	// getyx( *board, y, x );
	// getmaxyx( *board, maxy, maxx );

	// for( x += 1; x < maxx - 4; x += 4 )
	//	mvwprintw( *board, maxy - 1, x, "| %c |", x / 4 + 'a' );

	// for( y += 1; y < maxy - 2; y += 2 )
	//	mvwprintw( *board, y, 0, "%d", y / 2 );

	wrefresh( *board );
	wmove( *board, 0, 0 );
}

WINDOW* create_newwin( int height, int width, int starty, int startx )
{
	WINDOW* local_win;
	local_win = newwin( height, width, starty, startx );
	draw_board_border( &local_win );
	wrefresh( local_win );
	return local_win;
}

void fill_board( WINDOW** board )
{
	int starty, startx, maxy, maxx;
	getyx( *board, starty, startx );
	getmaxyx( *board, maxy, maxx );

	int x, y;
	int x_offset = 0;
	bool with_offset = false;
	for( y = starty; y < maxy; y += SQUARE_HEIGHT ) {
		for( x = startx + x_offset; x < maxx; x += SQUARE_WIDTH * 2 ) {
			for( int i = 0; i < SQUARE_HEIGHT; ++i )
				mvwchgat( *board, y + i, x, SQUARE_WIDTH, A_REVERSE, 0, NULL );
		}

		if( !with_offset ) {
			x_offset = SQUARE_WIDTH;
			with_offset = true;
		} else {
			x_offset = 0;
			with_offset = false;
		}
	}

	wrefresh( *board );
}

int main()
{
	WINDOW* board;
	int c_in;
	int startx, starty, width, height;

	initscr();
	cbreak();
	keypad( stdscr, TRUE );

	height = BOARD_HEIGHT;
	width = BOARD_WIDTH;
	starty = ( LINES - height ) / 2;
	startx = ( COLS - width ) / 2;
	refresh();
	board = create_newwin( height, width, starty, startx );
	fill_board( &board );

	getch();
	delwin( board );
	endwin();

	return 0;
}
