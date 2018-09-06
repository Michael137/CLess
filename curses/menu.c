#include <ncurses.h>
#include <stdio.h>
#include <string.h>

char* choices[] = {
	"Move",
	"Load PGN",
	"Select Game Mode",
	"Exit",
};
int n_choices = sizeof( choices ) / sizeof( char* );

int total_choices_len()
{
	int len = 0;
	for( int i = 0; i < n_choices; ++i )
		len += strlen( choices[i] );

	return len;
}
int choices_len = 0;

void print_menu( WINDOW* menu, int highlight )
{
	int x, y, i;

	box( menu, 0, 0 );
	x = 1;
	y = 1;
	for( i = 0; i < n_choices; ++i ) {
		if( highlight == i + 1 ) {
			wattron( menu, A_REVERSE );
			mvwprintw( menu, y, x, "%s", choices[i] );
			wattroff( menu, A_REVERSE );
		} else
			mvwprintw( menu, y, x, "%s", choices[i] );

		x += strlen( choices[i] ) + 1;
	}
	wrefresh( menu );
}

int main()
{
	WINDOW* menu;
	int highlight = 1;
	bool menu_is_active = false;
	int c;
	int choice = 0;
	choices_len = total_choices_len();

	initscr();
	clear();
	noecho();
	cbreak(); /* Line buffering disabled. pass on everything */

	menu = newwin( 3, 3 * choices_len, 20, 20 );
	keypad( menu, TRUE );
	refresh();
	print_menu( menu, highlight );
	while( 1 ) {
		c = wgetch( menu );
		if( c == KEY_F( 1 ) ) {
			if( menu_is_active )
				menu_is_active = false;
			else
				menu_is_active = true;
			continue;
		}

		if( menu_is_active ) {
			switch( c ) {
			case 'h':
				if( highlight == 1 )
					highlight = n_choices;
				else
					--highlight;
				break;
			case 'l':
				if( highlight == n_choices )
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			}
			print_menu( menu, highlight );
			if( choice !=
				0 ) /* User did a choice come out of the infinite loop */
				break;
		}
	}
	clrtoeol();
	refresh();
	endwin();
	return 0;
}
