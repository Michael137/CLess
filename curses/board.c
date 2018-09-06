#include "constants.h"
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

void draw_board_border( WINDOW** board )
{
	wborder( *board, '|', '|', '-', '-', '+', '+', '+', '+' );
	int y, x, maxy, maxx;
	getyx( *board, y, x );
	getmaxyx( *board, maxy, maxx );

	// Label squares 'A'->'H' on the bottom side of the board
	for( char ch = 'A'; ch <= 'H'; x += SQUARE_WIDTH, ++ch )
		mvwprintw( *board, maxy - 1, x + ( SQUARE_WIDTH / 2 ) + 2, "%c", ch );

	// Number squares 8 -> 1 on the left side of the board
	for( int num = 8; num > 0; y += SQUARE_HEIGHT, --num )
		mvwprintw( *board, y + ( SQUARE_HEIGHT / 2 ) + 1, 0, "%d", num );

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
	for( y = starty + BOARD_BORDER_HEIGHT; y < maxy - BOARD_BORDER_HEIGHT;
		 y += SQUARE_HEIGHT ) {
		for( x = startx + x_offset + BOARD_BORDER_WIDTH;
			 x < maxx - BOARD_BORDER_WIDTH; x += SQUARE_WIDTH * 2 ) {
			for( int i = 0; i < SQUARE_HEIGHT; ++i ) {
				attron( COLOR_PAIR( W_SQUARE_COLOR ) );
				mvwchgat( *board, y + i, x, SQUARE_WIDTH, A_REVERSE, 0, NULL );
				attroff( COLOR_PAIR( W_SQUARE_COLOR ) );
			}
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
	setlocale( LC_ALL, "en_US.UTF8" );

	if( has_colors() == FALSE ) {
		endwin();
		printf( "Your terminal does not support color\n" );
		exit( 1 );
	}

	start_color();
	init_pair( W_SQUARE_COLOR, W_SQUARE_FG, W_SQUARE_BG );
	init_pair( B_SQUARE_COLOR, B_SQUARE_FG, B_SQUARE_BG );

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
