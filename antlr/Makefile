####################
#################### Targets below currently not working from non-interactive 
#################### shell due to alias expansion issues 
####################

.PHONY:
build_:
	# Lexer/parser cpp files that can be included into project
	antlr4 -Dlanguage=Cpp RookParser.g4 RookLexer.g4 -listener -visitor -o generated/
	# To test with grun on command line need to generate and java target
	antlr4 RookParser.g4 RookLexer.g4 -listener -visitor -o generated/
	javac generated/Rook*.java

.PHONY:
run_:
	cd generated && grun Rook game -tokens -gui ../test/test_basic.in

####################
####################
####################
####################

.PHONY:
compile:
	if [ ! -d build ]; then mkdir build; fi
	cd build && cmake .. && make -j4

.PHONY:
clean:
	rm -f *.out
	rm -f *.o
	rm -rf generated
	# Delete files generated through CMake
	# Keep external to prevent from redownloading
	find build/ -maxdepth 1 ! -name externals ! -name build -exec rm -r "{}" \;

all: clean compile
