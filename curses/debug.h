#ifndef DEBUG_H_IN
#define DEBUG_H_IN

#include <ncurses.h>
#include <stdio.h>

// Debug helpers
#define PRINT_PIECE( COL, PIECE ) printf( "%lc\n", COL##_##PIECE##_UCS );
#define PRINTW_PIECE( COL, PIECE ) printw( "%lc\n", COL##_##PIECE##_UCS );

static inline void printw_pieces()
{
	PRINTW_PIECE( B, PAWN );
	PRINTW_PIECE( B, ROOK );
	PRINTW_PIECE( B, KNIGHT );
	PRINTW_PIECE( B, BISHOP );
	PRINTW_PIECE( B, QUEEN );
	PRINTW_PIECE( B, KING );

	PRINTW_PIECE( W, PAWN );
	PRINTW_PIECE( W, ROOK );
	PRINTW_PIECE( W, KNIGHT );
	PRINTW_PIECE( W, BISHOP );
	PRINTW_PIECE( W, QUEEN );
	PRINTW_PIECE( W, KING );
}

static inline void print_pieces()
{
	PRINT_PIECE( B, PAWN );
	PRINT_PIECE( B, ROOK );
	PRINT_PIECE( B, KNIGHT );
	PRINT_PIECE( B, BISHOP );
	PRINT_PIECE( B, QUEEN );
	PRINT_PIECE( B, KING );

	PRINT_PIECE( W, PAWN );
	PRINT_PIECE( W, ROOK );
	PRINT_PIECE( W, KNIGHT );
	PRINT_PIECE( W, BISHOP );
	PRINT_PIECE( W, QUEEN );
	PRINT_PIECE( W, KING );
}

#endif // DEBUG_H_IN
