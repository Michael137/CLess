.PHONY:
build:
	antlr4 -Dlanguage=Cpp RookParser.g4 RookLexer.g4 -listener -visitor -o generated/ -package rook # Lexer/parser cpp files that can be included into project
	antlr4 RookLexer.g4 RookParser.g4 # To test with grun need to generate java target
	javac Rook*.java

.PHONY:
run:
	grun Rook game -tokens -gui < test.in

.PHONY:
clean:
	rm -f Rook*.cpp
	rm -f Rook*.h
	rm -f *.java
	rm -f *.class
	rm -f *.tokens
	rm -f *.interp
	rm -f *.out
	rm -f *.o
	rm -rf generated

all: clean build
