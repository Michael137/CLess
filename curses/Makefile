.PHONY:
clean:
	rm -f a.out
	rm -f sample.out
	rm -f board.out
	rm -f menu.out
	rm -f tags

.PHONY:
build_sample:
	gcc sample.c -lncurses -o sample.out

.PHONY:
build_board:
	gcc board.c -lncurses -o board.out

.PHONY:
build_menu:
	gcc menu.c -lncurses -o menu.out

.PHONY:
tags:
	ctags *

all: clean tags build_sample build_board build_menu
