.PHONY:
build:
	# Lexer/parser cpp files that can be included into project
	antlr4 -Dlanguage=Cpp RookParser.g4 RookLexer.g4 -listener -visitor -o generated/ -package rook
	# To test with grun on command line need to generate and java target
	antlr4 RookLexer.g4 RookParser.g4 
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
	# Delete files generated through CMake
	rm -f Makefile
	rm -f CMakeCache.txt
	rm -rf cmakefiles

all: clean build
