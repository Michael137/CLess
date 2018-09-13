parser grammar RookParser ;

options {
	tokenVocab = RookLexer;
}

/*
 * Parser rules
 */

/* NOTE: changing below line to
			line+ EOF ;
		 introduces a bug when running the C++ parser. Not using grun.
		 Possibly related to a known ANTLR bug
		 (see https://stackoverflow.com/questions/19172841/antlr-mismatched-input-eof)
*/
game		:	line* EOF ;

line		:	  MOVE_NUM_LABEL (SCORE | moves+=move) (SCORE | moves+=move) COMMENT*
				| COMMENT+
				| NEWLINE
			 	;

move		:	(
					(
						(
							  PIECE? (ALPH_IDX? CAPTURE )? CELL
							| CASTLE_SHORT
							| CASTLE_LONG
							| PROMOTION
						) (CHECK|MATE)?
					)
					| WHITESPACE+
				)
				;
