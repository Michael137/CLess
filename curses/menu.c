#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( a[0] ) )
#define ARRAY_AGG_LEN( a, var )                                                \
	int var = 0;                                                               \
	for( int i__ = 0; i__ < ARRAY_SIZE( a ); ++i__ )                           \
		var += strlen( a[i__] );

char* choices[] = {"[I] Play", "[O] Load PGN", "[R] Singleplayer", "[Q]uit"};

enum SelectionModes
{
	NORMAL_MODE = 0,
	INSERT_MODE,

	NULL_MODE
};

static int mode;

int main()
{
	WINDOW* menu_win;
	MENU* menu;
	ITEM** items;

	mode = NORMAL_MODE;

	// Initialize curses system
	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );

	// Create window
	int n_choices = ARRAY_SIZE( choices );
	ARRAY_AGG_LEN( choices, choices_len );

	int const win_width = choices_len * 2;
	int const win_height = 3;

	menu_win = newwin( win_height, win_width, 0, 0 );
	keypad( menu_win, TRUE );
	box( menu_win, 0, 0 );
	refresh();

	// Create items
	items = (ITEM**)calloc( n_choices, sizeof( ITEM* ) );
	for( int i = 0; i < n_choices; ++i )
		items[i] = new_item( choices[i], NULL );

	// Create menu
	menu = new_menu( items );
	menu_opts_off( menu, O_SHOWDESC );

	// Set main window and sub window
	int const height_offset = 1;
	int const width_offset = 1;
	set_menu_win( menu, menu_win );
	set_menu_sub( menu, derwin( menu_win, win_height - height_offset,
								win_width - width_offset, height_offset,
								width_offset ) );
	set_menu_format( menu, 1, n_choices );
	set_menu_mark( menu, ">" );

	refresh();

	post_menu( menu );
	wrefresh( menu_win );

	int ch_in;
	while( 1 ) {
		ch_in = wgetch( menu_win );
		if( mode == NORMAL_MODE || ch_in == 27 ) {
			switch( ch_in ) {
			case 'q':
				mvwprintw( stdscr, 40, 0, "Exiting..." );
				refresh();
				wrefresh( menu_win );
				sleep( 1 /* seconds */ );
				goto CLEANUP;
			case 'i':
				mode = INSERT_MODE;
				// TODO: update menu icons here
				mvwprintw( stdscr, 40, 0, "Insert mode enabled (%c)", ch_in );
				break;
			case 'o':
				// TODO: load pgn file
				mvwprintw( stdscr, 40, 0, "Loading PGN file..." );
				break;
			case 'r':
				// TODO: switch game mode
				mvwprintw( stdscr, 40, 0, "Changing game mode..." );
				break;
			case 27: /* ESC */
				mode = NORMAL_MODE;
				mvwprintw( stdscr, 40, 0, "Normal mode enabled (%c)", ch_in );
				break;
			}
		} else {
			mvwprintw( stdscr, 50, 0, "Input: %c", ch_in );
		}
		refresh();
		wrefresh( menu_win );
	}

CLEANUP:
	unpost_menu( menu );
	free_menu( menu );
	for( int i = 0; i < n_choices; ++i )
		free_item( items[i] );
	endwin();
}
