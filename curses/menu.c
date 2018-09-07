#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( a[0] ) )
#define ARRAY_AGG_LEN( a, var )                                                \
	int var = 0;                                                               \
	for( int i__ = 0; i__ < ARRAY_SIZE( a ); ++i__ )                           \
		var += strlen( a[i__] );

char* choices[] = {"[I] Play", "[O] Load PGN", "[R] Singleplayer", "[Q]uit"};

void select_choice( MENU* menu, int key )
{
	menu_driver( menu, REQ_CLEAR_PATTERN );
	menu_driver( menu, '[' );
	menu_driver( menu, key );
	wrefresh( menu_win( menu ) );
}

int main()
{
	WINDOW* menu_win;
	MENU* menu;
	ITEM** items;

	// Initialize curses system
	initscr();
	cbreak();
	noecho();
	keypad( stdscr, TRUE );
	curs_set( 0 );

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
	menu_opts_off( menu, O_ONEVALUE );

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

	// TODO: fix menu item highlighting
	set_current_item( menu, items[n_choices - 1] );

	int ch_in = 0;
	while( 1 ) {
		ch_in = wgetch( menu_win );
		if( item_value( items[0] ) == FALSE || ch_in == 27 /* ESC */ ) {
			switch( ch_in ) {
			case 'q': /* Quit */
				goto CLEANUP;
			case 'i': /* Insert mode */
				// TODO: update menu icons here (to [ESC] Normal Mode)
				select_choice( menu, ch_in );
				menu_driver( menu, REQ_TOGGLE_ITEM );
				mvwprintw( stdscr, 40, 0, "Insert mode enabled (%c)", ch_in );
				break;
			case 'o': /* Load PGN file */
				// TODO: load pgn file
				select_choice( menu, ch_in );
				mvwprintw( stdscr, 40, 0, "Loading PGN file..." );
				break;
			case 'r': /* Cycle through game modes */
				// TODO: switch game mode (and update to "Multi Player")
				select_choice( menu, ch_in );
				mvwprintw( stdscr, 40, 0, "Changing game mode..." );
				break;
			case 27: /* ESC; Normal mode */
				set_current_item( menu, items[0] );
				menu_driver( menu, REQ_TOGGLE_ITEM );

				// TODO: fix menu item highlighting
				set_current_item( menu, items[n_choices - 1] );

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
