parser grammar RookParser ;

options {
	tokenVocab = RookLexer;
}

/*
 * Parser rules
 */
game		:		NEWLINE* line+ EOF ;
line		:		((COMMENT+) | COMMENT* MOVE_NUM_LABEL (SCORE | move) (SCORE | move) NEWLINE*) ;
move		:		((((PIECE? (ALPH_IDX? CAPTURE )? CELL) | CASTLE_SHORT | CASTLE_LONG | PROMOTION) (CHECK|MATE)?) | WHITESPACE+ | COMMENT+ ) ;
