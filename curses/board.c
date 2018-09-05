#include <ncurses.h>
#include <stdbool.h>

void draw_board_border( WINDOW** board )
{
	wborder( *board, '|', '|', '-', '-', '+', '+', '+', '+' );
	int y, x, maxy, maxx;
	getyx( *board, y, x );
	getmaxyx( *board, maxy, maxx );

	for( x += 1; x < maxx - 4; x += 4 )
		mvwprintw( *board, maxy - 1, x, "| %c |", x / 4 + 'a' );

	for( y += 1; y < maxy - 2; y += 2 )
		mvwprintw( *board, y, 0, "%d", y / 2 );

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
	int color_ctr = 2;
	for( y = starty + 1; y < maxy - 1; y += 2, color_ctr++ ) {
		for( x = startx + x_offset + 2; x < maxx - 2; x += 8 ) {
			mvwchgat( *board, y, x, 4, A_REVERSE, 0, NULL );
			mvwchgat( *board, y + 1, x, 4, A_REVERSE, 0, NULL );
		}

		if( color_ctr == 2 ) {
			x_offset = 4;
			color_ctr = 0;
		} else
			x_offset = 0;
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

	height = 18;
	width = 36;
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
