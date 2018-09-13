lexer grammar RookLexer ;

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

CAPTURE		:		'x' ;
CHECK		:		'+' ;
MATE		:		'#' ;
