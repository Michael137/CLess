.PHONY:
build:
	antlr4 -Dlanguage=Cpp Rook.g # Lexer/parser cpp files that can be included into project
	antlr4 Rook.g # To test with grun need to generate java target
	javac Rook*.java

.PHONY:
run:
	grun Rook game -tokens -gui < test.in

.PHONY:
clean:
	rm -f *.cpp
	rm -f *.h
	rm -f *.java
	rm -f *.class
	rm -f *.tokens
	rm -f *.interp
	rm -f *.out
	rm -f *.o

all: clean build
