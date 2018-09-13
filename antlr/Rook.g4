grammar Rook ;

/*
 * Parser rules
 */
game		:		line+ EOF ;
line		:		COMMENT* MOVE_NUM_LABEL (SCORE | move) (SCORE | move) NEWLINE ;
move		:		((((PIECE? (ALPH_IDX? 'x' )? CELL) | CASTLE_SHORT | CASTLE_LONG | PROMOTION) ('+'|'#')?) | WHITESPACE+ | COMMENT+ ) ;

/*
 * Lexer rules
 */
fragment NUMBER	:	[0-9] ;

CASTLE_SHORT	:		'O-O' ;
CASTLE_LONG		:		'O-O-O' ;
PIECE			:		[KNBQR] ;
NUM_IDX			:		[1-8] ;
ALPH_IDX		:		[a-h] ;
CELL			:		ALPH_IDX NUM_IDX ;
PROMOTION		:		ALPH_IDX ('0'|'1') PIECE ;

MOVE_NUM_LABEL	:		NUMBER+ [.] ;
SCORE			:		NUMBER+ '-' NUMBER+ ;

NEWLINE		:		('\r'? '\n' | '\r')+ ;
WHITESPACE	:		' ' -> skip ;
COMMENT		:		'(' TEXT* ')' -> skip;
TEXT		:		~[()] ;
